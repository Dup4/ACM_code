小美的书架
时间限制： 1000MS
内存限制： 65536KB
题目描述：
小美的书架上有很多书，是个爱读书的新时代好青年。

小团虽然也喜欢看书，但大多数时候都更喜欢来小美家蹭书读。

这就导致小美的书架上很多书都会被小团借走。

小美很烦这一点，就想出了一个招数，小美的书架是一行一行的，她会对一些行加锁，这样小团就借不走了。

现在小团想要借书，请你帮忙看看小团能不能借到书，如果可以借到的话在哪一行书架上有这本书。

为了简单起见，每本书将用一个正整数进行编号，小美的书架一共有N行。



输入描述
第一行两个正整数N，M，Q，表示小美书架有N行编号1到N，书本编号从1到M，接下来有Q个操作

接下来Q行，每行是下列操作中的一种：

1 x y : x是书本的编号，y是书架的行编号，代表小美将编号为x的书本放置到y行上。若该书本在小团手上则放置无效，若原来该书在书架上且原行上锁则放置无效，若该书被放置到一个锁了的行上则放置无效。

2 y : y是书架的行编号，代表小美将行编号为y的书架加锁，对已经上锁的书架行该操作无效。

3 y : y是书架的行编号，代表小美将行编号为y的书架锁去掉，对无锁的书架行该操作无效。

4 x : x 是书本的编号，代表小团想借编号为x的书本，对该操作若可以借到输出一行正整数在哪一行，借不到输出一行-1

5 x : x是书本的编号，代表小团还给小美编号为x的书本。若该书本不在小团手上该操作无效。

N ≤10000 , M≤10000 , Q≤100000

输出描述
对于每个操作4，若可以借到输出一行正整数在哪一行，借不到输出一行-1


样例输入
5 5 10
1 1 4
1 2 3
1 3 1
2 1
4 1
5 2
4 3
4 5
3 1
4 2
样例输出
4
-1
-1
3
