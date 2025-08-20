/**
 * @file hal_esp32.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "hal_esp32.h"
#include "hal_config.h"
#include "components/system_ctrl/system_ctrl.h"
#include "components/button/button.h"
#include "components/buzzer/buzzer.h"

#include <cstdint>
#include <mooncake_log.h>
#include <Arduino.h>

// 组件实例创建和杂项初始化
void HalEsp32::init()
{
    initArduino();

    // 系统控制
    _components.system_control = std::make_unique<SystemControlArduino>();
    _components.system_control->init();

    // 按钮
    _components.button = std::make_unique<ButtonArduino>();
    _components.button->init();

    // 蜂鸣器
    _components.buzzer = std::make_unique<BuzzerArduino>();

    hal_test();
}
