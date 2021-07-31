#include <iostream>
#include <vector>
#include <stack>
#include <map>

#define maxl 1000

#define maxn 100

#define maxw 100

#define inf 100000

  using namespace std;
  struct node {
      node(int a, int b, bool v) {
         fa = a;
         wn = b;
          vrfd = v;
      }
      node () {
          vrfd = false;
      }
      int fa, wn;
      bool vrfd;
  };
  int f[maxl+1];
  node lw[maxl+1];
  vector<string> words;
  stack<int> ans;
  string num;
  map<char, char> phone;


  int match(int pl, int wn) {
      for (int i = 0; i < words[wn].length(); i++) {
          if (pl == num.length() || phone[words[wn][i]] != num[pl])
              return -1;
          pl++;
      }
      return pl;
  }
  int main(int argc, const char * argv[]) {
      phone['o'] = phone['q'] = phone['z'] = '0';
      phone['w'] = phone['x'] = phone['y'] = '9';
      phone['t'] = phone['u'] = phone['v'] = '8';
      phone['p'] = phone['r'] = phone['s'] = '7';
      phone['m'] = phone['n'] = '6';
      phone['k'] = phone['l'] = '5';
      phone['g'] = phone['h'] = '4';
      phone['d'] = phone['e'] = phone['f'] = '3';
      phone['a'] = phone['b'] = phone['c'] = '2';
      phone['i'] = phone['j'] = '1';
      int wn, i, j, tmp1;
      string tmp;
      lw[0] = node(-1, -1, true);
      while (cin >> num && num != "-1") {
          words.clear();
          cin >> wn;
          while (wn--) {
              cin >> tmp;
              words.push_back(tmp);
          }
          f[0] = 0;
          for (i = 1; i <= maxl; i++) {
              f[i] = inf;
          }
          for (i = 1; i <= maxl; i++) {
              lw[i] = node(-1,-1,false);
          }
          for (i = 0; i < num.length(); i++) {
              for (j = 0; j < words.size(); j++) {
                  if (lw[i].vrfd && (tmp1 = match(i, j)) != -1 && f[tmp1] > f[i]+1) {
                      f[tmp1] = f[i] + 1;
                      lw[tmp1] = node(i, j, true);
                  }
              }
          }
          if (!lw[num.length()].vrfd) {
              cout << "No solution." << endl;
          } else {
              int itr = num.length();
              while (itr != 0) {
                  ans.push(lw[itr].wn);
                  itr = lw[itr].fa;
              }
              while (ans.size() != 1) {
                  cout << words[ans.top()] << " ";
                 ans.pop();
             }
             cout << words[ans.top()] << endl;
             ans.pop();
         }
     }
 }
