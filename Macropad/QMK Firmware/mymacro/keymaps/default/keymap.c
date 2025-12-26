#include QMK_KEYBOARD_H

// 1. Definitionen für unsere Logik
enum custom_keycodes {
    MODE_SW = SAFE_RANGE
};

int encoder_mode = 0; // Startet bei Modus 0 (Lautstärke)

// 2. Deine Tastenbelegung
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        // Zeile 1: Copy, Win+V (Clipboard), Cut
        C(KC_C),    G(KC_V),    C(KC_X),   
        
        // Zeile 2: Undo, Win+E (Explorer), Task Manager
        C(KC_Z),    G(KC_E),    C(S(KC_ESC)),   

        // Encoder Klick -> Wechselt jetzt die Modi durch
        MODE_SW
    )
};

// 3. Logik für den Button-Druck (Modus wechseln + Farbe als Feedback)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MODE_SW:
            if (record->event.pressed) {
                // Modus hochzählen: 0 -> 1 -> 2 -> 0 ...
                encoder_mode = (encoder_mode + 1) % 3;
                
                // Visuelles Feedback
                if (encoder_mode == 0) {
                    // Modus 0: Lautstärke -> Weiß
                    rgblight_sethsv_noeeprom(HSV_WHITE); 
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                } 
                else if (encoder_mode == 1) {
                    // Modus 1: RGB Effekt -> Blau
                    rgblight_sethsv_noeeprom(HSV_BLUE);
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
                } 
                else if (encoder_mode == 2) {
                    // Modus 2: Helligkeit -> Rot
                    rgblight_sethsv_noeeprom(HSV_RED);
                    // Hier der Fix: STATIC_LIGHT statt BLINKING
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); 
                }
            }
            return false; // Wir haben den Keycode behandelt
    }
    return true; // Alle anderen Tasten normal verarbeiten
}

// 4. Logik für das Drehen (abhängig vom Modus)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { 
        switch (encoder_mode) {
            case 0: // Modus 0: Lautstärke
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            case 1: // Modus 1: RGB Animation wechseln
                if (clockwise) {
                    rgblight_step(); // Nächster Effekt
                } else {
                    rgblight_step_reverse(); // Vorheriger Effekt
                }
                break;

            case 2: // Modus 2: Helligkeit
                if (clockwise) {
                    rgblight_increase_val(); // Heller
                } else {
                    rgblight_decrease_val(); // Dunkler
                }
                break;
        }
    }
    return false;
}