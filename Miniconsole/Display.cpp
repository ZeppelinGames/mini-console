#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128 // Change this to 96 for 1.27" OLED.

// Screen setup
#define SCLK_PIN 18
#define MOSI_PIN 23
#define DC_PIN 16
#define CS_PIN 17
#define RST_PIN 5

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

class Display
{
  public:
    Adafruit_SSD1351 disp = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

    void DrawLine(int x1, int y1, int x2, int y2, int c)
    {
      disp.drawLine(x1, y1, x2, y2, c);
    }

    void DrawRect(int x, int y, int scaleX, int scaleY, int c)
    {
      disp.drawRect(x, y, scaleX, scaleY, c);
    }

    int RandomColour()
    {
      int rndIndex = random(6);
      switch (rndIndex)
      {
        case 0:
          return BLUE;
          break;
        case 1:
          return RED;
          break;
        case 2:
          return GREEN;
          break;
        case 3:
          return CYAN;
          break;
        case 4:
          return MAGENTA;
          break;
        case 5:
          return YELLOW;
          break;
      }
    }

  private:

};
