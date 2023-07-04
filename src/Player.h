#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "MySDL.h"
#include "Coord.h"

/*! The object representing the player in VirusGame
 */
class Player
{
public:
    /*! Creates the Player
      @param pos start position
     */
    static const int radius=24;
    bool kill = 0;
    Player(Coord pos) :
        pos{pos}
    {}

    /*! Handles the keyboard events
      @param keyboardState the current state (keys pressed) of the keyboard
     */
    void keyboard(const Uint8* keyboardState)
    {
        double diff_speed=0.5;
        // for others keys see: https://wiki.libsdl.org/SDL_Scancode
        if (keyboardState[SDL_SCANCODE_UP])
            speed.y-=diff_speed;
        if (keyboardState[SDL_SCANCODE_DOWN])
            speed.y+=diff_speed;
        if (keyboardState[SDL_SCANCODE_LEFT])
            speed.x-=diff_speed;
        if (keyboardState[SDL_SCANCODE_RIGHT])
            speed.x+=diff_speed;
        if(keyboardState[SDL_SCANCODE_SPACE]){
            kill = 1;
            G = B = 0;
        }else{
            kill = 0;
            G = B = 255;
        }

        // if (keyboardState[SDL_SCANCODE_A])
        speed*=0.95; // reduce speed to create some resistance
    }

    /*! Makes a step in time
      @param mySDL for the size of the window
     */
    void step(MySDL& mySDL)
    {
        pos+=speed;
        if (pos.x<0 || pos.x>mySDL.size().x)
        { speed.x=-speed.x; }
        if (pos.y<0 || pos.y>mySDL.size().y)
        { speed.y=-speed.y; }
    }

    /*! Draws the Player
      @param mySDL for the size of the window
     */
    void draw(MySDL& mySDL) const
    {   aacircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(R,G,B)); }

    /*! Returns the position of the player
     */
    Coord getPosition() const
    {
        return pos;
    }
    
private:
    int R = 255, G = 255, B = 255;
    Coord pos,speed;
};

#endif
