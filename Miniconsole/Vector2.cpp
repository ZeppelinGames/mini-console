#include <cmath>

class Vector2 {
  public:
    double x;
    double y;

    Vector2() {
      this->x = 0;
      this->y = 0;
    }

    Vector2(double x, double y) {
      this->x = x;
      this->y = y;
    }

    Vector2* Add(Vector2* v) {
      return new Vector2(this->x + v->x, this->y + v->y);
    }
    Vector2* Mul(Vector2* v) {
      return new Vector2(this->x * v->x, this->y * v->y);
    }
    Vector2* Mul(double m) {
      return new Vector2(this->x * m, this->y * m);
    }

    double FDist(Vector2* v) {
      return ((this->x - v->x) * (this->x - v->x)) + ((this->y - v->y) * (this->y - v->y));
    }

    double FDist(double x, double y) {
      return ((this->x - x) * (this->x - x)) + ((this->y - y, 2) * (this->y - y));
    }

    double Dist(Vector2* v) {
      return sqrt(FDist(v));
    }

    void Normalise() {
      double h = hypot(this->x, this->y);
      this->x /= h;
      this->y /= h;
    }

    Vector2* Normalised() {
      double h = hypot(this->x, this->y);
      return new Vector2(this->x / h, this->y / h);
    }
};
