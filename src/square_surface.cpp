#include <iostream>
#include <random>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int k = 100;
    int n = k * k, m = 2 * (k - 1) * (k - 1) + (k - 1) + (k - 1);

    cout << n << ' ' << m << endl;

    auto point = [&](int x, int y){
        return 1 + k * x + y;
    };

    for(int i = 0; i < k; ++i)
        for(int j = 0; j < k; ++j)
            for(int dx = 0; dx < 2; ++dx){
                int di = i + dx, dj = j + 1 - dx;
                if(di == k || dj == k) continue;
                cout << point(i, j) << ' ' << point(di, dj) << '\n';
            }


    return 0;
}

