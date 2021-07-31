#include<iostream>          //Rakin Mohammad Sifullah
#include<time.h>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;
const int SIZE=50;
const int INF=0x3f3f3f3f;
const int MAXM=2000;
struct BigInteger {
    int len, s[SIZE + 5];

    BigInteger () {
        memset(s, 0, sizeof(s));
        len = 1;
    }
    BigInteger operator = (const char *num)
    {//String assignment
        memset(s, 0, sizeof(s));
        len = strlen(num);
        for(int i = 0; i < len; i++) s[i] = num[len - i - 1] - '0';
        return *this;
    }
        BigInteger operator = (const long long num)
        {//int assignment
        memset(s, 0, sizeof(s));
        char ss[SIZE + 5];
        sprintf(ss, "%lld", num);
        *this = ss;
        return *this;
    }
    BigInteger (long long num) {
        *this = num;
    }
    BigInteger (char* num) {
        *this = num;
    }
         string str() const {//Convert to string
        string res = "";
        for(int i = 0; i < len; i++) res = (char)(s[i] + '0') + res;
        if(res == "") res = "0";
        return res;
    }
    BigInteger clean() {
        while(len > 1 && !s[len - 1]) len--;
        return *this;
    }

    BigInteger operator + (const BigInteger& b) const {
        BigInteger c;
        c.len = 0;
        for(int i = 0, g = 0; g || i < max(len, b.len); i++) {
            int x = g;
            if(i < len) x += s[i];
            if(i < b.len) x += b.s[i];
            c.s[c.len++] = x % 10;
            g = x / 10;
        }
        return c.clean();
    }

    BigInteger operator - (const BigInteger& b) {
        BigInteger c;
        c.len = 0;
        for(int i = 0, g = 0; i < len; i++) {
            int x = s[i] - g;
            if(i < b.len) x -= b.s[i];
            if(x >= 0) g = 0;
            else {
                g = 1;
                x += 10;
            }
            c.s[c.len++] = x;
        }
        return c.clean();
    }

    BigInteger operator * (const int num) const {
        int c = 0, t;
        BigInteger pro;
        for(int i = 0; i < len; ++i) {
            t = s[i] * num + c;
            pro.s[i] = t % 10;
            c = t / 10;
        }
        pro.len = len;
        while(c != 0) {
            pro.s[pro.len++] = c % 10;
            c /= 10;
        }
        return pro.clean();
    }

    BigInteger operator * (const BigInteger& b) const {
        BigInteger c;
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < b.len; j++) {
                c.s[i + j] += s[i] * b.s[j];
                c.s[i + j + 1] += c.s[i + j] / 10;
                c.s[i + j] %= 10;
            }
        }
        c.len = len + b.len + 1;
        return c.clean();
    }

    BigInteger operator / (const BigInteger &b) const {
        BigInteger c, f;
        for(int i = len - 1; i >= 0; --i) {
            f = f * 10;
            f.s[0] = s[i];
            while(f >= b) {
                f = f - b;
                ++c.s[i];
            }
        }
        c.len = len;
        return c.clean();
    }
         //High precision modulo
    BigInteger operator % (const BigInteger &b) const{
        BigInteger r;
        for(int i = len - 1; i >= 0; --i) {
            r = r * 10;
            r.s[0] = s[i];
            while(r >= b) r = r - b;
        }
        r.len = len;
        return r.clean();
    }

    bool operator < (const BigInteger& b) const {
        if(len != b.len) return len < b.len;
        for(int i = len - 1; i >= 0; i--)
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
    bool operator > (const BigInteger& b) const {
        return b < *this;
    }
    bool operator <= (const BigInteger& b) const {
        return !(b < *this);
    }
    bool operator == (const BigInteger& b) const {
        return !(b < *this) && !(*this < b);
    }
    bool operator != (const BigInteger &b) const {
        return !(*this == b);
    }
    bool operator >= (const BigInteger &b) const {
        return *this > b || *this == b;
    }
    friend istream & operator >> (istream &in, BigInteger& x) {
        string s;
        in >> s;
        x = s.c_str();
        return in;
    }
    friend ostream & operator << (ostream &out, const BigInteger& x) {
        out << x.str();
        return out;
    }
};
struct MAT
{
    BigInteger s[2][2];
    MAT () {
        memset(s,0,sizeof(s));
    }
};

long long n,m,k;

MAT MAT_MUL(MAT &m1,MAT &m2)
{
    MAT m3;
    for (int i=0;i<2;i++) {
        for (int j=0;j<2;j++) {
            for (int k=0;k<2;k++)
                m3.s[i][j]=(m3.s[i][j]+m1.s[i][k]*m2.s[k][j])%m;
        }
    }
    return m3;
}
int main()
{
    while(scanf("%lld%lld%lld",&n,&k,&m)!=EOF)
    {
        BigInteger K(k),M(m);
        BigInteger ans;
        if (n==1) {
            ans=K-1;
            cout<<ans<<endl;
            continue;
        }
        else if (n==2) {
            ans=(K%M*(K-1+M)%M)%M;
            cout<<ans<<endl;
            continue;
        }
        else if (n==3) {
            BigInteger tmp=(K%M*(K-1+M)%M)%M;
            tmp=(tmp+K-1+M)%M;
            ans=((K-1+M)%M*tmp)%M;
            cout<<ans<<endl;
            continue;
        }
        BigInteger f2=(K%M*(K-1+M)%M)%M;
        BigInteger tmp=(K%M*(K-1+M)%M)%M;
        tmp=(tmp+K-1+M)%M;
        BigInteger f3=((K-1+M)%M*tmp)%M;
        //cout<<f2<<' '<<f3<<endl;
        K=K-1;
        MAT m1;
        m1.s[0][0]=f3;m1.s[0][1]=(long long)0;
        m1.s[1][0]=f2;m1.s[1][1]=(long long)0;
        MAT m2;
        m2.s[0][0]=K;m2.s[0][1]=K;
        m2.s[1][0]=(long long)1;m2.s[1][1]=(long long)0;
        n=n-3;
        while(n) {
            if (n&1) m1=MAT_MUL(m2,m1);
            m2=MAT_MUL(m2,m2);
            n=n>>1;
        }
        ans=m1.s[0][0];
        cout<<ans<<endl;
    }
    return 0;
}
