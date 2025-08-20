/**
 * @file button.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "utils/Button_Class/Button_Class.hpp"

namespace ButtonId
{
    enum ButtonId_t
    {
        None = 0,
        Power,
        Up,
        Ok,
        Down,
    };
}

namespace hal_components
{

    /**
     * @brief 按键组件基类
     *
     */
    class ButtonBase
    {
    public:
        virtual void init() {}

        /**
         * @brief 最基础的按钮状态获取，比如引脚电平
         *
         * @param id
         * @return true 按下
         * @return false 没按
         */
        virtual bool getButton(ButtonId::ButtonId_t id)
        {
            return false;
        }

        /**
         * @brief 获取当前系统运行毫秒数，防抖、双击什么的用的
         *
         * @return std::uint32_t
         */
        virtual std::uint32_t millis()
        {
            return 0;
        }

        // 按键状态类实例，对应按键 ID
        Button_Class BtnPower;
        Button_Class BtnUp;
        Button_Class BtnOk;
        Button_Class BtnDown;

        /**
         * @brief 刷新按钮状态
         *
         */
        inline void update()
        {
            BtnPower.setRawState(millis(), getButton(ButtonId::Power));
            BtnUp.setRawState(millis(), getButton(ButtonId::Up));
            BtnOk.setRawState(millis(), getButton(ButtonId::Ok));
            BtnDown.setRawState(millis(), getButton(ButtonId::Down));
        }
    };

} // namespace hal_components
