#include "Particles.hpp"

Particle::Particle(float pX, float pY, float pXDirection, float pYDirection)
:x(pX), y(pY), xDirection(pXDirection), yDirection(pYDirection)
{

}

void Particle::update(int xLimit, int yLimit)
{   
   x += xDirection;
   y += yDirection;

   if(x > xLimit){
       x = rand() % xLimit;
   }

   if(y > yLimit){
       y = rand() % yLimit;
   }
}

int Particle::getX()
{
    return x;
}

int Particle::getY()
{
    return y;
}


