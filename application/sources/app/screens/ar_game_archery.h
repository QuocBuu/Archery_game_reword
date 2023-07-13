#ifndef __AR_GAME_ARCHERY_H__
#define __AR_GAME_ARCHERY_H__

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

#define STEP_ARCHERY_AXIS_Y     (10)
#define SIZE_BITMAP_ARCHERY_X   (15)
#define SIZE_BITMAP_ARCHERY_Y   (15)
#define AXIT_X_ARCHERY          (0)
#define AXIT_Y_ARCHERY          (30)

typedef struct {
    uint32_t x, y;
    bool display;
    uint8_t animation;
} ar_game_archery;

extern ar_game_archery archery;

#endif //__AR_GAME_ARCHERY_H__