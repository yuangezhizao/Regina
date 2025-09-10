/**
 * @file hal_config.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

// I2C
#define HAL_I2C_BUS_PORT_NUM I2C_NUM_0
#define HAL_PIN_IMU_I2C_BUS_SCL 10
#define HAL_PIN_IMU_I2C_BUS_SDA 11

// IMU
#define HAL_IMU_DEVICE_ADDR 0x68
#define HAL_PIN_IMU_INT1 23
#define HAL_PIN_IMU_INT2 17

// Button
#define HAL_PIN_BTN_A 16
#define HAL_PIN_BTN_B 3
#define HAL_PIN_BTN_C 2
#define HAL_PIN_BTN_D 8

// Buzzer
#define HAL_PIN_BUZZ_CTRL 22

// OLED
#define HAL_SCREEN_WIDTH 128
#define HAL_SCREEN_HEIGHT 64
#define HAL_PIN_OLED_CS 9
#define HAL_PIN_OLED_DC 18
#define HAL_PIN_OLED_RST 19
#define HAL_PIN_OLED_SDA 20
#define HAL_PIN_OLED_SCL 21

// WDT
#define HAL_WATCH_DOG_TIMEOUT_S 6
