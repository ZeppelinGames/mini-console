#include "ConsoleGame.cpp"

class Breakout : public ConsoleGame {
    using ConsoleGame::ConsoleGame;

  public:
    int x = 1;
    int y = 1;

    std::string GameName() {
      return "Breakout";
    }
    std::string GameDesc() {
      return "Break blocks using a paddle";
    }

    void Setup() {
      disp->disp.fillScreen(BLACK);
      Serial.println("Setting up Breakout");
    }

    void Draw() {
      disp->disp.drawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, x, y, random(0, 2) == 0 ? RED : random(0, 2) == 1 ? MAGENTA : YELLOW);
      if (inputs[3]) {
        x += 4;
      }
      y++;
      if (x > SCREEN_WIDTH) {
        x = random(1, y);
      }
      if (y > SCREEN_HEIGHT) {
        y = random(1, x);
      }
    }
};
