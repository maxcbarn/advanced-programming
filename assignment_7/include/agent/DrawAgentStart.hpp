#ifndef DRAWAGENTSTART_HPP
#define DRAWAGENTSTART_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/GridAdapter.hpp"

class DrawAgentStart : DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentStart( DrawAgentDecorator * drawAgentDecorator );
    ~DrawAgentStart();
    void Draw( Size_t2 start , Size_t2 end , std::vector< Size_t2 > path ) override;
};

#endif