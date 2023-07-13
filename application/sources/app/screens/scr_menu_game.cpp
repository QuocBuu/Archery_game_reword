#include "scr_menu_game.h"

#define NUMBER_CHOICES_MENU	(4)

#define ICON_SIZE_X		(15)
#define ICON_SIZE_Y		(15)

#define FRAMES_W		(123)
#define FRAMES_H		(20)
#define FRAMES_R		(3)

#define SELECT_0 		(0)
#define SELECT_1 		(22)
#define SELECT_2 		(44)
#define SELECT_3 		(66)
#define SELECT_4 		(88)

#define STEP_MENU		(22)

uint8_t location_menu = 22;
uint8_t scroll_bar_location_y;
uint8_t screen_location_y;

bool chosse_1 = 0;
bool chosse_2 = 1;
bool chosse_3 = 1;
bool chosse_4 = 1;

static void view_scr_menu_game();

view_dynamic_t dyn_view_item_menu_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_menu_game
};

view_screen_t scr_menu_game = {
	&dyn_view_item_menu_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void update_screen() {
	switch (location_menu) {
		case SELECT_1: {
			chosse_1=0;
			chosse_2=1;
			chosse_3=1;
			chosse_4=1;
			scroll_bar_location_y = 0;
			screen_location_y = 0;
		}
			break;

		case SELECT_2: {
			chosse_1=1;
			chosse_2=0;
			chosse_3=1;
			chosse_4=1;
			scroll_bar_location_y = 16;
		}
			break;

		case SELECT_3: {
			chosse_1=1;
			chosse_2=1;
			chosse_3=0;
			chosse_4=1;
			scroll_bar_location_y = 32;
		}
			break;

		case SELECT_4: {
			chosse_1=1;
			chosse_2=1;
			chosse_3=1;
			chosse_4=0;
			scroll_bar_location_y = 48;
			screen_location_y = 22;
		}
			break;
		
		default:
			break;
	}
}

void view_scr_menu_game() {
	//scroll bar
	view_render.fillRect(125, scroll_bar_location_y, 3, 16, 1);
	view_render.drawBitmap(126, 0, epd_bitmap_Cham_Cham, 1, 64, 1);
	// khung chon
	view_render.fillRoundRect(0, location_menu-screen_location_y-STEP_MENU, FRAMES_W, FRAMES_H, FRAMES_R, WHITE);
	// Frames
	view_render.drawRoundRect(0, SELECT_1-STEP_MENU-screen_location_y, 	FRAMES_W, FRAMES_H, FRAMES_R, WHITE);
	view_render.drawRoundRect(0, SELECT_2-STEP_MENU-screen_location_y, 	FRAMES_W, FRAMES_H, FRAMES_R, WHITE);
	view_render.drawRoundRect(0, SELECT_3-STEP_MENU-screen_location_y, 	FRAMES_W, FRAMES_H, FRAMES_R, WHITE);
	view_render.drawRoundRect(0, SELECT_4-STEP_MENU-screen_location_y, 	FRAMES_W, FRAMES_H, FRAMES_R, WHITE);
	// icon
	view_render.drawBitmap(7,	SELECT_1-STEP_MENU-screen_location_y+2,	archery_icon, 	ICON_SIZE_X, 	ICON_SIZE_Y, 	chosse_1);
	view_render.drawBitmap(7,	SELECT_2-STEP_MENU-screen_location_y+2,	setting_icon, 	ICON_SIZE_X+1, 	ICON_SIZE_Y+1, 	chosse_2);
	view_render.drawBitmap(7,	SELECT_3-STEP_MENU-screen_location_y+2,	chart_icon, 	ICON_SIZE_X+1, 	ICON_SIZE_Y+1, 	chosse_3);
	view_render.drawBitmap(7,	SELECT_4-STEP_MENU-screen_location_y+2,	exit_icon, 		ICON_SIZE_X, 	ICON_SIZE_Y, 	chosse_4);
	// Name icon
	view_render.setTextSize(1);
	view_render.setTextColor(chosse_1);
    view_render.setCursor(20, SELECT_1-STEP_MENU-screen_location_y+7);
	view_render.print("   Archery Game");
	view_render.setTextColor(chosse_2);
    view_render.setCursor(20, SELECT_2-STEP_MENU-screen_location_y+7);
	view_render.print("   Setting");
	view_render.setTextColor(chosse_3);
    view_render.setCursor(20, SELECT_3-STEP_MENU-screen_location_y+7);
	view_render.print("   Charts");
	view_render.setTextColor(chosse_4);
	view_render.setCursor(20, SELECT_4-STEP_MENU-screen_location_y+7);
	view_render.print("   Exit");
}

void scr_menu_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY: {
			APP_DBG_SIG("SCREEN_ENTRY\n");
		}
			break;

		case AC_DISPLAY_BUTTON_MODE_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
			switch (location_menu){
				case SELECT_1: {
					SCREEN_TRAN(scr_archery_game_handle,	&scr_archery_game	);
				}
					break;

				case SELECT_2: {
					SCREEN_TRAN(scr_game_setting_handle,	&scr_game_setting	);
				}
					break;

				case SELECT_3: {
					SCREEN_TRAN(scr_charts_game_handle, 	&scr_charts_game	);
				}
					break;

				case SELECT_4: {
					SCREEN_TRAN(scr_idle_handle, 			&scr_idle			);
				}
					break;
				
				default:
					break;
			}
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_UP_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
			location_menu = location_menu - 22;
			if (location_menu == SELECT_0) { 
				location_menu = SELECT_4; 
			}
			update_screen();
		}
			break;

		case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
			location_menu = location_menu + 22;
			if (location_menu > SELECT_4) { 
				location_menu = SELECT_1;
			}
			update_screen();
		}	
			break;

		default:
			break;
	}
}