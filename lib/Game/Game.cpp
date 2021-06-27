#include <Game.h>
#include <BoxLock.h>
#include <Arduino.h>


const int MotorDigitalPin = 9;

const int SoundSensorPin = A0;
const int SoundSensorVolumeThreshold = 300;
// aka red
const RGB SoundSensorSideColor = {.red = 255, .green = 0, .blue = 0};

const int TiltSensorPin = 2;
// aka white
const RGB TiltSideColor = {.red = 255, .green = 255, .blue = 255};

const int LightSensorPin = A1;
//fimxe actually check what the value should be
const int LightSensorBrightnessThreshold = 600;
// aka yellow
const RGB LightSensorSideColor = {.red = 255, .green = 255, .blue = 0};

const int TemperatureAndMosturePin = 3;
const float ColdTemperatureDifferenceThreshold = 2.0;
// aka blue
const RGB ColdTemperatureSideColor = {.red = 0, .green = 0, .blue = 255};

const RGB NoColor = {.red = 0, .green = 0, .blue = 0};
const RGB SuccessColor = {.red = 0, .green = 255, .blue = 0};

void Game::startGame() {
    this->gameState = UpsideDownCheck;
    // fixme unify pin initalization
    this->boxLock.setup(MotorDigitalPin);
    this->rgbLed.setup(TiltSideColor);
    this->buzzer.setup();
    
    this->upsideDownCounter = 0;

    pinMode(TiltSensorPin, INPUT);
    digitalWrite(TiltSensorPin, HIGH);

    float temperature;
    float humidity;
    // Idk if it's actually necessary
    byte data[40] = {0};
    this->temperatureAndMoistureSensor.read2(TemperatureAndMosturePin, &temperature, &humidity, data);
    this->initialTemperature = temperature;
    Serial.println(this->initialTemperature);

    delay(2000);
    // this->buzzer.buzz(500);
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

bool isColdSolved(SimpleDHT11 sensor, float initialTemp) {
    float temperature;
    float humidity;
    // Idk if it's actually necessary
    byte data[40] = {0};
    sensor.read2(TemperatureAndMosturePin, &temperature, &humidity, data);
    Serial.print("Temperature and humidity sensor state: ");
    Serial.println(temperature);
    return initialTemp - temperature >= ColdTemperatureDifferenceThreshold;
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
    buzzer.update();
    switch (this->gameState) {
        case UpsideDownCheck:
            if (isUpsideDownSolved()) {
                this->upsideDownCounter += 1;
            } else {
                this->upsideDownCounter = 0;
            }
            if (this->upsideDownCounter > 4) {
                Serial.println("UpsideDownCheck solved!");
                rgbLed.setConstantColor(SoundSensorSideColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 200);
                this->gameState = SoundCheck;
            }
            break;
        case SoundCheck:
            if(isSoundSolved()) {
                Serial.println("SoundCheck solved!");
                rgbLed.setConstantColor(LightSensorSideColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 200);
                this->gameState = LightCheck;
            }
            break;
        case LightCheck:
            if (isLightSolved()) {
                Serial.println("LightCheck solved!");
                rgbLed.setConstantColor(ColdTemperatureSideColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 200);
                this->gameState = ColdCheck;
            }
            break;
        case ColdCheck:
            if (isColdSolved(temperatureAndMoistureSensor, initialTemperature)) {
                Serial.println("ColdCheck solved!");
                rgbLed.setConstantColor(SuccessColor);
                rgbLed.setFlashingColor(SuccessColor, 4000, 200);
                // buzzer.buzz(500);
                this->gameState = Done;
            }
            break;
        case Done:
            this->boxLock.openBox();
            break;
        default:
            break;
    }
}