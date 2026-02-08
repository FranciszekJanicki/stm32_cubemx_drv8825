#ifndef MAIN_CONFIG_H
#define MAIN_CONFIG_H

#include "drv8825_config.h"

#define PROP_GAIN (1.0F)
#define INT_GAIN (0.0F)
#define DOT_GAIN (0.0F)
#define SAT_GAIN (0.0F)
#define DOT_TIME (0.0F)
#define MIN_POSITION (0.0F)
#define MAX_POSITION (359.0F)
#define MIN_SPEED (0.5F)
#define MAX_SPEED (1000.0F)
#define MIN_ACCELERATION (0.0F)
#define MAX_ACCELERATION (1000.0F)
#define MOTOR_STEP (1.8F)
#define DRV8825_MICROSTEP (DRV8825_MICROSTEP_FULL)
#define STEP_CHANGE \
    ((MOTOR_STEP)) //* drv8825_microstep_to_fraction(DRV8825_MICROSTEP))
#define CURRENT_LIMIT (2.0F)
#define DEAD_ERROR (STEP_CHANGE)
#define MAGNET_POLARITY (true)

#define DELTA_TIME (10.0F / 1000.0F)

#define REFERENCE_POSITION (0.0F)
#define REFERENCE_SPEED (100.0F)
#define REFERENCE_ACCELERATION (100.0F)

#define LOG_UART_BUS (&huart2)

#define DELTA_TIMER (&htim1)

#define AS5600_I2C_ADDRESS (0x36U << 1U)
#define AS5600_I2C_BUS (&hi2c1)
#define AS5600_DIR_GPIO (GPIOB)
#define AS5600_DIR_PIN (1U << 7U)

#define INA226_I2C_BUS (&hi2c1)
#define INA226_I2C_ADDRESS (0x40U << 1U)

#define DRV8825_PWM_TIMER (&htim2)
#define DRV8825_PWM_CHANNEL (TIM_CHANNEL_2)
#define DRV8825_DIR_GPIO (GPIOA)
#define DRV8825_DIR_PIN (1U << 15U)
#define DRV8825_EN_GPIO (GPIOC)
#define DRV8825_EN_PIN (1U << 13U)
#define DRV8825_M0_GPIO (GPIOB)
#define DRV8825_M0_PIN (1U << 6U)
#define DRV8825_M1_GPIO (GPIOB)
#define DRV8825_M1_PIN (1U << 5U)
#define DRV8825_M2_GPIO (GPIOB)
#define DRV8825_M2_PIN (1U << 4U)

#endif // MAIN_CONFIG_H
