#pragma once

// To use the framework define _WINDOWS in project's settings!
#if defined(_WINDOWS)
    #if defined(FRAMEWORK_PROJECT)
        #define FRAMEWORK_API extern "C" __declspec(dllexport)
    #else
        #define FRAMEWORK_API extern "C" __declspec(dllimport)
    #endif
#else
    #define FRAMEWORK_API 
#endif

class SDL_Texture;

class Sprite 
{
public:
	Sprite(const char* path);
	~Sprite();

	void drawSprite(int x, int y);
	
	void getSpriteSize(int& w, int &h)
		{ w = _w; h = _h; }

	void setSpriteSize(int w, int h)
		{ _w = w; _h = h; }

private:
	int _w, _h;
	SDL_Texture* _tex;
};

FRAMEWORK_API void getScreenSize(int& w, int &h);

// Get the number of milliseconds since library initialization.
FRAMEWORK_API unsigned int getTickCount();

FRAMEWORK_API void showCursor(bool bShow);

enum class FRKey {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class Framework {
public:

	Framework(int width, int height, bool fullscreen);
	virtual ~Framework() {};

	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual void Close() = 0;

	// return value: if true will exit the application
	virtual bool Tick() = 0;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;

	virtual void onKeyPressed(FRKey k) = 0;

	virtual void onKeyReleased(FRKey k) = 0;

	virtual const char* GetTitle() = 0;
};


FRAMEWORK_API int run(Framework*);
