/**
 * @file system_config.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>

namespace hal_components
{

    /**
     * @brief 系统配置组件基类
     *
     */
    class SystemConfigBase
    {
    public:
        struct Config_t
        {
            // 想要保存的配置
            bool mute = false;
            bool hapticFeedback = true;
            std::string watchFace;
            std::string widgetA = "time";
            std::string widgetB = "date";
        };

        ~SystemConfigBase() = default;

        /**
         * @brief 从文件系统加载配置
         *
         * @return true
         * @return false
         */
        virtual bool loadConfig()
        {
            return false;
        }

        /**
         * @brief 把配置保存到文件系统
         *
         * @return true
         * @return false
         */
        virtual bool saveConfig()
        {
            return false;
        }

        /**
         * @brief 获取当前系统配置
         *
         * @return const Config_t&
         */
        virtual const Config_t &getConfig()
        {
            return _config;
        }

        /**
         * @brief 设置当前系统配置
         *
         * @return Config_t&
         */
        virtual Config_t &setConfig()
        {
            return _config;
        }

        /**
         * @brief 应用当前系统配置
         *
         * @return true
         * @return false
         */
        virtual bool applyConfig()
        {
            return false;
        }

        /**
         * @brief Log 出来看看
         *
         */
        virtual void logConfig() {}

    protected:
        Config_t _config;
    };

} // namespace hal_components
