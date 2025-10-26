# Minkowski Addition
In this assigment i was asked to program a Minkowski addition, to in the next assigment use to make collisions for a pathfindig algorithm.

It uses raylib has the graphics engine, so see in the repo root how to install. 

To create polygons press 1 and click using the left mouse button to create de vertexs, to finish the polygon press 1 again

# Algorithm

The input of te algorithm is a set of polygons and a base polygon, this base polygon is going to be used to calculate the minkowski sum of every polygon inside the set of polygons.

## Pre Processing

First we sort the first index of the polygons by lowest y axis, and then after by polar angle, this was implemented by rotatiing the vector of vertex that define the polygon so that the first has the lowest y axis.

Then we calculate the centroid of your base polygon and use it has a transformation to move the base polygon centroid to the ( 0 , 0 ) of the cordinate system, so that the minkowski additon when calculated sits on top of the original polygon without any extra tranformations.

## Minkowski Addition

For every poly in the set of polys:

Do the sum of the vertex of the base polygon and the polygon in the set
Calculate the cross product of the vectors created by the current index and the next of the polygon in the set and the base  polygon in this order
If is >= 0 and the index and the index is not the last of the polygon, advance the index by one ( if the vector are parralel or counter clock wise )
If is <= 0 and the index and the index is not the last of the base polygon, advance the index by one ( if the vector are parralel or clock wise )
Repeat until the last index of the polygon in the set and the base polygon

the cross product here is important to keep the vertexs in order and convex

# Complexity

B - Base polygon vertex quantity
N - Quantity of polygons in the set
V - All vertexs int the polys in the set

## Pre Processing

Sorting by y axis O( B + V )
Finding the centroid and transform the base polygon O( B )

Total O( 2B + V )

## Minkowski Addition

For all polys in the set of polys against the base poly, so that the resulting polys will have the sum of vertexs of the two polys 

O( B * N + V )

## Total

O( 2B + V + B * N + V )
O( 2B + 2V + B * N  ) 

Simplyfied - O( B * N )

# Benchmark

For the benchmark was generated random triangles, in quantitys of base 2, and for each quantity was computed 15 times the minkowski addition, so that when analyzed using python the data would be better.