import math
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

import seaborn as sns
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

d2s = []
axs = []
ays = []

def ResidualBlock(variables, observations):
	blockValue = 0 

	xx = variables[0]
	xy = variables[1]
	
	d2 = observations[0]
	ax = observations[1]
	ay = observations[2]
	
	blockValue = (ax-xx)**2 + (ay-xy)**2 - d2

	return blockValue

def CostFunction(variables):
	CostValue = 0

	xx = variables[0]
	xy = variables[1]

	sizeBlocks = len(axs)
	for ID in range(sizeBlocks):
		Observations = []
		Observations.append(d2s[ID])
		Observations.append(axs[ID])
		Observations.append(ays[ID])

		blockValue = ResidualBlock(variables,Observations)

		CostValue = CostValue + blockValue**2
		#print("ID {}, blockValue {}".format(ID,blockValue))

		t = 1.
		CostValue = CostValue - 1./t*math.log(-xx+110.)
		CostValue = CostValue - 1./t*math.log(xx+110.)
		CostValue = CostValue - 1./t*math.log(-xy+110.)
		CostValue = CostValue - 1./t*math.log(xy+110.)

	print("CostValue {}".format(CostValue))

	return CostValue

# main
print('Hello')
print(math.log(2.7))

#
data = open("observations.txt")
lines = data.readlines()
data.close()

for line in lines:
	line = line.strip()
	eles = line.split()
	AID = float(eles[0])
	axs.append(float(eles[1]))
	ays.append(float(eles[2]))
	XID = float(eles[3])
	d2s.append(float(eles[6]))


xxs = np.arange(-100,100,5.)
xys = np.arange(-100,100,5.)
#print(xx)

xxs_ = []
xys_ = []
costFunctionValues_ = []
costFunctionValues_Total_ = []
for IDy in range(len(xys)):
	costFunction_row = []
	for IDx in range(len(xxs)):
		xx = xxs[IDx]
		xy = xys[IDy]
		xxs_.append(xx)
		xys_.append(xy)
		variables = [xx,xy]
		print("variables")
		print(variables)
		value = CostFunction(variables)
		costFunction_row.append(value)
		costFunctionValues_Total_.append(value)
	costFunctionValues_.append(costFunction_row)

costFunctionValues = np.array(costFunctionValues_)
print(xxs)
print(xys)
print(costFunctionValues_)
print(costFunctionValues)


#fig = plt.figure()
#ax = Axes3D(fig)
# 
#xxs, xys = np.meshgrid(xxs, xys)
#ax.scatter(xxs, xys, costFunctionValues, marker='.', s=50, label='')
#plt.show()


list_region = xys_
list_kind = xxs_
list_values = costFunctionValues_Total_
counter = 0
for ele in list_values:
	list_values[counter] = -1.*math.log(ele)
	counter += 1

df = pd.DataFrame({'y':list_region,'x': list_kind,'CostFunctionValues':list_values})
#df['kind'].value_counts()
pt = df.pivot_table(index='y', columns='x', values='CostFunctionValues', aggfunc=np.sum)

f, (ax1) = plt.subplots(figsize = (6,4),nrows=1)
#cmap = sns.cubehelix_palette(start = 1.5, rot = 3, gamma=0.8, as_cmap = True)
#sns.heatmap(pt, linewidths = 0.05, ax = ax1, vmin=0, cmap=cmap)
sns.heatmap(pt, linewidths = 0.00, ax = ax1)

plt.show()
#
