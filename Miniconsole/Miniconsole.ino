//#include "ConsoleGame.cpp"
#include "Breakout.cpp"

ConsoleGame *games[] = {new Breakout()};
int gameCount = 0;

//0 - Selecting game / main menu
//1 - Game setup
//2 - Running game
int consoleState = 0;

ConsoleGame *currentGame;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    ;
  }
  Serial.println("Serial connection established");

  gameCount = 0;
  for (ConsoleGame *game : games) {
    Serial.print("Loaded game: ");
    Serial.println(game->GameName().c_str());
    gameCount++;
  }
}

void loop() {
  switch (consoleState) {
    case 0:
      if (gameCount > 0) {
        currentGame = games[0];
        consoleState = 1;
      }
      break;
    case 1:
      if (currentGame != NULL) {
        currentGame->Setup();
        consoleState = 2;
      } else {
        consoleState = 0;
      }
      break;
    case 2:
      for (int pinBind : currentGame->analoguePinBindings) {
        //currentGame->AnaloguePinUpdate(pinBind, analogRead(pinBind));
      }
      for (int pinBind : currentGame->digitalPinBindings) {
        //currentGame->DigitalPinUpdate(pinBind, digitalRead(pinBind));
      }
      currentGame->Draw();

      break;
  }
}
