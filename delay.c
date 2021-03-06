/*
 *
 * Copyright (c) 2020 iAchieved.it, LLC.
 * Copyright (c) 2019 SiFive, Inc.
 * 
 * The MIT License
*/

#include <stdio.h>
#include <metal/cpu.h>

#define RTC_FREQ    32768

struct metal_cpu* cpu;
struct metal_interrupt* cpu_intr, *tmr_intr;
int tmr_id;
volatile uint32_t timer_isr_flag;
static unsigned bootstrapped = 0;

int bootstrap(void);

// ISR - Interrupt Service Routine
void timer_isr(int id, void* data) {

  // Disable Timer interrupt
  metal_interrupt_disable(tmr_intr, tmr_id);

  // Flag showing we hit timer isr
  timer_isr_flag = 1;
}

/*
 *
 * delay for a bit, not guaranteed to be accurate
 * 
 */
void delay(unsigned seconds) {

  if (!bootstrapped) bootstrap();

  // Clear global timer ISR flag
  timer_isr_flag = 0;

  // Set timer
  metal_cpu_set_mtimecmp(cpu, metal_cpu_get_mtime(cpu) + (seconds*RTC_FREQ));

  // Enable Timer interrupt
  metal_interrupt_enable(tmr_intr, tmr_id);

  // wait till timer triggers and isr is hit
  while (timer_isr_flag == 0){};

  timer_isr_flag = 0;
}

/*
 *  
 * set things up for handling interrupts
 * 
 */
int bootstrap(void) {

    int rc;

    // Lets get the CPU and and its interrupt
    cpu = metal_cpu_get(metal_cpu_get_current_hartid());
    if (cpu == NULL) {
        printf("CPU null.\n");
        return 2;
    }
    cpu_intr = metal_cpu_interrupt_controller(cpu);
    if (cpu_intr == NULL) {
        printf("CPU interrupt controller is null.\n");
        return 3;
    }
    metal_interrupt_init(cpu_intr);

    tmr_intr = metal_cpu_timer_interrupt_controller(cpu);
    if (tmr_intr == NULL) {
        printf("TIMER interrupt controller is  null.\n");
        return 4;
    }
    metal_interrupt_init(tmr_intr);
    tmr_id = metal_cpu_timer_get_interrupt_id(cpu);
    rc = metal_interrupt_register_handler(tmr_intr, tmr_id, timer_isr, cpu);
    if (rc < 0) {
        printf("TIMER interrupt handler registration failed\n");
        return (rc * -1);
    }

    // Lastly CPU interrupt
    if (metal_interrupt_enable(cpu_intr, 0) == -1) {
        printf("CPU interrupt enable failed\n");
        return 6;
    }
}
