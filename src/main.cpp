#include <Arduino.h>
#include <Game.h>
#include <SimpleDHT.h>

Game game;

SimpleDHT11 dht;

void setup() {
  Serial.begin(9600);
  // game.startGame();
  // Give some time for game to setup
  delay(2000);
  // todo beep
}

void loop() {

  // game.checkState();
  delay(200);
}
