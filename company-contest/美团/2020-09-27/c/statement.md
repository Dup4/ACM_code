偏爱字母
时间限制： 1000MS
内存限制： 65536KB
题目描述：
小美喜欢字母E，讨厌字母F。在小美生日时，小团送了小美一个仅包含字母E和F的字符串，小美想从中选出一个包含字母E数量与字母F数量之差最大的子串。

*子串：从字符串前面连续删去若干个字符，从后面连续删去若干个字符剩下的字符串（也可以一个都不删），例如abcab是fabcab的子串，而不是abcad的子串。我们将空串看作所有字符串的子串。



输入描述
第一行一个正整数 n表示字符串的长度。

第二行长度为n，且仅包含大写字母’E’,’F’的字符串（不含引号）

n<=300000

输出描述
输出一个整数，表示最大的差值


样例输入
5
EFEEF
样例输出
2

提示
样例解释
选择子串EE,此时有2个E，0个F,有最大差值2-0=2
另外，选择子串EFEE也可以达到最大差值。
