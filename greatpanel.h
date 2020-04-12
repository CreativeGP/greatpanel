#ifndef GREATPANEL_H
/* ========================================================================
   $File: greatpanel.h $
   $Date: Apr 04 2020 $
   $Revision: $
   $Creator: Creative GP $
   $Notice: (C) Copyright 2020 by Creative GP. All Rights Reserved. $
   ======================================================================== */

#include <iostream>
#include <string>

#include <thread>
#include <atomic>

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <unistd.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask  0xff000000
#define gmask  0x00ff0000
#define bmask  0x0000ff00
#define amask  0x000000ff
#else
#define rmask  0x000000ff
#define gmask  0x0000ff00
#define bmask  0x00ff0000
#define amask  0xff000000
#endif


namespace GreatPanel {
    
    struct XY {
        int x, y;
    };

    class Component {
    public:
        Component() {}
        Component(int w, int h) : size(XY{w,h})
        {
            surface = SDL_CreateRGBSurface(0,w,h,32,rmask,gmask,bmask,amask);
        }
        Component(int x, int y, int w, int h) : pos(XY{x,y}), size(XY{w,h})
        {
            surface = SDL_CreateRGBSurface(0,w,h,32,rmask,gmask,bmask,amask);
        }
        ~Component() {
            free_surface();
            surface = 0;
        }
        
        virtual void update() {
            if (surface) free_surface();
            surface = SDL_CreateRGBSurface(0,size.x,size.y,8,rmask,gmask,bmask,amask);

            *changed = true;
        }
        virtual void blit(SDL_Surface *dst) {
            SDL_Rect tmp {pos.x,pos.y,size.x,size.y};
            std::cout << pos.x << " " << pos.y << " " << size.x << " " << size.y << " ";
            SDL_BlitSurface(surface, 0, dst, &tmp);
        }
        void free_surface() { SDL_FreeSurface(surface); surface = 0; }
        uint32_t *pixels() { return (uint32_t *) surface->pixels; }

        SDL_Surface *surface = 0;
        XY pos, size;
        bool *changed;
    };

//     class Paragraph : public Component {
//     public:
//         Paragraph(std::string ttf_file_name) {
// //            font = 
//         }
//         ~Paragraph() {
//             TTF_CloseFont(font); font = 0;
//         }
//         void update() override {
//             if (surface) free_surface();
//             surface = TTF_RenderText_Solid(Sans, text, White);
//         }
        
//         std::string text;
//     private:
//         TTF_Font *font;
//     };

    class Container : public Component {
    public:
        
    private:
        std::vector<Component> components;
    };

    class Canvas : public Component {
    public:
        Canvas(int x, int y) : Component(x,y) {}
        Canvas(int x, int y, int w, int h) : Component(x,y,w,h) {}
    };
    
    class Panel {
    public:
        Panel() {}
        ~Panel() { close(); }

        bool init(int width, int height, std::string title);
        void open();
        void close();
//        void load_xml(std::string filename);
    
        XY size;
        std::atomic<bool> running = false;
        std::atomic<int> fps = 30;
        std::thread loop;
        SDL_Surface *surface = 0;
    private:
        std::atomic<SDL_Window*> window = 0;
    };
}

#define GREATPANEL_H
#endif
