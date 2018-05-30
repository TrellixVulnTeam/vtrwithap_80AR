#ifndef CLOCK_MODELING_H
#define CLOCK_MODELING_H

#include "clustered_netlist_fwd.h"

enum e_clock_modeling_method {
    IDEAL_CLOCK, //Treat the clock pins as ideal (i.e. not routed)
    ROUTED_CLOCK //Treat the clock pins as normal nets (i.e. routed)
};


namespace ClockModeling
{
    /* Removes global pin flag from clock pins.
       This causes clock nets to also be treated as non-global;
       therefore, they will be routed using inter-block routing */
    void treat_clock_pins_as_non_globals();
}

#endif

