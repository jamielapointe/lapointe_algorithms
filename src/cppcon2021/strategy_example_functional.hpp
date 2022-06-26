#include <functional>
#include <utility>

class Shape {
 public:
  Shape() {}
  virtual void draw(/** **/) const      = 0;
  virtual void serialize(/** **/) const = 0;
};

class Circle;

// uses functional instead of having to deal with pointers and questions of ownerhsip
using DrawCircleStrategy = std::function<void(Circle const&)>;

class Circle : public Shape {
 public:
  Circle(double radius, DrawCircleStrategy strategy)
      : radius_{radius},
        // .. other data members,
        drawing_{std::move(strategy)} {}

  double radius() const noexcept { return radius_; }

  void   draw(/*...*/) const override { drawing_(*this /*,...*/); }
  void   serialize(/*...*/) const override;

 private:
  double             radius_;
  // other data members
  DrawCircleStrategy drawing_;
};
