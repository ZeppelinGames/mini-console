#include "ConsoleGame.cpp"

class ControllerTest : public ConsoleGame {
    using ConsoleGame::ConsoleGame;

  public:
    std::string GameName() {
      return "Controller Test";
    }
    std::string GameDesc() {
      return "Test controls/buttons";
    }

    void Setup() {
      disp->disp.fillScreen(BLACK);
      Serial.println("Setting up Controller Test");

      for (int i = 0; i < 6; i++) {
        disp->disp.drawCircle(btCPos[(i * 2)], btCPos[(i * 2) + 1], 10, WHITE);
      }
    }

    void Draw() {
      for (int i = 0; i < 6; i++) {
        if (inputs[i]) {
          disp->disp.fillCircle(btCPos[(i * 2)], btCPos[(i * 2) + 1], 8, RED);
          updated[i] = true;
        } else {
          if (updated[i]) {
            updated[i] = false;
            disp->disp.fillCircle(btCPos[(i * 2)], btCPos[(i * 2) + 1], 9, BLACK);
          }
        }
      }

      disp->DisplayFPS();
    }

  private:
    bool updated[6];

    int btCPos[12] = {
      92, 74,
      112, 54,

      16, 64,
      36, 44,
      56, 64,
      36, 84
    };
};
