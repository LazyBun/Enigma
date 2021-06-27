#pragma once
#include <BoxLock.h>
#include <RgbLed.h>
#include <SimpleDHT.h>
#include <Buzzer.h>

enum State {
    SoundCheck,
    UpsideDownCheck,
    LightCheck,
    ColdCheck,
    HotWaterCheck,
    Done
};

class Game {
    private:
        State gameState;
        BoxLock boxLock;
        RgbLed rgbLed;
        Buzzer buzzer;
        SimpleDHT11 temperatureAndMoistureSensor;
        int upsideDownCounter;
        float initialTemperature;
    public: 
        void startGame();
        void checkState();
};