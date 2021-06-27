#pragma once

class Buzzer {
    private:
        unsigned long buzzStartTimestamp;
        unsigned long buzzDuration;
    public:
        void setup();
        void buzz(unsigned long duration);
        void update();
};