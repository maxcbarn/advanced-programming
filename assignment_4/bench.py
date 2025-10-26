import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline

def main():
    data = pd.read_csv( "./logbenchmark.csv",  names=[  'ExecutionTime' , 'VertexQuantity' , 'VertexQuantityRobot' , 'PolyQuantity'] )
    drawTimeNumberOfPointsData = data.groupby( 'VertexQuantity' )['ExecutionTime'].mean().reset_index()
    DrawTimeNumberOfPoints( drawTimeNumberOfPointsData )

def DrawTimeNumberOfPoints( data ):
    
    x_smooth = np.linspace(data['ExecutionTime'].min(), data['ExecutionTime'].max(), 300)
    spl = make_interp_spline(data['ExecutionTime'], data['VertexQuantity'], k=3)  # k=3 → cúbica
    y_smooth = spl(x_smooth)

    # Plotar linha suave
    plt.plot(  y_smooth , x_smooth)
    plt.xlabel("Number Of Vertex")
    plt.ylabel("Time To Compute (ms)")
    plt.title("Time To Compute The Minkowski Sum In Relation To Vertex Quantity Of The Polygons")
    plt.legend()
    plt.grid( True )
    plt.tight_layout()
    plt.savefig( "timeXvertex.png" , bbox_inches='tight' );



main()