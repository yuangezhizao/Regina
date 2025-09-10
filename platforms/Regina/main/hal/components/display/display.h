/**
 * @file display.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class DisplayOLED : public hal_components::DisplayBase
{

public:
    void init() override;
};
