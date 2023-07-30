#pragma once

namespace Ventgame {
    class TimeStep {
    public:
        explicit TimeStep(float time = 0.0f)
                : _time(time)
        {
        }

        explicit operator float() const { return _time; }

        [[nodiscard]] float GetSeconds() const { return _time; }
        [[nodiscard]] float GetMilliseconds() const { return _time * 1000.0f; }
    private:
        float _time {};
    };
}
