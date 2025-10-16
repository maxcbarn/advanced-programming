import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline

def main():
    data = pd.read_csv( "./largelog.csv",  names=[  'NumberOfPoints' , 'ExecutionTime' , 'NumberOfPointsOfConvex' , 'NumberOfPointsInsideConvex' ] )
    drawTimeNumberOfPointsData = data.groupby( 'NumberOfPoints' )['ExecutionTime'].mean().reset_index()
    DrawTimeNumberOfPoints( drawTimeNumberOfPointsData )
    AAA( data )

def AAA( data ):
    pointsIn =  data.groupby( 'NumberOfPointsInsideConvex' )['ExecutionTime'].mean().reset_index()
    pointsCovex =  data.groupby( 'NumberOfPointsOfConvex' )['ExecutionTime'].mean().reset_index()

    # Plotar linha suave
    plt.plot( pointsIn[ 'NumberOfPointsInsideConvex' ],pointsIn[ 'ExecutionTime' ], label='Inside Convex', color='blue', linestyle='-')

    # Plot the second line
    plt.plot( pointsCovex[ 'NumberOfPointsOfConvex' ], pointsCovex[ 'ExecutionTime' ],label='Convex Hull', color='red', linestyle='-')
    plt.xlabel("Number Of Points")
    plt.ylabel("Time To Compute (ms)")
    plt.title("Time To Compute The Convex Hull In Relation To Quantity Of Points")
    plt.legend()
    plt.grid( True )
    plt.savefig( "pointInConvexXtime.png" );

def DrawTimeNumberOfPoints( data ):
    
    x_smooth = np.linspace(data['ExecutionTime'].min(), data['ExecutionTime'].max(), 300)
    spl = make_interp_spline(data['ExecutionTime'], data['NumberOfPoints'], k=3)  # k=3 → cúbica
    y_smooth = spl(x_smooth)

    # Plotar linha suave
    plt.plot(  y_smooth , x_smooth)
    plt.xlabel("Number Of Points")
    plt.ylabel("Time To Compute (ms)")
    plt.title("Time To Compute The Convex Hull In Relation To Quantity Of Points")
    plt.legend()
    plt.grid( True )
    plt.savefig( "pointXtime.png" );



main()