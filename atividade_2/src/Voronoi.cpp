#include "../lib/Voronoi.hpp"
#define EDGE_WIDTH 4


Voronoi::Voronoi( std::vector< Vector2 > points, Sides *sides , Constrains * constrains ) {
    if( points.size() <= 0 ) {
        return;
    }
    
    std::pair< Vertex * , Vertex * > aux;

    this->points = points;
    this->constrains = constrains;
    this->sides = sides;
    
    
    initialBox.push_back( Vector2{ ( float )constrains->minXPosition , ( float )constrains->minYPosition } );
    initialBox.push_back( Vector2{ ( float )constrains->maxXPosition , ( float )constrains->minYPosition } );
    initialBox.push_back( Vector2{ ( float )constrains->maxXPosition , ( float )constrains->maxYPosition } );
    initialBox.push_back( Vector2{ ( float )constrains->minXPosition , ( float )constrains->maxYPosition } ); 
}

Voronoi::~Voronoi() {
    points.clear();
}

std::deque < std::deque< Vector2 > > Voronoi::Compute() {
    auto isEqual = []( Vector2 point1 , Vector2 point2 ) {
        return point1.x == point2.x && point1.y == point2.y;
    };
    std::deque < std::deque< Vector2 > > cells;
    std::deque< Vector2 > cell, newCell;
    Vector2 startVertex, endVertex;
    size_t firstIntersectionIndex, lastIntersectionIndex;
    Vector2 firstIntersection, lastIntersection;
    float distanceLineToSite, distanceLineToPoint;
    const float EPS = 7.5e-4f;

    for ( size_t indexSite = 0 ; indexSite < points.size() ; indexSite++ ) {
        cell = initialBox;
        for ( size_t indexPoint = 0 ; indexPoint < points.size() ; indexPoint++ ) {
            if( indexPoint == indexSite ) {
                continue;
            }
            Line linePerpendicularBisector = PerpendicularBisector( points.at( indexSite ) , points.at( indexPoint ) );
            if( linePerpendicularBisector.a == 0 && linePerpendicularBisector.b == 0 ) {
                continue;
            }
            newCell = std::deque< Vector2 >();
            for ( size_t vertexIndex = 0 ; vertexIndex < cell.size() ; vertexIndex++ ){
                startVertex = cell.at( vertexIndex );
                endVertex = cell.at( ( vertexIndex + 1 ) % cell.size() );
                firstIntersection = LineIntersectsEdge( linePerpendicularBisector , startVertex , endVertex );
                if( firstIntersection.x != -100 && firstIntersection.y != -100 ) {
                    if ( firstIntersection.x == endVertex.x && firstIntersection.y == endVertex.y ) {
                        newCell.push_back( endVertex );
                        newCell.push_back( cell.at( ( vertexIndex + 2 ) % cell.size() ) );

                        firstIntersectionIndex = ( vertexIndex + 2 ) % cell.size();
                    } else {
                        newCell.push_back( firstIntersection );
                        newCell.push_back( endVertex );

                        firstIntersectionIndex = ( vertexIndex + 1 ) % cell.size();
                    }
                    break;
                }
            }
            if( newCell.size() == 0 ) {
                newCell = cell;
            } else {
                for ( size_t vertexIndex = firstIntersectionIndex ; vertexIndex < cell.size() ; vertexIndex++ ) {
                    startVertex = cell.at( vertexIndex );
                    endVertex = cell.at( ( vertexIndex + 1 ) % cell.size() );
                    lastIntersection = LineIntersectsEdge( linePerpendicularBisector , startVertex , endVertex );
                    if( lastIntersection.x != -100 && lastIntersection.y != -100 ) {
                        newCell.push_back( lastIntersection );
                        lastIntersectionIndex = ( vertexIndex + 1 );

                        break;
                    } else {
                        newCell.push_back( endVertex );
                    }
                }
                if( !IsPointInPolygon( points.at( indexSite ) , newCell ) )  {
                    newCell = std::deque< Vector2 >();
                    if( !isEqual( lastIntersection , cell[ lastIntersectionIndex % cell.size() ] ) ) {
                        newCell.push_back( lastIntersection );
                    } 
                    for ( size_t vertexIndex = lastIntersectionIndex ; vertexIndex % cell.size() < firstIntersectionIndex || vertexIndex % cell.size() > firstIntersectionIndex ; vertexIndex++ ) {
                        startVertex = cell.at( vertexIndex % cell.size() );
                        endVertex = cell.at( ( vertexIndex + 1 ) % cell.size() );
                        if ( isEqual( startVertex , endVertex ) ) {
                            continue;
                        }
                        newCell.push_back( startVertex );
                    }
                    if( !isEqual( firstIntersection , startVertex ) ) {
                        newCell.push_back( firstIntersection );
                    }
                }
            }
            cell = newCell;
            firstIntersectionIndex = -1;
            lastIntersectionIndex = -1;
        }
        if( cell.size() > 0 ) {
            cells.push_back( cell );
            for ( size_t indexPoint = 0 ; indexPoint < points.size() ; indexPoint++ ) {
                if( indexSite == indexPoint ) {
                    continue;
                }
                for ( size_t edgeIndex = 0 ; edgeIndex < cell.size() ; edgeIndex++ ){
                    Vector2 midPoint = Vector2{ ( cell.at( edgeIndex ).x + cell.at( ( edgeIndex + 1 ) % cell.size() ).x ) / 2 , ( cell.at( edgeIndex ).y + cell.at( ( edgeIndex + 1 ) % cell.size() ).y ) / 2 };
                    distanceLineToPoint = DistancePointToPoint( midPoint , points.at( indexPoint ) ); 
                    distanceLineToSite = DistancePointToPoint( midPoint , points.at( indexSite ) ); 
                    if( std::fabs( distanceLineToPoint - distanceLineToSite ) < EPS ) {
                        sides->CreateSide( points.at( indexPoint ) , points.at( indexSite ) , constrains , BLUE , EDGE_WIDTH  );
                    }  
                }
            }
        } else {
            cells.push_back( std::deque< Vector2 >() );
        }
    }

    for ( size_t indexCells = 0 ; indexCells < cells.size() ; indexCells++ ) {
        for ( size_t index = 0 ; index < cells.at( indexCells ).size() ; index++ ) {
            sides->CreateSide( cells.at( indexCells ).at( index ) , cells.at( indexCells ).at( ( index + 1 ) % cells.at( indexCells ).size() ) , constrains , WHITE , EDGE_WIDTH );
        }
    }
    return cells;
}

