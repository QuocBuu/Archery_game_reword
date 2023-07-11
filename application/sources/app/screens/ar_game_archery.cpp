#include "ar_game_archery.h"

ar_game_archery archery;

int archery_y = AXIT_Y_ARCHERY;

#define AR_GAME_ARCHERY_SETUP() \
do { \
    archery.x = AXIT_X_ARCHERY; \
    archery.y = AXIT_Y_ARCHERY; \
    archery.display = WHITE; \
    archery.animation = 1; \
} while (0);

void ar_game_archery_update() {
    archery.y = archery_y;
}

void ar_game_archery_up() {
    archery_y -= STEP_ARCHERY_AXIS_Y;
    if (archery_y < 0) {archery_y = 0;}
}

void ar_game_archery_down() {
    archery_y += STEP_ARCHERY_AXIS_Y;
    if (archery_y > 40) {archery_y = 40;}
}

#define AR_GAME_ARCHERY_RESET() \
do { \
    archery.x = AXIT_X_ARCHERY; \
    archery.y = AXIT_Y_ARCHERY; \
    archery.display = BLACK; \
    archery_y = AXIT_Y_ARCHERY; \
} while(0);

void ar_game_archery_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case AR_GAME_ARCHERY_SETUP: {
        APP_DBG_SIG("AR_GAME_ARCHERY_SETUP\n");
        AR_GAME_ARCHERY_SETUP();
    }
        break;

    case AR_GAME_ARCHERY_UPDATE: {
        APP_DBG_SIG("AR_GAME_ARCHERY_UPDATE\n");
        ar_game_archery_update();
    }
        break;

    case AR_GAME_ARCHERY_UP: {
        APP_DBG_SIG("AR_GAME_ARCHERY_UP\n");
        ar_game_archery_up();
    }
        break;

    case AR_GAME_ARCHERY_DOWN: {
        APP_DBG_SIG("AR_GAME_ARCHERY_DOWN\n");
        ar_game_archery_down();
    }
        break;

    case AR_GAME_ARCHERY_RESET: {
        APP_DBG_SIG("AR_GAME_ARCHERY_RESET\n");
        AR_GAME_ARCHERY_RESET();
    }
        break;

    default:
        break;
    }
}