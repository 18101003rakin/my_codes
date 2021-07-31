
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define EPS 10e-8

using namespace std;int main(){
    double p,q;
    cin >>p>>q;
    double  k = 1;
    p+=EPS;q-=EPS;
    while(1){
        int a = int(k*p)/100,b=int(k*q)/100;
        //cout<<ceil(a)<<" "<<floor(b)<<endl;
        if(a!=b) break;
        k++;
    }
    cout<< k<<endl;
    return 0;
}
