#include "ConsoleGame.cpp"

class GameTemplate : public ConsoleGame {
    using ConsoleGame::ConsoleGame;

  public:
    std::string GameName() {
      return "Game Template";
    }
    std::string GameDesc() {
      return "A template for games";
    }

    void Setup() {
    }

    void Draw() {
    }

  private:
};
