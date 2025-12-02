#ifndef DRAWAGENTPATH_HPP
#define DRAWAGENTPATH_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>
#include "agent/DrawAgentDecorator.hpp"
#include "grid/GridAdapterFactory.hpp"
#include "grid/GridAdapter.hpp"
#include "agent/Agent.hpp"

class DrawAgentPath : public DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentPath( DrawAgentDecorator * drawAgentDecorator );
    ~DrawAgentPath();
    void Draw( Agent * agent ) override;
};

#endif