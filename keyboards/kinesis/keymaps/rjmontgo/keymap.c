#include QMK_KEYBOARD_H

enum layer_names {
    _BASE_DVORAK,
    _RAISE,
    _KEYPAD,
};

// Mac-specific macros
#define MACCOPY LGUI(KC_C)
#define MACPAST LGUI(KC_V)
#define MACUNDO LGUI(KC_Z)
#define MACREDO LGUI(KC_Y)
#define MACLOCK LGUI(LCTL(KC_Q))

#define LSA_ LSA(KC_NO)
#define SFT_ESC SFT_T(KC_ESC)
#define KEYPAD TG(_KEYPAD)
#define RAISE MO(_RAISE)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE_DVORAK] = LAYOUT (
           // Left Hand
           MACLOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
           KC_PIPE, KC_PLUS, KC_LBRC, KC_LCBR, KC_LPRN, KC_AMPR,
           KC_TAB,  KC_SCLN, KC_COMM, KC_DOT,  KC_P,    KC_Y,
           SFT_ESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
           KC_LSFT, KC_QUOT, KC_Q,    KC_J,    KC_K,    KC_X,
                    KC_DLR,  KC_BSLS, KC_LEFT, KC_RGHT,
           // Left Thumb
                    KC_LCTL, KC_LALT,
                             KC_LGUI,
           KC_BSPC, KC_DEL,  RAISE,

           // Right Hand
           KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCROLL_LOCK, KC_PAUS, KEYPAD,  QK_REBOOT,
           KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_ASTR, KC_EXLM,
           KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSLS,
           KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
           KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                    KC_DOWN, KC_UP,   KC_SLSH, KC_AT,
           // Right Thumb
           KC_RALT, KC_RCTL,
           KC_RGUI,
           RAISE, KC_ENT, KC_SPC
    ),

[_RAISE] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
           _______, KC_COLN, KC_LABK, KC_RABK, S(KC_P), S(KC_Y),
           _______, S(KC_A), S(KC_O), S(KC_E), S(KC_U), S(KC_I),
           _______, KC_DQUO, S(KC_Q), S(KC_J), S(KC_K), S(KC_X),
                    KC_TILD, KC_PIPE, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PERC,
           S(KC_F), S(KC_G), S(KC_C), S(KC_R), S(KC_L), KC_HASH,
           S(KC_D), S(KC_H), S(KC_T), S(KC_N), S(KC_S), KC_UNDS,
           S(KC_B), S(KC_M), S(KC_W), S(KC_V), S(KC_Z), _______,
                    _______, _______, KC_QUES, KC_CIRC,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, _______
    ),

[_KEYPAD] = LAYOUT (
           // Left Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
           _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,
           // Left Thumb
                    _______, _______,
                             _______,
           _______, _______, _______,

           // Right Hand
           _______, _______, _______, _______, _______, _______, _______, _______, _______,
           _______, KC_NUM_LOCK, KC_PEQL, KC_PSLS, KC_PAST, _______,
           _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
           _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
           _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
                    _______, _______, KC_PDOT, KC_PENT,
           // Right Thumb
           _______, _______,
           _______,
           _______, _______, KC_P0
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _KEYPAD:
        writePinLow(LED_COMPOSE_PIN);
        break;
    case _RAISE:
        writePinLow(LED_CAPS_LOCK_PIN);
        break;
    default: //  for any other layers, or the default layer
        writePinHigh(LED_NUM_LOCK_PIN);
        writePinHigh(LED_CAPS_LOCK_PIN);
        writePinHigh(LED_SCROLL_LOCK_PIN);
        writePinHigh(LED_COMPOSE_PIN);
        break;
    }
  return state;
}

bool led_update_user(led_t led_state) {
    // Disable led_update_kb() so that layer indication code doesn't get overridden.
    return false;
}
