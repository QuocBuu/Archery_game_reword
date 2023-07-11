#ifndef __SCR_ARCHER_GAME_H__
#define __SCR_ARCHER_GAME_H__

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

#include "eeprom.h"
#include "app_eeprom.h"

#include "buzzer.h"
#include <math.h>
#include <vector>

#include "scr_menu_game.h"
#include "scr_game_setting.h"
#include "scr_idle.h"

extern bool lose;
extern uint8_t num_arrow;
extern uint8_t arrow_speed;
extern uint8_t meteoroid_speed;
extern uint8_t archery_game_on;

extern view_dynamic_t dyn_view_item_archer_game;

extern view_screen_t scr_archer_game;
extern void scr_archer_game_handle(ak_msg_t* msg);
#endif //__SCR_ARCHER_GAME_H__
