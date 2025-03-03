#include "drv8825.hpp"
#include "utility.hpp"

using namespace Utility;

namespace DRV8825 {

    float DRV8825::microstep_to_fraction(Microstep const microstep) noexcept
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

    DRV8825::DRV8825(PWMDevice&& pwm_device,
                     GPIO const pin_mode0,
                     GPIO const pin_mode1,
                     GPIO const pin_mode2,
                     GPIO const pin_reset,
                     GPIO const pin_sleep,
                     GPIO const pin_dir,
                     GPIO const pin_enable,
                     GPIO const pin_decay) noexcept :
        pwm_device_{std::forward<PWMDevice>(pwm_device)},
        pin_mode0_{pin_mode0},
        pin_mode1_{pin_mode1},
        pin_mode2_{pin_mode2},
        pin_reset_{pin_reset},
        pin_sleep_{pin_sleep},
        pin_dir_{pin_dir},
        pin_enable_{pin_enable},
        pin_decay_{pin_decay}
    {
        this->initialize();
    }

    DRV8825::~DRV8825() noexcept
    {
        this->deinitialize();
    }

    void DRV8825::set_frequency(std::uint32_t const frequency) noexcept
    {
        this->pwm_device_.set_frequency(frequency);
    }

    void DRV8825::set_microstep(Microstep const microstep) const noexcept
    {
        switch (microstep) {
            case Microstep::FULL:
                this->set_full_microstep();
                break;
            case Microstep::HALF:
                this->set_half_microstep();
                break;
            case Microstep::QUARTER:
                this->set_quarter_microstep();
                break;
            case Microstep::EIGHTH:
                this->set_eighth_microstep();
                break;
            case Microstep::SIXTEENTH:
                this->set_sixteenth_microstep();
                break;
            case Microstep::THIRTYSECOND:
                this->set_thirtysecond_microstep();
                break;
            default:
                break;
        }
    }

    void DRV8825::set_full_microstep() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_mode0_, GPIO_PIN_RESET);
            gpio_write_pin(this->pin_mode1_, GPIO_PIN_RESET);
            gpio_write_pin(this->pin_mode2_, GPIO_PIN_RESET);
        }
    }

    void DRV8825::set_half_microstep() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_mode0_, GPIO_PIN_SET);
            gpio_write_pin(this->pin_mode1_, GPIO_PIN_RESET);
            gpio_write_pin(this->pin_mode2_, GPIO_PIN_RESET);
        }
    }

    void DRV8825::set_quarter_microstep() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_mode0_, GPIO_PIN_RESET);
            gpio_write_pin(this->pin_mode1_, GPIO_PIN_SET);
            gpio_write_pin(this->pin_mode2_, GPIO_PIN_RESET);
        }
    }

    void DRV8825::set_eighth_microstep() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_mode0_, GPIO_PIN_SET);
            gpio_write_pin(this->pin_mode1_, GPIO_PIN_SET);
            gpio_write_pin(this->pin_mode2_, GPIO_PIN_RESET);
        }
    }

    void DRV8825::set_sixteenth_microstep() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_mode0_, GPIO_PIN_RESET);
            gpio_write_pin(this->pin_mode1_, GPIO_PIN_RESET);
            gpio_write_pin(this->pin_mode2_, GPIO_PIN_SET);
        }
    }

    void DRV8825::set_thirtysecond_microstep() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_mode0_, GPIO_PIN_SET);
            gpio_write_pin(this->pin_mode1_, GPIO_PIN_SET);
            gpio_write_pin(this->pin_mode2_, GPIO_PIN_SET);
        }
    }

    void DRV8825::set_direction(Direction const direction) const noexcept
    {
        switch (direction) {
            case Direction::FORWARD:
                this->set_forward_direction();
                break;
            case Direction::BACKWARD:
                this->set_backward_direction();
                break;
            default:
                break;
        }
    }

    void DRV8825::set_forward_direction() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_dir_, GPIO_PIN_RESET);
        }
    }

    void DRV8825::set_backward_direction() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_dir_, GPIO_PIN_SET);
        }
    }

    void DRV8825::set_decay(Decay const decay) const noexcept
    {
        switch (decay) {
            case Decay::FAST:
                this->set_fast_decay();
                break;
            case Decay::SLOW:
                this->set_slow_decay();
                break;
            default:
                break;
        }
    }

    void DRV8825::set_fast_decay() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_decay_, GPIO_PIN_SET);
        }
    }

    void DRV8825::set_slow_decay() const noexcept
    {
        if (this->initialized_) {
            gpio_write_pin(this->pin_decay_, GPIO_PIN_RESET);
        }
    }

    void DRV8825::set_reset(bool const reset) const noexcept
    {
        gpio_write_pin(this->pin_reset_, reset ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }

    void DRV8825::set_enable(bool const enable) const noexcept
    {
        gpio_write_pin(this->pin_enable_, enable ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }

    void DRV8825::set_sleep(bool const sleep) const noexcept
    {
        gpio_write_pin(this->pin_sleep_, sleep ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }

    void DRV8825::set_step(bool const step) const noexcept
    {
        if (this->initialized_) {
            this->pwm_device_.set_compare_raw(step ? 10U : 0U);
        }
    }

    void DRV8825::initialize() noexcept
    {
        this->set_reset(false);
        this->set_enable(true);
        this->set_sleep(false);
        this->set_step(false);
        this->initialized_ = true;
    }

    void DRV8825::deinitialize() noexcept
    {
        this->set_reset(true);
        this->set_enable(false);
        this->set_sleep(true);
        this->set_step(false);
        this->initialized_ = false;
    }

}; // namespace DRV8825