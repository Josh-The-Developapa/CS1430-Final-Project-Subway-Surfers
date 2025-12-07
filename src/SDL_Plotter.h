/*
 * SDL_Plotter.h
 *
 * Version 3.1
 * Add: color and point constructors
 * 12/14/2022
 *
 * Version 3.0
 * 5/31/2022
 *
 * Version 2.4
 * 4/4/2022
 *
 * Version 2.3
 *  6/28/2021
 *
 * Version 2.2
 *  4/26/2019
 *
 *  Dr. Booth
 */

#ifndef SDL_PLOTTER_H_
#define SDL_PLOTTER_H_

// OSX Library
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_thread.h>

// Windows Library
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>

#include <string.h>

#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;

const char UP_ARROW = 1;
const char DOWN_ARROW = 2;
const char LEFT_ARROW = 3;
const char RIGHT_ARROW = 4;
const int RED_SHIFT = 65536;
const int GREEN_SHIFT = 256;
const int BLUE_SHIFT = 1;
const int ALPHA_SHIFT = 16777216;
const int WHITE = 255;
const int MAX_THREAD = 100;

// Point
struct point {
    int x, y;
    point() {
        x = y = 0;
    }

    point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

// Color
struct color {
    unsigned int R, G, B;
    color() {
        R = G = B = 0;
    }

    color(int r, int g, int b) {
        R = r;
        G = g;
        B = b;
    }
};

// Threaded Sound Function
struct param {
    bool play;
    bool running;
    bool pause;
    SDL_Thread* threadID;
    SDL_cond* cond;
    SDL_mutex* mut;
    string name;

    param() {
        play = false;
        running = false;
        pause = false;
        cond = nullptr;
        mut = nullptr;
        threadID = nullptr;
        name = "";
    }
};

class SDL_Plotter {
   private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Window* window;
    Uint32* pixels;
    const Uint8* currentKeyStates;
    SDL_Event event;
    int row, col;
    bool quit;

    // Keyboard Stuff
    queue<char> key_queue;

    // Mouse Stuff
    queue<point> click_queue;

    // Sound Stuff
    bool SOUND;
    int soundCount;
    map<string, param> soundMap;

    // description: converts SDL keyboard event to char
    // return: char of key pressed
    // precondition: event is valid
    // postcondition: char representation of key returned
    char getKeyPress(SDL_Event& event);

public:
    // description: makes SDL_Plotter window
    // return: N/A (constructor)
    // precondition: SDL2 installed
    // postcondition: window created, sound initialized if WITH_SOUND true
    SDL_Plotter(int r = 480, int c = 640, bool WITH_SOUND = true);

    // description: cleans up SDL_Plotter
    // return: N/A (destructor)
    // precondition: object exists
    // postcondition: SDL stuff freed, window closed
    ~SDL_Plotter();

    // description: refreshes screen with pixel buffer
    // return: void
    // precondition: window initialized
    // postcondition: screen updated, events handled
    void update();

    // description: check if user wants to quit
    // return: bool quit status
    // precondition: object exists
    // postcondition: quit flag returned
    bool getQuit();

    // description: set quit flag
    // return: void
    // precondition: object exists
    // postcondition: quit set to flag
    void setQuit(bool flag);

    // description: see if key was pressed
    // return: bool if key available
    // precondition: object exists
    // postcondition: true if keys in queue
    bool kbhit();

    // description: see if mouse was clicked
    // return: bool if click happened
    // precondition: object exists
    // postcondition: true if clicks in queue
    bool mouseClick();

    // description: get key from queue
    // return: char of key
    // precondition: kbhit is true
    // postcondition: key removed from queue and returned
    char getKey();

    // description: get mouse click location
    // return: point with click coords
    // precondition: mouseClick is true
    // postcondition: click removed from queue and returned
    point getMouseClick();

    // description: draw pixel with RGB values
    // return: void
    // precondition: x,y in bounds, r,g,b between 0-255
    // postcondition: pixel colored at x,y
    void plotPixel(int x, int y, int r, int g, int b);

    // description: draw pixel at point with RGB
    // return: void
    // precondition: p in bounds, r,g,b between 0-255
    // postcondition: pixel colored at point
    void plotPixel(point p, int r, int g, int b);

    // description: draw pixel with color struct
    // return: void
    // precondition: x,y in bounds
    // postcondition: pixel colored at x,y
    void plotPixel(int x, int y, color = color{});

    // description: draw pixel at point with color struct
    // return: void
    // precondition: p in bounds
    // postcondition: pixel colored at point
    void plotPixel(point p, color = color{});

    // description: make screen black
    // return: void
    // precondition: window initialized
    // postcondition: all pixels black
    void clear();

    // description: get window height
    // return: int rows
    // precondition: object exists
    // postcondition: row returned
    int getRow();

    // description: get window width
    // return: int columns
    // precondition: object exists
    // postcondition: col returned
    int getCol();

    // description: load sound file
    // return: void
    // precondition: sound file exists, SOUND enabled
    // postcondition: sound in soundMap ready to use
    void initSound(string sound);

    // description: play loaded sound
    // return: void
    // precondition: sound initialized
    // postcondition: sound playing on thread
    void playSound(string sound);

    // description: stop sound and free it
    // return: void
    // precondition: sound in soundMap
    // postcondition: sound thread ended, memory freed
    void quitSound(string sound);

    // description: wait for ms milliseconds
    // return: void
    // precondition: ms >= 0
    // postcondition: execution paused for ms milliseconds
    void Sleep(int ms);

    // description: check if mouse button pressed
    // return: bool if button down
    // precondition: object exists
    // postcondition: x,y have mouse coords if true
    bool getMouseDown(int& x, int& y);

    // description: check if mouse button released
    // return: bool if button up
    // precondition: object exists
    // postcondition: x,y have mouse coords if true
    bool getMouseUp(int& x, int& y);

    // description: check if mouse moving
    // return: bool if mouse moved
    // precondition: object exists
    // postcondition: x,y have mouse coords if true
    bool getMouseMotion(int& x, int& y);

    // description: get where mouse is
    // return: void
    // precondition: object exists
    // postcondition: x,y have mouse coords
    void getMouseLocation(int& x, int& y);

    // description: get color of pixel
    // return: Uint32 color value
    // precondition: x,y in bounds
    // postcondition: color at x,y returned
    Uint32 getColor(int x, int y);
};

#endif  // SDL_PLOTTER_H_
