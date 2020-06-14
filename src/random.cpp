#include <iostream>
#include <map>
#include <vector>
#include <complex>
#include <random>
using namespace std;

using ll = long long;
using cd = complex<double>;

int main(){
    mt19937 mt(time(nullptr));

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 100, m = 150;

    cout << n << ' ' << m << endl;
    for(int i = 1; i < n; ++i)
        cout << i << ' ' << i + 1 << '\n';

    for(int i = n; i <= m; ++i){
        int x = uniform_int_distribution<int>(1, n)(mt);
        int y;
        do{
            y = uniform_int_distribution<int>(1, n)(mt);
        } while(x == y);

        cout << x << ' ' << y << '\n';
    }

    return 0;
}
