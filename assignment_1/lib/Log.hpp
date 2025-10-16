#ifndef LOG_HPP
#define LOG_HPP

#include "../lib/raylib.h"
#include <fstream>
#include <string>

class Log
{   
private:
    std::ofstream outFile;
public:
    Log();
    ~Log();
    void FormLog( Vector2 mousePosition , bool leftMouseButtonClick , bool rightMouseButtonClick , double drawTime , double actionTime , int pointQuantity , int vertexQuantity );
};

#endif