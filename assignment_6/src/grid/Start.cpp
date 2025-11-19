#include "../../lib/grid/Start.hpp"


Start::Start( IntVector2 position ) : Cell( position ) {
    
}

Start::~Start() {

}

void Start::Draw() {
    std::vector< Vector2 > aux;
    aux.push_back( Vector2{ position.y * cellSize.y  , position.x * cellSize.x } );
    aux.push_back( Vector2{ position.y * cellSize.y , ( 1 + position.x  ) * cellSize.x } );
    aux.push_back( Vector2{ ( 1 + position.y  ) * cellSize.y , ( 1 + position.x  ) * cellSize.x } );
    aux.push_back( Vector2{ ( 1 + position.y  ) * cellSize.y , position.x * cellSize.x } );
    DrawTriangleFan( aux.data() , 4 , START_COLOR );
    aux.clear();
}

