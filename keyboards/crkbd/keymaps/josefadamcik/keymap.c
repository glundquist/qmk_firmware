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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUITB GUI_T(KC_TAB)

#define KC_K_BSPFN LT(_SYMB, KC_BSPC)  /* Tap for backspace, hold for symbols layer */
/* Linux/win variants */
#define KC_W_UND LCTL(KC_Z)
#define KC_W_CUT LCTL(KC_X)
#define KC_W_CPY LCTL(KC_C)
#define KC_W_PST LCTL(KC_V)
#define KC_W_PWD LCTL(KC_LEFT)
#define KC_W_NWD LCTL(KC_RIGHT)
#define KC_W_LSTR KC_HOME
#define KC_W_LEND KC_END
/* Mac variants */
#define KC_M_UND LGUI(KC_Z)
#define KC_M_CUT LGUI(KC_X)
#define KC_M_CPY LGUI(KC_C)
#define KC_M_PST LGUI(KC_V)
#define KC_M_PWD LALT(KC_LEFT)
#define KC_M_NWD LALT(KC_RIGHT)
#define KC_M_LSTR LGUI(KC_LEFT)
#define KC_M_LEND LGUI(KC_RIGHT)

#define KC_GUIZ LGUI_T(KC_Z)
#define KC_ALTX LALT_T(KC_X)
#define KC_ALTDOT RALT_T(KC_DOT)
#define KC_GUISLSH RGUI_T(KC_SLSH)

#define KC_GUIEQ LGUI_T(KC_EQUAL)
#define KC_ALTMINS LALT_T(KC_MINS)
#define KC_ALTCOLN RALT_T(KC_COLN)
#define KC_GUIBSLS RGUI_T(KC_BSLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     F,     P,     G,                      J,     L,     U,     Y,  SCLN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TAB,     A,     R,     S,     T,     D,                      H,     N,     E,     I,     O,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,  GUIZ,  ALTX,     C,     V,     B,                      K,     M,  COMM, ALTDOT,GUISLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LCTL, LOWER,   ENT,   SPC, RAISE, RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       ESC,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      GRV,   EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  DQT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, GUIEQ,ALTMINS, PLUS,  LCBR,  RCBR,                   LBRC,  RBRC,  SCLN,ALTCOLN,GUIBSLS, RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LCTL, LOWER,   ENT,      SPC, RAISE, RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  PGUP , W_PWD,    UP, W_NWD, XXXXX, BSPC,\
  //|------+------+------+------+------+------|                |-u-----+------+------+------+------+------|
       TAB,  LALT,  LCTL,  LSFT, XXXXX,  CAPS,                  PGDN ,  LEFT,  DOWN, RIGHT,   DEL, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, W_UND, W_CUT, W_CPY, W_PST, XXXXX,                  XXXXX,W_LSTR, XXXXX,W_LEND, XXXXX, RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LCTL, LOWER,   ENT,      SPC, RAISE, RCTL \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        F1,    F2,    F3,    F4,    F5,    F6,                     F7,    F8,    F9,  F10,   F11,  F12 ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX,  RST,   LRST, XXXXX, XXXXX,                   INS,   PSCR,  APP, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 LCTL, LOWER,   ENT,      SPC, RAISE, RCTL \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

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
// void set_timelog(void);
// const char *read_timelog(void);

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
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
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
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}