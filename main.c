#include "btstack_port_esp32.h"
#include "btstack_run_loop.h"

#include <stddef.h>

int 
app_main(void){
    btstack_init();

    // Enter run loop (forever)
    btstack_run_loop_execute();
    return 0;
}

