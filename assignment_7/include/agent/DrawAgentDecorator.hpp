#ifndef DRAWAGENTDECORATOR_HPP
#define DRAWAGENTDECORATOR_HPP

#include "raylib.hpp"
#include "Settings.hpp"
#include <vector>

class DrawAgentDecorator{
private:
    DrawAgentDecorator * drawAgentDecorator;
public:
    DrawAgentDecorator( DrawAgentDecorator * drawAgentDecorator );
    virtual ~DrawAgentDecorator();
    virtual void Draw( Size_t2 start , Size_t2 end , std::vector< Size_t2 > path );
};

#endif