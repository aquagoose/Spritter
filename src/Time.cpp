#include "Spritter/Time.h"

#include <SDL3/SDL.h>

namespace Spritter
{
    uint32_t _targetFps;
    double _targetDelta{};
    uint64_t _prevCount{};

    uint32_t Time::TargetFPS()
    {
        return _targetFps;
    }

    void Time::SetTargetFPS(const uint32_t fps)
    {
        _targetFps = fps;
        _targetDelta = fps == 0 ? 0.0 : 1.0 / static_cast<double>(fps);
    }

    bool Time::Update(bool ignoreFpsLimit)
    {
        auto ticks = SDL_GetTicksNS();
        auto diff = ticks - _prevCount;

        _deltaTime = SDL_NS_TO_SECONDS(static_cast<double>(diff));

        if (!ignoreFpsLimit && _deltaTime < _targetDelta)
            return true;

        _prevCount = ticks;
        _totalFrames++;

        return false;
    }

}
