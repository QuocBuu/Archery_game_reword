#include "ar_game_meteoroid.h"
#include "ar_game_arrow.h"
#include "ar_game_bang.h"
#include "ar_game_border.h"
#include "scr_archer_game.h"

ar_game_meteoroid meteoroid[NUM_METEOROIDS];

#define AR_GAME_METEOROID_SETUP() \
do { \
    meteoroid[0].y = AXIT_Y_METEOROID_0; \
    meteoroid[1].y = AXIT_Y_METEOROID_1; \
    meteoroid[2].y = AXIT_Y_METEOROID_2; \
    meteoroid[3].y = AXIT_Y_METEOROID_3; \
    meteoroid[4].y = AXIT_Y_METEOROID_4; \
    for (int i = 0; i < NUM_METEOROIDS; i++) { \
        meteoroid[i].x = (rand() % 39) + 130; \
        meteoroid[i].display = WHITE; \
        meteoroid[i].animation = rand() % 3 + 1; \
    } \
} while (0);

void ar_game_meteoroid_run() {
    for (int i = 0; i < NUM_METEOROIDS; i++) {
        if (meteoroid[i].display == WHITE) {
            meteoroid[i].x -= (int)meteoroid_speed;
            if (meteoroid[i].animation < 4) {
                meteoroid[i].animation++;
            }
            if (meteoroid[i].animation == 4) {
                meteoroid[i].animation = 1;
            }
        }
    }
}

void ar_game_meteoroid_detonator() {
    for (int i = 0; i < NUM_BANG; i++) {
        if (meteoroid[i].display == WHITE) {
            for (int j = 0; j < MAX_NUM_ARROW; j++) {
                if (meteoroid[i].x < (arrow[j].x + SIZE_BITMAP_ARROW_X - 3)) {
                    if ((meteoroid[i].y + 8) > arrow[j].y) {
                        if ((meteoroid[i].y - 1) < arrow[j].y) {
                            meteoroid[i].display = BLACK;
                            arrow[j].display = BLACK;
                            bang[i].display = WHITE;
                            bang[i].x = meteoroid[i].x-5;
                            bang[i].y = meteoroid[i].y+2;
                            arrow[j].x = 0;
                            meteoroid[i].x = (rand() % 39) + 130;
                            num_arrow++;
                            score += 10;
                            BUZZER_PlayTones(tones_BUM);
                        }
                    }
                }
            }
        }
    }
}


#define AR_GAME_METEOROID_RESET() \
do { \
    for (int i = 0; i < NUM_METEOROIDS; i++) { \
        meteoroid[i].x = (rand() % 39) + 130; \
        meteoroid[i].display = BLACK; \
        meteoroid[i].animation = rand() % 3 + 1; \
    } \
} while (0);

void ar_game_meteoroid_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case AR_GAME_METEOROID_SETUP: {
        APP_DBG_SIG("AR_GAME_METEOROID_SETUP\n");
        AR_GAME_METEOROID_SETUP();
    }
        break;

    case AR_GAME_METEOROID_RUN: {
        APP_DBG_SIG("AR_GAME_METEOROID_RUN\n");
        ar_game_meteoroid_run();
    }
        break;

    case AR_GAME_METEOROID_DETONATOR: {
        APP_DBG_SIG("AR_GAME_METEOROID_DETONATOR\n");
        ar_game_meteoroid_detonator();
    }
        break;

    case AR_GAME_METEOROID_RESET: {
        APP_DBG_SIG("AR_GAME_METEOROID_RESET\n");
        AR_GAME_METEOROID_RESET();
    }
        break;

    default:
        break;
    }
}