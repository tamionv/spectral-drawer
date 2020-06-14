#include <iostream>
#include <map>
#include <vector>
#include <random>
using namespace std;

auto mt = mt19937(12353);

class cactus{
    map<int, int> sizes;
    vector<pair<int, int>> edges;
public:
    cactus(){}

    void add_node(int index, int sz){
        assert(sz > 0);
        assert(sz % 2 == 1);
        sizes[index] = sz;
    }

    int prev = -1e9;
    void add_edge(int a, int b){
        assert(a > b);
        assert(a > prev);
        prev = a;
        edges.emplace_back(a, b);
    }

    vector<pair<int, int>> synthesize_edge_list(){
        vector<pair<int, int>> ret;

        map<int, vector<int>> indices;

        int curr = 1;
        for(auto x : sizes)
            for(int i = 0; i < x.second; ++i)
                indices[x.first].push_back(curr++);

        for(auto x : indices){
            assert(x.second.size() % 2 == 1);
            if((int)x.second.size() > 1)
                for(int i = 0, j = 1; i < (int)x.second.size(); ++i, ++j, j %= x.second.size())
                    ret.emplace_back(x.second[i], x.second[j]);
        }

        auto select_node_from_comp = [&](int x){
            return indices[x][
                uniform_int_distribution<int>(0, indices[x].size() - 1)(mt)];
        };

        for(auto x : edges)
            ret.emplace_back(
                    select_node_from_comp(x.first),
                    select_node_from_comp(x.second));

        return ret;
    }
};

void output_testcase(int n, vector<pair<int, int>> vec){
    shuffle(begin(vec), end(vec), mt);

    vector<int> permut(n + 1 , 0);
    iota(begin(permut), end(permut), 0);
    shuffle(begin(permut) + 1, end(permut), mt);

    for(auto& x : vec)
        x.first = permut[x.first],
        x.second = permut[x.second];

    cout << n << ' ' << vec.size() << '\n';
        
    for(auto x : vec)
        if(bernoulli_distribution(0.5)(mt))
            cout << x.first << ' ' << x.second << '\n';
        else
            cout << x.second << ' ' << x.first << '\n';

}

constexpr int maxn = 1000;

void generate_sun_testcase(int n){
    assert(n > 0 && n % 2 == 0);
    vector<pair<int, int>> edges;

    for(int i = 1; i < n / 2; ++i)
        edges.emplace_back(i, i+1);

    edges.emplace_back(1, n / 2);

    for(int i = 1, j = n / 2 + 1; i <= n / 2; ++i, ++j)
        edges.emplace_back(i, j);
    output_testcase(n, edges);
}

void generate_normal_testcase(double exp_cycle_size, double expected_cnt_simple_node, int max_height_difference){
    cactus cc;
    int left = maxn;

    for(int i = 0; left; ++i){
        int comp_sz = geometric_distribution<int>(1 / exp_cycle_size)(mt);
        if(comp_sz % 2 == 0) ++comp_sz;
        comp_sz = min(comp_sz, (left%2 == 0 ? left-1 : left));
        comp_sz = max(comp_sz, 1);

        if(bernoulli_distribution(expected_cnt_simple_node / maxn)(mt))
            comp_sz = 1;

        cc.add_node(i, comp_sz);
        left -= comp_sz;

        if(i > 0)
            cc.add_edge(
                i,
                uniform_int_distribution<int>(
                    max(0, i - max_height_difference),
                    i-1)(mt));
    }

    output_testcase(maxn, cc.synthesize_edge_list());
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    generate_normal_testcase(500, 50, 100000000);

    return 0;
}

