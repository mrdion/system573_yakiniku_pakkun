#ifndef _MAIN_H
#define _MAIN_H
#include <psx.h>
#include <stdio.h>
#include <stdlib.h>
#include "ksys573_pad.h"
#define MODE_TITLE = 0
#define MODE_GAME = 1

int game_mode;
volatile int display_is_old;
volatile int time_counter;
GsDispEnv game_dispenv;
GsDrawEnv game_drawenv;
int game_version;
GsImage game_image;

#endif