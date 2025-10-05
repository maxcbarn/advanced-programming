# Voronoi Diagram and Delaunay Triangulation

This code generates a voronoi diagram and using it generates a delaunau triangulation, i implemented the naive or brute force method, this method is like you are doing it on paper, so it relays in the mathematics principles of geometric analysis to find the intersections of lines and edges to make the voronoi cell.

It's logging the time to calculate the voronoi diagram and the delaunay triangulation and the number of points, so i made a graphical diagram in relation of these two variables.

## Use Cases 

The voronoi diagram can use to simulate cell structures, animal territories and the use that is most compelling to me is knowing the coverage area of services.

Link to some exemples: https://medium.com/data-science/the-fascinating-world-of-voronoi-diagrams-da8fc700fa1b

## Complexity

P = Points/Sites of voronoi
E = Edges of a voronoi cell
Ev = All edges of the voronoi diagram
Ed = All edges of the delaunay triangulation 

Time O( 2 * P² * E ) or simplified O( P² * E )  to compute voronoi and delaunay

Space O( P + Ev + Ed )
