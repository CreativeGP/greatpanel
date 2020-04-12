/* ========================================================================
   $File: greatpanel.cpp $
   $Date: Apr 04 2020 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2020 by Creative GP. All Rights Reserved. $
   ======================================================================== */

#include "greatpanel.h"

using namespace GreatPanel;


bool Panel::init(int width, int height, std::string title) {
    bool success = true;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    
    window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        size = XY {width, height};
        surface = SDL_GetWindowSurface( window );
    }

    return success;
}

void Panel::close() {
    running = false;
    
    if (loop.joinable()) loop.join();

    if (surface)
        SDL_FreeSurface(surface);
    surface = 0;
    
    if (window)
        SDL_DestroyWindow(window);
    window = 0;

    SDL_Quit();
}


void Panel::open() {
    running = true;

    loop = std::thread([this] {
        while (running) {
            SDL_UpdateWindowSurface(window);
            SDL_Delay(1000/fps);
        }
    });
}

// bool Panel::load_xml_file(std::string filename) {
//     using namespace boost::property_tree;

//     ptree pt;
//     read_xml(filename, pt);
// }


// void Panel::update() {
//     running = true;
//     SDL_UpdateWindowSurface(window);
//     // TODO: 他の処理を考慮する
//     SDL_Delay(1000/fps);
// }

// void Panel::update_only() {
//     running = true;
//     SDL_UpdateWindowSurface(window);
// }
