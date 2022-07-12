#include "ConsoleGame.cpp"

class NotDoom : public ConsoleGame {
    using ConsoleGame::ConsoleGame;

  public:
    std::string GameName() {
      return "Not Doom";
    }
    std::string GameDesc() {
      return "A raycaster";
    }

    //Player position
    double px = 128;
    double py = 128;

    //Movement deltas
    double pdx = 0;
    double pdy = 0;

    //Player angle (rotation)
    double pa = 0;

    double moveSpeed = 10;
    double rotateSpeed = 5;

    //Map
    const int gridSize = 8;
    const int hGridSize = (int)(gridSize / 2);

    int levelSizeX = 8;
    int levelSizeY = 8;
    int levelSize = levelSizeX * levelSizeY;
    int level[64] = {
      1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
    };

    int wallClearX[64];
    int wallClearY[64];
    int wallClearH[64];

    int wallDrawX[64];
    int wallDrawY[64];
    int wallDrawH[64];
    int wallDrawC[64];

    void Setup() {
      disp->disp.fillScreen(BLACK);

      UpdateRotation();
      DrawRays();
      DrawRays();
      DrawMiniMap();
    }

    void Draw() {
      bool updated = HandleInput();
      if (updated) {
        DrawRays();
        DrawMiniMap();
      }
      disp->DisplayFPS();
    }

    bool HandleInput() {
      bool hasUpdated = false;
      if (LEFT()) {
        pa += rotateSpeed;
        UpdateRotation();

        hasUpdated = true;
      }
      if (RIGHT()) {
        pa -= rotateSpeed;
        UpdateRotation();

        hasUpdated = true;
      }
      if (UP()) {
        px += (pdx * moveSpeed);
        py += (pdy * moveSpeed);

        hasUpdated = true;
      }
      if (DOWN()) {
        px -= (pdx * moveSpeed);
        py -= (pdy * moveSpeed);

        hasUpdated = true;
      }

      return hasUpdated;
    }

    void UpdateRotation() {
      pa = FixAng(pa);
      pdx = cos(degToRad(pa));
      pdy = -sin(degToRad(pa));
    }

    void DrawMiniMap() {
      for (int i = 0; i < levelSize; i++) {
        if (level[i] > 0) {
          disp->disp.fillRect((i % levelSizeX) * 2 + (128 - (levelSizeX * 2)), (i / levelSizeX) * 2, 2, 2, YELLOW);
        }
      }
    }

