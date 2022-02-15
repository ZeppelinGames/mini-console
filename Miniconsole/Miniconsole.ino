#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#include "Breakout.cpp"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128 // Change this to 96 for 1.27" OLED.

ConsoleGame *games[] = {new Breakout()};
int gameCount = 0;

//0 - Selecting game / main menu
//1 - Game setup
//2 - Running game
int consoleState = 0;

ConsoleGame *currentGame;
int currGameSelection = 0;

#define SCLK_PIN 18
#define MOSI_PIN 23
#define DC_PIN   16
#define CS_PIN   17
#define RST_PIN  5

Adafruit_SSD1351 oled = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

void setup() {
  Serial.begin(115200);
  Serial.println("Serial connection established");

  gameCount = 0;
  for (ConsoleGame *game : games) {
    Serial.print("Loaded game: ");
    Serial.println(game->GameName().c_str());
    gameCount++;
  }

  oled.begin();
  oled.fillScreen(BLACK);
  //lcdTestPattern();
}

void loop() {
  switch (consoleState) {
    case 0: {
        int i = 0;
        int y = 0;
        for (ConsoleGame *game : games) {
          drawText(((i == currGameSelection ? "- " : "") + game->GameName()).c_str(), 1, y, (i==currGameSelection) ? YELLOW : WHITE);
          y += 25;
          i++;
        }
        break;
      }
    case 1: {
        if (currentGame != NULL) {
          currentGame->Setup();
          consoleState = 2;
        } else {
          consoleState = 0;
        }
        break;
      }
    case 2: {
        //      for (int pinBind : currentGame->analoguePinBindings) {
        //        //currentGame->AnaloguePinUpdate(pinBind, analogRead(pinBind));
        //      }
        //      for (int pinBind : currentGame->digitalPinBindings) {
        //        //currentGame->DigitalPinUpdate(pinBind, digitalRead(pinBind));
        //      }
        //currentGame->Draw();

        break;
      }
  }
}

void drawText(char const* text, int posX, int posY, uint16_t color) {
  oled.setCursor(posX, posY);
  oled.setTextColor(color);
  oled.print(text);
}

void lcdTestPattern() {
  const uint16_t colors[] = { RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, BLACK, WHITE };

  for (uint8_t c = 0; c < 8; c++) {
    oled.fillRect(0, SCREEN_HEIGHT * c / 8, SCREEN_WIDTH, SCREEN_HEIGHT / 8, colors[c]);
  }
}
