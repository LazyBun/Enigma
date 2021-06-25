#include <Servo.h>
#include <BoxLock.h>

void BoxLock::setup(int digitalPinNumber) {
  // fixme this seems like it can fail horribly
  this->servo.attach(digitalPinNumber);

  // Need button to restart
  this->_isBoxOpen = false;
  this->closeBox();
}


bool BoxLock::isBoxOpen() {
    return this->_isBoxOpen;
}

void BoxLock::closeBox() {
  servo.write(0);
  servo.write(90);
  _isBoxOpen = false;
}
void BoxLock::openBox() {
  servo.write(0);
  _isBoxOpen = true;
}