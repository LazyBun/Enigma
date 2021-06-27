#include <Buzzer.h>
#include <Arduino.h>

// fixme decide whether this is correct pin
const int BuzzerPin = 7;


void Buzzer::setup() {
    pinMode(BuzzerPin, OUTPUT);
    this->buzzStartTimestamp = millis();
    this->buzzDuration = 0;
}

void Buzzer::buzz(unsigned long duration) {
    this->buzzStartTimestamp = millis();
    this->buzzDuration = duration;
}

void Buzzer::update() {
    unsigned int now = millis();
    if (now - this->buzzDuration > this->buzzStartTimestamp) {
        digitalWrite(BuzzerPin, LOW);
    } else {
        digitalWrite(BuzzerPin, HIGH);
    }
}

