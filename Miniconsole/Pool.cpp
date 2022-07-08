#include "ConsoleGame.cpp"

class Pool : public ConsoleGame {
    using ConsoleGame::ConsoleGame;

  public:
    std::string GameName() {
      return "8-Ball Pool";
    }
    std::string GameDesc() {
      return "Pool with 8 balls";
    }

    int gameState = 0; //0: Player's turn, 1: Ball movement, 2: AI's turn, 3: Gameover

    float aimAngle = 0;

    int* ballPosX;
    int* ballPosY;
    bool* ballState;

    int holeX[6] = {16, 16, 68, 68, 120, 120};
    int holeY[6] = {38, 104, 38, 104, 38, 104};

    void Setup() {
      Serial.println("Setting up Pool");

      disp->disp.fillScreen(BLACK);
      disp->disp.fillRect(8, 32, 120, 80, GREEN);
      disp->disp.fillRect(16, 40, 104, 64, YELLOW);

      for (int i = 0; i < 6; i++) {
        disp->disp.fillCircle(holeX[i], holeY[i], 5, BLACK);
      }
    }

    void Draw() {
//      disp->disp.fillRect(54, 54, 24, 24, YELLOW);
//      disp->disp.drawCircle(64, 64, 5, BLACK);
//      disp->disp.drawLine(64, 64, (int)(cos(aimAngle) * 10 + 64), (int)(sin(aimAngle) * 10 + 64), BLACK);

      if (inputs[2]) {
        aimAngle += 0.01;
      }
      if (inputs[4]) {
        aimAngle -= 0.01;
      }
    }

  private:
};
