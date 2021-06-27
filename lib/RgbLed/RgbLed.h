#pragma once

struct RGB {
    int red;
    int green;
    int blue;
};


class RgbLed {
    private:
        RGB constantColor;
        RGB flashingColor;
        unsigned long flashingStopTimestamp;
        unsigned long lastFlash;
        unsigned long flashingInterval;
        unsigned long isDark;
    public:
        void setup(RGB initialConstantColor);
        void setConstantColor(RGB color);
        void update();
        void setFlashingColor(RGB color, unsigned long duration, unsigned long interval);
};