#include "digitalio.h"

#include <assert.h>
#include <metal/gpio.h>

/*
 * Set the mode of a pin to either input or output
 *
 * @param pin
 * @param mode
 */
void pinMode(uint8_t pin, uint8_t mode) {
  struct metal_gpio* gpio_device = metal_gpio_get_device(0);
  if (!gpio_device) return;

  switch (mode) {
    case INPUT: {
      metal_gpio_disable_output(gpio_device, pin);
      metal_gpio_enable_input(gpio_device, pin);
    } break;
    case OUTPUT: {
      metal_gpio_enable_output(gpio_device, pin);
      metal_gpio_disable_input(gpio_device, pin);
    } break;
    case DISABLE: {
      metal_gpio_disable_output(gpio_device, pin);
      metal_gpio_disable_input(gpio_device, pin);
    } break;
    default:
      break;
  }
}

/*
 * Set the output of a pin to a given value
 *
 * @param pin
 * @param val
 */
void digitalWrite(uint8_t pin, uint8_t val) {
  struct metal_gpio* gpio_device = metal_gpio_get_device(0);
  if (!gpio_device) return;

  metal_gpio_set_pin(gpio_device, pin, val);
}
