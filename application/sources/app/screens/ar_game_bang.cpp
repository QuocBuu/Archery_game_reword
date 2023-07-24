#include "ar_game_bang.h"

#include "ar_game_meteoroid.h"
#include "ar_game_arrow.h"

#define AR_GAME_BANG_SETUP() \
do { \
    for (uint8_t i = 0; i < NUM_BANG; i++) { \
        bang[i].x = 0; \
        bang[i].y = 0; \
        bang[i].visible = BLACK; \
        bang[i].action_image = 1; \
    } \
} while (0);

#define AR_GAME_BANG_RESET() \
do { \
    for (uint8_t i = 0; i < NUM_BANG; i++) { \
        bang[i].visible = BLACK; \
        bang[i].action_image = 1; \
    } \
} while (0);

ar_game_bang bang[NUM_BANG];

void ar_game_bang_update() {
    for (uint8_t i = 0; i < NUM_BANG; i++) {
        if (bang[i].visible == WHITE) {
            bang[i].action_image++;
        }
        if (bang[i].action_image == 4) {
            bang[i].action_image = 1;
            bang[i].visible = BLACK;
            meteoroid[i].visible = WHITE;
        }
    }
}

void ar_game_bang_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case AR_GAME_BANG_SETUP: {
        APP_DBG_SIG("AR_GAME_BANG_SETUP\n");
        AR_GAME_BANG_SETUP();
    }
        break;

    case AR_GAME_BANG_UPDATE: {
        APP_DBG_SIG("AR_GAME_BANG_UPDATE\n");
        ar_game_bang_update();
    }
        break;

    case AR_GAME_BANG_RESET: {
        APP_DBG_SIG("AR_GAME_BANG_RESET\n");
        AR_GAME_BANG_RESET();
    }
        break;

    default:
        break;
    }
}