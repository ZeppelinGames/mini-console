#include "ConsoleGame.cpp"

class Breakout : public ConsoleGame {
  public:
    std::string GameName() {
      return "Breakout";
    }
    std::string GameDesc() {
      return "Break blocks using a paddle";
    }

    void Setup() {
      Serial.println("Setting up Breakout");
      *analoguePinBindings = {23};
    }

    void Draw() {

    }

    void AnaloguePinUpdate(int pinID, float pinVal) {
      Serial.print("Pin ");
      Serial.print(pinID);
      Serial.print(": ");
      Serial.println(pinVal);
    }
    void DigitalPinUpdate(int pinID, float pinVal) {
      
    }
};
