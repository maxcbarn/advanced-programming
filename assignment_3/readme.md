# Convex Hull Algorithm

In this assignment the objective was to implement a convex hull algorithm, my implementation uses raylib to display the points and edges so make sure it's installed on your os, i implemented a incremental algorithm to solve the problem, having a time complexity of O ( n * log n ) that is the complexity of the sorting algorithm that is used to sort the points.

To analyze execution time i executed the program 30 time with a set number of points to get a precise reding, the results are in pointXtime.

The voronoi diagramm and the convex hull have a corelation that is kinda bizarre, if you get the 2d point and perform a paraboloid lift to 3d and calculate the convex hull of that set of 3d points and after that project the faces on 2d again you will have de delaunay triangulation that is the dual of the voronoi diagram.