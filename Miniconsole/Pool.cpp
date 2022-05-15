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

    void Setup() {
    }

    void Draw() {
    }

  private:
};
