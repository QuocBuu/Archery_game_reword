#include "scr_game_over.h"

int score_game_over=0;
int score_1st_o;
int score_2nd_o;
int score_3rd_o;

// 'icon_restart', 15x15px
static const unsigned char PROGMEM epd_bitmap_icon_restart [] = {
	0x01, 0x00, 0x07, 0x00, 0x0f, 0xc0, 0x0f, 0xf0, 0x07, 0x78, 0x63, 0x9c, 0x61, 0x0c, 0x60, 0x0c, 
	0x60, 0x0c, 0x60, 0x0c, 0x60, 0x0c, 0x70, 0x1c, 0x38, 0x38, 0x1f, 0xf0, 0x07, 0xc0
};

// 'icon_xep_hang', 17x15px
static const unsigned char PROGMEM epd_bitmap_icon_xep_hang [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x28, 0x00, 0x00, 
	0xa8, 0x00, 0x00, 0xa8, 0x00, 0x02, 0xa8, 0x00, 0x02, 0xa8, 0x00, 0x0a, 0xa8, 0x00, 0x0a, 0xa8, 
	0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'icon_go_home', 16x16px
static const unsigned char PROGMEM epd_bitmap_icon_go_home [] = {
	0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x02, 0x40, 0x05, 0xa0, 0x0b, 0xd0, 0x17, 0xe8, 0x2f, 0xf4, 
	0x5f, 0xfb, 0xbc, 0x3d, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x1c, 0x38, 0x00, 0x00
};

static void view_scr_game_over();

view_dynamic_t dyn_view_item_game_over = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_game_over
};

view_screen_t scr_game_over = {
	&dyn_view_item_game_over,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void score_read() {
	eeprom_read(2, 	(uint8_t*)&score_game_over, 4U);
	eeprom_read(6, 	(uint8_t*)&score_1st_o, 	4U);
	eeprom_read(10,	(uint8_t*)&score_2nd_o, 	4U);
	eeprom_read(14,	(uint8_t*)&score_3rd_o, 	4U);
}

void rank_ranking() {
	if (score_game_over > score_1st_o) {
		score_3rd_o = score_2nd_o;
		score_2nd_o = score_1st_o;
		score_1st_o = score_game_over;
	}
	else if (score_game_over > score_2nd_o) {
		score_3rd_o = score_2nd_o;
		score_2nd_o = score_game_over;
	}
	else if (score_game_over > score_3rd_o) {
		score_3rd_o = score_game_over;
	}
}

void view_scr_game_over() {
	view_render.fillScreen(1);
	view_render.setTextSize(2);
	view_render.setTextColor(BLACK);
	view_render.setCursor(11, 10);
	view_render.print("GAME OVER");
	view_render.setTextSize(1);
	view_render.setTextColor(BLACK);
	view_render.setCursor(16, 35);
	view_render.print("Your score:");
	view_render.setCursor(81, 35);
	view_render.print(score_game_over);
	view_render.drawBitmap(10, 48, epd_bitmap_icon_restart, 15, 15, 0);
	view_render.drawBitmap(55, 50, epd_bitmap_icon_xep_hang, 17, 15, 0);
	view_render.drawBitmap(100, 48, epd_bitmap_icon_go_home, 16, 16, 0);
}

void scr_game_over_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		case AC_DISPLAY_INITIAL: {
		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		view_render.initialize();
		view_render_display_on();
		score_read();
		rank_ranking();
		}
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		eeprom_write(6,  (uint8_t*)&score_1st_o, 	4U);
		eeprom_write(10, (uint8_t*)&score_2nd_o, 	4U);
		eeprom_write(14, (uint8_t*)&score_3rd_o, 	4U);	
		SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
		eeprom_write(6,  (uint8_t*)&score_1st_o, 	4U);
		eeprom_write(10, (uint8_t*)&score_2nd_o, 	4U);
		eeprom_write(14, (uint8_t*)&score_3rd_o, 	4U);	
		SCREEN_TRAN(scr_charts_game_handle  	, &scr_charts_game );
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
		eeprom_write(6,  (uint8_t*)&score_1st_o, 	4U);
		eeprom_write(10, (uint8_t*)&score_2nd_o, 	4U);
		eeprom_write(14, (uint8_t*)&score_3rd_o, 	4U);	
		SCREEN_TRAN(scr_archer_game_handle  	, &scr_archer_game );
	}	
		BUZZER_PlayTones(tones_cc);
		break;

	default:
		break;
	}
}