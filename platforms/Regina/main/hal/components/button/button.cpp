/**
 * @file button.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "button.h"
#include "../../hal_config.h"
#include <Arduino.h>
#include <mooncake_log.h>

void ButtonArduino::init()
{
    mclog::tagInfo("btn", "init");
    pinMode(HAL_PIN_BTN_A, INPUT_PULLUP);
    pinMode(HAL_PIN_BTN_B, INPUT_PULLUP);
    pinMode(HAL_PIN_BTN_C, INPUT_PULLUP);
    pinMode(HAL_PIN_BTN_D, INPUT_PULLUP);
}

bool ButtonArduino::getButton(ButtonId::ButtonId_t id)
{
    switch (id)
    {
    case ButtonId::A:
        return digitalRead(HAL_PIN_BTN_A) == 0;
    case ButtonId::B:
        return digitalRead(HAL_PIN_BTN_B) == 0;
    case ButtonId::C:
        return digitalRead(HAL_PIN_BTN_C) == 0;
    case ButtonId::D:
        return digitalRead(HAL_PIN_BTN_D) == 0;
    default:
        return false;
    }
    return false;
}

std::uint32_t ButtonArduino::millis()
{
    return ::millis();
}
