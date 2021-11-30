#include <iostream>
#include <vector>

using namespace std;

    
class DSU {
    int* parent;
    int* rank;
public:
    DSU(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
    int find(int i) {
        if (parent[i] == -1) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]){
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

class Graph {
    vector<vector<int>> edgelist;
    int V;
public:
    Graph(int V) {
        this->V = V;
    }
    void addEdge(int x, int y, int w) {
        edgelist.push_back({ w,x,y });
    }
    int kruskals_mst() {

        for (int i = 0; i < edgelist.size(); i++) {
            for (int j = i; j < (edgelist.size()); j++) {
                if (edgelist[i] > edgelist[j]) {
                    swap(edgelist[i], edgelist[j]);
                }
            }
        }

        DSU s(V);
        int ans = 0;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            if (s.find(x) != s.find(y)) {
                cout << x << " - " << y << endl;
                s.unite(x, y);
                ans += w;
            }
        }
        return ans;
    }
};

struct input {
    int x;
    int y;
    int w;
};

int main()
{
    
        // x, y, weight
    /*
    input z[51];
    int c=0,x,y,w;
    while (x != '\0'){
      cin>>x>>y>>w;
      if (x == '\0') break;
      c++;

    }

    */
    Graph g(20);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 11, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.addEdge(8, 9, 4);
    g.addEdge(9, 10, 7);
    g.addEdge(10, 2, 9);//17
    g.addEdge(2, 11, 3);
    g.addEdge(11, 7, 1);//19
    g.addEdge(10, 11, 4);

    /*g.addEdge(10, 17, 8);
    g.addEdge(11, 12, 8);
    g.addEdge(11, 17, 11);
    g.addEdge(12, 13, 7);
    g.addEdge(12, 18, 2);
    g.addEdge(12, 15, 4);
    g.addEdge(13, 14, 9);
    g.addEdge(13, 15, 14);
    g.addEdge(14, 15, 10);
    g.addEdge(15, 16, 2);
    g.addEdge(16, 17, 1);
    g.addEdge(16, 18, 6);
    g.addEdge(17, 18, 7);*/

    cout << g.kruskals_mst();
}

