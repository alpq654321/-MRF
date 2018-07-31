#include <bits/stdc++.h>
using namespace std;
vector <int> v[100005];
int lb[100005],n,m,A,B;
int N,M,i,j,X,aa[100005];
double tt[15][15],NEW[15][15],S,S2,Z,sum1,sum2;
int main()
{
    freopen("graph.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for (i=1; i<=n; i++) scanf("%d",&lb[i]);
    for (i=1; i<=n; i++) aa[i]=bool(rand()%10<5); //枚举每个点是否在训练集中，在这里训练集和测试集的概率是相同的。
    for (i=1; i<=m; i++)
    {
        scanf("%d%d",&A,&B);
        if (aa[A] && aa[B]){
        v[A].push_back(B);
        v[B].push_back(A);  //如果看做有向图删除这一句话即可。
        }
    }
    for (i=1; i<=n; i++)
        for (j=0; j<v[i].size(); j++)
            tt[lb[i]][lb[v[i][j]]]++;  //tt表示的就是local feature function
    double rt=0.00001; //学习率
    while (1) //不断迭代
    {
        rt/=2;  //这里做的是梯度下降，因此我们每次让学习率减少为它之前的二分之一
        for (M=1; M<=10; M++)
            for (N=1; N<=10; N++) NEW[M][N]=tt[M][N];  //NEW表示本次迭代后这个tt会变成什么样
        for (M=1; M<=10; M++)  
            for (N=1; N<=10; N++)
            {
                for (i=1; i<=n; i++)
                if (v[i].size()>0)
                {
                    sum1=0;
                    for (j=0; j<v[i].size(); j++)
                        if (lb[i]==M && lb[v[i][j]]==N) sum1++;
                    sum2=0;
                    for (j=0; j<v[i].size(); j++)
                        if (lb[v[i][j]]==N) sum2++;
                    S=0;
                    for (j=0; j<v[i].size(); j++)
                        if (lb[v[i][j]] == N)
                            S+=exp(tt[M][lb[v[i][j]]]);
                    Z=0;
                    for (X=1; X<=10; X++)
                    {
                        for (j=0; j<v[i].size(); j++)
                            Z+=exp(tt[X][lb[v[i][j]]]);
                    }
                    NEW[M][N]-=(sum1-S/Z)*rt;  //这里是利用论文里的推导出来的公式进行计算
                }
            }
		bool FLAG=true;
		for (M=1; M<=10; M++)
			for (N=1; N<=10; N++)
				if (fabs(NEW[M][N]-tt[M][N])<1e-5) FLAG=false;
		if (FLAG) break;  //这里用FLAG来表示表中的所有元素是否已经收敛，如果全部收敛则退出迭代。
        for (M=1; M<=10; M++)
            for (N=1; N<=10; N++) {tt[M][N]=NEW[M][N]; NEW[M][N]=0;}  //重新赋值给tt
    }
    freopen("table-new.txt","w",stdout);  //将整张表输出到table-new.txt中。 
    for (i=1; i<=10; i++)
    {
        for (j=1; j<=10; j++) cout<<tt[i][j]<<".0 ";
        cout<<endl;
    }
    fclose(stdout);
    freopen("pro.txt","w",stdout);  //将所有点是训练集还是测试集的信息输出到pro.txt中。
    for (i=1; i<=n; i++) cout<<aa[i]<<' ';
    return 0;
}
