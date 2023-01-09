/*=============================================================================
	launch.cpp: basic framework
	Copyright 2018 Dragonslake, LLC. All Rights Reserved.
=============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Framework.h"
#include "logger.hpp"


static SDL_Renderer *g_renderer;

static int g_width = 800;
static int g_height = 600;
static bool g_fullscreen = false;
static int g_framework_initialized = true;

FRAMEWORK_API Sprite::~Sprite()
{
	SDL_assert(g_framework_initialized);
	SDL_DestroyTexture(_tex);
}

FRAMEWORK_API Sprite::Sprite(const char* path) 
	: _w(0), _h(0), _tex(nullptr)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);

	SDL_Texture* texture = IMG_LoadTexture(g_renderer, path);
	if (!texture) {
		CORE_LOG_ERROR("Couldn't load {}: {}\n", path, SDL_GetError());
	}

	SDL_QueryTexture(texture, NULL, NULL, &_w, &_h);
	_tex = texture;
}

FRAMEWORK_API void Sprite::drawSprite(int x, int y)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);

	SDL_Rect r;
	r.w = _w;
	r.h = _h;
	r.x = x;
	r.y = y;
	SDL_RenderCopy(g_renderer, _tex, NULL, &r);
}

FRAMEWORK_API void getScreenSize(int& w, int &h)
{
	SDL_assert(g_framework_initialized);
	SDL_assert(g_renderer);

	SDL_Rect viewport;
	SDL_RenderGetViewport(g_renderer, &viewport);
	w = viewport.w;
	h = viewport.h;
}

FRAMEWORK_API unsigned int getTickCount()
{
	return SDL_GetTicks();
}

FRAMEWORK_API void showCursor(bool bShow)
{
	SDL_ShowCursor(bShow?1:0);
}

bool GKeyState[(int)FRKey::COUNT] = {};

FRAMEWORK_API Framework::Framework(int width, int height, bool fullscreen)
{
	g_width = width;
	g_height = height;
	g_fullscreen = fullscreen;
}

FRAMEWORK_API int run(Framework* framework)
{
	initLogger();

    SDL_Window *window;
    Uint32 flags;
    int done;
    SDL_Event event;

	for (int i = 0; i < (int)FRKey::COUNT; ++i)
	{
		GKeyState[i] = false;
	}

	Framework* GFramework = framework;

    flags = SDL_WINDOW_HIDDEN;
	if (g_fullscreen) {
		SDL_ShowCursor(0);
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL_Init(SDL_INIT_VIDEO) failed: %s\n", SDL_GetError());
        return(2);
    }

    if (SDL_CreateWindowAndRenderer(0, 0, flags, &window, &g_renderer) < 0) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer() failed: %s\n", SDL_GetError());
        return(2);
    }

	{
        /* Show the window */
        SDL_SetWindowTitle(window, GFramework->GetTitle());
        SDL_SetWindowSize(window, g_width, g_height);
        SDL_ShowWindow(window);

		g_framework_initialized = true;


		if (!GFramework->Init())
		{
			fprintf(stderr, "Framework::Init failed\n");
			SDL_Quit();
			exit(1);
		}

        done = 0;
        while ( ! done ) {
            while ( SDL_PollEvent(&event) ) {
                switch (event.type) {
                    case SDL_KEYUP:
                        switch (event.key.keysym.sym) {
                            case SDLK_RIGHT:
                            case SDLK_LEFT:
                            case SDLK_DOWN:
                            case SDLK_UP:
							{
								int key_index = (event.key.keysym.sym - SDLK_RIGHT);
								if (GKeyState[key_index])
								{
									GFramework->onKeyReleased((FRKey)key_index);
									GKeyState[key_index] = false;
								}
								break;
							}
                            case SDLK_ESCAPE:
								done = 1;
                            break;
	                        default:
		                        break;
                        }
                        break;
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym) {
						case SDLK_RIGHT:
						case SDLK_LEFT:
						case SDLK_DOWN:
						case SDLK_UP:
						{
							int key_index = (event.key.keysym.sym - SDLK_RIGHT);
							if (!GKeyState[key_index])
							{
								GFramework->onKeyPressed((FRKey)key_index);
								GKeyState[key_index] = true;
							}
						}
							break;

						default:
							break;
						}
						break;
                    case SDL_MOUSEBUTTONDOWN:
						if (event.button.button <= SDL_BUTTON_RIGHT) {
							GFramework->onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), false);
						}
						break;
                    case SDL_MOUSEBUTTONUP:
						if (event.button.button <= SDL_BUTTON_RIGHT) {
							GFramework->onMouseButtonClick((FRMouseButton)(event.button.button - SDL_BUTTON_LEFT), true);
						}
                        break;
					case SDL_MOUSEMOTION:
						GFramework->onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                        break;
                    case SDL_QUIT:
                        done = 1;
                        break;
                    default:
                        break;
                }
            }

			SDL_RenderClear(g_renderer);

			SDL_Rect viewport;
			SDL_RenderGetViewport(g_renderer, &viewport);

			/* Draw a gray background */
			SDL_SetRenderDrawColor(g_renderer, 0xA0, 0xA0, 0xA0, 0xFF);
			SDL_RenderClear(g_renderer);

			done |= GFramework->Tick() ? 1 : 0;

            SDL_RenderPresent(g_renderer);

            SDL_Delay(1);
        }
    }

	GFramework->Close();

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(window);

	//g_framework_initialized = false;

    /* We're done! */
    SDL_Quit();
    return(0);
}
