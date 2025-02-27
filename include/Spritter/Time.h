#pragma once
#include <cstdint>

namespace Spritter
{
    class Time
    {
        inline static double _deltaTime;
        inline static uint64_t _totalFrames;

    public:
        /// Get the amount of time, in seconds, that have passed since the last frame.
        static double DeltaTime()
        {
            return _deltaTime;
        }

        /// Get the total number of frames that have passed since the application started.
        static uint64_t TotalFrames()
        {
            return _totalFrames;
        }

        //static uint32_t FPS();

        /// Get the target FPS for the application.
        static uint32_t TargetFPS();

        /// Set the target FPS the application will try to achieve. A value of 0 will result in an unlocked (unlimited)
        /// frame rate. This value is ignored if VSync is enabled.
        /// @param fps The target FPS.
        static void SetTargetFPS(uint32_t fps);

        /// Intended for internal use only.
        static bool Update(bool ignoreFpsLimit);
    };
}
