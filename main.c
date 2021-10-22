#include "btstack_port_esp32.h"
#include "btstack_run_loop.h"

#include "driver/gpio.h"

#include <stdio.h>
#include <stddef.h>

/* Btn */

static btstack_timer_source_t btn_timer;
static void
btn_kick_timer(void){
    btstack_run_loop_set_timer(&btn_timer, 100);
    btstack_run_loop_add_timer(&btn_timer);
}

static void
btn_check_handler(btstack_timer_source_t* ts){
    (void)ts;
    printf("Btn = %d\n", gpio_get_level(39));

    btn_kick_timer();
}

static void
btn_config(void){
    int r;
    gpio_config_t cfg;
    cfg.intr_type = GPIO_INTR_DISABLE;
    cfg.mode = GPIO_MODE_INPUT;
    cfg.pull_up_en = 1;
    // G39 pin
    cfg.pin_bit_mask = GPIO_SEL_39;
    r = gpio_config(&cfg);
    printf("gpio config = %d\n", r);

    btn_timer.process = &btn_check_handler;
    btn_kick_timer();
}

/* App */

int 
app_main(void){
    int r;
    r = btstack_init();
    printf("btstack init = %d\n", r);

    btn_config();

    // Enter run loop (forever)
    btstack_run_loop_execute();
    return 0;
}

