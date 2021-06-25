#include <Game.h>
#include <BoxLock.h>
#include <Arduino.h>


const int MotorDigitalPin = 9;

const int SoundSensorAnalogPin = A0;
const int SoundSensorVolumeThreshold = 300;

void Game::startGame() {
    this->gameState = SoundCheck;
    this->boxLock.setup(MotorDigitalPin);

}

void Game::checkState() {
    switch (this->gameState)
    {
    case SoundCheck:
        if(isSoundSolved()) {
            // Todo change led color to indicate box side
            // Todo change state
            Serial.println("SoundCheck solved!");
        }
        break;
    default:
        break;
    }
}

bool isSoundSolved() {
    int soundValue = analogRead(A0);
    return soundValue >= SoundSensorVolumeThreshold;
}