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
    imu_test();
    // button_test();
    // buzzer_test();
}

void HalEsp32::imu_test()
{
    while (1)
    {
        HAL::Imu().update();
        mclog::info("{:0.2f}\t{:0.2f}\t{:0.2f}\t|\t{:0.2f}\t{:0.2f}\t{:0.2f}", HAL::Imu().getData().accelX,
                    HAL::Imu().getData().accelY, HAL::Imu().getData().accelZ, HAL::Imu().getData().gyroX,
                    HAL::Imu().getData().gyroY, HAL::Imu().getData().gyroZ);

        delay(50);
        HAL::SysCtrl().feedTheDog();
    }
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

void HalEsp32::buzzer_test()
{
    while (1)
    {
        mclog::info("is playing: {}", HAL::Buzzer().isPlaying());
        HAL::Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

        while (HAL::Buzzer().isPlaying())
        {
            mclog::info("is playing: {}", HAL::Buzzer().isPlaying());
            HAL::SysCtrl().feedTheDog();
            delay(1000);
        }

        // 打断测试
        int interval = 2000;
        while (interval >= 500)
        {
            HAL::Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

            mclog::info("delay {}", interval);
            delay(interval);
            interval -= 500;
            HAL::SysCtrl().feedTheDog();
        }

        interval = 500;
        while (interval >= 20)
        {
            HAL::Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

            mclog::info("delay {}", interval);
            delay(interval);
            interval -= 20;
            HAL::SysCtrl().feedTheDog();
        }
    }
}
