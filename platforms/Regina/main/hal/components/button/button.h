/**
 * @file button.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class ButtonArduino : public hal_components::ButtonBase
{
public:
    void init() override;
    bool getButton(ButtonId::ButtonId_t id) override;
    std::uint32_t millis() override;

private:
};
