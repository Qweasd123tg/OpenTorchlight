#ifndef TL_HEADLESS_GUI_H
#define TL_HEADLESS_GUI_H

#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <CEGUI.h>
#include <Ogre.h>
#include <OgreDefaultHardwareBufferManager.h>

// Test-only rendering adapter. Uses the shipped CEGUI and OGRE libraries and
// real resources, but never opens a window or validates rendered pixels.
namespace tlheadless
{
class ZipResources : public CEGUI::ResourceProvider {
public:
    virtual void loadRawDataContainer(const CEGUI::String& name, CEGUI::RawDataContainer& output, const CEGUI::String&) {
        Ogre::DataStreamPtr stream=Ogre::ResourceGroupManager::getSingleton().openResource(name.c_str(),"Headless");
        size_t size=stream->size();
        unsigned char* data=new unsigned char[size];
        if(stream->read(data,size)!=size) { delete[] data; throw CEGUI::FileIOException("short resource read"); }
        output.setData(data); output.setSize(size);
    }
    virtual void unloadRawDataContainer(CEGUI::RawDataContainer& data) {
        delete[] data.getDataPtr(); data.setData(0); data.setSize(0);
    }
};
class HeadlessTexture : public CEGUI::Texture {
    CEGUI::ushort width_, height_;
public:
    HeadlessTexture(CEGUI::Renderer* r, unsigned int size=1) : Texture(r), width_(size), height_(size) {}
    virtual ~HeadlessTexture() {}
    virtual CEGUI::ushort getWidth() const { return width_; }
    virtual CEGUI::ushort getHeight() const { return height_; }
    virtual void loadFromFile(const CEGUI::String& name, const CEGUI::String&) {
        Ogre::DataStreamPtr stream=Ogre::ResourceGroupManager::getSingleton().openResource(name.c_str(),"Headless");
        unsigned char header[20];
        size_t count=stream->read(header,sizeof(header));
        // OGRE's DDS decoder dereferences the active RenderSystem for DXT
        // capabilities. A null renderer needs only validated dimensions;
        // compressed pixel content is deliberately not decoded or compared.
        if(count==sizeof(header) && std::memcmp(header,"DDS ",4)==0) {
            unsigned int h=header[12]|(static_cast<unsigned int>(header[13])<<8)|(static_cast<unsigned int>(header[14])<<16)|(static_cast<unsigned int>(header[15])<<24);
            unsigned int w=header[16]|(static_cast<unsigned int>(header[17])<<8)|(static_cast<unsigned int>(header[18])<<16)|(static_cast<unsigned int>(header[19])<<24);
            if(stream->size()<128 || header[4]!=124 || header[5] || header[6] || header[7] || !w || !h || w>65535 || h>65535)
                throw CEGUI::FileIOException("invalid DDS dimensions");
            width_=w; height_=h;
        } else {
            Ogre::Image image; image.load(name.c_str(),"Headless");
            width_=image.getWidth(); height_=image.getHeight();
        }
    }
    virtual void loadFromMemory(const void*, CEGUI::uint w, CEGUI::uint h, PixelFormat) {
        if (!w || !h || w > 65535 || h > 65535)
            throw CEGUI::InvalidRequestException("invalid headless texture dimensions");
        width_=w; height_=h;
    }
};
class HeadlessRenderer : public CEGUI::Renderer {
    bool queued_;
    std::vector<HeadlessTexture*> textures_;
public:
    HeadlessRenderer() : queued_(false) {}
    virtual ~HeadlessRenderer() { destroyAllTextures(); }
    virtual void addQuad(const CEGUI::Rect&, float, const CEGUI::Texture*, const CEGUI::Rect&, const CEGUI::ColourRect&, CEGUI::QuadSplitMode) {}
    virtual void doRender() {}
    virtual void clearRenderList() {}
    virtual void setQueueingEnabled(bool x) { queued_=x; }
    virtual bool isQueueingEnabled() const { return queued_; }
    virtual CEGUI::Texture* createTexture() { return createTexture(1.0f); }
    virtual CEGUI::Texture* createTexture(const CEGUI::String& name,const CEGUI::String& group) {
        HeadlessTexture* texture=static_cast<HeadlessTexture*>(createTexture());
        try { texture->loadFromFile(name,group); } catch(...) { destroyTexture(texture); throw; }
        return texture;
    }
    virtual CEGUI::Texture* createTexture(float size) {
        if (!(size > 0 && size <= 4096))
            throw CEGUI::InvalidRequestException("invalid headless texture size");
        HeadlessTexture* t=new HeadlessTexture(this,(unsigned int)size); textures_.push_back(t); return t;
    }
    virtual void destroyTexture(CEGUI::Texture* t) {
        std::vector<HeadlessTexture*>::iterator i=std::find(textures_.begin(),textures_.end(),t);
        if(i!=textures_.end()) { delete *i; textures_.erase(i); }
    }
    virtual void destroyAllTextures() { while(!textures_.empty()) destroyTexture(textures_.back()); }
    virtual float getWidth() const { return 1024; }
    virtual float getHeight() const { return 768; }
    virtual CEGUI::Size getSize() const { return CEGUI::Size(1024,768); }
    virtual CEGUI::Rect getRect() const { return CEGUI::Rect(0,0,1024,768); }
    virtual CEGUI::uint getMaxTextureSize() const { return 4096; }
    virtual CEGUI::uint getHorzScreenDPI() const { return 96; }
    virtual CEGUI::uint getVertScreenDPI() const { return 96; }
};

class Environment
{
    Ogre::Root root_;
    Ogre::DefaultHardwareBufferManager buffers_;
    ZipResources resources_;
    HeadlessRenderer renderer_;
    CEGUI::System gui_;
public:
    Environment()
        : root_("", "", "/tmp/opentorchlight-headless-ogre.log"),
          gui_(&renderer_, &resources_, 0, 0, "", "/tmp/opentorchlight-headless-cegui.log")
    {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation("pak.zip", "Zip", "Headless");
    }
    Ogre::Root& root() { return root_; }
    void loadGameSkin() { CEGUI::SchemeManager::getSingleton().loadScheme("media/ui/GuiLookSkin.scheme"); }
private:
    Environment(const Environment&);
    Environment& operator=(const Environment&);
};

inline void appendString(std::ostream& out, const CEGUI::String& text)
{
    out << text.length() << ':';
    for (size_t i = 0; i < text.length(); ++i)
        out << static_cast<unsigned int>(text[i]) << ';';
}

// Tree and public property snapshot. Event names are included, but do not
// encode subscriber identity/count: callback effects need explicit probes.
inline void appendWindow(std::ostream& out, const CEGUI::Window& window)
{
    appendString(out, window.getName());
    appendString(out, window.getType());
    CEGUI::PropertySet::Iterator properties = window.getPropertyIterator();
    while (!properties.isAtEnd())
    {
        const CEGUI::String name = properties.getCurrentKey();
        appendString(out, name);
        appendString(out, window.getProperty(name));
        ++properties;
    }
    out << "|events|";
    CEGUI::EventSet::Iterator events = window.getEventIterator();
    while (!events.isAtEnd())
    {
        appendString(out, events.getCurrentKey());
        ++events;
    }
    out << "|children|" << window.getChildCount() << ':';
    for (size_t i = 0; i < window.getChildCount(); ++i)
        appendWindow(out, *window.getChildAtIdx(i));
}

inline std::string snapshot(const CEGUI::Window& window)
{
    std::ostringstream out;
    appendWindow(out, window);
    return out.str();
}
}
#endif
