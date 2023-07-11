#ifndef __AR_GAME_BORDER_H__
#define __AR_GAME_BORDER_H__

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

#include "buzzer.h"

#define AXIT_X_BORDER           (15)
#define AXIT_Y_BORDER_ON        (2)
#define AXIT_Y_BORDER_UNDER     (52)

typedef struct {
	int x, y;
    bool display;
    int animation;
} ar_game_border;

extern int score;
extern ar_game_border border;

#endif //__AR_GAME_BORDER_H__