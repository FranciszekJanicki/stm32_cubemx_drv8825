#include "as5600.h"
#include "config.h"
#include "drv8825.h"
#include "gpio.h"
#include "i2c.h"
#include "ina226.h"
#include "motor_driver.h"
#include "pid_regulator.h"
#include "step_motor.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int32_t current_step = 0;

// --- Set motor direction ---
static void StepMotor_SetDirection(bool forward)
{
    HAL_GPIO_WritePin(DRV8825_DIR_GPIO,
                      DRV8825_DIR_PIN,
                      forward ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// --- Enable/Disable motor driver ---
static void StepMotor_Enable(bool enable)
{
    HAL_GPIO_WritePin(DRV8825_EN_GPIO,
                      DRV8825_EN_PIN,
                      enable ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

// --- Convert target position (degrees) to step count ---
static int32_t StepMotor_PositionToStep(float target_position)
{
    return (int32_t)(target_position / STEP_CHANGE);
}

// --- Set PWM frequency for step pulse generation ---
static void StepMotor_SetFrequency(uint32_t frequency_hz)
{
    uint32_t clock_hz = HAL_RCC_GetPCLK1Freq();
    if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1) {
        clock_hz *= 2;
    }

    uint32_t period = clock_hz / frequency_hz;
    uint32_t prescaler = 0;
    while (period > 0xFFFF && prescaler < 0xFFFF) {
        prescaler++;
        period = clock_hz / ((prescaler + 1) * frequency_hz);
    }

    __HAL_TIM_DISABLE(DRV8825_PWM_TIMER);
    __HAL_TIM_SET_PRESCALER(DRV8825_PWM_TIMER, prescaler);
    __HAL_TIM_SET_AUTORELOAD(DRV8825_PWM_TIMER, period);
    __HAL_TIM_SET_COMPARE(DRV8825_PWM_TIMER, DRV8825_PWM_CHANNEL, period / 2);
    __HAL_TIM_ENABLE(DRV8825_PWM_TIMER);
}

// --- Move motor to target position in degrees ---
void StepMotor_MoveTo(float target_position)
{
    int32_t target_step = StepMotor_PositionToStep(target_position);
    bool forward = (target_step > current_step);
    StepMotor_SetDirection(forward);

    uint32_t step_diff =
        forward ? (target_step - current_step) : (current_step - target_step);
    if (step_diff == 0)
        return;

    // Set PWM frequency proportional to speed
    StepMotor_SetFrequency(MAX_SPEED);

    current_step = target_step;
}

// --- HAL callback for step pulse finished ---
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim)
{
    if (htim == DRV8825_PWM_TIMER) {
        // Increment or decrement step count each pulse
        current_step += (HAL_GPIO_ReadPin(DRV8825_DIR_GPIO, DRV8825_DIR_PIN) ==
                         GPIO_PIN_SET)
                            ? 1
                            : -1;
    }
}



void SystemClock_Config(void);
// --- Main example ---
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    SCB->CPACR |= (0xF << 20);

    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_USB_DEVICE_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_I2C1_Init();

    HAL_TIM_PWM_Start_IT(DRV8825_PWM_TIMER, DRV8825_PWM_CHANNEL);

    // Move motor to 90 degrees
    StepMotor_MoveTo(180.0f);

    // Wait indefinitely
    while (1) {
    }
}
