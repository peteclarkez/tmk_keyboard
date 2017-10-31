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

#include <avr/io.h>
#include "stdint.h"
#include "led.h"

#include "print.h"
#include "debug.h"

void led_set(uint8_t usb_led)
{
    dprint("usb_led!: ");
    dprintf("%02X", usb_led);

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        dprintf(" CAPS ON ");
        DDRD |= (1<<0);
        PORTD |= (1<<0);
    } else {
        dprintf(" CAPS OFF ");
        // Hi-Z
        DDRD |= (1<<0);
        PORTD &= ~(1<<0);
    }
    dprintln();

}
