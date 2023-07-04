
#include "Utils.h"
#include "MySDL.h"
#include "Coord.h"
#include "Player.h"
#include "Virus.h"
#include "HandleEvents.h"
#include <list>
#include <algorithm>

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

/*! @file
   The starting point of VirusGame, holds the main() function.
*/
extern "C" int main()
{
    std::cout<<"Use the cursor keys to move around\n";
    srand(time(NULL));        // seed the speudo random number generator 
    MySDL mySDL("VirusGame"); // create an SDL graphics window

    Coord window_size = mySDL.size(); // Store the window size in a variable

    Player player(window_size*0.5); // player

    const int max_nr_units=20;    // maximum number of units, feel free to change
    int nr_units=0;               // current number of units
    std::list<Virus> units;         // holds all units in the game
    double new_virus_chance=0.01; // the chance that a new virus is created each time step
    double new_virus_max_speed=3; // maximum speed of a new virus
    Coord player_pos;
    bool quit=false;
    while (!quit) // the game loop, this loops has gotten large, better split it up in multiple functions?
    {
        int ticks_start=SDL_GetTicks();
        SDL_SetRenderDrawColor(mySDL.renderer(),0,0,0,255); // black background
        SDL_RenderClear(mySDL.renderer()); // clear graphics window

        EventHandler::handleEvents(mySDL, quit);
        const Uint8* keyboardState=SDL_GetKeyboardState(NULL); // get keyboard state

        player.keyboard(keyboardState); // control the player by keyboard
        player.step(mySDL);
        player.draw(mySDL);
        player_pos = player.getPosition();
        if (rand_0_1()<new_virus_chance && nr_units<max_nr_units) // by chance create a new virus
        {
            Coord window_size=window_size;
            Coord pos  = Coord(window_size.x       * rand_0_1() ,  window_size.y       * rand_0_1() );
            Coord speed= Coord(new_virus_max_speed * rand_m1_1(),  new_virus_max_speed * rand_m1_1());
            units.push_back(Virus(pos,speed));
            nr_units+=1;
        }

        
        
        units.erase(std::remove_if(units.begin(), units.end(), [&](Virus& unit) {

            Coord pos = unit.getPosition();

            // Calculate the distance between the positions of the player and the unit
            double distance = std::sqrt(std::pow((pos.x - player_pos.x), 2) + std::pow((pos.y - player_pos.y), 2));

            // Check if the unit is inside the player circle
            if (player.kill && distance <= (player.radius + unit.radius)) {
                // The unit is inside the player circle, handle the collision here
                // ...

                return true;  // Remove the unit from the list
            }

            unit.step(mySDL);
            unit.draw(mySDL);

            return false;  // Keep the unit in the list
        }), units.end());


        
        SDL_RenderPresent(mySDL.renderer()); // update graphics window
        int frame_ticks=SDL_GetTicks()-ticks_start;
        if( frame_ticks < SCREEN_TICKS_PER_FRAME ) SDL_Delay( SCREEN_TICKS_PER_FRAME - frame_ticks ); // delay for right framerate
    }
    return 0;
}
