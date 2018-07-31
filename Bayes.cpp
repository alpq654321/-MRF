#include <bits/stdc++.h>
using namespace std;
int lb[100005],n,m,A,B,i,j,t[15][100005],pi[100005],k,a[100005],ans,num[15],X;
double lpi[100005],lt[15][100005],sum,MAX;
vector <int> v[100005];
int main()
{
    freopen("feature.txt","r",stdin);
	// 读入feature图的信息
    scanf("%d%d",&n,&m);
    for (i=1; i<=n; i++) scanf("%d",&lb[i]);
    for (i=1; i<=n; i++)
    {
        scanf("%d",&A);
        while (A--)
        {
            scanf("%d",&B);
            v[i].push_back(B);
        }
    }
    
    for (i=1; i<=n; i++) a[i]=i;
    for (double rt=0.1; rt<=0.95; rt+=0.1)  //枚举training 数据集的比例
    {
        for (i=1; i<=10; i++) pi[i]=num[i]=0;
        for (i=1; i<=10; i++)
            for (j=1; j<=m; j++) t[i][j]=0;
        random_shuffle(a+1,a+n+1);
        k=int(n*rt);  //令前k个点为training 数据集 
        for (i=1; i<=k; i++)
        {
            for (j=0; j<v[a[i]].size(); j++)
              t[lb[a[i]]][v[a[i]][j]]++;  //表示论文中的beta
            pi[lb[a[i]]]++;  //表示论文中的pi
        }
        for (i=1; i<=10; i++)  //这里是上课讲过的改良版的Bayes，论文里由于空间限制没有提到
            for (j=1; j<=m; j++)
            {
                t[i][j]++;
                num[i]+=t[i][j];
            }
		//得到t和pi经过取对数后的值
        for (i=1; i<=10; i++) lpi[i]=log((double)pi[i]/k);
        for (i=1; i<=10; i++)
            for (j=1; j<=m; j++)
              lt[i][j]=log((double)t[i][j]/num[i]); 
        for (i=k+1; i<=n; i++)  //枚举测试集里的所有元素
        {
            X=0;
            for (j=1; j<=10; j++)  //枚举所有domain
            {
                sum=lpi[j];
                for (int K=0; K<v[a[i]].size(); K++)
                    sum+=lt[j][v[a[i]][K]];
                if (sum>MAX || X==0) MAX=sum,X=j;  //寻找概率最高的domain
            }
            if (X==lb[a[i]]) ans++; //ans 存储预测正确的结果个数
        }
        printf("%.1f %.5f\n",rt,(double)ans/(n-k));  
        ans=0;
    }
    return 0;
}
