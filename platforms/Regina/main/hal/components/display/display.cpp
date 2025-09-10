/**
 * @file display.cpp
 * @author Forairaaaaa
 * @brief Ref: https://github.com/lovyan03/LovyanGFX/blob/master/examples/HowToUse/2_user_setting/2_user_setting.ino
 * @version 0.1
 * @date 2023-11-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "display.h"
#include "../../hal_config.h"
#include "../utils/oled/oled.h"
// #include <cstdint>
#include <LovyanGFX.hpp>
#include <mooncake_log.h>

Oled *__get_oled();

static const char *_tag = "display";

void DisplayOLED::init()
{
    mclog::tagInfo(_tag, "init");

    // 1. display
    _lgfx_data.display = __get_oled();
    mclog::tagInfo(_tag, "display ptr = {}", (void *)_lgfx_data.display);
    mclog::tagInfo(_tag, "panel ptr = {}", (void *)_lgfx_data.display->getPanel());

    // 2. canvas
    _lgfx_data.canvas = new LGFX_SpriteFx(_lgfx_data.display);
    _lgfx_data.canvas->createSprite(_lgfx_data.display->width(), _lgfx_data.display->height());
}
