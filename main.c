#include <stdio.h>
#include "digitalio.h"
#include "gpios.h"

extern int  bootstrap(void);
extern void delay(unsigned);
void        loop(void);

int main(void) {

  bootstrap();

  pinMode(METAL_GPIO_19, DISABLE);
  pinMode(METAL_GPIO_21, DISABLE);
  pinMode(METAL_GPIO_22, DISABLE);

  while (1) {
    loop(); // Arduino-style
  }
}


#define RED_ON   0x1
#define GREEN_ON 0x2
#define BLUE_ON  0x4

void loop(void) {

  for (int i = 0; i < 8; i++) {

    if (i & RED_ON) {
      printf("R");
      pinMode(METAL_GPIO_22, OUTPUT);
    } else {
      printf("_");
      pinMode(METAL_GPIO_22, DISABLE);
    }

    if (i & GREEN_ON) {
      printf("G");
      pinMode(METAL_GPIO_19, OUTPUT);
    } else {
      printf("_");
      pinMode(METAL_GPIO_19, DISABLE);
    }

    if (i & BLUE_ON) {
      printf("B\n");
      pinMode(METAL_GPIO_21, OUTPUT);
    } else {
      printf("_\n");
      pinMode(METAL_GPIO_21, DISABLE);
    }

    delay(1);

  }
}
