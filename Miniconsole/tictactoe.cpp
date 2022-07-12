#include "ConsoleGame.cpp"

class tictactoe : public ConsoleGame {
    using ConsoleGame::ConsoleGame;

  public:
    std::string GameName() {
      return "TicTacToe";
    }
    std::string GameDesc() {
      return "Get 3 in a row";
    }

    int** pos = new int*[3];

    int currX = 0;
    int currY = 0;

    int gridSize = 37;

    boolean inputDown[6];

    int turn = 1;

    bool gameOver = false;

    void Setup() {
      Serial.println("Setting up TicTacToe");

      gameOver = false;
      disp->disp.fillScreen(BLACK);

      for (int x = 0; x < 3; x++) {
        pos[x] = new int[3];
        for (int y = 0; y < 3; y++) {
          pos[x][y] = -1;
        }
      }

      disp->disp.drawRect(8, 8, 112, 112, WHITE);

      for (int i = 1; i < 3; i++) {
        disp->disp.drawLine((i * gridSize) + 8, 8, (i * gridSize) + 8, 119, WHITE);
        disp->disp.drawLine(8, (i * gridSize) + 8, 119, (i * gridSize) + 8, WHITE);
      }

      DrawTurn(currX, currY);
    }

    void Draw() {
      if (!gameOver) {
        MoveCursor();
        DrawBoard();
      }
    }

    void MoveCursor() {
      int oldX = currX;
      int oldY = currY;

      //Left
      if (inputs[2]) {
        inputDown[2] = true;
      }
      if (!inputs[2] && inputDown[2]) {
        inputDown[2] = false;
        currX--;
      }
      //up
      if (inputs[3]) {
        inputDown[3] = true;
      }
      if (!inputs[3] && inputDown[3]) {
        inputDown[3] = false;
        currY--;
      }
      //right
      if (inputs[4]) {
        inputDown[4] = true;
      }
      if ( !inputs[4] && inputDown[4]) {
        inputDown[4] = false;
        currX++;
      }
      //down
      if (inputs[5]) {
        inputDown[5] = true;
      }
      if (!inputs[5] && inputDown[5]) {
        inputDown[5] = false;
        currY++;
      }

      currX = currX < 0 ? 0 : currX > 2 ? 2 : currX;
      currY = currY < 0 ? 0 : currY > 2 ? 2 : currY;

      if (inputs[0]) {
        if (pos[currX][currY] == -1) {
          pos[currX][currY] = turn;
          CheckWin(0);
          CheckWin(1);

          if (gameOver) {
            return;
          }

          turn = turn == 1 ? 0 : 1;

          DrawTurn(currX, currY);

        }
      }

      if (oldX != currX || oldY != currY) {
        DrawTurn(oldX, oldY);
      }
    }

    void DrawBoard() {
      for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
          if (pos[x][y] == 0) {
            //draw O
            disp->disp.drawCircle(x * gridSize + 9 + (gridSize / 2), y * gridSize + 9 + (gridSize / 2), gridSize / 4, WHITE);
          }
          if (pos[x][y] == 1) {
            //draw X
            DrawX(x, y, -8, false, WHITE);
          }
        }
      }
    }

    void CheckWin(int p) {
      bool win = false;

      bool dWin = true;
      bool d2Win = true;

      for (int x = 0; x < 3; x++) {
        bool vWin = true;
        bool hWin = true;

        int vWinI = x;
        int hWinI = x;
        for (int y = 0; y < 3; y++) {

          if (pos[x][y] != p) {
            hWin = false;
            hWinI = -1;
          }

          if (pos[y][x] != p) {
            vWin = false;
            vWinI = -1;
          }
        }

        if (vWin) {
          disp->disp.drawLine(8, vWinI * gridSize  + gridSize - 9, 2 * gridSize + gridSize + 8, vWinI * gridSize + gridSize - 9, RED);
          win = true;
        }
        if (hWin) {
          disp->disp.drawLine(hWinI * gridSize  + gridSize - 9, 8, hWinI * gridSize + gridSize - 9, 2 * gridSize + gridSize + 8, RED);
          win = true;
        }

        if (pos[x][x] != p) {
          dWin = false;
        }
        if (pos[2 - x][x] != p ) {
          d2Win = false;
        }
      }

      if (dWin || d2Win) {
        win = true;
      }

      if (win) {
        gameOver = true;
        //disp->disp.fillRect(0, 0, 8, 8, turn == 1 ? RED : BLUE);
      }
    }

    void DrawTurn(int oldX, int oldY) {
      disp->disp.fillRect(oldX * gridSize + 10, oldY * gridSize + 10, gridSize - 2, gridSize - 2, BLACK);

      if (turn == 1) {
        DrawX(currX, currY, -14, true, YELLOW);
      } else {
        disp->disp.fillCircle(currX * gridSize + 9 + (gridSize / 2), currY * gridSize + 9 + (gridSize / 2), gridSize / 6, YELLOW);
      }
    }

    void DrawX(int x, int y, int s, bool t, int c) {
      int nx = x * gridSize + (gridSize / 4);
      int ny = y * gridSize + (gridSize / 4);

      int nx1 =  (x + 1) * gridSize + (gridSize / 4);
      int ny1 =  (y + 1) * gridSize + (gridSize / 4);

      disp->disp.drawLine(nx - s, ny - s, nx1 + s, ny1 + s, c);
      disp->disp.drawLine(nx - s, ny1 + s, nx1 + s, ny - s, c);

      if (t) {
        ///up
        disp->disp.drawLine(nx - s, ny - s - 1, nx1 + s, ny1 + s - 1, c);
        disp->disp.drawLine(nx - s, ny1 + s - 1, nx1 + s, ny - s - 1, c);

        //down
        disp->disp.drawLine(nx - s, ny - s + 1, nx1 + s, ny1 + s + 1, c);
        disp->disp.drawLine(nx - s, ny1 + s + 1, nx1 + s, ny - s + 1, c);

        ///left
        disp->disp.drawLine(nx - s - 1, ny - s, nx1 + s - 1, ny1 + s, c);
        disp->disp.drawLine(nx - s - 1, ny1 + s, nx1 + s - 1, ny - s, c);

        //right
        disp->disp.drawLine(nx - s + 1, ny - s, nx1 + s + 1, ny1 + s, c);
        disp->disp.drawLine(nx - s + 1, ny1 + s, nx1 + s + 1, ny - s, c);
      }
    }

  private:
};
