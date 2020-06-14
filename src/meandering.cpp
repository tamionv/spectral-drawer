#include <iostream>
#include <vector>
#include <random>
using namespace std;

mt19937 mt(1231);

constexpr int maxn = 1000;
int nxt = 2;
vector<pair<int, int>> edges;

constexpr double bushyness = 0.3, backness = 0.015;

void dfs(vector<int> st){
    int cnt = geometric_distribution<int>(bushyness)(mt);

    for(int i = 0; i < cnt && nxt < maxn; ++i){
        edges.emplace_back(st.back(), nxt);
        st.push_back(nxt++);
        dfs(st);
        st.pop_back();
    }

    if((bernoulli_distribution(backness)(mt)) && st.size() > 1)
        edges.emplace_back(st.back(), st.rbegin()[uniform_int_distribution<int>(1, st.size() - 1)(mt)]);
}


int main(){
    vector<int> v = { 1 };
    dfs(v);

    cout << nxt - 1 << ' ' << edges.size() << endl;
    for(auto x : edges)
        cout << x.first << ' ' << x.second << endl;
    return 0;
}

