#ifndef DRV8825_HPP
#define DRV8825_HPP

#include "drv8825_config.hpp"
#include <cstdint>

namespace DRV8825 {

    struct DRV8825 {
    public:
        DRV8825() noexcept = default;
        DRV8825(PWMDevice&& pwm_device,
                GPIO const pin_mode0,
                GPIO const pin_mode1,
                GPIO const pin_mode2,
                GPIO const pin_reset,
                GPIO const pin_sleep,
                GPIO const pin_dir,
                GPIO const pin_enable,
                GPIO const pin_decay) noexcept;

        DRV8825(DRV8825 const& other) = delete;
        DRV8825(DRV8825&& other) noexcept = default;

        DRV8825& operator=(DRV8825 const& other) = delete;
        DRV8825& operator=(DRV8825&& other) noexcept = default;

        ~DRV8825() noexcept;

        void set_frequency(std::uint32_t const frequency) noexcept;

        void set_microstep(Microstep const microstep) const noexcept;
        void set_full_microstep() const noexcept;
        void set_half_microstep() const noexcept;
        void set_quarter_microstep() const noexcept;
        void set_eighth_microstep() const noexcept;
        void set_sixteenth_microstep() const noexcept;
        void set_thirtysecond_microstep() const noexcept;

        void set_direction(Direction const direction) const noexcept;
        void set_forward_direction() const noexcept;
        void set_backward_direction() const noexcept;

        void set_decay(Decay const decay) const noexcept;
        void set_fast_decay() const noexcept;
        void set_slow_decay() const noexcept;

        void set_reset(bool const reset = true) const noexcept;
        void set_enable(bool const enable = true) const noexcept;
        void set_sleep(bool const sleep = true) const noexcept;
        void set_step(bool const step = true) const noexcept;

    private:
        void initialize() noexcept;
        void deinitialize() noexcept;

        PWMDevice pwm_device_{};

        GPIO pin_mode0_{};
        GPIO pin_mode1_{};
        GPIO pin_mode2_{};
        GPIO pin_reset_{};
        GPIO pin_sleep_{};
        GPIO pin_dir_{};
        GPIO pin_enable_{};
        GPIO pin_decay_{};

        bool initialized_{false};
    };

}; // namespace DRV8825

#endif // DRV8825_HPP