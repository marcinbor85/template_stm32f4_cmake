#include <stdint.h>

#include "system/tick.h"

uint32_t timer_port_get_current_tick(void)
{
        return tick_get_value();
}