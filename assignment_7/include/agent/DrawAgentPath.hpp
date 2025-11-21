#ifndef DRAWAGENTPATH_HPP
#define DRAWAGENTPATH_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/GridAdapter.hpp"

class DrawAgentPath : DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentPath( DrawAgentDecorator * drawAgentDecorator );
    ~DrawAgentPath();
    void Draw( Size_t2 start , Size_t2 end , std::vector< Size_t2 > path ) override;
};

#endif