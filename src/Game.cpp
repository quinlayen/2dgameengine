#include "Game.h"
#include <iostream>
#include <SDL2/SDL.h>

Game::Game()
{
    isRunning = false;
    std::cout << "Game constructor called" << std::endl;
}

Game::~Game()
{
    std::cout << "Game destructor called" << std::endl;
}

void Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
 
    //next create a pointer called window of type SDL_Window which points to a function called SDL_CreateWindow
    //first parameter is the title.  In the below case I used NULL to indicate no title
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_BORDERLESS
        );
        if (!window)
        {
            std::cerr << "Error creating SDL window" << std::endl;
            return;
        }

    //Create a renderer and pass in the window we created above as the parameter.  -1 indicates to use the default display and 0 means no flags
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "Error creating renderer" << std::endl;
        return;
    }
    isRunning = true;
}

void Game::Run()
{
    while(isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput()
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT: //When user tries to close the window
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                break;
        }
    };
}

void Game::Update()
{

}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 0 , 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}