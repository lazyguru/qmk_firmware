#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┌───┬───┬───┬───┐
     * │ ` │Esc│Tab│MO1│Bsp│
     * ├───┼───┼───┼───┼───┤
     * │ , │Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ 4 │ 5 │ 6 │   │
     * └───┴───────┴───┴───┘
     */
    [0] = LAYOUT_numpad_4x5(
        KC_1,    KC_2,  KC_3,   KC_4,    KC_5,
        KC_Q,    KC_H,  KC_W,   KC_LCTL, KC_F,
        KC_X,    KC_A,  KC_S,   KC_D,    KC_B,
        KC_LSFT, KC_V,  KC_SPC, KC_TAB,  MO(1)
    ),

    [1] = LAYOUT_numpad_4x5(
        MO(2),    KC_E,    KC_R,    KC_T,     KC_ESC,
        KC_K,     KC_I,    KC_P,    KC_L,     KC_G,
        KC_EQUAL,  KC_U,    KC_J,    KC_QUOTE, KC_LALT,
        KC_ENTER, _______, _______, KC_M,  XXXXXXX
    ),

    [2] = LAYOUT_numpad_4x5(
        XXXXXXX, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______
    )
};

#ifdef OLED_ENABLE

#define L_ESO_1 0
#define L_ESO_2 2
#define L_FLASH 4

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_ESO_1:
            oled_write_ln_P(PSTR("ESO 1\n"), false);
            oled_write_ln_P(PSTR("1 2 3 4 5"), false);
            oled_write_ln_P(PSTR("Q H W ^ F"), false);
            oled_write_ln_P(PSTR("X A S D B"), false);
            oled_write_ln_P(PSTR("# V _ > *"), false);
            break;
        case L_ESO_2:
            oled_write_ln_P(PSTR("ESO 2\n"), false);
            oled_write_ln_P(PSTR("* E R T [ESC]"), false);
            oled_write_ln_P(PSTR("K I P L G"), false);
            oled_write_ln_P(PSTR("= U J ' [ALT]"), false);
            oled_write_ln_P(PSTR("[ENTER] . . M ."), false);
            break;
        case L_FLASH:
            oled_write_ln_P(PSTR("Flash\n"), false);
            oled_write_ln_P(PSTR(". . . . [BOOT]"), false);
            oled_write_ln_P(PSTR(". . . . ."), false);
            oled_write_ln_P(PSTR(". . . . ."), false);
            oled_write_ln_P(PSTR(". . . . ."), false);
            break;
    }
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

/*
static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}
*/

bool oled_task_user(void) {
    oled_render_layer_state();
    return false;
}
void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}
#endif // OLED_ENABLE
