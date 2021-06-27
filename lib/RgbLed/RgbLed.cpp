#include <Arduino.h>
#include <RgbLed.h>

const int RedPin = 10;
const int GreenPin = 11;
const int BluePin = 12;

void RgbLed::setup(RGB initialConstantColor) {
    pinMode(RedPin, OUTPUT);
    pinMode(GreenPin, OUTPUT);
    pinMode(BluePin, OUTPUT);
    this->setConstantColor(initialConstantColor);
    this->flashingStopTimestamp = millis();
    this->lastFlash = millis();
    this->flashingInterval = 100;
    this->isDark = true;
}

void RgbLed::setConstantColor(RGB color) {
    this->constantColor = color;
}
void RgbLed::setFlashingColor(RGB color, unsigned long duration, unsigned long interval) {
    this->flashingColor = color;
    this->flashingStopTimestamp = millis() + duration;
    this->flashingInterval = interval;
}

void RgbLed::update() {
    unsigned long currentTime = millis();
    if (currentTime > flashingStopTimestamp) {
        analogWrite(RedPin, constantColor.red);
        analogWrite(GreenPin, constantColor.green);
        analogWrite(BluePin, constantColor.blue);
    } else {
        if (currentTime - flashingInterval > lastFlash) {
            lastFlash = currentTime;
            if (isDark) {
                analogWrite(RedPin, flashingColor.red);
                analogWrite(GreenPin, flashingColor.green);
                analogWrite(BluePin, flashingColor.blue);
                isDark = false;
            } else {
                analogWrite(RedPin, 0);
                analogWrite(GreenPin, 0);
                analogWrite(BluePin, 0);
                isDark = true;
            }
        }
    }
}

