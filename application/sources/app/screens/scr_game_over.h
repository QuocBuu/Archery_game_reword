#ifndef __SCR_GAME_OVER_H__
#define __SCR_GAME_OVER_H__

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
#include "scr_archery_game.h"
#include "scr_charts_game.h"

extern view_dynamic_t dyn_view_item_game_over;

extern view_screen_t scr_game_over;
extern void scr_game_over_handle(ak_msg_t* msg);

#endif //__SCR_GAME_OVER_H__
