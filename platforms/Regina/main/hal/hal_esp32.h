/**
 * @file hal_esp32.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class HalEsp32 : public HAL::HalBase
{
public:
    std::string type() override
    {
        return "ESP32";
    }

    void init() override;

private:
    void i2c_init();
    void fs_init();
    void oled_init();

    // 调驱动用
    void hal_test();
    void imu_test();
    void button_test();
    void buzzer_test();
    void oled_test();
};
