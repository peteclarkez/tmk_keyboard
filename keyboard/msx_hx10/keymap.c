/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

/*
  //http://problemkaputt.de/portar.htm
  https://www.msx.org/forum/msx-talk/openmsx/rpilinux-keymapping
  Line  Bit_7 Bit_6 Bit_5 Bit_4 Bit_3 Bit_2 Bit_1 Bit_0
   0     "7"   "6"   "5"   "4"   "3"   "2"   "1"   "0"
   1     ";"   "]"   "["   "\"   "="   "-"   "9"   "8"
   2     "B"   "A"   ???   "/"   "."   ","   "'"   "`"
   3     "J"   "I"   "H"   "G"   "F"   "E"   "D"   "C"
   4     "R"   "Q"   "P"   "O"   "N"   "M"   "L"   "K"
   5     "Z"   "Y"   "X"   "W"   "V"   "U"   "T"   "S"
   6     F3    F2    F1   CODE   CAP  GRAPH CTRL  SHIFT
   7     RET   SEL   BS   STOP   TAB   ESC   F5    F4
   8    RIGHT DOWN   UP   LEFT   DEL   INS  HOME  SPACE
 ( 9    NUM4  NUM3  NUM2  NUM1  NUM0  NUM/  NUM+  NUM*  )
 ( 10   NUM.  NUM,  NUM-  NUM9  NUM8  NUM7  NUM6  NUM5  )

*/

/*
Line   0   1   2   3   4   5  6     7    8
Bit_7 "7" ";" "B" "J" "R" "Z" F3    RET  RIGHT
Bit_6 "6" "]" "A" "I" "Q" "Y" F2    SEL  DOWN
Bit_5 "5" "[" DED "H" "P" "X" F1    BS   UP
Bit_4 "4" "\" "/" "G" "O" "W" CODE  STOP LEFT
Bit_3 "3" "=" "." "F" "N" "V" CAP   TAB  DEL
Bit_2 "2" "-" "," "E" "M" "U" GRAPH ESC  INS
Bit_1 "1" "9" "'" "D" "L" "T" CTRL  F5   HOME
Bit_0 "0" "8" "`" "C" "K" "S" SHIFT F4   SPACE
*/

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {
    {KC_7,KC_SCOLON,   KC_B,     KC_J,KC_R,KC_Z,KC_F3,       KC_ENTER,  KC_RIGHT},
    {KC_6,KC_RBRACKET, KC_A,     KC_I,KC_Q,KC_Y,KC_F2,       KC_NO,     KC_DOWN},
    {KC_5,KC_LBRACKET, KC_NO,    KC_H,KC_P,KC_X,KC_F1,       KC_BSPACE, KC_UP},
    {KC_4,KC_BSLASH,   KC_SLASH, KC_G,KC_O,KC_W,KC_NO,       KC_NO,     KC_LEFT},
    {KC_3,KC_EQUAL,    KC_DOT,   KC_F,KC_N,KC_V,KC_CAPSLOCK, KC_TAB,    KC_DEL},
    {KC_2,KC_MINUS,    KC_COMMA, KC_E,KC_M,KC_U,KC_NO,       KC_ESC,    KC_INS},
    {KC_1,KC_9,        KC_QUOTE, KC_D,KC_L,KC_T,KC_LCTRL,     KC_F5,     KC_HOME},
    {KC_0,KC_8,        KC_NO,    KC_C,KC_K,KC_S,KC_LSHIFT,    KC_F4,     KC_SPACE}
    },
};

/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
};