    void DrawRays()
    {
      //disp->disp.fillScreen(BLACK); slow af
      for (int i = 0; i < 64; i++) {
        if (wallClearH[i] > 0) {
          disp->disp.fillRect(wallClearX[i], wallClearY[i] - 1, 8, wallClearH[i] + 2, BLACK);
          wallClearH[i] = 0;
        }
        if (wallDrawH[i] > 0) {
          disp->disp.fillRect(wallDrawX[i], wallDrawY[i], 8, wallDrawH[i], wallDrawC[i]);
          wallClearX[i] = wallDrawX[i];
          wallClearY[i] = wallDrawY[i];
          wallClearH[i] = wallDrawH[i];

          wallDrawH[i] = 0;
        }
      }

      int wClear = 0;
      int wDraw = 0;
      int r, mx, my, mp, dof, side;
      double vx, vy, rx, ry, ra, xo, yo, disV, disH;

      ra = FixAng(pa + 30); //ray set back 30 degrees

      for (r = 0; r < 60; r++)
      {
        //---Vertical---
        dof = 0;
        side = 0;
        disV = 10000;
        double Tan = tan(degToRad(ra));
        if (cos(degToRad(ra)) > 0.001) {
          rx = (((int)px >> 6) << 6) + 64;       //looking left
          ry = (px - rx) * Tan + py;
          xo = 64;
          yo = -xo * Tan;
        }
        else if (cos(degToRad(ra)) < -0.001) {
          rx = (((int)px >> 6) << 6) - 0.0001;  //looking right
          ry = (px - rx) * Tan + py;
          xo = -64;
          yo = -xo * Tan;
        }
        else {
          rx = px;  //looking up or down. no hit
          ry = py;
          dof = 8;
        }

        while (dof < 8)
        {
          mx = (int)(rx) >> 6;
          my = (int)(ry) >> 6;
          mp = my * levelSizeX + mx;

          if (mp > 0 && mp < levelSize && level[mp] > 0) {
            dof = 8;  //hit
            disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
          }
          else {
            rx += xo;  //check next horizontal
            ry += yo;
            dof += 1;
          }
        }
        vx = rx; vy = ry;

        //---Horizontal---
        dof = 0;
        disH = 10000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001) {
          ry = (((int)py >> 6) << 6) - 0.0001;  //looking up
          rx = (py - ry) * Tan + px;
          yo = -64;
          xo = -yo * Tan;
        }
        else if (sin(degToRad(ra)) < -0.001) {
          ry = (((int)py >> 6) << 6) + 64;       //looking down
          rx = (py - ry) * Tan + px;
          yo = 64;
          xo = -yo * Tan;
        }
        else {
          rx = px;  //looking straight left or right
          ry = py;
          dof = 8;
        }

        while (dof < 8)
        {
          mx = (int)(rx) >> 6;
          my = (int)(ry) >> 6;
          mp = (my * levelSizeX) + mx;

          if (mp > 0 && mp < levelSize && level[mp] > 0) {
            dof = 8;  //hit
            disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
          }
          else {
            rx += xo;  //check next horizontal
            ry += yo;
            dof += 1;
          }
        }

        int wallColour = disp->RGB(0, 0, 255);
        if (disV < disH) {
          rx = vx;  //horizontal hit first
          ry = vy;
          disH = disV;
          wallColour = disp->RGB(0, 0, 127);
        }

        int ca = FixAng(pa - ra);
        disH = disH * cos(degToRad(ca)); //fix fisheye

        int lineH = (levelSize * 127) / (disH); if (lineH > 127) {
          lineH = 127; //line height and limit
        }
        int lineOff = 64 - (lineH >> 1);                                             //line offset

        //glLineWidth(8); glBegin(GL_LINES); glVertex2i(); glVertex2i(); glEnd(); //draw vertical wall
        //disp->disp.fillRect(wallClearX[mp], 0, 8, 128, BLACK);
        if (lineH > 1) {
          //disp->disp.fillRect(r * 8, lineOff, 8, lineH, wallColour);
          wallDrawX[wDraw] = r * 8;
          wallDrawY[wDraw] = lineOff;
          wallDrawH[wDraw] = lineH;
          wallDrawC[wDraw] = wallColour;
          wDraw++;
        }

        //        wallClearX[wClear] = r * 8;
        //        wallClearY[wClear] = lineOff;
        //        wallClearH[wClear] = lineH;
        //        wClear++;

        ra = FixAng(ra - 0.5); //go to next ray
      }
    }
    //
    //    void Render() {
    //      for (int i = 0; i < levelSizeX * levelSizeY; i++) {
    //        if (level[i] > 0) {
    //          Vector2* basePos = new Vector2((i % levelSizeX) * gridSize, (i / levelSizeX) * gridSize);
    //          Vector2* verts[4] = {
    //            basePos,
    //            basePos->Add(new Vector2(gridSize, 0)),
    //            basePos->Add(new Vector2(0, gridSize)),
    //            basePos->Add(new Vector2(gridSize, gridSize))
    //          };
    //
    //          double vertDists[4];
    //
    //          int useVertsCount = 0;
    //          int useVerts[3];
    //
    //          for (int i = 0; i < 4; i++) {
    //            vertDists[i] = verts[i]->FDist(px, py);
    //
    //            double cDist = 0;
    //            bool col = false;
    //
    //            //0: no isssue
    //            //1: check dist > actualDist
    //            //2: Collision with check box
    //            int check = 0;
    //
    //            Vector2* stepVec = (verts[i]->Normalised())->Mul(hGridSize);
    //            Vector2* startVec = new Vector2(px, py);
    //
    //            while (check > 0) {
    //              cDist = startVec->FDist(px, py);
    //              if (startVec->x < basePos->x + gridSize && startVec->x > basePos->x) {
    //                if (startVec->y < basePos->y + gridSize && startVec->y > basePos->y) {
    //                  check = 2;
    //                }
    //              }
    //              if (cDist > vertDists[i]) {
    //                check = 1;
    //              }
    //
    //              startVec = startVec->Add(stepVec);
    //            }
    //
    //            if (check == 1) {
    //              useVerts[useVertsCount] = i;
    //              useVertsCount++;
    //            }
    //          }
    //
    //          for (int i = 0; i < useVertsCount; i++) {
    //            //draw that shit
    //          }
    //        }
    //      }
    //    }

    double distance(double ax, double ay, double bx, double by, double ang) {
      return cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay);
    }

    double degToRad(int a) {
      return a * PI / 180.0;
    }
    int FixAng(int a) {
      if (a > 359) {
        a -= 360;
      } if (a < 0) {
        a += 360;
      } return a;
    }

  private:

};
