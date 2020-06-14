#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 1 << 6, m = n * 6 / 2;

    cout << n << ' ' << m << endl;

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < 6; ++j){
            int ii = i ^ (1 << j);
            if(i > ii) continue;

            cout << i+1 << ' ' << ii+1 << '\n';
        }

    return 0;
}
