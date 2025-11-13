#include "../../lib/grid/End.hpp"


End::End( Vector2 cellSize , IntVector2 position ) : Cell( cellSize , position ) {
    
}

End::~End() {

}

void End::Draw() {
    std::vector< Vector2 > aux;
    aux.push_back( Vector2{ position.y * cellSize.y  , position.x * cellSize.x } );
    aux.push_back( Vector2{ position.y * cellSize.y , ( 1 + position.x  ) * cellSize.x } );
    aux.push_back( Vector2{ ( 1 + position.y  ) * cellSize.y , ( 1 + position.x  ) * cellSize.x } );
    aux.push_back( Vector2{ ( 1 + position.y  ) * cellSize.y , position.x * cellSize.x } );
    DrawTriangleFan( aux.data() , 4 , END_COLOR );
    aux.clear();
}

