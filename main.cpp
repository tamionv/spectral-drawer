#include <valarray>
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
using namespace std;

constexpr double eps = 1e-3;

using vec = valarray<double>;

constexpr int imgsize = 512;

// Given a linear operator v on an n-dimensional vector space,
// find the k eigenvectors that correspond to the largest
// eigenvalues.
template <typename F>
vector<vec> find_nonnull_eigenvectors(F&& f, int n, int k){
    mt19937 mt(time(nullptr));

    // The eigenvalues found so far
    vector<vec> ret;

    while(ret.size() < k){
        // The current eigenvector
        vec me(n);

        // Randomly initialise `me`.
        for(int i = 0; i < n; ++i)
            me[i] = uniform_real_distribution<double>(-1000, 1000)(mt);

        // Now find eigenvector as limit of iteration.
        for(int i = 0; i < 100000; ++i){
            // Apply f.
            f(me);

            // Make perpendicular to ret.
            for(auto x : ret)
                me -= (me * x).sum() * x;
            
            // Normalise
            me /= sqrt((me * me).sum());
        }
       
        // Add `me` to result.
        ret.push_back(me);
    }

    return ret;
}

int main(){
    // Read # of vertices, # of edges.
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    vector<vector<int>> neighbours(n);

    // Read edges, storing them appropriately.
    for(auto& x : edges){
        cin >> x.first >> x.second;

        // Vertices will be 0-indexed internally,
        // but are read 1-indexed.
        --x.first;
        --x.second;

        neighbours[x.first].push_back(x.second);
        neighbours[x.second].push_back(x.first);
    }

    // This is the iteration described by the paper mentioned
    // in the README. The eigenvectors of this iteration that
    // correspond to large eigenvalues are the ones we will
    // use to draw the graph.
    auto apply = [&](vec& v) {
        static vec w(n);

        for(int i = 0; i < n; ++i){
            w[i] = 0;
            for(auto j : neighbours[i])
                w[i] += v[j];
            w[i] /= neighbours[i].size();
        }

        v = (w + v) / 2.0;
    };

    // Since the graph is presumably connected, we only need
    // 3 eigenvectors. The first one (the largest one) is 
    // constant, and is discarded. The next two form the
    // x and y coordinates we want.
    auto t = find_nonnull_eigenvectors(apply, n, 3);
    auto xs = t[1], ys = t[2];


    // These will be used to translate and scale the points
    // appropriately.
    const double maxx = xs.max() + eps, minx = xs.min() - eps;
    const double maxy = ys.max() + eps, miny = ys.min() - eps;

    // This array will store the image data.
    int img[imgsize][imgsize] = {};

    // Draw all edges.
    for(auto e : edges){
        // Each edge is drawn by adding `imgsize` + 100 intermediate
        // points to the image.
        const int points = imgsize + 100;

        // Calculate each ntermediate point.
        for(int i = 0; i < points; ++i){
            assert(xs[e.first] <= maxx);
            double x = xs[e.first] * i / points + xs[e.second] * (points - i) / points;
            double y = ys[e.first] * i / points + ys[e.second] * (points - i) / points;
            int xx = (x - minx) * (imgsize - 1) / (maxx - minx);
            int yy = (y - miny) * (imgsize - 1) / (maxy - miny);

            // And add it to the image.
            img[xx][yy] = 1;
        }
    }

    // Now we output the image in a pgm format.
    cout << "P1\n" << imgsize << ' ' << imgsize << '\n';
    for(int i = 0; i < imgsize; ++i)
        for(int j = 0; j < imgsize; ++j)
            cout << img[i][j] << ' ';

    return 0;
}
