#include "Signal.h"

void Signal::connect(const Slot& slot){
    slotss.push_back(slot);
}

void Signal::emit_cords(std::array<float, 2> point){
    for(auto &slot :slotss){
        slot(point);
    }
}
