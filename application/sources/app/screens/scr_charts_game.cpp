#include "scr_charts_game.h"

uint32_t score_1st;
uint32_t score_2nd;
uint32_t score_3rd;

static void view_scr_charts_game();

view_dynamic_t dyn_view_item_charts_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_charts_game
};

view_screen_t scr_charts_game = {
	&dyn_view_item_charts_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void read_score_charts() {
	eeprom_read(6, 	(uint8_t*)&score_1st, 	4U);
	eeprom_read(10, (uint8_t*)&score_2nd, 	4U);
	eeprom_read(14, (uint8_t*)&score_3rd, 	4U);
}

void reset_score_charts() {
	score_1st = 0;
	score_2nd = 0;
	score_3rd = 0;
	eeprom_write(6,  (uint8_t*)&score_1st, 	4U);
	eeprom_write(10, (uint8_t*)&score_2nd, 	4U);
	eeprom_write(14, (uint8_t*)&score_3rd, 	4U);
}

void view_scr_charts_game() {
 	view_render.clear();
    view_render.fillScreen(1);
    view_render.drawBitmap(35, 5, bitmap_icon_charts, 60, 20, 0);
    view_render.fillRoundRect(0, 28, 128, 12, 5, 0);
	view_render.fillRoundRect(0, 51, 128, 12, 5, 0);
    view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(16, 30);
	view_render.print(score_1st);
	view_render.setCursor(86, 30);
	view_render.print(": 1st");
	view_render.setCursor(16, 54);
	view_render.print(score_3rd);
	view_render.setCursor(86, 54);
	view_render.print(": 3rd");
    view_render.setTextColor(BLACK);
	view_render.setCursor(16, 42);
	view_render.print(score_2nd);
	view_render.setCursor(86, 42);
	view_render.print(": 2nd");
}

void scr_charts_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY: {
			case AC_DISPLAY_INITIAL: {
				APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
				read_score_charts();
				view_render.initialize();
				view_render_display_on();
			}
		}
			break;

		case AC_DISPLAY_BUTTON_MODE_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
			SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);	
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_UP_LONG_PRESSED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_LONG_PRESSED\n");
			reset_score_charts();
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
			SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
		}	
			BUZZER_PlayTones(tones_cc);
			break;

		default:
			break;
	}
}