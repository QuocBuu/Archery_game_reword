#include "scr_charts_game.h"

#include "app_eeprom.h"

/*****************************************************************************/
/* Variable Declaration - Charts game */
/*****************************************************************************/
// 'bitmap_icon_charts', 60x20px
static const unsigned char PROGMEM bitmap_icon_charts [] = {
	0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 
	0x7e, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x07, 0xe0, 0xe7, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x0e, 0x70, 
	0xe7, 0x00, 0x00, 0x39, 0xc0, 0x00, 0x0e, 0x70, 0x7f, 0x00, 0x60, 0x70, 0xe0, 0x60, 0x0f, 0xe0, 
	0x03, 0xc0, 0xfe, 0xe0, 0x77, 0xf0, 0x3c, 0x00, 0x01, 0xf9, 0xc7, 0x80, 0x1e, 0x39, 0xf8, 0x00, 
	0x00, 0xff, 0x87, 0x00, 0x0e, 0x1f, 0x70, 0x00, 0x00, 0x73, 0xce, 0x00, 0x07, 0x7c, 0xe0, 0x00, 
	0x00, 0x38, 0x7c, 0x00, 0x03, 0xe1, 0xc0, 0x00, 0x00, 0x1c, 0x18, 0x00, 0x00, 0x03, 0x80, 0x00, 
	0x00, 0x0e, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 
	0x00, 0x03, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00
};

static ar_game_score_t GameScore_charts;

/*****************************************************************************/
/* View - Charts game */
/*****************************************************************************/
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

void view_scr_charts_game() {
 	view_render.clear();
    view_render.fillScreen(WHITE);
    view_render.drawBitmap(35, 5, bitmap_icon_charts, 60, 20, 0);
    view_render.fillRoundRect(1, 28, 126, 12, 5, 0);
	view_render.fillRoundRect(1, 51, 126, 12, 5, 0);
    view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(16, 30);
	view_render.print(GameScore_charts.score_1st);
	view_render.setCursor(86, 30);
	view_render.print(": 1st");
	view_render.setCursor(16, 54);
	view_render.print(GameScore_charts.score_3rd);
	view_render.setCursor(86, 54);
	view_render.print(": 3rd");
    view_render.setTextColor(BLACK);
	view_render.setCursor(16, 42);
	view_render.print(GameScore_charts.score_2nd);
	view_render.setCursor(86, 42);
	view_render.print(": 2nd");
}

/*****************************************************************************/
/* Handle - Charts game */
/*****************************************************************************/
void reset_score_charts() {
	GameScore_charts.score_1st = 0;
	GameScore_charts.score_2nd = 0;
	GameScore_charts.score_3rd = 0;
	eeprom_write(	EEPROM_SCORE_ADDR, \
					(uint8_t*)&GameScore_charts, \
					sizeof(GameScore_charts));
}

void scr_charts_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY: {
			case AC_DISPLAY_INITIAL: {
				APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
				view_render.initialize();
				view_render_display_on();
				// Read score 
				eeprom_read(EEPROM_SCORE_ADDR, \
							(uint8_t*)&GameScore_charts, \
							sizeof(GameScore_charts));
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