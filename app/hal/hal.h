/**
 * @file hal.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <memory>
#include <string>
// #include "components/components_config.h"
#include "components/system_control.h"
#include "components/imu.h"
#include "components/buzzer.h"
// #include "components/touchpad.h"
// #include "components/encoder.h"
#include "components/system_config.h"
#include "components/haptic_engine.h"
#include "components/battery_monitor.h"
#include "components/button.h"
#include "components/ble.h"

/**
 * @brief 硬件抽象层，提供统一的硬件、平台相关行为接口
 *
 */
namespace HAL
{

    /**
     * @brief 硬件抽象基类
     *
     */
    class HalBase
    {
    public:
        virtual ~HalBase() = default;

        /* -------------------------------------------------------------------------- */
        /*                                Hardware APIs                               */
        /* -------------------------------------------------------------------------- */
        // 硬件行为抽象，也就是创建自己的 HAL 时所要重写的方法
        // 在这里加上你需要的虚函数方法
        // 比如从某个接口拉取信息：
        // virtual std::string fetchInfoFromHttp(std::string api) { return ""; }
        // 如果行为比较复杂的，可以封装成组件，参考 components 目录

        /**
         * @brief 获取硬件抽象类型
         *
         * @return std::string
         */
        virtual std::string type()
        {
            return "Base";
        }

        /**
         * @brief 在这里初始化硬件，以及组件的实例创建
         *
         */
        virtual void init() {}

        /* -------------------------------------------------------------------------- */
        /*                              Components Getter                             */
        /* -------------------------------------------------------------------------- */
        // 组件实例接口
        hal_components::SystemControlBase &SysCtrl();
        hal_components::ImuBase &Imu();
        hal_components::BuzzerBase &Buzzer();
        hal_components::SystemConfigBase &SysCfg();
        hal_components::HapticEngineBase &HapticEngine();
        hal_components::BatteryMonitorBase &BatteryMonitor();
        hal_components::ButtonBase &Button();
        hal_components::BleBase &Ble();

    protected:
        // 组件实例管理
        struct Components_t
        {
            std::unique_ptr<hal_components::SystemControlBase> system_control;
            std::unique_ptr<hal_components::ImuBase> imu;
            std::unique_ptr<hal_components::BuzzerBase> buzzer;
            std::unique_ptr<hal_components::SystemConfigBase> system_config;
            std::unique_ptr<hal_components::HapticEngineBase> haptic_engine;
            std::unique_ptr<hal_components::BatteryMonitorBase> battery_monitor;
            std::unique_ptr<hal_components::ButtonBase> button;
            std::unique_ptr<hal_components::BleBase> ble;
        };
        Components_t _components;
    };

    /* -------------------------------------------------------------------------- */
    /*                                  Singleton                                 */
    /* -------------------------------------------------------------------------- */
    // 提供一个可注入的全局单例

    /**
     * @brief 获取当前 HAL 实例
     *
     * @return HalBase&
     */
    HalBase &Get();

    /**
     * @brief 注入 HAL，期间会调用 init() 以初始化 HAL
     *
     * @param hal
     */
    void Inject(std::unique_ptr<HalBase> hal);

    /**
     * @brief 销毁当前 HAL 实例
     *
     */
    void Destroy();

    // 封装一下不然长的一
    inline hal_components::SystemControlBase &SysCtrl()
    {
        return Get().SysCtrl();
    }
    inline hal_components::ImuBase &Imu()
    {
        return Get().Imu();
    }
    inline hal_components::BuzzerBase &Buzzer()
    {
        return Get().Buzzer();
    }
    inline hal_components::SystemConfigBase &SysCfg()
    {
        return Get().SysCfg();
    }
    inline hal_components::HapticEngineBase &HapticEngine()
    {
        return Get().HapticEngine();
    }
    inline hal_components::BatteryMonitorBase &BatteryMonitor()
    {
        return Get().BatteryMonitor();
    }
    inline void BtnUpdate()
    {
        Get().Button().update();
    }
    inline hal_components::Button_Class &BtnA()
    {
        return Get().Button().BtnA;
    }
    inline hal_components::Button_Class &BtnB()
    {
        return Get().Button().BtnB;
    }
    inline hal_components::Button_Class &BtnC()
    {
        return Get().Button().BtnC;
    }
    inline hal_components::Button_Class &BtnD()
    {
        return Get().Button().BtnD;
    }
    inline hal_components::BleBase &Ble()
    {
        return Get().Ble();
    }

} // namespace HAL
