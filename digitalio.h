#ifndef __digitalio_h__
#define __digitalio_h__

#include <stdint.h>

enum pin_mode {INPUT, OUTPUT, DISABLE};

#define HIGH 1
#define LOW  0

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);

#endif
