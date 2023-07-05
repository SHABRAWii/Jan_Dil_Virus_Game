#ifndef EVENTHANDLER_INCLUDED
#define EVENTHANDLER_INCLUDED

#include "MySDL.h"
#include <iostream>

/*!
  EventHandler handles events in the game.
 */
class EventHandler
{
public:
    EventHandler() = default;
    ~EventHandler() = default;

    static void handleEvents(bool& quit);
};

void EventHandler::handleEvents(bool& quit)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        int x, y;
        switch (e.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                std::cout << "mouse down: " << x << "," << y << '\n';
                break;
        }
    }
}

#endif
