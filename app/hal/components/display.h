/**
 * @file display.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
// #include <M5GFX.h>
#include <LovyanGFX.hpp>
#include "utils/lgfx_fx/lgfx_fx.h"

namespace hal_components
{

    /**
     * @brief 显示屏基类
     *
     */
    class DisplayBase
    {
    public:
        /**
         * @brief LGFX 数据
         *
         */
        struct LGFXData_t
        {
            LGFX_Device *display = nullptr;
            LGFX_SpriteFx *canvas = nullptr;
        };

        ~DisplayBase() = default;

        /**
         * @brief 初始化
         *
         */
        virtual void init() {}

        /**
         * @brief Display device
         *
         * @return LGFX_Device*
         */
        virtual LGFX_Device *GetDisplay()
        {
            return _lgfx_data.display;
        }

        /**
         * @brief Full screen canvas (sprite)
         *
         * @return LGFX_SpriteFx*
         */
        virtual LGFX_SpriteFx *GetCanvas()
        {
            return _lgfx_data.canvas;
        }

        /**
         * @brief Push framebuffer
         *
         */
        virtual void canvasUpdate()
        {
            GetCanvas()->pushSprite(0, 0);
        }

        /**
         * @brief Render fps panel
         *
         */
        virtual void RenderFpsPanel()
        {
            static unsigned long time_count = 0;

            _lgfx_data.canvas->setTextColor(TFT_WHITE, TFT_BLACK);
            _lgfx_data.canvas->setTextSize(1);
            _lgfx_data.canvas->setTextDatum(top_left);
            _lgfx_data.canvas->drawNumber(1000 / (millis() - time_count), 0, 0, &fonts::Font0);
            // _lgfx_data.canvas->drawNumber(123, 0, 0, &fonts::Font0);

            time_count = millis();
        }

        static constexpr int _msg_start_x = 16;
        static constexpr int _msg_start_y = 130;
        static constexpr int _msg_line_height = 32;

        /**
         * @brief Pop error message and wait reboot
         *
         * @param msg
         */
        virtual void PopFatalError(std::string msg)
        {
            // // Echo
            // spdlog::error("{}", msg);

            // /* ---------------------------------- Face ---------------------------------- */
            // _lgfx_data.canvas->setTextColor(TFT_WHITE, AssetPool::GetColor().Misc.bgPopFatalError);
            // _lgfx_data.canvas->fillScreen(AssetPool::GetColor().Misc.bgPopFatalError);

            // _lgfx_data.canvas->setTextSize(1);
            // _lgfx_data.canvas->setTextDatum(top_left);
            // _lgfx_data.canvas->loadFont(AssetPool::GetStaticAsset()->Font.montserrat_semibolditalic_72);
            // _lgfx_data.canvas->setCursor(20, 10);
            // _lgfx_data.canvas->printf(":(");

            // /* ----------------------------------- Msg ---------------------------------- */
            // int line_height = _msg_start_y;
            // AssetPool::LoadFont24(_lgfx_data.canvas);
            // _lgfx_data.canvas->setCursor(_msg_start_x, line_height);
            // _lgfx_data.canvas->printf("Fatal Error!");

            // std::istringstream msg_stream(msg);
            // std::string line;
            // while (std::getline(msg_stream, line))
            // {
            //     line_height += _msg_line_height;
            //     _lgfx_data.canvas->setCursor(_msg_start_x, line_height);
            //     _lgfx_data.canvas->print(line.c_str());
            // }

            // /* ---------------------------------- Push ---------------------------------- */
            // _lgfx_data.canvas->pushSprite(0, 0);
            // _lgfx_data.display->setBrightness(255);

            // // Press any button to poweroff
            // while (1)
            // {
            //     feedTheDog();
            //     delay(50);

            //     if (getAnyButton())
            //         reboot();
            // }
        }

        /**
         * @brief Pop warning message and wait continue
         *
         * @param msg
         */
        virtual void PopWarning(std::string msg) {}

        /**
         * @brief Pop success message and wait continue
         *
         * @param msg
         */
        virtual void PopSuccess(std::string msg, bool showSuccessLabel = true) {}

    protected:
        LGFXData_t _lgfx_data;
    };
} // namespace hal_components
