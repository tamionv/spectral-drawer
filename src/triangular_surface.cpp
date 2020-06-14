#include <iostream>
#include <random>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int k = 100;
    int n = k * (k + 1) / 2, m = 3 * k * (k - 1) / 2;

    cout << n << ' ' << m << endl;

    auto point = [&](int level, int where){
        return level * (level + 1) / 2 + where + 1;
    };

    for(int i = 0; i < k; ++i){
        for(int j = 0; j < i; ++j)
            cout << point(i, j) << ' ' << point(i, j + 1) << '\n';
        if(i < k - 1){
            for(int j = 0; j <= i; ++j){
                cout << point(i, j) << ' ' << point(i + 1, j) << '\n';
                cout << point(i, j) << ' ' << point(i + 1, j + 1) << '\n';
            }
        }
    }




    return 0;
}

