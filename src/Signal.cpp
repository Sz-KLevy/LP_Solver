#include "Signal.h"

void Signal::connect_cords(const Slot& slot){
    cord_slots.push_back(slot);
}

void Signal::emit_cords(std::array<float, 2> point){
    for(auto &slot :cord_slots){
        slot(point);
    }
}


void Signal::connect_optimal(const Slot& slot){
    optimal_slots.push_back(slot);
}

void Signal::emit_optimal(std::array<float, 2> point){
    for(auto &slot :optimal_slots){
        slot(point);
    }
}
