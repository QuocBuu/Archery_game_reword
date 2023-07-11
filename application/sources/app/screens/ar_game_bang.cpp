#include "ar_game_bang.h"
#include "ar_game_meteoroid.h"
#include "ar_game_arrow.h"

ar_game_bang bang[NUM_BANG];

#define AR_GAME_BANG_SETUP() \
do { \
    for (int i = 0; i < NUM_BANG; i++) { \
        bang[i].x = 0; \
        bang[i].y = 0; \
        bang[i].display = BLACK; \
        bang[i].animation = 1; \
    } \
} while (0);

void ar_game_bang_update() {
    for (int i = 0; i < NUM_BANG; i++) {
        if (bang[i].display == WHITE) {
            bang[i].animation++;
        }
        if (bang[i].animation == 4) {
            bang[i].animation = 1;
            bang[i].display = BLACK;
            meteoroid[i].display = WHITE;
        }
    }
}

#define AR_GAME_BANG_RESET() \
do { \
    for (int i = 0; i < NUM_BANG; i++) { \
        bang[i].display = BLACK; \
        bang[i].animation = 1; \
    } \
} while (0);

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