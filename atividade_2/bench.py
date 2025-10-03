import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def main():
    data = pd.read_csv( "./log_1.csv",  names=['MouseX' , 'MouseY' , 'LeftMouseButton' , 'RightMouseButton' , 'DrawTime' , 'ActionTime' , "NumberOfPoints" , 'MunberOfSides' ] )
    drawTimeNumberOfPointsData = data.groupby( 'NumberOfPoints' , as_index=False )['DrawTime'].mean()
    DrawTimeNumberOfPoints( drawTimeNumberOfPointsData )


def DrawTimeNumberOfPoints( data ):
    
    plt.plot( data['NumberOfPoints'] , data['DrawTime'] )
    plt.xlabel("Number Of Points")
    plt.ylabel("Time To Draw (ms)")
    plt.title("Time To Draw Points On Screen In Relation To Quantity")
    plt.legend()
    plt.grid( True )
    plt.savefig( "graph.png" );
    plt.show()







main()