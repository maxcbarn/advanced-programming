#ifndef REMOVECELL_HPP
#define REMOVECELL_HPP

#include "actions/Command.hpp"
#include "Settings.hpp"
#include "grid/Cell.hpp"

class RemoveCell : Command
{
private:
    Cell * cell;
public:
    RemoveCell();
    ~RemoveCell();
    void Execute() override;
};

#endif
