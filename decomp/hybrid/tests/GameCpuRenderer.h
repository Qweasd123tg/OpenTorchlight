#ifndef GAME_CPU_RENDERER_H
#define GAME_CPU_RENDERER_H
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <cstdlib>
namespace Ogre {
// Genuine SDK subclass: native RenderSystem C1/D1 owns every base container.
// Only config queries are used here; an unexpected rendering operation fails.
class GameCpuRenderer: public RenderSystem {
public:
 String name;ConfigOptionMap options;
 GameCpuRenderer():name("Game CPU comparison renderer"){
   ConfigOption&v=options["Rendering Device"];v.name="Rendering Device";v.currentValue="old";v.possibleValues.push_back("first");v.possibleValues.push_back("second");v.immutable=false;
 }
virtual const String& getName(void) const{ return name; }
virtual ConfigOptionMap& getConfigOptions(void){ return options; }
virtual void setConfigOption(const String &name, const String &value){ std::abort(); }
virtual HardwareOcclusionQuery* createHardwareOcclusionQuery(void){ std::abort(); }
virtual String validateConfigOptions(void){ std::abort(); }
virtual RenderSystemCapabilities* createRenderSystemCapabilities() const{ std::abort(); }
virtual void reinitialise(void){ std::abort(); }
virtual void setAmbientLight(float r, float g, float b){ std::abort(); }
virtual void setShadingType(ShadeOptions so){ std::abort(); }
virtual void setLightingEnabled(bool enabled){ std::abort(); }
virtual RenderWindow* _createRenderWindow(const String &name, unsigned int width, unsigned int height, bool fullScreen, const NameValuePairList *miscParams){ std::abort(); }
virtual MultiRenderTarget * createMultiRenderTarget(const String & name){ std::abort(); }
virtual String getErrorDescription(long errorNumber) const{ std::abort(); }
virtual void _useLights(const LightList& lights, unsigned short limit){ std::abort(); }
virtual void _setWorldMatrix(const Matrix4 &m){ std::abort(); }
virtual void _setViewMatrix(const Matrix4 &m){ std::abort(); }
virtual void _setProjectionMatrix(const Matrix4 &m){ std::abort(); }
virtual void _setSurfaceParams(const ColourValue &ambient, const ColourValue &diffuse, const ColourValue &specular, const ColourValue &emissive, Real shininess, TrackVertexColourType tracking){ std::abort(); }
virtual void _setPointSpritesEnabled(bool enabled){ std::abort(); }
virtual void _setPointParameters(Real size, bool attenuationEnabled, Real constant, Real linear, Real quadratic, Real minSize, Real maxSize){ std::abort(); }
virtual void _setTexture(size_t unit, bool enabled, const TexturePtr &texPtr){ std::abort(); }
virtual void _setTextureCoordSet(size_t unit, size_t index){ std::abort(); }
virtual void _setTextureCoordCalculation(size_t unit, TexCoordCalcMethod m, const Frustum* frustum){ std::abort(); }
virtual void _setTextureBlendMode(size_t unit, const LayerBlendModeEx& bm){ std::abort(); }
virtual void _setTextureUnitFiltering(size_t unit, FilterType ftype, FilterOptions filter){ std::abort(); }
virtual void _setTextureLayerAnisotropy(size_t unit, unsigned int maxAnisotropy){ std::abort(); }
virtual void _setTextureAddressingMode(size_t unit, const TextureUnitState::UVWAddressingMode& uvw){ std::abort(); }
virtual void _setTextureBorderColour(size_t unit, const ColourValue& colour){ std::abort(); }
virtual void _setTextureMipmapBias(size_t unit, float bias){ std::abort(); }
virtual void _setTextureMatrix(size_t unit, const Matrix4& xform){ std::abort(); }
virtual void _setSceneBlending(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor){ std::abort(); }
virtual void _setSeparateSceneBlending(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendFactor sourceFactorAlpha, SceneBlendFactor destFactorAlpha){ std::abort(); }
virtual void _setAlphaRejectSettings(CompareFunction func, unsigned char value, bool alphaToCoverage){ std::abort(); }
virtual void _beginFrame(void){ std::abort(); }
virtual void _endFrame(void){ std::abort(); }
virtual void _setViewport(Viewport *vp){ std::abort(); }
virtual void _setCullingMode(CullingMode mode){ std::abort(); }
virtual void _setDepthBufferParams(bool depthTest, bool depthWrite, CompareFunction depthFunction){ std::abort(); }
virtual void _setDepthBufferCheckEnabled(bool enabled){ std::abort(); }
virtual void _setDepthBufferWriteEnabled(bool enabled){ std::abort(); }
virtual void _setDepthBufferFunction(CompareFunction func){ std::abort(); }
virtual void _setColourBufferWriteEnabled(bool red, bool green, bool blue, bool alpha){ std::abort(); }
virtual void _setDepthBias(float constantBias, float slopeScaleBias){ std::abort(); }
virtual void _setFog(FogMode mode, const ColourValue& colour, Real expDensity, Real linearStart, Real linearEnd){ std::abort(); }
virtual VertexElementType getColourVertexElementType(void) const{ std::abort(); }
virtual void _convertProjectionMatrix(const Matrix4& matrix, Matrix4& dest, bool forGpuProgram){ std::abort(); }
virtual void _makeProjectionMatrix(const Radian& fovy, Real aspect, Real nearPlane, Real farPlane, Matrix4& dest, bool forGpuProgram){ std::abort(); }
virtual void _makeProjectionMatrix(Real left, Real right, Real bottom, Real top, Real nearPlane, Real farPlane, Matrix4& dest, bool forGpuProgram){ std::abort(); }
virtual void _makeOrthoMatrix(const Radian& fovy, Real aspect, Real nearPlane, Real farPlane, Matrix4& dest, bool forGpuProgram){ std::abort(); }
virtual void _applyObliqueDepthProjection(Matrix4& matrix, const Plane& plane, bool forGpuProgram){ std::abort(); }
virtual void _setPolygonMode(PolygonMode level){ std::abort(); }
virtual void setStencilCheckEnabled(bool enabled){ std::abort(); }
virtual void setStencilBufferParams(CompareFunction func, uint32 refValue, uint32 mask, StencilOperation stencilFailOp, StencilOperation depthFailOp, StencilOperation passOp, bool twoSidedOperation){ std::abort(); }
virtual void setVertexDeclaration(VertexDeclaration* decl){ std::abort(); }
virtual void setVertexBufferBinding(VertexBufferBinding* binding){ std::abort(); }
virtual void setNormaliseNormals(bool normalise){ std::abort(); }
virtual void bindGpuProgramParameters(GpuProgramType gptype, GpuProgramParametersSharedPtr params){ std::abort(); }
virtual void bindGpuProgramPassIterationParameters(GpuProgramType gptype){ std::abort(); }
virtual void setScissorTest(bool enabled, size_t left, size_t top, size_t right, size_t bottom){ std::abort(); }
virtual void clearFrameBuffer(unsigned int buffers, const ColourValue& colour, Real depth, unsigned short stencil){ std::abort(); }
virtual Real getHorizontalTexelOffset(void){ std::abort(); }
virtual Real getVerticalTexelOffset(void){ std::abort(); }
virtual Real getMinimumDepthInputValue(void){ std::abort(); }
virtual Real getMaximumDepthInputValue(void){ std::abort(); }
virtual void preExtraThreadsStarted(){ std::abort(); }
virtual void postExtraThreadsStarted(){ std::abort(); }
virtual void registerThread(){ std::abort(); }
virtual void unregisterThread(){ std::abort(); }
virtual void setClipPlanesImpl(const PlaneList& clipPlanes){ std::abort(); }
virtual void initialiseFromRenderSystemCapabilities(RenderSystemCapabilities* caps, RenderTarget* primary){ std::abort(); }
};
}
#endif
