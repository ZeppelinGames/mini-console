//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1351.h>
//#include <SPI.h>

//#include "Display.cpp"

//Include new games here
#include "Breakout.cpp"
#include "ControllerTest.cpp"
#include "Pool.cpp"

Display *disp = new Display();

//Add new games here
ConsoleGame *games[] = {
  new ControllerTest(disp),
  new Breakout(disp),
  new Pool(disp)
};
int gameCount = 0;

//0 - Selecting game / main menu
//1 - Game setup
//2 - Running game
int consoleState = 0;

ConsoleGame *currentGame;
int currGameSelection = 0;

//a,b,left,up,right,down
int btns[6] = {14, 27, 33, 25, 26, 12};
int lastMillis[6] = {0, 0, 0, 0, 0, 0};
bool btnVals[6];

int lastFrame = 0;

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

void IRAM_ATTR ISR_0() {
  HandleInput(0);
}
void IRAM_ATTR ISR_1() {
  HandleInput(1);
}
void IRAM_ATTR ISR_2() {
  HandleInput(2);
}
void IRAM_ATTR ISR_3() {
  HandleInput(3);
}
void IRAM_ATTR ISR_4() {
  HandleInput(4);
}
void IRAM_ATTR ISR_5() {
  HandleInput(5);
}

void HandleInput(int i) {
  if (millis() - lastMillis[i] > 10) {
    btnVals[i] = !btnVals[i];

    if (currentGame != NULL) {
      currentGame->UpdateInput(i, btnVals[i]);
    }
  }
  lastMillis[i] = millis();
}

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
    btnVals[i] = false;
  }

  attachInterrupt(btns[0], ISR_0, CHANGE);
  attachInterrupt(btns[1], ISR_1, CHANGE);
  attachInterrupt(btns[2], ISR_2, CHANGE);
  attachInterrupt(btns[3], ISR_3, CHANGE);
  attachInterrupt(btns[4], ISR_4, CHANGE);
  attachInterrupt(btns[5], ISR_5, CHANGE);

  disp->disp.begin();
  disp->disp.fillScreen(BLACK);

  RedrawGames();
  //lcdTestPattern();
}

void loop() {
  //HandleInputs();

  switch (consoleState) {
    case 0: {
        //Select game
        if (btnVals[0]) {
          currentGame = games[currGameSelection];
          currentGame->UpdateInputs(btnVals);
          consoleState = 1;
        }

        //Move selection up
        if (btnVals[5]) {
          currGameSelection = currGameSelection + 1 > gameCount - 1 ? 0 : currGameSelection + 1;
          RedrawGames();
        }

        //Move selection down
        if (btnVals[3]) {
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
        if (millis() - lastFrame > 2) {
          lastFrame = millis();
          currentGame->Draw();
        }

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

void drawText(char const * text, int posX, int posY, uint16_t color) {
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
