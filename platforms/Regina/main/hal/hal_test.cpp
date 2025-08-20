/**
 * @file hal_test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "esp32-hal-gpio.h"
#include "esp32-hal.h"
#include "hal/hal.h"
#include "hal_esp32.h"
#include "hal_config.h"
#include <mooncake_log.h>
#include <Arduino.h>

void HalEsp32::hal_test()
{
    /* ---------------------------------- Test ---------------------------------- */
    button_test();
}

void HalEsp32::button_test()
{
    while (1)
    {
        HAL::BtnUpdate();
        mclog::info("Buttons - A: {} B: {} C: {} D: {}",
                    HAL::BtnA().isPressed(),
                    HAL::BtnB().isPressed(),
                    HAL::BtnC().isPressed(),
                    HAL::BtnD().isPressed());

        delay(100);
        HAL::SysCtrl().feedTheDog();
    }
}
