/*
Copyright 2017 Peter Clarke <pete@clarkez.co.uk>

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
#include "keymap_common.h"

/*
  //
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
 /* 0 Qwerty */
     KEYMAP(7, SCLN,   B,    J,R,Z, F3,     ENT,   RIGHT , \
            6, RBRC,   A,    I,Q,Y, F2,     END,   DOWN, \
            5, LBRC,   FN0,  H,P,X, F1,     BSPC,  UP, \
            4, NUBS,   SLSH, G,O,W, LGUI,   F6,    LEFT, \
            3, EQL,    DOT,  F,N,V, CAPS,   TAB,   DEL, \
            2, MINS,   COMM, E,M,U, LALT,   ESC,   INS, \
            1, 9,      GRV,  D,L,T, LCTRL,  F5,    HOME, \
            0, 8,      QUOT, C,K,S, LSHIFT, F4,    SPC),
 /* 1 Functions */
     KEYMAP(TRNS, TRNS,   TRNS, TRNS,TRNS,TRNS, F9,   TRNS, TRNS , \
            TRNS, TRNS,   TRNS, TRNS,TRNS,TRNS, F8,   TRNS, PGDOWN, \
            TRNS, TRNS,   TRNS, TRNS,TRNS,TRNS, F7,   TRNS, PGUP, \
            TRNS, TRNS,   TRNS, TRNS,TRNS,TRNS, RGUI, F12,  TRNS, \
            TRNS, TRNS,   TRNS, TRNS,TRNS,TRNS, TRNS, TRNS, PGUP, \
            TRNS, TRNS,   TRNS, TRNS,TRNS,PGUP, TRNS, TRNS, PSCR, \
            TRNS, TRNS,   NUHS, PGDOWN,TRNS,TRNS, TRNS, F11,  PGDOWN, \
            TRNS, TRNS,   TRNS, TRNS,TRNS,TRNS, TRNS, F10,  TRNS)


};

const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};