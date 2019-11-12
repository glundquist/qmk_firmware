#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _M_COLEMAK,
    // _M_QWERTY,
    _W_COLEMAK,
    // _W_QWERTY,
    _M_LOWER,
    _W_LOWER,
    _M_RAISE,
    _W_RAISE,
    _ADJUST,
};
// #define _QWERTY 0
// #define _COLEMAK 0
// #define _LOWER 1
// #define _RAISE 2
// #define _ADJUST 3

enum custom_keycodes {
  W_QWERTY = SAFE_RANGE,
  W_COLEMAK,
  M_QWERTY,
  M_COLEMAK,
  M_LOWER,
  W_LOWER,
  M_RAISE,
  W_RAISE,
  ADJUST,
};

/* Linux/win variants */
#define W_UNDO    LCTL(KC_Z)
#define W_CUT     LCTL(KC_X)
#define W_COPY    LCTL(KC_C)
#define W_PASTE   LCTL(KC_V)
#define W_PRVWD LCTL(KC_LEFT)
#define W_NXTWD LCTL(KC_RIGHT)
#define W_LSTRT KC_HOME
#define W_LEND KC_END
#define W_DLINE LCTL(KC_BSPC)

/* Mac variants */
#define M_UNDO LGUI(KC_Z)
#define M_CUT LGUI(KC_X)
#define M_COPY LGUI(KC_C)
#define M_PASTE LGUI(KC_V)
#define M_PRVWD LALT(KC_LEFT)
#define M_NXTWD LALT(KC_RIGHT)
#define M_LSTRT LGUI(KC_LEFT)
#define M_LEND LGUI(KC_RIGHT)
#define M_DLINE LGUI(KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
/*
 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_NO,      KC_NO,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                    KC_LGUI, KC_LALT, KC_LCTRL,LOWER, KC_ENT,   KC_SPC,  RAISE,   KC_RCTRL,KC_RALT, KC_RGUI \
),
*/

/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_M_COLEMAK] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_ESC,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_NO,     KC_NO,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                    KC_LCTRL,KC_LALT,KC_LGUI,M_LOWER, KC_ENT,   KC_SPC, M_RAISE,  KC_RGUI, KC_RALT, KC_RCTRL \
),
[_W_COLEMAK] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_ESC,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_NO,     KC_NO,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                    KC_LGUI, KC_LALT,KC_LCTRL,W_LOWER,KC_ENT,   KC_SPC,  W_RAISE, KC_RCTRL,KC_RALT, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_M_LOWER] = LAYOUT( \
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,\
  KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12, \
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______, \
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
),
[_W_LOWER] = LAYOUT( \
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,\
  KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12, \
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______, \
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_M_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______,  KC_INS, KC_PSCR,  KC_APP, XXXXXXX, XXXXXXX,                     KC_PGUP, M_PRVWD, KC_UP  , M_NXTWD, M_DLINE, _______, \
  _______, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_CAPS,                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , XXXXXXX, \
  _______,  M_UNDO,   M_CUT,  M_COPY, M_PASTE, XXXXXXX,  _______, _______,  XXXXXXX, M_LSTRT, XXXXXXX, M_LEND,  XXXXXXX, _______, \
                    _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______ \
),
[_W_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______,  KC_INS, KC_PSCR,  KC_APP, XXXXXXX, XXXXXXX,                     KC_PGUP, W_PRVWD, KC_UP  , W_NXTWD, W_DLINE, _______, \
  _______, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_CAPS,                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , XXXXXXX, \
  _______,  W_UNDO,   W_CUT,  W_COPY, W_PASTE, XXXXXXX,  _______, _______,  XXXXXXX, W_LSTRT, XXXXXXX, W_LEND,  XXXXXXX, _______, \
                    _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET,   XXXXXXX,M_QWERTY,M_COLEMAK,XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX,W_QWERTY,W_COLEMAK, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT , XXXXXXX, XXXXXXX,\
                    _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______ \
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    matrix_write_ln(matrix, read_timelog());
  } else {
    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    // matrix_write_ln(matrix, read_timelog());
    //matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
    set_timelog();
#endif
  }

  switch (keycode) {
    case W_COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_W_COLEMAK);
      }
      return false;
      break;
    case M_COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_M_COLEMAK);
      }
      return false;
      break;
    case M_LOWER:
      if (record->event.pressed) {
        layer_on(_M_LOWER);
        update_tri_layer_RGB(_M_LOWER, _M_RAISE, _ADJUST);
      } else {
        layer_off(_M_LOWER);
        update_tri_layer_RGB(_M_LOWER, _M_RAISE, _ADJUST);
      }
      return false;
      break;
    case M_RAISE:
      if (record->event.pressed) {
        layer_on(_M_RAISE);
        update_tri_layer_RGB(_M_LOWER, _M_RAISE, _ADJUST);
      } else {
        layer_off(_M_RAISE);
        update_tri_layer_RGB(_M_LOWER, _M_RAISE, _ADJUST);
      }
      return false;
      break;
    case W_LOWER:
      if (record->event.pressed) {
        layer_on(_W_LOWER);
        update_tri_layer_RGB(_W_LOWER, _W_RAISE, _ADJUST);
      } else {
        layer_off(_W_LOWER);
        update_tri_layer_RGB(_W_LOWER, _W_RAISE, _ADJUST);
      }
      return false;
      break;
    case W_RAISE:
      if (record->event.pressed) {
        layer_on(_W_RAISE);
        update_tri_layer_RGB(_W_LOWER, _W_RAISE, _ADJUST);
      } else {
        layer_off(_W_RAISE);
        update_tri_layer_RGB(_W_LOWER, _W_RAISE, _ADJUST);
      }
      return false;
      break;

    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}

/* encoder support */

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_DOWN);
    } else {
      tap_code(KC_UP);
    }
  } else if (index == 1) {
    if (clockwise) {
      tap_code(KC_DOWN);
    } else {
      tap_code(KC_UP);
    }
  }
}