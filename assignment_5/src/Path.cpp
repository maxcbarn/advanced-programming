#include "../lib/Path.hpp"

Path::Path( std::pair< size_t , size_t> start , std::pair< size_t , size_t > end , std::pair< Edges * , std::vector< size_t > > path ) {
    this->start = start;
    this->end = end;
    this->path = path.first;
    pathRowsColumns = path.second;
}

Path::~Path() {
    delete path;
    pathRowsColumns.clear();
}

void Path::Draw() {
    if( path == nullptr ) {
        return;
    }
    path->Draw( EDGE_PATH_COLOR );
}

void Path::SetPath( std::pair< Edges * , std::vector< size_t > > path ) {
    if( this->path != nullptr ) {
        delete this->path;
    }
    this->path = path.first;
    pathRowsColumns = path.second;
}