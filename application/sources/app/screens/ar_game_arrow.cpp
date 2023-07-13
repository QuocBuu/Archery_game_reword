#include "ar_game_arrow.h"

#include "ar_game_archery.h"
#include "scr_archery_game.h"

#define AR_GAME_ARROW_SETUP()  \
do { \
    for (uint8_t i = 0; i < num_arrow; i++) { \
        arrow[i].x = 0; \
        arrow[i].y = 0; \
        arrow[i].display = BLACK; \
        arrow[i].animation = 1; \
    } \
} while (0);

#define AR_GAME_ARROW_RESET() \
do { \
    for (uint8_t i = 0; i < num_arrow; i++) { \
        arrow[i].x = 0; \
        arrow[i].y = 0; \
        arrow[i].display = BLACK; \
        arrow[i].animation = 1; \
    } \
} while (0);

ar_game_arrow arrow[MAX_NUM_ARROW];

void ar_game_arrow_run() {
    for (uint8_t i = 0; i < MAX_NUM_ARROW; i++) {
		if (arrow[i].display == WHITE) {
            // Arrow run
			arrow[i].x += arrow_speed;
            // Arrows ends 
            if (arrow[i].x == MAX_AXIT_X_ARROW) {
				arrow[i].display = BLACK;
				arrow[i].x = 0;
				num_arrow++;
			}
		}
    }
}

void ar_game_arrow_shoot() {
    for (uint8_t i = 0; i < MAX_NUM_ARROW; i++) {
        if (arrow[i].display == BLACK && num_arrow != 0) {
            num_arrow--;
            arrow[i].display = WHITE;
            arrow[i].y = archery.y + 5;
            BUZZER_PlayTones(tones_cc);
            break;
        }
        else if (num_arrow == 0) {
            BUZZER_PlayTones(tones_3beep);
            break;
        }
    }
}

void ar_game_arrow_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case AR_GAME_ARROW_SETUP: {
        APP_DBG_SIG("AR_GAME_ARROW_SETUP\n");
        AR_GAME_ARROW_SETUP();
    }
        break;

    case AR_GAME_ARROW_RUN: {
        APP_DBG_SIG("AR_GAME_ARROW_RUN\n");
        ar_game_arrow_run();
    }
        break;

    case AR_GAME_ARROW_SHOOT: {
        APP_DBG_SIG("AR_GAME_ARROW_SHOOT\n");
        ar_game_arrow_shoot();
    }
        break;

    case AR_GAME_ARROW_RESET: {
        APP_DBG_SIG("AR_GAME_ARROW_RESET\n");
        AR_GAME_ARROW_RESET();
    }
        break;

    default:
        break;
    }
}