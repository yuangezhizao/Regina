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
#include "components/imu/imu.h"
#include "components/button/button.h"
#include "components/buzzer/buzzer.h"
#include "components/display/display.h"
// #include "components/utils/oled/oled.h"

extern "C"
{
#include "components/utils/wear_levelling/wear_levelling.h"
}

#include <cstdint>
#include <mooncake_log.h>
#include <Arduino.h>
#include <driver/i2c.h>

// 组件实例创建和杂项初始化
void HalEsp32::init()
{
    initArduino();

    // 文件系统
    fs_init();

    // 系统控制
    _components.system_control = std::make_unique<SystemControlArduino>();
    _components.system_control->init();

    // I2C
    i2c_init();

    // IMU
    _components.imu = std::make_unique<ImuBmi270>();
    _components.imu->init();

    // 按钮
    _components.button = std::make_unique<ButtonArduino>();
    _components.button->init();

    // 蜂鸣器
    _components.buzzer = std::make_unique<BuzzerArduino>();

    // OLED
    // oled_init();

    // 显示屏
    _components.display = std::make_unique<DisplayOLED>();
    _components.display->init();

    hal_test();

    hal_test_with_ui();
}

/* -------------------------------------------------------------------------- */
/*                                     I2C                                    */
/* -------------------------------------------------------------------------- */
void HalEsp32::i2c_init()
{
    const std::string tag = "i2c";
    mclog::tagInfo(tag, "init");

    // 初始化
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = HAL_PIN_IMU_I2C_BUS_SDA;
    conf.scl_io_num = HAL_PIN_IMU_I2C_BUS_SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 400000;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;
    i2c_param_config(HAL_I2C_BUS_PORT_NUM, &conf);

    if (i2c_driver_install(HAL_I2C_BUS_PORT_NUM, conf.mode, 0, 0, 0) != ESP_OK)
    {
        mclog::tagError(tag, "i2c driver install failed");
    }

    // 扫描
    uint8_t device_num = 0;
    uint8_t WRITE_BIT = I2C_MASTER_WRITE;
    uint8_t ACK_CHECK_EN = 0x1;
    uint8_t address;
    mclog::tagInfo(tag, "scan bus..");
    for (int i = 0; i < 128; i += 16)
    {
        for (int j = 0; j < 16; j++)
        {
            fflush(stdout);
            address = i + j;
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (address << 1) | WRITE_BIT, ACK_CHECK_EN);
            i2c_master_stop(cmd);
            esp_err_t ret = i2c_master_cmd_begin(HAL_I2C_BUS_PORT_NUM, cmd, portMAX_DELAY);
            i2c_cmd_link_delete(cmd);
            if (ret == ESP_OK)
            {
                if (address == 0)
                    continue;
                mclog::tagInfo(tag, ">> {:#X}", address);
                device_num++;
            }
        }
    }
    mclog::tagInfo(tag, "found {} device", device_num);
}

/* -------------------------------------------------------------------------- */
/*                                    OLED                                    */
/* -------------------------------------------------------------------------- */

// static Oled *_oled = nullptr;

// // 暴露给 Display 组件用
// Oled *__get_oled()
// {
//     return _oled;
// }

// void HalEsp32::oled_init()
// {
//     const std::string tag = "oled";
//     mclog::tagInfo(tag, "init");

//     if (_oled != nullptr)
//     {
//         mclog::tagError(tag, "already inited");
//         return;
//     }

//     _oled = new Oled;
//     _oled->init();

//     mclog::tagInfo(tag, "size: {} x {}", _oled->width(), _oled->height());
// }

/* -------------------------------------------------------------------------- */
/*                                     FS                                     */
/* -------------------------------------------------------------------------- */
void HalEsp32::fs_init()
{
    const std::string tag = "fs";
    mclog::tagInfo(tag, "init");

    if (!wl_fs_init())
    {
        mclog::tagError(tag, "failed");
    }
}
