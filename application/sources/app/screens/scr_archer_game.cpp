#include "scr_archer_game.h"

#include "ar_game_archery.h"
#include "ar_game_arrow.h"
#include "ar_game_bang.h"
#include "ar_game_border.h"
#include "ar_game_meteoroid.h"

#include "bitmap_archery_game.h"

uint8_t num_arrow;
uint8_t arrow_speed;
uint8_t meteoroid_speed;

static void view_scr_archer_game();

view_dynamic_t dyn_view_item_archer_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_archer_game
};

view_screen_t scr_archer_game = {
	&dyn_view_item_archer_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

/*****************************************************************************/
/*  Archery game screen*/
/*****************************************************************************/

void ar_game_screen_display() {
	view_render.setTextSize(1);				// Size 
	view_render.setTextColor(WHITE);		// Color
	view_render.setCursor(2,55);			// Location
	view_render.print("Arrow:");			
	view_render.print((int)num_arrow);
	view_render.setCursor(60,55);
	view_render.print(" Score:");
	view_render.print(score);
	view_render.drawLine(0, LCD_HEIGHT, 	LCD_WIDTH, LCD_HEIGHT,		WHITE);
	view_render.drawLine(0, LCD_HEIGHT-10, 	LCD_WIDTH, LCD_HEIGHT-10,	WHITE);
	view_render.drawRect(0, 0, 128, 64, 1);
} 

void ar_game_archery_display() {
	if (archery.display == WHITE && num_arrow != 0) {
		view_render.drawBitmap(	archery.x, 
								archery.y,
								bitmap_archery_I,
								SIZE_BITMAP_ARCHERY_X, 
								SIZE_BITMAP_ARCHERY_Y,
								WHITE);
	}
	else if (archery.display == WHITE && num_arrow == 0) {
		view_render.drawBitmap(	archery.x, 
								archery.y,
								bitmap_archery_II,
								SIZE_BITMAP_ARCHERY_X, 
								SIZE_BITMAP_ARCHERY_Y,
								WHITE);
	}
}

void ar_game_arrow_display() {
	for (int i = 0; i < MAX_NUM_ARROW; i++) {
		if (arrow[i].display == WHITE) {
			view_render.drawBitmap(	arrow[i].x, 
									arrow[i].y,
									bitmap_arrow,	
									SIZE_BITMAP_ARROW_X, 
									SIZE_BITMAP_ARROW_Y,
									WHITE);
		}
	}
}

void ar_game_meteoroid_display() {
	for (int i = 0; i < NUM_METEOROIDS; i++) {
		if (meteoroid[i].display == WHITE) {
			if (meteoroid[i].animation == 1) {
				view_render.drawBitmap(	meteoroid[i].x, 
										meteoroid[i].y,
										bitmap_meteoroid_I,		
										SIZE_BITMAP_METEOROIDS_X, 
										SIZE_BITMAP_METEOROIDS_Y,
				 						WHITE);
			}
			else if (meteoroid[i].animation == 2) {
				view_render.drawBitmap(	meteoroid[i].x, 
										meteoroid[i].y,
										bitmap_meteoroid_II,		
										SIZE_BITMAP_METEOROIDS_X, 
										SIZE_BITMAP_METEOROIDS_Y,
										WHITE);
			}
			else if (meteoroid[i].animation == 3) {
				view_render.drawBitmap(	meteoroid[i].x, 
										meteoroid[i].y,
										bitmap_meteoroid_III,		
										SIZE_BITMAP_METEOROIDS_X, 
										SIZE_BITMAP_METEOROIDS_Y,
				 						WHITE);
			}
		}
	}
}

void ar_game_border_display() {
	if (border.display == WHITE) {
		view_render.drawFastVLine(	border.x, 
									AXIT_Y_BORDER_ON,
									AXIT_Y_BORDER_UNDER, 
									WHITE);
		for (int i = 0; i < NUM_METEOROIDS; i++) {
			view_render.fillCircle(	border.x, 
									meteoroid[i].y + 5, 
									1, 
									WHITE);
		}
	}
}

void ar_game_bang_display() {
	for (int i = 0; i < NUM_BANG; i++) {
		if (bang[i].display == WHITE) {
			if (bang[i].animation == 1) {
				view_render.drawBitmap(	bang[i].x, 
										bang[i].y,
										bitmap_bang_I,		
										SIZE_BITMAP_BANG_I_X, 
										SIZE_BITMAP_BANG_I_Y,
										WHITE);
			}
			else if (bang[i].animation == 2) {
				view_render.drawBitmap(	bang[i].x, 
										bang[i].y,
										bitmap_bang_II,		
										SIZE_BITMAP_BANG_I_X, 
										SIZE_BITMAP_BANG_I_Y,
				 						WHITE);
			}
			else if (bang[i].animation == 3) {
				view_render.drawBitmap( bang[i].x + 2, 
										bang[i].y - 1,		
										bitmap_bang_III,		
										SIZE_BITMAP_BANG_II_X, 
										SIZE_BITMAP_BANG_II_Y,
				 						WHITE);
			}
		}
	}
}

void view_scr_archer_game() {
	ar_game_screen_display();
	ar_game_archery_display();
	ar_game_arrow_display();
    ar_game_meteoroid_display();
	ar_game_border_display();
	ar_game_bang_display();
}

/*****************************************************************************/
/*  Archery game handle*/
/*****************************************************************************/

void ar_game_screen_setup() {
	view_render.initialize();
	view_render_display_on();
}

void ar_game_level_setup() {
    eeprom_read(18, (uint8_t*)&num_arrow, 		1U);
	eeprom_read(20, (uint8_t*)&arrow_speed,		1U);
	eeprom_read(22, (uint8_t*)&meteoroid_speed,	1U);
}

void ar_game_time_tick_setup() {
	timer_set(	AC_TASK_DISPLAY_ID, \
				AR_GAME_TIME_TICK, \
				AR_GAME_TIME_TICK_INTERVAL, \
				TIMER_PERIODIC);
}

void ar_game_save_score() {
    eeprom_write(2, (uint8_t*)&score, sizeof(score));
    score = 10;
}

void scr_archer_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		case AR_GAME_INITIAL_SETUP: {
			APP_DBG_SIG("AR_GAME_INITIAL_SETUP\n");
			ar_game_screen_setup();
			ar_game_level_setup();
			task_post_pure_msg(AR_GAME_ARCHERY_ID, 	 AR_GAME_ARCHERY_SETUP		);
			task_post_pure_msg(AR_GAME_ARROW_ID, 	 AR_GAME_ARROW_SETUP		);
			task_post_pure_msg(AR_GAME_METEOROID_ID, AR_GAME_METEOROID_SETUP	);
			task_post_pure_msg(AR_GAME_BORDER_ID, 	 AR_GAME_BORDER_SETUP		);
			task_post_pure_msg(AR_GAME_BANG_ID, 	 AR_GAME_BANG_SETUP			);
			ar_game_time_tick_setup();		
		}
	}
		break;

	case AR_GAME_TIME_TICK: {
		APP_DBG_SIG("AR_GAME_TIME_TICK\n");
		task_post_pure_msg(AR_GAME_ARCHERY_ID, 		AR_GAME_ARCHERY_UPDATE		);
		task_post_pure_msg(AR_GAME_ARROW_ID, 		AR_GAME_ARROW_RUN			);
		task_post_pure_msg(AR_GAME_METEOROID_ID,	AR_GAME_METEOROID_RUN		);
		task_post_pure_msg(AR_GAME_METEOROID_ID,	AR_GAME_METEOROID_DETONATOR	);
		task_post_pure_msg(AR_GAME_BORDER_ID, 		AR_GAME_BORDER_UPDATE		);
		task_post_pure_msg(AR_GAME_BANG_ID, 		AR_GAME_BANG_UPDATE			);
		task_post_pure_msg(AR_GAME_BORDER_ID, 		AR_GAME_CHECK_GAME_OVER		);
	}
		break;

	case AR_GAME_RESET: {
		APP_DBG_SIG("AR_GAME_RESET\n");
		task_post_pure_msg(AR_GAME_ARCHERY_ID, 		AR_GAME_ARCHERY_RESET		);
		task_post_pure_msg(AR_GAME_ARROW_ID, 		AR_GAME_ARROW_RESET			);
		task_post_pure_msg(AR_GAME_METEOROID_ID,	AR_GAME_METEOROID_RESET		);
		task_post_pure_msg(AR_GAME_BORDER_ID, 		AR_GAME_BORDER_RESET		);
		task_post_pure_msg(AR_GAME_BANG_ID, 		AR_GAME_BANG_RESET			);
		task_post_pure_msg(AR_GAME_SCREEN_ID, 		AR_GAME_EXIT_GAME			);
		BUZZER_PlayTones(tones_3beep);
}
		break;

	case AR_GAME_EXIT_GAME: {
		APP_DBG_SIG("AR_GAME_EXIT_GAME\n");
		ar_game_save_score();
		SCREEN_TRAN(scr_game_over_handle, &scr_game_over);		
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		task_post_pure_msg(AR_GAME_ARROW_ID, 		AR_GAME_ARROW_SHOOT			);
	}
		break;

	case AC_DISPLAY_BUTTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
		task_post_pure_msg(AR_GAME_ARCHERY_ID, 		AR_GAME_ARCHERY_UP			);
	}
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
		task_post_pure_msg(AR_GAME_ARCHERY_ID, 		AR_GAME_ARCHERY_DOWN		);
	}	
		break;

	default:
		break;
	}
}
