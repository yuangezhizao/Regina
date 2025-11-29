/**
 * @file hal_test_with_ui.cpp
 * @author yuangezhizao
 * @brief
 * @version 0.1
 * @date 2025-12-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "esp32-hal.h"
#include "hal/hal.h"
#include "hal_esp32.h"
#include "hal_config.h"
#include <mooncake_log.h>
#include <Arduino.h>

void HalEsp32::hal_test_with_ui()
{
    /* ---------------------------------- Test ---------------------------------- */
    // imu_test_with_ui();
    // button_test_with_ui();
    // buzzer_test_with_ui();
    oled_test_with_ui();
}

void HalEsp32::imu_test_with_ui()
{
    // 基础参数
    constexpr int FONT0_HEIGHT = 8;
    constexpr int TEXT_PADDING = 3;

    // 表格行
    constexpr int ROW_HEIGHT = FONT0_HEIGHT + TEXT_PADDING * 2; // 8 + 3 * 2 = 14
    constexpr int ROW_0_Y = FONT0_HEIGHT + 1;                   // 8 + 1 = 9
    constexpr int ROW_1_Y = ROW_0_Y + ROW_HEIGHT;               // 9 + 14 = 23
    constexpr int ROW_2_Y = ROW_1_Y + ROW_HEIGHT;               // 23 + 14 = 37
    constexpr int ROW_3_Y = ROW_2_Y + ROW_HEIGHT;               // 37 + 14 = 51

    // 表格列
    constexpr int COL_WIDTH = HAL_SCREEN_WIDTH / 3; // 128 / 3 = 42
    constexpr int COL_1_X = COL_WIDTH / 2;          // 42 / 2 = 21
    constexpr int COL_2_X = COL_1_X + COL_WIDTH;    // 21 + 42 = 63
    constexpr int COL_3_X = COL_2_X + COL_WIDTH;    // 63 + 42 = 105

    // 单元格
    constexpr int CELL_0_Y = ROW_0_Y + TEXT_PADDING; // 9 + 3 = 12
    constexpr int CELL_1_Y = ROW_1_Y + TEXT_PADDING; // 23 + 3 = 26
    constexpr int CELL_2_Y = ROW_2_Y + TEXT_PADDING; // 37 + 3 = 40

    while (1)
    {
        HAL::Imu().update();
        const hal_components::ImuBase::ImuData_t &imuData = HAL::Imu().getData();

        float accelX = imuData.accelX;
        float accelY = imuData.accelY;
        float accelZ = imuData.accelZ;
        float gyroX = imuData.gyroX;
        float gyroY = imuData.gyroY;
        float gyroZ = imuData.gyroZ;

        mclog::info("accel: {:>7.2f} {:>7.2f} {:>7.2f} | gyro: {:>7.2f} {:>7.2f} {:>7.2f}", accelX, accelY, accelZ,
                    gyroX, gyroY, gyroZ);

        HAL::Display().GetCanvas()->fillScreen(TFT_BLACK);
        HAL::Display().RenderFpsPanel();

        // 绘制 3 x 3 表格线
        // 水平线
        HAL::Display().GetCanvas()->drawFastHLine(0, ROW_0_Y, HAL_SCREEN_WIDTH, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastHLine(0, ROW_1_Y, HAL_SCREEN_WIDTH, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastHLine(0, ROW_2_Y, HAL_SCREEN_WIDTH, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastHLine(0, ROW_3_Y, HAL_SCREEN_WIDTH, TFT_WHITE);
        // 垂直线
        HAL::Display().GetCanvas()->drawFastVLine(COL_WIDTH, ROW_0_Y, ROW_3_Y - ROW_0_Y, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastVLine(COL_WIDTH * 2, ROW_0_Y, ROW_3_Y - ROW_0_Y, TFT_WHITE);

        HAL::Display().GetCanvas()->setFont(&fonts::Font0);
        HAL::Display().GetCanvas()->setTextDatum(top_center);

        // 表头：X Y Z
        HAL::Display().GetCanvas()->drawString("X", COL_1_X, CELL_0_Y);
        HAL::Display().GetCanvas()->drawString("Y", COL_2_X, CELL_0_Y);
        HAL::Display().GetCanvas()->drawString("Z", COL_3_X, CELL_0_Y);

        // 第 1 行：加速度
        char buf[12];
        snprintf(buf, sizeof(buf), "%.2f", accelX);
        HAL::Display().GetCanvas()->drawString(buf, COL_1_X, CELL_1_Y);
        snprintf(buf, sizeof(buf), "%.2f", accelY);
        HAL::Display().GetCanvas()->drawString(buf, COL_2_X, CELL_1_Y);
        snprintf(buf, sizeof(buf), "%.2f", accelZ);
        HAL::Display().GetCanvas()->drawString(buf, COL_3_X, CELL_1_Y);

        // 第 2 行：陀螺仪
        snprintf(buf, sizeof(buf), "%.2f", gyroX);
        HAL::Display().GetCanvas()->drawString(buf, COL_1_X, CELL_2_Y);
        snprintf(buf, sizeof(buf), "%.2f", gyroY);
        HAL::Display().GetCanvas()->drawString(buf, COL_2_X, CELL_2_Y);
        snprintf(buf, sizeof(buf), "%.2f", gyroZ);
        HAL::Display().GetCanvas()->drawString(buf, COL_3_X, CELL_2_Y);

        HAL::Display().canvasUpdate();
        delay(50);

        HAL::SysCtrl().feedTheDog();
    }
}

void HalEsp32::button_test_with_ui()
{
    // 基础参数
    constexpr int FONT0_HEIGHT = 8;
    constexpr int TEXT_PADDING = 3;
    constexpr int ICON_PADDING = 2;
    constexpr int INDICATOR_SIZE = 10;

    // 表格行
    constexpr int ROW_HEIGHT = FONT0_HEIGHT + TEXT_PADDING * 2; // 8 + 3 * 2 = 14
    constexpr int ROW_0_Y = FONT0_HEIGHT + 1;                   // 8 + 1 = 9
    constexpr int ROW_1_Y = ROW_0_Y + ROW_HEIGHT;               // 9 + 14 = 23
    constexpr int ROW_2_Y = ROW_1_Y + ROW_HEIGHT;               // 23 + 14 = 37

    // 表格列
    constexpr int COL_WIDTH = HAL_SCREEN_WIDTH / 4; // 128 / 4 = 32
    constexpr int COL_1_X = COL_WIDTH / 2;          // 32 / 2 = 16
    constexpr int COL_2_X = COL_1_X + COL_WIDTH;    // 16 + 32 = 48
    constexpr int COL_3_X = COL_2_X + COL_WIDTH;    // 48 + 32 = 80
    constexpr int COL_4_X = COL_3_X + COL_WIDTH;    // 80 + 32 = 112

    // 单元格
    constexpr int CELL_0_Y = ROW_0_Y + TEXT_PADDING; // 9 + 3 = 12
    constexpr int CELL_1_Y = ROW_1_Y + ICON_PADDING; // 23 + 2 = 25

    while (1)
    {
        HAL::BtnUpdate();

        bool btnA = HAL::BtnA().isPressed();
        bool btnB = HAL::BtnB().isPressed();
        bool btnC = HAL::BtnC().isPressed();
        bool btnD = HAL::BtnD().isPressed();

        mclog::info("Buttons - A: {:>5} B: {:>5} C: {:>5} D: {:>5}", btnA, btnB, btnC, btnD);

        HAL::Display().GetCanvas()->fillScreen(TFT_BLACK);
        HAL::Display().RenderFpsPanel();

        // 绘制 4 x 2 表格线
        // 水平线
        HAL::Display().GetCanvas()->drawFastHLine(0, ROW_0_Y, HAL_SCREEN_WIDTH, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastHLine(0, ROW_1_Y, HAL_SCREEN_WIDTH, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastHLine(0, ROW_2_Y, HAL_SCREEN_WIDTH, TFT_WHITE);
        // 垂直线
        HAL::Display().GetCanvas()->drawFastVLine(COL_WIDTH, ROW_0_Y, ROW_2_Y - ROW_0_Y, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastVLine(COL_WIDTH * 2, ROW_0_Y, ROW_2_Y - ROW_0_Y, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastVLine(COL_WIDTH * 3, ROW_0_Y, ROW_2_Y - ROW_0_Y, TFT_WHITE);

        HAL::Display().GetCanvas()->setFont(&fonts::Font0);
        HAL::Display().GetCanvas()->setTextDatum(top_center);

        // 第 1 行：按钮标签
        HAL::Display().GetCanvas()->drawString("A", COL_1_X, CELL_0_Y);
        HAL::Display().GetCanvas()->drawString("B", COL_2_X, CELL_0_Y);
        HAL::Display().GetCanvas()->drawString("C", COL_3_X, CELL_0_Y);
        HAL::Display().GetCanvas()->drawString("D", COL_4_X, CELL_0_Y);

        // 第 2 行：按钮状态
        int cols[] = {COL_1_X, COL_2_X, COL_3_X, COL_4_X};
        bool btns[] = {btnA, btnB, btnC, btnD};
        for (int i = 0; i < 4; i++)
        {
            int cx = cols[i];
            int cy = CELL_1_Y + INDICATOR_SIZE / 2;
            if (btns[i])
            {
                HAL::Display().GetCanvas()->fillCircle(cx, cy, INDICATOR_SIZE / 2, TFT_WHITE);
            }
            else
            {
                HAL::Display().GetCanvas()->drawCircle(cx, cy, INDICATOR_SIZE / 2, TFT_WHITE);
            }
        }

        HAL::Display().canvasUpdate();
        delay(100);

        HAL::SysCtrl().feedTheDog();
    }
}

void HalEsp32::buzzer_test_with_ui()
{
    // 布局常量
    constexpr int TABLE_TOP = 16;
    constexpr int TABLE_HEIGHT = 34;
    constexpr int TABLE_BOTTOM = TABLE_TOP + TABLE_HEIGHT; // 16 + 34 = 50
    constexpr int SCREEN_CENTER_X = HAL_SCREEN_WIDTH / 2;  // 128 / 2 = 64

    // 音量条参数
    constexpr int BAR_COUNT = 7;
    constexpr int BAR_WIDTH = 8;
    constexpr int BAR_GAP = 4;
    constexpr int BAR_MAX_HEIGHT = 28;
    constexpr int BAR_START_X = (HAL_SCREEN_WIDTH - (BAR_COUNT * BAR_WIDTH + (BAR_COUNT - 1) * BAR_GAP)) / 2; // (128 - (7 * 8 + (7 - 1) * 4)) / 2 = 16
    constexpr int BAR_BASE_Y = TABLE_BOTTOM - 2;                                                              // 50 - 2 = 48

    // 显示刷新函数
    auto updateDisplay = [&](bool isPlaying, int interval, const char *phase)
    {
        static uint8_t animFrame = 0;
        animFrame++;

        HAL::Display().GetCanvas()->fillScreen(TFT_BLACK);
        HAL::Display().RenderFpsPanel();

        // 上下分隔线
        HAL::Display().GetCanvas()->drawFastHLine(0, TABLE_TOP, HAL_SCREEN_WIDTH, TFT_WHITE);
        HAL::Display().GetCanvas()->drawFastHLine(0, TABLE_BOTTOM, HAL_SCREEN_WIDTH, TFT_WHITE);

        // 绘制音量条动画
        for (int i = 0; i < BAR_COUNT; i++)
        {
            int barX = BAR_START_X + i * (BAR_WIDTH + BAR_GAP);
            int barHeight;

            if (isPlaying)
            {
                // 播放时：随机高度的跳动动画
                barHeight = 4 + ((animFrame + i * 3) % 5) * (BAR_MAX_HEIGHT - 4) / 5;
            }
            else
            {
                // 停止时：最小高度
                barHeight = 4;
            }

            HAL::Display().GetCanvas()->fillRect(barX, BAR_BASE_Y - barHeight, BAR_WIDTH, barHeight, TFT_WHITE);
        }

        // 底部状态显示
        HAL::Display().GetCanvas()->setFont(&fonts::Font0);
        HAL::Display().GetCanvas()->setTextDatum(top_center);

        char statusText[32];
        if (interval > 0)
        {
            snprintf(statusText, sizeof(statusText), "%s %dms", phase, interval);
        }
        else
        {
            snprintf(statusText, sizeof(statusText), "%s", isPlaying ? "PLAYING" : "STOPPED");
        }
        HAL::Display().GetCanvas()->drawString(statusText, SCREEN_CENTER_X, TABLE_BOTTOM + 4);

        HAL::Display().canvasUpdate();
    };

    while (1)
    {
        mclog::info("is playing: {}", HAL::Buzzer().isPlaying());
        HAL::Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

        while (HAL::Buzzer().isPlaying())
        {
            mclog::info("is playing: {}", HAL::Buzzer().isPlaying());
            updateDisplay(true, 0, "");
            HAL::SysCtrl().feedTheDog();
            delay(100);
        }
        updateDisplay(false, 0, "");
        delay(500);

        // 打断测试
        int interval = 2000;
        while (interval >= 500)
        {
            HAL::Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

            mclog::info("delay {}", interval);

            // 在等待期间持续刷新显示
            for (int t = 0; t < interval; t += 100)
            {
                updateDisplay(HAL::Buzzer().isPlaying(), interval, "INT");
                HAL::SysCtrl().feedTheDog();
                delay(100);
            }
            interval -= 500;
        }

        interval = 500;
        while (interval >= 20)
        {
            HAL::Buzzer().playRtttlMusic("NokiaTun:d=4,o=5,b=225:8e6,8d6,f#,g#,8c#6,8b,d,e,8b,8a,c#,e,2a");

            mclog::info("delay {}", interval);

            // 在等待期间持续刷新显示
            for (int t = 0; t < interval; t += 50)
            {
                updateDisplay(HAL::Buzzer().isPlaying(), interval, "FAST");
                HAL::SysCtrl().feedTheDog();
                delay(50);
            }
            interval -= 20;
        }
    }
}

void HalEsp32::oled_test_with_ui()
{
    // 布局参数
    constexpr int FONT0_HEIGHT = 8;
    constexpr int CONTENT_TOP = FONT0_HEIGHT + 4;                          // 8 + 4 = 12
    constexpr int SCREEN_CENTER_X = HAL_SCREEN_WIDTH / 2;                  // 128 / 2 = 64
    constexpr int SCREEN_CENTER_Y = (HAL_SCREEN_HEIGHT + CONTENT_TOP) / 2; // (64 + 12) / 2 = 38

    // 旋转指示器参数
    constexpr int SPINNER_RADIUS = 10;
    constexpr int SPINNER_X = SCREEN_CENTER_X;     // 64
    constexpr int SPINNER_Y = SCREEN_CENTER_Y - 8; // 38 - 8 = 30

    // 文字位置
    constexpr int TEXT_Y = SPINNER_Y + SPINNER_RADIUS + 6; // 30 + 10 + 6 = 46

    static int frameCount = 0;
    static int spinnerAngle = 0;

    while (1)
    {
        HAL::Display().GetCanvas()->fillScreen(TFT_BLACK);
        HAL::Display().RenderFpsPanel();

        // 绘制旋转指示器（圆环 + 旋转点）
        HAL::Display().GetCanvas()->drawCircle(SPINNER_X, SPINNER_Y, SPINNER_RADIUS, TFT_WHITE);

        // 计算旋转点位置（8 个位置）
        float angle = spinnerAngle * 3.14159f / 4.0f; // 每次转 45 度
        int dotX = SPINNER_X + (int)(SPINNER_RADIUS * 0.7f * cos(angle));
        int dotY = SPINNER_Y + (int)(SPINNER_RADIUS * 0.7f * sin(angle));
        HAL::Display().GetCanvas()->fillCircle(dotX, dotY, 3, TFT_WHITE);

        // 显示帧计数
        HAL::Display().GetCanvas()->setFont(&fonts::Font0);
        HAL::Display().GetCanvas()->setTextDatum(top_center);

        char frameText[24];
        snprintf(frameText, sizeof(frameText), "Frame: %d", frameCount++);
        HAL::Display().GetCanvas()->drawString(frameText, SCREEN_CENTER_X, TEXT_Y);

        // 更新旋转角度
        spinnerAngle = (spinnerAngle + 1) % 8;

        HAL::Display().canvasUpdate();
        delay(1);

        HAL::SysCtrl().feedTheDog();
    }
}
