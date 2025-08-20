/**
 * @file buzzer.h
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

class BuzzerArduino : public hal_components::BuzzerBase
{
public:
    void beep(float frequency, std::uint32_t duration) override;
    void stop() override;
    void playRtttlMusic(const std::string &rtttlMusic) override;
    bool isPlaying() override;

private:
};
