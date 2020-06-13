#include <valarray>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

constexpr double eps = 1e-3;

using vec = valarray<double>;

constexpr int imgsize = 512;

double dot(const vec& v, const vec& w){
    return (v * w).sum();
}

vec normalise(const vec& v){
    return v / sqrt((v * v).sum());
}

vec project(const vec& q, const vec& v){
    return dot(v, q) * q;
}

vec perpendicularise(const vec& q, const vec& v){
    return v - project(q, v);
}

template <typename F>
vector<vec> find_nonnull_eigenvectors(F&& f, int n, int k){
    vector<vec> ret;

    while(ret.size() < k){
        bool is_good = true;

        vec me(1, n);
        for(int i = 0; i < n; ++i)
            me[i] = rand();

        for(auto x : ret)
            me = perpendicularise(x, me);
        me = normalise(me);

        for(int i = 0; i < 1000; ++i){
            auto new_me = f(me);

            for(auto x : ret)
                new_me = perpendicularise(x, new_me);

            me = normalise(new_me);
        }
       
        ret.push_back(me);
    }

    return ret;
}

int main(int argc, char **argv){
    srand(time(nullptr));

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    vector<vector<int>> neighbours(n);

    for(auto& x : edges){
        cin >> x.first >> x.second;
        --x.first;
        --x.second;

        neighbours[x.first].push_back(x.second);
        neighbours[x.second].push_back(x.first);
    }

    auto apply = [&](const vec& v) -> vec {
        vec w(n);

        for(int i = 0; i < n; ++i){
            w[i] = 0;
            for(auto j : neighbours[i])
                w[i] += v[j];
            w[i] /= neighbours[i].size();
        }
        return (w + v) / 2.0;
    };

    auto t = find_nonnull_eigenvectors(apply, n, 3);

    auto xs = t.rbegin()[0], ys = t.rbegin()[1];

    const double maxx = xs.max() + eps, minx = xs.min() - eps;
    const double maxy = ys.max() + eps, miny = ys.min() - eps;

    int arr[imgsize][imgsize] = {};

    for(auto e : edges){
        const int points = imgsize + 100;

        for(int i = 0; i < points; ++i){
            assert(xs[e.first] <= maxx);
            double x = xs[e.first] * i / points + xs[e.second] * (points - i) / points;
            double y = ys[e.first] * i / points + ys[e.second] * (points - i) / points;
            int xx = (x - minx) * (imgsize - 2) / (maxx - minx);
            int yy = (y - miny) * (imgsize - 2) / (maxy - miny);

            arr[xx][yy] = 1;
        }
    }

    cout << "P1\n" << imgsize << ' ' << imgsize << '\n';

    for(int i = 0; i < imgsize; ++i)
        for(int j = 0; j < imgsize; ++j)
            cout << arr[i][j] << ' ';

    return 0;
}
