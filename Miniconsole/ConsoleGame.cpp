#include <string>
#include "arduino.h"

class ConsoleGame {
  public:
    virtual std::string GameName();
    virtual std::string GameDesc();

    virtual void Setup();
    virtual void Draw();

    int *analoguePinBindings;
    int *digitalPinBindings;
    virtual void AnaloguePinUpdate(int pinID, float pinVal);
    virtual void DigitalPinUpdate(int pinID, float pinVal);
};
