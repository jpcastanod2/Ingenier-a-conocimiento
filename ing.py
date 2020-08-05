from tkinter import filedialog as fd
import pandas as pd
import numpy as np

direcionBD = fd.askopenfilename()
direcionBD

BD = pd.read_excel(direcionBD)asd
BD.head()

BD.shape

BD.info()

BD.head()

BD.describe()


#Limpiamos missings en valor

BD[11].replace(to_replace=0, value=np.nan, inplace = True)
BD.head()

#Limpiamos columnas iguales
BD.iloc[0, 11]
i = 0
j = 0
while (i<9):
    iguales = True
    while (j<1000):
        if (BD.iloc[j,i] == BD.iloc [j,i+1]):
            j = j+1
        else:
            iguales = False
            break
            j =  j+1
    if (iguales == True):
        BD.drop(i, axis=1, inplace= True)
    i = i +1
    
BD.head()
            
    
