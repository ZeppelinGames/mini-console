//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1351.h>
//#include <SPI.h>

//#include "Display.cpp"
#include "Breakout.cpp"
#include "ControllerTest.cpp"

Display *disp = new Display();
ConsoleGame *games[] = {new ControllerTest(disp), new Breakout(disp)};
int gameCount = 0;

//0 - Selecting game / main menu
//1 - Game setup
//2 - Running game
int consoleState = 0;

ConsoleGame *currentGame;
int currGameSelection = 0;

//a,b,left,up,right,down
int btns[6] = {26, 27, 32, 33, 25, 14};
bool btnVals[6];

////Screen setup
//#define SCREEN_WIDTH  128
//#define SCREEN_HEIGHT 128 // Change this to 96 for 1.27" OLED.

//#define SCLK_PIN 18
//#define MOSI_PIN 23
//#define DC_PIN   16
//#define CS_PIN   17
//#define RST_PIN  5
//
//Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);
//
//#define BLACK           0x0000
//#define BLUE            0x001F
//#define RED             0xF800
//#define GREEN           0x07E0
//#define CYAN            0x07FF
//#define MAGENTA         0xF81F
//#define YELLOW          0xFFE0
//#define WHITE           0xFFFF

void setup() {
  Serial.begin(115200);
  Serial.println("Serial connection established");

  gameCount = 0;
  for (ConsoleGame *game : games) {
    Serial.print("Loaded game: ");
    Serial.println(game->GameName().c_str());
    gameCount++;
  }

  for (int i = 0; i < 6; i++) {
    pinMode(btns[i], INPUT_PULLUP);
  }

  disp->disp.begin();
  disp->disp.fillScreen(BLACK);
  
  RedrawGames();
  //lcdTestPattern();
}

void loop() {
  HandleInputs();

  switch (consoleState) {
    case 0: {
        //Select game
        if (btnVals[0]) {
          currentGame = games[currGameSelection];
          consoleState = 1;
        }

        //Move selection up
        if (btnVals[3]) {
          currGameSelection = currGameSelection + 1 > gameCount - 1 ? 0 : currGameSelection + 1;
          RedrawGames();
        }

        //Move selection down
        if (btnVals[5]) {
          currGameSelection = currGameSelection - 1 < 0 ? gameCount - 1 : currGameSelection - 1;
          RedrawGames();
        }
        break;
      }
    case 1: {
        if (currentGame != NULL) {
          currentGame->Setup();
          consoleState = 2;
        } else {
          consoleState = 0;
          RedrawGames();
        }
        break;
      }
    case 2: {
        currentGame->Draw();

        if (btnVals[0] && btnVals[1]) {
          disp->disp.fillScreen(BLACK);
          consoleState = 0;
          RedrawGames();
        }
        break;
      }
  }
}

void RedrawGames() {
  int i = 0;
  int y = 0;
  for (ConsoleGame *game : games) {
    disp->disp.fillRect(1, y, 128, 16, BLACK);
    drawText(((i == currGameSelection ? "- " : "") + game->GameName()).c_str(), 1, y, (i == currGameSelection) ? YELLOW : WHITE);
    y += 18;
    i++;
  }
}

void HandleInputs() {
  for (int i = 0; i < 6; i++) {
    int val = digitalRead(btns[i]);
    btnVals[i] = val == LOW;
    if (val == LOW) {
      Serial.print(btns[i]);
      Serial.println(" DOWN");
    }
  }

  if (currentGame != NULL) {
    currentGame->UpdateInputs(btnVals);
  }
}

void drawText(char const* text, int posX, int posY, uint16_t color) {
  disp->disp.setCursor(posX, posY);
  disp->disp.setTextColor(color);
  disp->disp.print(text);
}

void lcdTestPattern() {
  const uint16_t colors[] = { RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, BLACK, WHITE };

  for (uint8_t c = 0; c < 8; c++) {
    disp->disp.fillRect(0, SCREEN_HEIGHT * c / 8, SCREEN_WIDTH, SCREEN_HEIGHT / 8, colors[c]);
  }
}
