import numpy as np
import factorgraph as fg

# Make an empty graph
g = fg.Graph()

filetable = open("table-new.txt","r") #读入local feature function
rdtable = filetable.readlines()
tb = []
nnum = 0
for i in rdtable:  #处理信息压入tb中
	tb2 = []
	for j in i.split(' ')[:-1]:
		tb2.append(float(j))
	tb.append(tb2)
	
file = open("graph.txt","r")  #graph.txt是处理后的citation图，其中第一行两个数n,m表示点数和边数，第二行n个数表示它们的label，接下来m行每行两个数表示这两个数存在引用关系
rd = file.readlines()
nm = rd[0].split(' ') 
n=int(nm[0])  #得到点数和边数
m=int(nm[1])

for i in range(1,n+1): #对于所有边都有10*10的local feature function
	g.rv(str(i),10)

lb=rd[1].split(' ')
filepro = open("pro.txt","r")  #pro.txt表示中有n个01数，若第i个数为1，则表示它在训练集，否则表示它在测试集。
rdpro = filepro.readlines()
aa=rdpro[0].split(' ')

for i in range(1,n+1):  #枚举所有训练集中的点，表示它们是已知的。
	if (aa[i-1]=='1'):
		ff=[]
		for j in range(1,11):
			if (j!=int(lb[i-1])):
				ff.append(0.0)
			else:
				ff.append(1.0)
		g.factor([str(i)],potential=np.array(ff))
for i in range(2,len(rd)):  #枚举所有边，将这条边对应的10*10的表压入factorgraph中
	g.factor([str(int(rd[i].split(' ')[0])),str(int(rd[i].split(' ')[1]))], potential=np.array(tb))
# Run (loopy) belief propagation (LBP)
iters, converged = g.lbp(normalize=True)
print(('LBP ran for %d iterations. Converged = %r' % (iters, converged)))
print ()

# Print out the final marginals
Q,P=g.print_rv_marginals()  #将得到的答案存入Q中，并输出正确率
yess = 0
ssum = 0
for i in range(0,n):
	if (aa[i]=='0'):
		ssum += 1
		if (int(lb[i]) == Q[i]):
			yess += 1
print(yess,ssum,yess/ssum)
