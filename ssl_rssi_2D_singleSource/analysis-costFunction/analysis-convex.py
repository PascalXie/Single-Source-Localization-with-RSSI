import numpy as np 
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import pyplot as plt 
from matplotlib import cm

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

	sizeBlocks = len(axs)
	for ID in range(sizeBlocks):
		Observations = []
		Observations.append(d2s[ID])
		Observations.append(axs[ID])
		Observations.append(ays[ID])

		blockValue = ResidualBlock(variables,Observations)

		CostValue = CostValue + blockValue**2
		#print("ID {}, blockValue {}".format(ID,blockValue))

	print("CostValue {}".format(CostValue))

	return CostValue

# main
print('Hello')

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


xxs = np.arange(-500,500,10.1)
xys = np.arange(-500,500,10.1)
#print(xx)

xxs_ = []
xys_ = []
costFunctionValues_ = []
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
	costFunctionValues_.append(costFunction_row)

costFunctionValues = np.array(costFunctionValues_)
print(xxs)
print(xys)
print(costFunctionValues_)
print(costFunctionValues)


fig = plt.figure()
ax = Axes3D(fig)
 
xxs, xys = np.meshgrid(xxs, xys)
ax.scatter(xxs, xys, costFunctionValues, marker='.', s=50, label='')
plt.show()
