#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <vector>

class Signal{
public:
    using Slot = std::function<void(std::array<float, 2>)>;

    void connect_cords(const Slot& slot);
    void emit_cords(std::array<float, 2>);

    void connect_optimal(const Slot& slot);
    void emit_optimal(std::array<float, 2>);


private:
    std::vector<Slot> cord_slots;
    std::vector<Slot> optimal_slots;
};


#endif
