/*
 *
 * Copyright (c) 2020 iAchieved.it, LLC.
 * Copyright (c) 2019 SiFive, Inc.
 * 
 * The MIT License
 * 
 * This code was written to blink the SiFive HiFive1 Rev B
 * onboard LED through its 7 colors by way of the GPIO controller.
 * 
*/

#include <stdio.h>

#include "digitalio.h"
#include "gpios.h"
#include "delay.h"

enum {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

const char* COLOR_SEQUENCE[] = {
"\e[30mBlack   - ",
"\e[31mRed     - ",
"\e[32mGreen   - ",
"\e[33mYellow  - ",
"\e[34mBlue    - ",
"\e[35mMagenta - ",
"\e[36mCyan    - ",
"\e[37mWhite   - "
};

#define RED_ON   0x1
#define GREEN_ON 0x2
#define BLUE_ON  0x4

int main(void) {

  pinMode(DIG_PIN_2, OUTPUT);
  pinMode(DIG_PIN_4, OUTPUT);
  pinMode(DIG_PIN_7, OUTPUT);
  pinMode(METAL_GPIO_19, DISABLE);
  pinMode(METAL_GPIO_21, DISABLE);
  pinMode(METAL_GPIO_22, DISABLE);
  
  while (1) {
    for (int i = 0; i < 8; i++) {

      printf(COLOR_SEQUENCE[i]);

      if (i & RED_ON) {
        printf("r ");
        pinMode(METAL_GPIO_22, OUTPUT);
        digitalWrite(DIG_PIN_2, 1);
      } else {
        printf("_ ");
        pinMode(METAL_GPIO_22, DISABLE);
        digitalWrite(DIG_PIN_2, 0);
      }

      if (i & GREEN_ON) {
        printf("g ");
        pinMode(METAL_GPIO_19, OUTPUT);
        digitalWrite(DIG_PIN_4, 1);
      } else {
        printf("_ ");
        pinMode(METAL_GPIO_19, DISABLE);
        digitalWrite(DIG_PIN_4, 0);
      }

      if (i & BLUE_ON) {
        printf("b\n");
        pinMode(METAL_GPIO_21, OUTPUT);
        digitalWrite(DIG_PIN_7, 1);
      } else {
        printf("_\n");
        pinMode(METAL_GPIO_21, DISABLE);
        digitalWrite(DIG_PIN_7, 0);
      }
      delay(1);
    }
  }
}
