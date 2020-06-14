#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int h = 100, rad = 50;

    cout << h * rad << ' ' << 2 * (h - 1) * rad + rad << '\n';
 
    auto point = [&](int x, int y){
        return rad * x + y + 1;
    };

    for(int i = 0; i < h; ++i){
        for(int j = 0; j < rad; ++j){
            cout << point(i, j) << ' ' << point(i, (j + 1)%rad) << '\n';
            if(i+1 < h)
                cout << point(i, j) << ' ' << point(i+1, j) << '\n';
        }
    }




    return 0;
}

