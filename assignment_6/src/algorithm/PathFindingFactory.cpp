#include "../../lib/algorithm/PathFindingFactory.hpp"

PathFindingFactory::PathFindingFactory() {

}

PathFindingFactory::~PathFindingFactory() {

}

PathFinding * PathFindingFactory::Create( PATH_TYPE pathType ) {
    switch (pathType)
    {
    case EXACT:
        return ( PathFinding * )new Dijkstra();
        break;
    
    default:
        return nullptr;
        break;
    }
}