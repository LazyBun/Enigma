#pragma once
#include <BoxLock.h>
#include <RgbLed.h>
#include <SimpleDHT.h>

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
        SimpleDHT11 temperatureAndMoistureSensor;
    public: 
        void startGame();
        void checkState();
};