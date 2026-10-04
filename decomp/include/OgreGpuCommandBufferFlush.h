#ifndef OGREGPUCOMMANDBUFFERFLUSH_H
#define OGREGPUCOMMANDBUFFERFLUSH_H

#include <OgrePrerequisites.h>
#include <OgreFrameListener.h>
#include <vector>

namespace Ogre
{
    // Helper from the OGRE samples: limits the number of frames the GPU
    // may queue by waiting on occlusion queries.
    class GpuCommandBufferFlush : public FrameListener
    {
    protected:
        bool mUseOcclusionQuery;
        typedef std::vector<HardwareOcclusionQuery*> HOQList;
        HOQList mHOQList;
        size_t mMaxQueuedFrames;
        size_t mCurrentFrame;
        bool mStartPull;
        bool mStarted;

    public:
        GpuCommandBufferFlush();
        virtual ~GpuCommandBufferFlush();

        void start(size_t maxQueuedFrames = 2);
        void stop();
        bool frameStarted(const FrameEvent& evt);
        bool frameEnded(const FrameEvent& evt);
    };
}

#endif
