#include "ar_game_border.h"

#include "ar_game_meteoroid.h"
#include "ar_game_archery.h"

#define AR_GAME_BORDER_SETUP() \
do { \
    border.x = AXIT_X_BORDER; \
    border.display = WHITE; \
    border.animation = 0; \
} while (0);

#define AR_GAME_BORDER_RESET() \
do { \
    border.x = AXIT_X_BORDER; \
    border.display = BLACK; \
} while (0);

ar_game_border border;

uint32_t score = 10;

void ar_game_border_update() {
    if (score%200 == 0) {
        border.x += 10;
        score += 10;
    }
}

void ar_game_check_game_over() {
    for (uint8_t i = 0; i < NUM_METEOROIDS; i++) {
        if (meteoroid[i].x <= (border.x - 3)) {
            task_post_pure_msg(AR_GAME_SCREEN_ID, AR_GAME_RESET);
        }
    }
}

void ar_game_border_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case AR_GAME_BORDER_SETUP: {
        APP_DBG_SIG("AR_GAME_BORDER_SETUP\n");
        AR_GAME_BORDER_SETUP();
    }
        break;

    case AR_GAME_BORDER_UPDATE: {
        APP_DBG_SIG("AR_GAME_BORDER_UPDATE\n");
        ar_game_border_update();
    }
        break;

    case AR_GAME_BORDER_RESET: {
        APP_DBG_SIG("AR_GAME_BORDER_RESET\n");
        AR_GAME_BORDER_RESET();
    }
        break;
    
    case AR_GAME_CHECK_GAME_OVER: {
        APP_DBG_SIG("AR_GAME_CHECK_GAME_OVER\n");
        ar_game_check_game_over();
    }
        break;

    default:
        break;
    }
}