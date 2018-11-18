import pandas as pd

test = pd.read_csv("output.csv", header=0, nrows=10, usecols=[0,1,2,3])
print(test.head())
