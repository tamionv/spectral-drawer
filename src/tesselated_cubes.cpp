#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int sz = 14;
    int n = sz * sz * sz;

    vector<pair<int, int>> edges;

    auto point = [&](int x, int y, int z){
        return 1 + sz * sz * x + sz * y + z;
    };

    for(int i = 0; i < sz; ++i)
        for(int j = 0; j < sz; ++j)
            for(int k = 0; k < sz; ++k)
                for(int dx = 0; dx < 2; ++dx)
                    for(int dy = 0; dx + dy < 2; ++dy){
                        int di = i + dx, dj = j + dy, dk = k + 1 - dx - dy; 
                        if(di == sz || dj == sz || dk == sz) continue;

                        edges.emplace_back(point(i, j, k), point(di, dj, dk));
                    }


    cout << n << ' ' << edges.size() << endl;

    for(auto x : edges)
        cout << x.first << ' ' << x.second << endl;



    return 0;
}