float Voronoi::DistancePointToPoint( Vector2 point1 , Vector2 point2 ) {
    return std::sqrt( std::pow( point2.x - point1.x , 2 ) + std::pow( point2.y - point1.y , 2 ) );
}

bool Voronoi::IsPointInPolygon( Vector2 point , std::deque< Vector2 > polygon ) {
    Vector2 startVertex, endVertex, vectorEdge, vectorToPoint;
    float crossProduct, prevCrossProduct = 0;
    for ( size_t index = 0 ; index < polygon.size() ; index++ ) {
        startVertex = polygon.at( index );
        endVertex = polygon.at( ( index + 1 ) % polygon.size() );

        vectorEdge = Vector2{ endVertex.x - startVertex.x , endVertex.y - startVertex.y };
        vectorToPoint = Vector2{ point.x - startVertex.x , point.y - startVertex.y };

        crossProduct = ( vectorEdge.x * vectorToPoint.y ) - ( vectorEdge.y * vectorToPoint.x );

        if( crossProduct != 0 ) {
            if( prevCrossProduct == 0 ) {
                prevCrossProduct = crossProduct;
            } else if( crossProduct * prevCrossProduct < 0 ) {
                return false;
            }
        }
    }
    return true;   
}

Line Voronoi::PerpendicularBisector( Vector2 point1 , Vector2 point2 ) { // aX + bY + c = 0 line 
    Line line;
    Vector2 midPoint = Vector2{ ( point1.x + point2.x ) / 2 , ( point1.y + point2.y ) / 2 };
    line.a = point2.x - point1.x;
    line.b = point2.y - point1.y;
    line.c = -midPoint.x*line.a - midPoint.y*line.b;
    return line;
}

Line Voronoi::LineEquation( Vector2 point1 , Vector2 point2 ) { // aX + bY + c = 0 line 
    Line line;
    line.a = point1.y - point2.y;
    line.b = point2.x - point1.x;
    line.c = point1.x * point2.y - point2.x * point1.y;
    return line;
}

// Made with ai because i was struggling to make it robust enough, and getting rouding erros with floating point

Vector2 Voronoi::LineIntersectsEdge( Line linePerpendicularBisector, Vector2 startVertex, Vector2 endVertex) {
    // tolerâncias (ajuste conforme a escala do seu problema)
    const float D_TOL     = 1e-8f;   // determinante ~ paralelismo
    const float SEG_TOL   = 1e-8f;   // aresta degenerada (|v|^2)
    const float PARAM_TOL = 1e-6f;   // tolerância para t ∈ [0,1]

    Vector2 intersection;
    intersection.x = -100.0f; // sentinel
    intersection.y = -100.0f;

    Line edge = LineEquation(startVertex, endVertex);

    float a1 = linePerpendicularBisector.a, b1 = linePerpendicularBisector.b, c1 = linePerpendicularBisector.c;
    float a2 = edge.a,                b2 = edge.b,                c2 = edge.c;

    // Determinante (Cramer's rule)
    float D = a1 * b2 - a2 * b1;
    if (std::fabs(D) <= D_TOL) {
        // linhas praticamente paralelas ou coincidentes -> sem interseção única
        return intersection;
    }

    // Resolver sistema: a*x + b*y = -c
    float x = (b1 * c2 - b2 * c1) / D;
    float y = (a2 * c1 - a1 * c2) / D;

    // Verifica se a aresta é degenerada (pontos coincidentes)
    float dx = endVertex.x - startVertex.x;
    float dy = endVertex.y - startVertex.y;
    float len2 = dx*dx + dy*dy;
    if (len2 <= SEG_TOL) {
        // aresta muito curta -> sem interseção (ou implementar comportamento alternativo)
        return intersection;
    }

    // Teste robusto de pertencimento ao segmento via parâmetro t (projeção)
    // t = dot((P - P0), (P1 - P0)) / |P1-P0|^2
    float t = ((x - startVertex.x) * dx + (y - startVertex.y) * dy) / len2;
    if (t < -PARAM_TOL || t > 1.0f + PARAM_TOL) {
        // fora do segmento (mesmo com folga)
        return intersection;
    }

    // "Snap" para os endpoints se estiver ligeiramente fora por erro numérico
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    intersection.x = startVertex.x + t * dx;
    intersection.y = startVertex.y + t * dy;
    return intersection;
}