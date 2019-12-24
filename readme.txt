为了使整个代码框架更清晰，我们使用中文来进行讲解。
在这个codes文件夹中，代码和功能如下：
1) get_feature.py  利用Core中的所有domain和title进行feature提取。在提取之前我们已将数据进行处理得到简化后的数据，并存放在useful.txt中。
2) Bayes.cpp  在C++中实现的Bayes算法，从feature.txt中读入所有feature，并测试Bayes算法的正确率。在测试combined algorithm中只需对Bayes.cpp进行稍许改动就能正常工作。
3) ml.py  包含其余5个基于feature的预测方法，这里我们直接调用现成的库，并测试它们的正确率。
4) factorgraph.py  从github里找到的LBP的代码，可以控制最大迭代次数以及处理非对称的factor graph，在实验过程中我们多次调用这一代码。
5) MRF.py  将整个local feature function读入进MRF中，并调用LBP来预测所有paper每个domain的概率，最终可以求得MRF的正确率。
6) get_graph_factor.cpp  在C++中实现的MRF关于训练集的学习方法，其中包括初始local feature function以及每次迭代时的变化，最终输出这张表到table-new.txt再让MRF.py来进行调用。

test

sese