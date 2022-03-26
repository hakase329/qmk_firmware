#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 1 │ 2 │ 3 │ A │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ B │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │ C │
     * ├───┼───┼───┼───┤
     * │ * │ 0 │ # │ D │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_P1,   KC_P2,   KC_P3,  KC_A,
        KC_P4,   KC_P5,   KC_P6,  KC_B,
        KC_P7,   KC_P8,   KC_P9,  KC_C,
        KC_PAST, KC_P0, KC_HASH,  KC_D
    )
};
