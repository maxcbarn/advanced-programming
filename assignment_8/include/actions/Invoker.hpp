#ifndef INVOKER_HPP
#define INVOKER_HPP

#include "actions/Command.hpp"
#include <deque>
#include "grid/GridAdapter.hpp"

class Invoker
{
private:
    Invoker();
    inline static Invoker * invoker = nullptr;
    std::deque< Command * > actionList;
    GridAdapter * gridAdapter;
public:
    ~Invoker();
    static Invoker * GetInvoker();
    void Input();
    Command * GetCommand();
};

#endif
