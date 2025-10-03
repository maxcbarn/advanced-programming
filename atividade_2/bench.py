import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def main():
    data = pd.read_csv( "./log_1.csv",  names=['MouseX' , 'MouseY' , 'LeftMouseButton' , 'RightMouseButton' , 'DrawTime' , 'ActionTime' , 'VoronoiDelaunayTime' , "NumberOfPoints" , 'MunberOfSides' ] )
    drawTimeNumberOfPointsData = data.groupby( 'NumberOfPoints' , as_index=False )['VoronoiDelaunayTime'].mean()
    DrawTimeNumberOfPoints( drawTimeNumberOfPointsData )


def DrawTimeNumberOfPoints( data ):
    
    plt.plot( data['NumberOfPoints'] , data['VoronoiDelaunayTime'] )
    plt.xlabel("Number Of Points")
    plt.ylabel("Time To Draw (ms)")
    plt.title("Time To Compute Voronoi And Delaunay In Relation To Quantity Of Points")
    plt.legend()
    plt.grid( True )
    plt.savefig( "graph.png" );
    plt.show()







main()