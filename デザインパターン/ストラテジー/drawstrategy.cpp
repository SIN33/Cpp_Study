
#include <memory>
#include <utility>
class Shape
{
 public:
   virtual ~Shape() = default;

   virtual void draw( /*some arguments*/ ) const = 0;
};



template< typename T >
class DrawStrategy
{
 public:
   virtual ~DrawStrategy() = default;
   virtual void draw( T const& ) const = 0;
};



class Circle : public Shape
{
 public:
   using DrawCircleStrategy = DrawStrategy<Circle>;

   explicit Circle( double radius, std::unique_ptr<DrawCircleStrategy> drawer )
      : radius_( radius )
      , drawer_( std::move(drawer) )
   {
   }

   void draw( /*some arguments*/ ) const override
   {
      drawer_->draw( *this /*, some arguments*/ );
   }

   double radius() const { return radius_; }

 private:
   double radius_;
   std::unique_ptr<DrawCircleStrategy> drawer_;
};


class Square : public Shape
{
 public:
   using DrawSquareStrategy = DrawStrategy<Square>;

   explicit Square( double side, std::unique_ptr<DrawSquareStrategy> drawer )
      : side_( side )
      , drawer_( std::move(drawer) )
   {
   }

   void draw( /*some arguments*/ ) const override
   {
      drawer_->draw( *this /*, some arguments*/ );
   }

   double side() const { return side_; }

 private:
   double side_;
   std::unique_ptr<DrawSquareStrategy> drawer_;
};


class Shape;

void drawAllShapes( std::vector<std::unique_ptr<Shape>> const& shapes );



void drawAllShapes( std::vector<std::unique_ptr<Shape>> const& shapes )
{
   for( auto const& shape : shapes )
   {
      shape->draw( /*some arguments*/ );
   }
}


class OpenGLCircleStrategy : public DrawStrategy<Circle>
{
 public:
   explicit OpenGLCircleStrategy( /* Drawing related arguments */ )
   {}

   void draw( Circle const& circle /*, ...*/ ) const override
   {
      // ... Implementing the logic for drawing a circle by means of OpenGL
   }

 private:
   /* Drawing related data members, e.g. colors, textures, ... */
};



class OpenGLSquareStrategy : public DrawStrategy<Square>
{
 public:
   explicit OpenGLSquareStrategy( /* Drawing related arguments */ )
   {}

   void draw( Square const& square /*, ...*/ ) const override
   {
      // ... Implementing the logic for drawing a square by means of OpenGL
   }

 private:
   /* Drawing related data members, e.g. colors, textures, ... */
};



int main()
{
   using Shapes = std::vector<std::unique_ptr<Shape>>;

   Shapes shapes{};

   // Creating some shapes, each one
   //   equipped with the according OpenGL drawing strategy
   shapes.emplace_back(
      std::make_unique<Circle>(
         2.3, std::make_unique<OpenGLCircleStrategy>(/*...red...*/) ) );
   shapes.emplace_back(
      std::make_unique<Square>(
         1.2, std::make_unique<OpenGLSquareStrategy>(/*...green...*/) ) );
   shapes.emplace_back(
      std::make_unique<Circle>(
         4.1, std::make_unique<OpenGLCircleStrategy>(/*...blue...*/) ) );

   drawAllShapes(shapes);

   return EXIT_SUCCESS;
}