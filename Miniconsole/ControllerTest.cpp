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
    }

    void Draw() {
      for (int i = 0; i < 6; i++) {
        if (inputs[i]) {
          disp->disp.fillCircle(btCPos[(i * 2)], btCPos[(i * 2) + 1], 10, RED);
        } else {
          disp->disp.fillCircle(btCPos[(i * 2)], btCPos[(i * 2) + 1], 11, BLACK);
          disp->disp.drawCircle(btCPos[(i * 2)], btCPos[(i * 2) + 1], 10, WHITE);
        }
      }
    }

  private:
    int btCPos[12] = {
      16, 54,
      36, 74,
      72, 64,
      92, 44,
      112, 64,
      92, 84
    };
};
