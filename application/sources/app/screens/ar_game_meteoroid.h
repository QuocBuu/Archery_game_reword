#ifndef __AR_GAME_METEOROID_H__
#define __AR_GAME_METEOROID_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#define NUM_METEOROIDS              (5)
#define SIZE_BITMAP_METEOROIDS_X    (20)
#define SIZE_BITMAP_METEOROIDS_Y    (10)

#define AXIT_Y_METEOROID_0          (2)
#define AXIT_Y_METEOROID_1          (12)
#define AXIT_Y_METEOROID_2          (22)
#define AXIT_Y_METEOROID_3          (32)
#define AXIT_Y_METEOROID_4          (42)

typedef struct {
	uint32_t x, y;
    bool display;
    uint8_t animation;
} ar_game_meteoroid;

extern ar_game_meteoroid meteoroid[NUM_METEOROIDS];

#endif //__AR_GAME_METEOROID_H__