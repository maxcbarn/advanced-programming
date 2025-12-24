import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline

def main():
    dataTime = pd.read_csv("./log30X30.csv", names=['Ticks', 'TimeToMoveAgents' ])

    Log( dataTime )

def Log( data ):
    
    
    plt.plot(data['Ticks'], data['TimeToMoveAgents'] ,label='With Obstacle')
    
    plt.xlabel("Ticks")
    plt.ylabel("Time To Move Agents (s)")
    plt.title("Time To Move Agents Per Tick In Grid Size 30x30")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig( "graf.png" , bbox_inches='tight' );
    plt.clf()

    

""" def ObstacleXTime( data , df40 ):
    data = data[ data['PathQuantity'] == 20 ]
    data = data.groupby('PathQuantity')['ExecutionTime'].mean().reset_index()
    
    plt.plot(data['PathQuantity'], data['ExecutionTime'] ,label='With Obstacle')
    plt.plot(df40['PathQuantity'], df40['ExecutionTime'], label='Without Obstacle')
    
    plt.xlabel("Quantity of Paths")
    plt.ylabel("Time To Compute (ms)")
    plt.title("Time To Compute The Paths In Relation To The Quantity Of Obstacle Being 8 Times More Than Paths, And Grid Size 40x40")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig( "timeXobstacle.png" , bbox_inches='tight' );
    plt.clf()

def TimeXQuantity( data ):
    
    #x_smooth = np.linspace(data['ExecutionTime'].min(), data['ExecutionTime'].max(), 300)
    #spl = make_interp_spline(data['ExecutionTime'], data['PathQuantity'], k=3)  # k=3 → cúbica
    #y_smooth = spl(x_smooth)

    df20 = data[ data['Size'] == 20 ]
    df20 = df20.groupby('PathQuantity')['ExecutionTime'].mean().reset_index()
    df40 = data[ data['Size'] == 40 ]
    df40 = df40.groupby('PathQuantity')['ExecutionTime'].mean().reset_index()
    
    # Plotar linha suave
    plt.plot(df20[ 'PathQuantity' ], df20['ExecutionTime'], label='Grid Size 20x20')
    plt.plot(df40[ 'PathQuantity' ], df40['ExecutionTime'], label='Grid Size 40x40')
    
    plt.xlabel("Quantity of Paths")
    plt.ylabel("Time To Compute (ms)")
    plt.title("Time To Compute The Paths In Relation To The Path Quantity And Grid Size")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig( "timeXquantity.png" , bbox_inches='tight' );
    plt.clf()


def TimeXDist( data ):
    
    #x_smooth = np.linspace(data['ExecutionTime'].min(), data['ExecutionTime'].max(), 300)
    #spl = make_interp_spline(data['ExecutionTime'], data['PathQuantity'], k=3)  # k=3 → cúbica
    #y_smooth = spl(x_smooth)
    
    # Plotar linha suave
    plt.plot(data[ 'Dist' ], data['ExecutionTime'])
    
    plt.xlabel("Path Distance")
    plt.ylabel("Time To Compute (ms)")
    plt.title("Time To Compute The Paths In Relation To The Path Distance Grid Size 30x30")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig( "timeXdist.png" , bbox_inches='tight' );
    plt.clf() """

main()