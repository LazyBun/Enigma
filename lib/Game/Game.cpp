#include <Game.h>
#include <BoxLock.h>
#include <Arduino.h>


const int MotorDigitalPin = 9;

const int SoundSensorPin = A0;
const int SoundSensorVolumeThreshold = 300;
// aka violet
const RGB SoundSensorSideColor = {.red = 191, .green = 21, .blue = 230};

const int TiltSensorPin = 2;
// aka brown
const RGB TiltSideColor = {.red = 158, .green = 127, .blue = 24};

const int LightSensorPin = A1;
//fimxe actually check what the value should be
const int LightSensorBrightnessThreshold = 950;
// aka yellow
const RGB LightSensorSideColor = {.red = 255, .green = 255, .blue = 0};

const int TemperatureAndMosturePin = 3;
const float ColdTemperatureThreshold = 15.0;
// aka blue
const RGB ColdTemperatureSideColor = {.red = 0, .green = 110, .blue = 255};

const int WaterSensorPin = A4;
//fixme actually check what the value should be
const int WaterSensorThreshold = 100;
const int TemperatureOnlyPin = A5;
//fixme actually check what the value should be
const int HotWaterThreshold = 40;
// aka red
const RGB HotWaterSideColor = {.red = 255, .green = 0, .blue = 0};

const RGB NoColor = {.red = 0, .green = 0, .blue = 0};
const RGB SuccessColor = {.red = 0, .green = 255, .blue = 0};

void Game::startGame() {
    this->gameState = UpsideDownCheck;
    this->boxLock.setup(MotorDigitalPin);
    this->rgbLed.setup(TiltSideColor);


    pinMode(TiltSensorPin, INPUT);
    digitalWrite(TiltSensorPin, HIGH);
}

bool isUpsideDownSolved() {
    // todo possible debounce needed here
    int tiltSensorState = digitalRead(TiltSensorPin);
    Serial.print("Tilt sensor state: ");
    Serial.println(tiltSensorState);
    return tiltSensorState == 1;
}

bool isSoundSolved() {
    int soundValue = analogRead(SoundSensorPin);
    Serial.print("Sound sensor state: ");
    Serial.println(soundValue);
    return soundValue >= SoundSensorVolumeThreshold;
}

bool isLightSolved() {
    int lightValue = analogRead(LightSensorPin);
    Serial.print("Light sensor state: ");
    Serial.println(lightValue);
    return lightValue >= LightSensorBrightnessThreshold;
}

bool isColdSolved(SimpleDHT11 sensor) {
    float temperature;
    float humidity;
    // Idk if it's actually necessary
    byte data[40] = {0};
    sensor.read2(TemperatureAndMosturePin, &temperature, &humidity, data);
    Serial.print("Temperature and humidity sensor state: ");
    Serial.println(temperature);
    return temperature <= ColdTemperatureThreshold;
}

// TODO: decide whether to do that or maybe just change it to temperature check (like match near sensor)
bool isHotWaterSolved() {
    // int temperature;
    // int waterLevel;
    // return temperature >= HotWaterThreshold && waterLevel >= WaterSensorThreshold;
    return true;
}

// Todo Add some sort of indicator for:
// * puzzle solve (e.g. buzzing) (buzzer in separate class)
void Game::checkState() {
    // maybe make this public and run update in main
    rgbLed.update();
    switch (this->gameState) {
        case UpsideDownCheck:
            if (isUpsideDownSolved()) {
                Serial.println("UpsideDownCheck solved!");
                rgbLed.setConstantColor(SoundSensorSideColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 500);
                this->gameState = SoundCheck;
            }
            break;
        case SoundCheck:
            if(isSoundSolved()) {
                Serial.println("SoundCheck solved!");
                rgbLed.setConstantColor(LightSensorSideColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 500);
                this->gameState = LightCheck;
            }
            break;
        case LightCheck:
            if (isLightSolved()) {
                Serial.println("LightCheck solved!");
                rgbLed.setConstantColor(ColdTemperatureSideColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 500);
                this->gameState = ColdCheck;
            }
            break;
        case ColdCheck:
            if (isColdSolved(temperatureAndMoistureSensor)) {
                Serial.println("ColdCheck solved!");
                rgbLed.setConstantColor(HotWaterSideColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 500);
                this->gameState = HotWaterCheck;
            }
            break;
        case HotWaterCheck:
            Serial.println("HotWaterCheck solved!");
            rgbLed.setConstantColor(SuccessColor);
            rgbLed.setFlashingColor(SuccessColor, 4000, 500);
            this->gameState = Done;
            break;
        case Done:
            this->boxLock.openBox();
            break;
        default:
            break;
    }
}