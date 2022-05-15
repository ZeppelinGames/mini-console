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

    int gameState = 0; //0 - New ball, 1 - playing, 2 - gameover
    int balls = 3;

    float prevBallX = 64;
    float prevBallY = 32;
    float ballX = 64;
    float ballY = 32;

    float ballVX = 0;
    float ballVY = 1;

    float ballSpeed = 0.35;

    float prevPaddleX = 64;
    float paddleX = 64;
    int paddleY = 112;

    float moveSpeed = 0.4;

    int* blockPosX;
    int* blockPosY;
    bool* blockState;

    const int blockWidth = 16;
    const int blockHeight = 8;
    int remBlocks = 24;

    bool startingTouch = true;

    void Setup() {
      gameState = 0;
      balls = 3;

      ballX = 64;
      ballY = 32;

      prevBallX = 64;
      prevBallY = 32;

      ballVX = 0;
      ballVY = 0;

      paddleX = 56;
      prevPaddleX = 56;
      paddleY = 112;

      startingTouch = true;

      disp->disp.fillScreen(BLACK);
      Serial.println("Setting up Breakout");

      int blocksX = 24;
      remBlocks = 24;

      blockPosX = new int[blocksX];
      blockPosY = new int[blocksX];
      blockState = new bool[blocksX];

      int i = 0;
      for (int y = 0; y < 24; y += 8) {
        for (int x = 0; x < 128; x += 16) {
          blockPosX[i] = (int)x;
          blockPosY[i] = (int)y;
          blockState[i] = true;

          disp->disp.fillRect((int)x, (int)y, 16, 8, disp->RandomColour());
          i++;
        }
      }

      DrawBall(true);
      DrawPaddle(true);
    }

    void Draw() {
      if (gameState == 0) {
        if (inputs[0] || inputs[1] || inputs[2] || inputs[3] || inputs[4] || inputs[5]) {
          gameState = 1;
          ballVY = 1;
        }
      }

      if (gameState == 1) {
      }

      if (gameState != 2) {
        if (!(inputs[2] && inputs[4])) {
          if (inputs[2]) {
            MovePaddle(-1);
          }

          // Right
          if (inputs[4]) {
            MovePaddle(1);
          }
        }

        UpdateBall();
      }

      if (remBlocks <= 0) {
        gameState = 2;
        disp->drawText("YOU WIN :)", 38, 64, WHITE);
      }

      DrawBall();
      DrawPaddle();
    }

    void UpdateBall() {
      ballX += ballVX * ballSpeed;
      ballY += ballVY * ballSpeed;

      if (ballX < 0) {
        ballX = 0;
        ballVX = 1;
      }

      if (ballX > 128) {
        ballX = 128;
        ballVX = -1;
      }

      if (ballY < 0) {
        ballY = 0;
        ballVY = 1;
      }

      if (ballY > 128) {
        //GAME OVER
        if (startingTouch) {
          balls--;
        }
        if (balls < 0) {
          gameState = 2;
          disp->drawText("GAME-OVER", 38, 64, WHITE);
        }

        startingTouch = false;

        ballVY = 1;
        ballVX = 0;

        ballX = 64;
        ballY = 32;
      }

      if (circleRectCol(ballX, ballY, 2, paddleX, paddleY, 16, 4)) {
        ballVY = -1;
        ballVX = (ballX - (paddleX + 8)) / 8;
        startingTouch = true;
      }

      for (int i = 0; i < 24; i++) {
        if (blockState[i]) {
          if (circleRectCol(ballX, ballY, 2, blockPosX[i], blockPosY[i], 16, 8)) {
            ballVY = -ballVY;
            ballY += ballVY;

            blockState[i] = false;
            remBlocks--;
            disp->disp.fillRect(blockPosX[i], blockPosY[i], 16, 8, BLACK);
          }
        }
      }
    }

    void MovePaddle(int moveDir) {
      float newPos = paddleX + (moveDir * moveSpeed);
      newPos = newPos > 112 ? 112 : (newPos < 0 ? 0 : newPos);

      paddleX = newPos;
    }

    void DrawBall(bool force = false) {
      if (!force) {
        if (prevBallX == ballX && prevBallY == ballY) {
          return;
        }
      }

      disp->disp.fillRect(prevBallX - 2, prevBallY - 2, 5, 5, BLACK);
      disp->disp.fillCircle((int)ballX, (int)ballY, 2, WHITE);

      prevBallX = ballX;
      prevBallY = ballY;
    }

    void DrawPaddle(bool force = false) {
      if (!force) {
        if (prevPaddleX == paddleX) {
          return;
        }
      }

      disp->disp.fillRect(prevPaddleX, paddleY, 16, 4, BLACK);
      disp->disp.fillRect((int)paddleX, paddleY, 16, 4, WHITE);

      prevPaddleX = paddleX;
    }

    bool circleRectCol(int cX, int cY, int r, int rX, int rY, int rW, int rH) {
      if (cX < rX + rW + r && ballX > rX - r) {
        if (cY < rY + rH + r && ballY > rY - r) {
          return true;
        }
      }
      return false;
    }
};
