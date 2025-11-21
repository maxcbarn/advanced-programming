#ifndef DRAWAGENTEND_HPP
#define DRAWAGENTEND_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "grid/GridAdapterFactory.hpp"

class DrawAgentEnd : DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentEnd( DrawAgentDecorator * drawAgentDecorator );
    ~DrawAgentEnd();
    void Draw( Size_t2 start , Size_t2 end , std::vector< Size_t2 > path ) override;
};

#endif