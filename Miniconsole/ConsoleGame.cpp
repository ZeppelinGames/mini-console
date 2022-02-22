#include <string>
#include "arduino.h"
#include "Display.cpp"

class ConsoleGame {
  public:
    boolean inputs[6];

    Display *disp;
    explicit ConsoleGame(Display *d) {
      disp = d;
    }

    virtual std::string GameName();
    virtual std::string GameDesc();

    void UpdateInputs(boolean newInputs[]) {
      for (int i = 0; i < 6; i++) {
        inputs[i] = newInputs[i];
      }
    }
    virtual void Setup();
    virtual void Draw();
};
