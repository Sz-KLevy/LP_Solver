#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>
#include <vector>

class Signal{
public:
    using Slot = std::function<void(std::array<float, 2>)>;

    void connect(const Slot& slot);
    void emit_cords(std::array<float, 2>);

private:
    std::vector<Slot> slotss;
};


#endif
