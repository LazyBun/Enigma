#include <Arduino.h>
#include <Game.h>

Game game;

void setup() {
  Serial.begin(9600);
  game.startGame();
}

void loop() {
  game.checkState();
  delay(100);
}
