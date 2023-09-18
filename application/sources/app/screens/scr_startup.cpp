#include "scr_startup.h"

/*****************************************************************************/
/* View - startup */
/*****************************************************************************/
static void view_scr_startup();

view_dynamic_t dyn_view_startup = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_startup
};

view_screen_t scr_startup = {
	&dyn_view_startup,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_startup() {
#define AK_LOGO_AXIS_X		(23)
#define AK_LOGO_TEXT		(AK_LOGO_AXIS_X + 4)
	/* ak logo */
	BUZZER_PlayTones(tones_startup);
	view_render.clear();
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(AK_LOGO_AXIS_X, 3);
	view_render.print("   __    _  _ ");
	view_render.setCursor(AK_LOGO_AXIS_X, 10);
	view_render.print("  /__\\  ( )/ )");
	view_render.setCursor(AK_LOGO_AXIS_X, 20);
	view_render.print(" /(__)\\ (   (");
	view_render.setCursor(AK_LOGO_AXIS_X, 30);
	view_render.print("(__)(__)(_)\\_)");
	view_render.setCursor(AK_LOGO_TEXT, 42);
	view_render.print("Active Kernel");
	view_render.update();
}

/*****************************************************************************/
/* Handle - startup */
/*****************************************************************************/
void check_setting_game() {
#define INIT_SETTING_GAME_ARROW_SPEED		(5)
#define INIT_SETTING_GAME_METEOROID_SPEED	(1)
#define INIT_SETTING_GAME_NUM_ARROW			(5)

	// Read setting data
	eeprom_read(	EEPROM_SETTING_START_ADDR, \
							(uint8_t*)&settingdata, \
							sizeof(settingdata));
	// Check data
		if (settingdata.meteoroid_speed == 0 \
			|| settingdata.arrow_speed == 0 \
			|| settingdata.num_arrow == 0) {
			// Init data setting
			settingdata.arrow_speed = INIT_SETTING_GAME_ARROW_SPEED;
			settingdata.meteoroid_speed = INIT_SETTING_GAME_METEOROID_SPEED;
			settingdata.num_arrow = INIT_SETTING_GAME_NUM_ARROW;
			// Write data
			eeprom_write(	EEPROM_SETTING_START_ADDR, \
								(uint8_t*)&settingdata, \
								sizeof(settingdata));
		}
	BUZZER_Sleep(settingdata.silent);
}

void scr_startup_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_DISPLAY_INITIAL: {
		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		view_render.initialize();
		view_render_display_on();
		timer_set(	AC_TASK_DISPLAY_ID, \
					AC_DISPLAY_SHOW_LOGO, \
					AC_DISPLAY_STARTUP_INTERVAL, \
					TIMER_ONE_SHOT);
		// Check setting game
		check_setting_game();
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
	}
		break;

	case AC_DISPLAY_SHOW_LOGO: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_LOGO\n");
		SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
	}
		break;

	default:
		break;
	}
}
