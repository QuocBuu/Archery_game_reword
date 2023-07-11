#ifndef __SCR_CHARTS_GAME_H__
#define __SCR_CHARTS_GAME_H__

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
#include "view_render.h"

#include "buzzer.h"

#include <math.h>
#include <vector>

#include "scr_menu_game.h"
#include "scr_game_over.h"



extern view_dynamic_t dyn_view_item_charts_game;

extern view_screen_t scr_charts_game;
extern void scr_charts_game_handle(ak_msg_t* msg);

#endif //__SCR_CHARTS_GAME_H__
