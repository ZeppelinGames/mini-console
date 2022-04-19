#include "ConsoleGame.cpp"

class Breakout : public ConsoleGame {
    using ConsoleGame::ConsoleGame;

  public:
    std::string GameName() {
      return "Breakout";
    }
    std::string GameDesc() {
      return "Break blocks using a paddle";
    }

    void Setup() {
      disp->disp.fillScreen(BLACK);
      Serial.println("Setting up Breakout");

      //      blockPosX = new int[blocksX];
      //      blockPosY = new int[blocksX];
      //
      //      int i = 0;
      //      for (int y = 0; y < blockHeight * 6; y += blockHeight) {
      //        for (int x = 0; x < SCREEN_WIDTH; x += blockWidth) {
      //          blockPosX[i] = x;
      //          blockPosY[i] = y;
      //          blockColor[i] = disp->RandomColour();
      //          blockState[i] = true;
      //          i++;
      //        }
      //      }
    }

    void Draw() {
      //      for (int i = 0; i < blocksCount; i++) {
      //        if (blockState[i]) {
      //          disp->DrawRect(blockPosX[i], blockPosY[i], blockWidth, blockHeight, blockColor[i]);
      //        }
      //      }
      //
      //      // LeFt
      //      if (!(inputs[2] && inputs[4])) {
      //        if (inputs[2]) {
      //          paddleX--;
      //          paddleX = paddleX < 0 ? 0 : paddleX;
      //        }
      //
      //        // right
      //        if (inputs[4]) {
      //          paddleX++;
      //          paddleX = paddleX > 128 ? 128 : paddleX;
      //        }
      //      }
    }

  private:
    int ballX = SCREEN_WIDTH / 2;
    int ballY = 32;

    int paddleX = SCREEN_WIDTH / 2;
    int paddleY = 16;

    int blockPosX[];
    int blockPosY[];
    bool blockState[];
    int blockColor[];

    int blockWidth = SCREEN_WIDTH / 8;
    int blockHeight = SCREEN_HEIGHT / 16;
    int blocksCount = blockWidth * 6; // 8 creates width, 6 is amount of rows
};
