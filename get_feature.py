import nltk.stem as ns
from textblob import TextBlob

MP={}
ff = 0
ssum = []
def work(x):  #利用自然语言处理库TextBlob进行处理
	wiki = TextBlob(x)

	lemmatizer = ns.WordNetLemmatizer()
	sum = []
	for word in wiki.tags:
		lemma = lemmatizer.lemmatize(word[0],'n')  #名词变原型
		lemma = lemmatizer.lemmatize(lemma,'v')  #动词变原型
		sum.append(lemma)
	wiki = TextBlob(' '.join(sum))

	#DT:the  IN:连词  CD:数次  TO:to  PRP:it  PRP$:them  CC:and  屏蔽这些feature
	List=wiki.tags
	lc = []
	for i in List:
		if i[1] not in ['DT','IN','CD','TO','PRP','PRP$','CC',''] and i[0]!="is":
			if i[0] not in MP:
				global ff
				ff += 1
				MP[i[0]] = ff  #得到的词典存放在MP中
			lc.append(MP[i[0]])
	ssum.append(lc)

file = open("useful.txt" , "r")  #简化后的数据
a = file.readlines() #a[0]存的是编号， a[1]存的是label
idx=a[0].split(' ')[:-1]
lb =a[1].split(' ')[:-1]
file2 = open("paper_dict.txt","r")
a = file2.readlines() #存标题
pp=[]
num = 0
for i in a:
	if int(lb[num])!=0:
		pp.append(i.split('\t')[1])
	num+=1
#pp里存的是所有paper的标题
for i in pp:  #对所有标题进行处理
	work(i)
	
filew = open("feature.txt","w")  #输出到feature.txt中
print(len(pp),ff,file=filew)
for i in lb:
	if int(i)!=0:
		print(i,end=" ",file=filew)
print(file=filew)
for i in ssum:
	print(len(i),end=" ",file=filew)
	for j in i:
		print(j,end=" ",file=filew)
	print(file=filew)
print(idx)
