#pragma once

#include <functional>
#include <vector>

namespace Spritter
{
    template <typename... Args>
    class Event
    {
    private:
        std::vector<std::function<void(Args...)>> _subscribers;

    public:
        void Subscribe(const std::function<void(Args...)>& func)
        {
            _subscribers.push_back(func);
        }

        void Invoke(Args... args)
        {
            for (const auto& subscriber : _subscribers)
                subscriber(args...);
        }
    };
}
