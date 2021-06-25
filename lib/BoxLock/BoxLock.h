#include <Servo.h>

/*

For controlling micro servo: SG90.

Brown: Ground
Red: Power
Yellow: Signal (digital)

*/

class BoxLock {
    private:
        bool _isBoxOpen;
        Servo servo;
    public:
        void closeBox();
        void openBox();
        bool isBoxOpen();
        void setup(int digitalPinNumber);
};