#include <functional>
#include <utility>

class Shape {
 public:
  Shape() {}
  virtual void draw(/** **/) const      = 0;
  virtual void serialize(/** **/) const = 0;
};

// uses template instead of having to deal with pointers and questions of ownerhsip
// in this case a functional probably makes more sense than a template...
template <typename DrawCircleStrategy>
class Circle : public Shape {
 public:
  explicit Circle(double radius)
      : radius_{radius}  // , ... other data members
  {}

  double radius() const noexcept { return radius_; }

  void   draw(/*...*/) const override { DrawCircleStrategy{}(*this /*,...*/); }
  void   serialize(/*...*/) const override;

 private:
  double radius_;
  // other data members
};
