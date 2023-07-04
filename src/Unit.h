// #ifndef UNIT_INCLUDED
// #define UNIT_INCLUDED

// #include <vector>
// #include <memory>

// class Unit; // forward declaration

// #include "MySDL.h"
// #include "Coord.h"

// class Unit : public Entity
// {
// public:
// Unit()
// {}

// Unit(int radius,Coord pos,Coord speed=Coord{0,0}) :
// Entity{radius,pos}, speed{speed}
// {}

// virtual ~Unit()
// {}

// virtual bool step_collide_unit(Unit* u2) = 0; // Pure virtual function

// bool step(MySDL& mySDL)
// {
// Coord prev_pos=step_move();
// bool collision=false;
// collision|=step_collide_units();
// collision|=step_collide_wall(mySDL.size());
// if (collision)
// step_reset_move(prev_pos);
// return collision;
// }

// virtual Coord step_move()
// {
// auto prev_pos=pos;
// pos+=speed;
// return prev_pos;
// }

// void step_reset_move(Coord c) { pos=c; }

// virtual bool step_collide_units()
// {
// bool collision=false;
// for (auto& u : units)
// collision|=step_collide_unit(u.get());
// return collision;
// }

// virtual bool step_collide_wall(Coord c)
// {
// bool collide=false;
// if (pos.x<0 || pos.x>c.x)
// {
// speed.x=-speed.x;
// collide=true;
// }
// if (pos.y<0 || pos.y>c.y)
// {
// speed.y=-speed.y;
// collide=true;
// }
// return collide;
// }

// void draw(MySDL& mySDL) const override
// {   filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(0,255,0)); }

// Coord speed;
// };

// #endif
#ifndef UNIT_INCLUDED
#define UNIT_INCLUDED

#include <vector>
#include <memory>

#include "Entity.h"

// Forward declaration of Unit class
class Unit;

// Forward declaration of check_collide_units function
template<typename U1,typename U2>
bool check_collide_units(U1 u1,U2 u2);

// Forward declaration of span function
bool span(std::shared_ptr<Unit> unit,std::vector< std::shared_ptr<Unit> >& units,const Coord& size);

#include "MySDL.h"
#include "Coord.h"

// Unit class definition
class Unit : public Entity
{
public:
Unit()
{}

/*! Creates a Unit
@param pos start position
@param speed start speed
*/
Unit(int radius,Coord pos,Coord speed=Coord{0,0}) :
Entity{radius,pos}, speed{speed}
{}

virtual ~Unit()
{}

// Pure virtual function for handling collision with another unit
virtual bool step_collide_unit(Unit* u2) = 0;

/*! Makes a step in time
@param mySDL for the size of the window
*/
bool step(MySDL& mySDL)
{
Coord prev_pos=step_move();
bool collision=false;
collision|=step_collide_units();
collision|=step_collide_wall(mySDL.size());
if (collision)
step_reset_move(prev_pos);
return collision;
}

virtual Coord step_move()
{
auto prev_pos=pos;
pos+=speed;
return prev_pos;
}

void step_reset_move(Coord c) { pos=c; }

virtual bool step_collide_units()
{
bool collision=false;
for (auto& u : units)
collision|=step_collide_unit(u.get());
return collision;
}

virtual bool step_collide_wall(Coord c)
{
bool collide=false;
if (pos.x<0 || pos.x>c.x)
{
speed.x=-speed.x;
collide=true;
}
if (pos.y<0 || pos.y>c.y)
{
speed.y=-speed.y;
collide=true;
}
return collide;
}

/*! Draws the Unit
@param mySDL for the size of the window
*/
void draw(MySDL& mySDL) const override
{   filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(0,255,0)); }

Coord speed;
};