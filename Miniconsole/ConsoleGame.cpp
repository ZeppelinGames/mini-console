#pragma once

#include <string>
#include "arduino.h"
#include "Display.cpp"

class ConsoleGame {
  public:
    boolean prevInputs[6];
    boolean inputs[6];

    Display *disp;
    ConsoleGame(Display *d) {
      disp = d;
    }

    virtual std::string GameName();
    virtual std::string GameDesc();

    void UpdateInputs(boolean newInputs[]) {
      for (int i = 0; i < 6; i++) {
        if (inputs[i] != newInputs[i]) {
          prevInputs[i] = inputs[i];
          inputs[i] = newInputs[i];
        }
      }
    }


    void UpdateInput(int i, boolean val) {
      if (inputs[i] != val) {
        prevInputs[i] = inputs[i];
        inputs[i] = val;
      }
    }

    virtual void Setup();
    virtual void Draw();
};
