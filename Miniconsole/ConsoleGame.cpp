#pragma once

#include <string>
#include "arduino.h"
#include "Display.cpp"
#include "Vector2.cpp"

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

    boolean A() {
      return inputs[0];
    }
    boolean B() {
      return inputs[1];
    }
    boolean UP() {
      return inputs[3];
    }
    boolean DOWN() {
      return inputs[5];
    }
    boolean LEFT() {
      return inputs[2];
    }
    boolean RIGHT() {
      return inputs[4];
    }


    virtual void Setup();
    virtual void Draw();
};
