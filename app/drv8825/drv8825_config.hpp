#ifndef DRV8825_CONFIG_HPP
#define DRV8825_CONFIG_HPP

#include "gpio.hpp"
#include "pwm_device.hpp"
#include "utility.hpp"

namespace DRV8825 {

    enum struct Microstep : std::uint8_t {
        FULL,
        HALF,
        QUARTER,
        EIGHTH,
        SIXTEENTH,
        THIRTYSECOND,
    };

    enum struct Decay : std::uint8_t {
        FAST,
        SLOW,
    };

    enum struct Direction : std::uint8_t {
        FORWARD,
        BACKWARD,
    };

    using PWMDevice = Utility::PWMDevice;
    using GPIO = Utility::GPIO;

    inline float microstep_to_fraction(Microstep const microstep) noexcept
    {
        switch (microstep) {
            case Microstep::FULL:
                return 1.0F;
            case Microstep::HALF:
                return 0.5F;
            case Microstep::QUARTER:
                return 0.25F;
            case Microstep::EIGHTH:
                return 0.125F;
            case Microstep::SIXTEENTH:
                return 0.0625F;
            case Microstep::THIRTYSECOND:
                return 0.03125F;
            default:
                return 0.0F;
        }
    }

}; // namespace DRV8825

#endif // DRV8825_CONFIG_HPP