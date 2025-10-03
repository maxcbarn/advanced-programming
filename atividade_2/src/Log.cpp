#include "../lib/Log.hpp"

Log::Log() {
    outFile.open("./log.csv"); 
}

Log::~Log() {
    outFile.close();
}

void Log::FormLog( Vector2 mousePosition , bool leftMouseButtonClick , bool rightMouseButtonClick , double drawTime , double actionTime , int pointQuantity , int vertexQuantity , double voronoiTime ) {
    outFile << mousePosition.x << "," << mousePosition.y << "," << leftMouseButtonClick << "," << rightMouseButtonClick << "," << drawTime << "," << actionTime << ","  << voronoiTime << "," << pointQuantity << "," << vertexQuantity << std::endl;
}