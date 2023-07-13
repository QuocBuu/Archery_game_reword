#include "scr_game_setting.h"

#define TEXT			(20)
#define LEVEL			(110)

#define CHOSSE_ICON_X	(20)
#define CHOSSE_ICON_Y	(20)

#define FRAMES_SIZE_W	(103)
#define FRAMES_SIZE_H	(13)
#define FRAMES_SIZE_R	(3)

uint8_t chosse_location = 15;
uint8_t num_arrow_lv;
uint8_t arrow_speed_lv;
uint8_t meteoroid_speed_lv;

static void view_scr_game_setting();

view_dynamic_t dyn_view_item_game_setting = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_game_setting
};

view_screen_t scr_game_setting = {
	&dyn_view_item_game_setting,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_game_setting() {
	view_render.clear();
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
    // Icon
	view_render.drawBitmap(0, chosse_location-17, chosse_icon2, CHOSSE_ICON_X, CHOSSE_ICON_Y, WHITE);
    // Frames
	view_render.drawRoundRect(20,  2, FRAMES_SIZE_W, FRAMES_SIZE_H, FRAMES_SIZE_R, WHITE);
    view_render.drawRoundRect(20, 17, FRAMES_SIZE_W, FRAMES_SIZE_H, FRAMES_SIZE_R, WHITE);
    view_render.drawRoundRect(20, 32, FRAMES_SIZE_W, FRAMES_SIZE_H, FRAMES_SIZE_R, WHITE);
    view_render.drawRoundRect(20, 47, FRAMES_SIZE_W, FRAMES_SIZE_H, FRAMES_SIZE_R, WHITE);	
	// Count Arrow
    view_render.setCursor(TEXT, 5);
	view_render.print(" Arrow        { }");
	view_render.setCursor(LEVEL, 5);
	view_render.print(num_arrow_lv);    
	// Arrow speed
	view_render.setCursor(TEXT, 20);
	view_render.print(" Arrow speed  { }");
	view_render.setCursor(LEVEL, 20);
	view_render.print(arrow_speed_lv);
	// Mine speed
	view_render.setCursor(TEXT, 35);
	view_render.print(" Mine  speed  { }");
	view_render.setCursor(LEVEL, 35);
	view_render.print(meteoroid_speed_lv);
	// EXIT
	view_render.setCursor(TEXT+30, 50);
	view_render.print("  EXIT ") ;
	view_render.update();
}

void scr_game_setting_handle(ak_msg_t* msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY: {
			APP_DBG_SIG("SCREEN_ENTRY\n");
			eeprom_read(18, (uint8_t*)&num_arrow_lv, 	1U);
			eeprom_read(20, (uint8_t*)&arrow_speed_lv, 	1U);
			eeprom_read(22, (uint8_t*)&meteoroid_speed_lv, 	1U);
		}
			break;

		case AC_DISPLAY_BUTTON_MODE_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
			switch (chosse_location) {
				case 15: {
					num_arrow_lv++;
					if (num_arrow_lv > 5) {
						num_arrow_lv = 1;
					}
				}
					break;

				case 30: {
					arrow_speed_lv++;
					if (arrow_speed_lv > 5) { 
						arrow_speed_lv = 1;
					}
				}
					break;
				
				case 45: {
					meteoroid_speed_lv++;
					if (meteoroid_speed_lv > 5) { 
						meteoroid_speed_lv = 1;
					}
				}
					break;

				case 60: {
					eeprom_write(18, (uint8_t*)&num_arrow_lv, 		1U);
					eeprom_write(20, (uint8_t*)&arrow_speed_lv, 	1U);
					eeprom_write(22, (uint8_t*)&meteoroid_speed_lv, 1U);
					SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
					BUZZER_PlayTones(tones_startup);
				}
					break;
				
				default:
					break;
			}
			BUZZER_PlayTones(tones_cc);
		}
			break;
		
		case AC_DISPLAY_BUTTON_UP_LONG_PRESSED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_LONG_PRESSED\n");
			num_arrow_lv = 5;
			arrow_speed_lv = 5;
			meteoroid_speed_lv = 5;
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_UP_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
			chosse_location = chosse_location - 15;
			if (chosse_location == 0) { 
				chosse_location = 60;
			}     
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_DOWN_LONG_PRESSED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_LONG_PRESSED\n");
			num_arrow_lv = 1;
			arrow_speed_lv = 1;
			meteoroid_speed_lv = 1;
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
			chosse_location = chosse_location + 15;
			if (chosse_location > 60) { 
				chosse_location = 15;
			}
		}
			BUZZER_PlayTones(tones_cc);
			break;

		default:
			break;
	}
}