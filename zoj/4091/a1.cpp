#include <bits/stdc++.h>
using namespace std;

class BigNum {
private:
    static const int MAXN = 9999;
    static const int DLEN = 4;
    int a[500];  //可以控制大数的位数
    int len;     //大数长度
public:
    //构造函数
    BigNum() {
        len = 1;
        memset(a, 0, sizeof(a));
    }
    //将一个int类型的变量转化为大数
    BigNum(const int b) {
        int c, d = b;
        len = 0;
        memset(a, 0, sizeof(a));
        while (d > MAXN) {
            c = d - (d / (MAXN + 1)) * (MAXN + 1);
            d = d / (MAXN + 1);
            a[len++] = c;
        }
        a[len++] = d;
    }
    //将一个字符串类型的变量转化为大数
    BigNum(const char *s) {
        int t, k, index, l, i;
        memset(a, 0, sizeof(a));
        l = strlen(s);
        len = l / DLEN;
        if (l % DLEN)
            ++len;
        index = 0;
        for (i = l - 1; i >= 0; i -= DLEN) {
            t = 0;
            k = i - DLEN + 1;
            if (k < 0)
                k = 0;
            for (int j = k; j <= i; j++) t = t * 10 + s[j] - '0';
            a[index++] = t;
        }
    }
    //拷贝构造函数
    BigNum(const BigNum &T) : len(T.len) {
        memset(a, 0, sizeof(a));
        for (int i = 0; i < len; i++) a[i] = T.a[i];
    }
    //重载赋值运算符，大数之间进行赋值运算
    BigNum &operator=(const BigNum &n) {
        len = n.len;
        memset(a, 0, sizeof(a));
        for (int i = 0; i < len; i++) a[i] = n.a[i];
        return *this;
    }
    //重载输入运算符
    friend istream &operator>>(istream &in, BigNum &b) {
        static char ch[MAXN * 4];
        int i = -1;
        in >> ch;
        int l = strlen(ch);
        int count = 0, sum = 0;
        for (i = l - 1; i >= 0;) {
            sum = 0;
            int t = 1;
            for (int j = 0; j < 4 && i >= 0; j++, i--, t *= 10) {
                sum += (ch[i] - '0') * t;
            }
            b.a[count] = sum;
            count++;
        }
        b.len = count++;
        return in;
    }
    //重载输出运算符
    friend ostream &operator<<(ostream &out, BigNum &b) {
        out << b.a[b.len - 1];
        for (int i = b.len - 2; i >= 0; i--) {
            out.width(DLEN);
            out.fill('0');
            out << b.a[i];
        }
        return out;
    }
    //重载加法运算符，两个大数之间的相加运算
    BigNum operator+(const BigNum &T) const {
        BigNum t(*this);
        int big;  //位数
        big = T.len > len ? T.len : len;
        for (int i = 0; i < big; i++) {
            t.a[i] += T.a[i];
            if (t.a[i] > MAXN) {
                t.a[i + 1]++;
                t.a[i] -= MAXN + 1;
            }
        }
        if (t.a[big] != 0)
            t.len = big + 1;
        else
            t.len = big;
        return t;
    }
    //重载减法运算符，两个大数之间的相减运算
    BigNum operator-(const BigNum &T) const {
        int i, j, big;
        bool flag;
        BigNum t1, t2;
        if (*this > T) {
            t1 = *this;
            t2 = T;
            flag = 0;
        } else {
            t1 = T;
            t2 = *this;
            flag = 1;
        }
        big = t1.len;
        for (i = 0; i < big; i++) {
            if (t1.a[i] < t2.a[i]) {
                j = i + 1;
                while (t1.a[j] == 0) j++;
                t1.a[j--]--;
                while (j > i) t1.a[j--] += MAXN;
                t1.a[i] += MAXN + 1 - t2.a[i];
            } else {
                t1.a[i] -= t2.a[i];
            }
        }
        t1.len = big;
        while (t1.a[t1.len - 1] == 0 && t1.len > 1) {
            t1.len--;
            big--;
        }
        if (flag)
            t1.a[big - 1] = 0 - t1.a[big - 1];
        return t1;
    }
    //重载乘法运算符，两个大数之间的相乘运算
    BigNum operator*(const BigNum &T) const {
        BigNum ret;
        int i = 0, j = 0, up;
        int temp, temp1;
        for (i = 0; i < len; i++) {
            up = 0;
            for (j = 0; j < T.len; j++) {
                temp = a[i] * T.a[j] + ret.a[i + j] + up;
                if (temp > MAXN) {
                    temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);
                    up = temp / (MAXN + 1);
                    ret.a[i + j] = temp1;
                } else {
                    up = 0;
                    ret.a[i + j] = temp;
                }
            }
            if (up != 0)
                ret.a[i + j] = up;
        }
        ret.len = i + j;
        while (ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
        return ret;
    }
    //重载除法运算符，大数对一个整数进行相除运算
    BigNum operator/(const int &b) const {
        BigNum ret;
        int i, down = 0;
        for (i = len - 1; i >= 0; i--) {
            ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
            down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
        }
        ret.len = len;
        while (ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
        return ret;
    }
    //大数的n次方运算
    BigNum operator^(const int &n) const {
        BigNum t, ret(1);
        assert(n >= 0);
        if (n == 0)
            return 1;
        if (n == 1)
            return *this;
        int m = n, i;
        while (m > 1) {
            t = *this;
            for (i = 1; i << 1 <= m; i <<= 1) t = t * t;
            m -= i;
            ret = ret * t;
            if (m == 1)
                ret = ret * (*this);
        }
        return ret;
    }
    //大数对一个int类型的变量进行取模运算
    int operator%(const int &b) const {
        int i, d = 0;
        for (i = len - 1; i >= 0; i--) {
            d = ((d * (MAXN + 1)) % b + a[i]) % b;
        }
        return d;
    }
    //大数和另一个大数的大小比较
    bool operator>(const BigNum &T) const {
        int ln;
        if (len > T.len)
            return true;
        else if (len == T.len) {
            ln = len - 1;
            while (a[ln] == T.a[ln] && ln >= 0) ln--;
            if (ln >= 0 && a[ln] > T.a[ln])
                return true;
            else
                return false;
        } else {
            return false;
        }
    }
    //大数和一个int类型的变量的大小比较
    bool operator>(const int &t) const {
        BigNum b(t);
        return *this > b;
    }
    //输出大数
    void print() {
        cout << a[len - 1];
        for (int i = len - 2; i >= 0; i--) {
            cout.width(DLEN);
            cout.fill('0');
            cout << a[i];
        }
        cout << endl;
    }
};

char s[100010];
int main(void) {
    BigNum zero("0");
    int T;
    scanf("%d", &T);
    while (T--) {
        BigNum num, ans("0");
        cin >> num;
        while (num > zero) {
            num = num / 2;
            ans = ans + num;
        }
        cout << ans << endl;
    }
    return 0;
}
