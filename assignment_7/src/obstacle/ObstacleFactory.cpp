#include "obstacle/ObstacleFactory.hpp"

ObstacleFactory::ObstacleFactory() {

}

ObstacleFactory::~ObstacleFactory() {
    
}

ObstacleFactory * ObstacleFactory::GetObstacleFactory() {
    if( obstacleFactory == nullptr ) {
        obstacleFactory = new ObstacleFactory();
    }
    return obstacleFactory;
}

Obstacle * ObstacleFactory::Create( OBSTACLE_TYPE obstacleType , Size_t2 position ) {
    switch (obstacleType)
    {
    case WALL:
        return ( Obstacle * )new Wall( position );
        break;
    case MUD:
        return ( Obstacle * )new Mud( position );
        break;
    
    default:
        return nullptr;
        break;
    }
}