#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

vector<string> splitString(string str)
{
    vector<string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, ' '))
    {
        result.push_back(token);
    }
    return result;
}

// initialize number of comparisons to 0
int num_comparisons = 0;

// function to compare the weight of two edges
// returns true when first edge weight is less than second edge weight
// indicating first edge comes before second in output
bool compare(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
{
    num_comparisons++;
    return a.first < b.first;
}

class Graph
{
public:
    int V;
    vector<pair<int, pair<int, int>>> edges;

    Graph(int V)
    {
        this->V = V;
    }
    // adds edge between vertices u and v with weight w
    void addEdge(int u, int v, int w)
    {
        edges.push_back(make_pair(w, make_pair(min(u, v), max(u, v))));
    }

    // returns vector of all edges in graph
    vector<pair<int, pair<int, int>>> getEdges()
    {
        return edges;
    }
};

class UnionFind
{
public:
    vector<int> parent; // stores parent of each element
    vector<int> rank;   // stores rank of each element

    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // returns parent of element x
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // merges sets containing u and v
    bool merge(int u, int v)
    {
        int set1 = find(u);
        int set2 = find(v);

        if (set1 == set2)
        {
            return false;
        }
        else if (rank[set1] < rank[set2])
        {
            parent[set1] = set2;
        }
        else
        {
            parent[set2] = set1;
        }
        if (rank[set1] == rank[set2])
        {
            rank[set2]++;
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
    // read input file
    int V = 0;
    fstream newfile;
    Graph *G;
    string fileName(argv[1]);
    newfile.open(fileName, ios::in);
    if (newfile.is_open())
    {
        string tp;
        vector<string> strVec;
        while (getline(newfile, tp))
        {
            strVec = splitString(tp);
            if (strVec.at(0) == "g")
            {
                V = stoi(strVec.at(1)) + 1;
                G = new Graph(V);
                break;
            }
        }
        while (getline(newfile, tp))
        {
            strVec = splitString(tp);
            if (strVec.at(0) == "e")
            {
                G->addEdge(stoi(strVec.at(1)) - 1, stoi(strVec.at(2)) - 1, stoi(strVec.at(3)));
            }
        }
    }
    newfile.close();

    // run Kruskal's algorithm to find minimum spanning tree
    vector<pair<int, pair<int, int>>> edges = G->getEdges();
    auto start_time = high_resolution_clock::now();
    sort(edges.begin(), edges.end(), compare);
    UnionFind *uf = new UnionFind(V);
    int cost = 0;
    int num_edges = 0;
    vector<pair<int, pair<int, int>>> mstEdges; // to store the edges in the minimum spanning tree
    for (int i = 0; i < edges.size() && num_edges < V - 1; i++)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        int w = edges[i].first;

        if (uf->merge(u, v))
        {
            num_edges++;
            cost += w;
            mstEdges.push_back(make_pair(w, make_pair(u, v)));
        }
    }
    // calculate runtime and output weight, runtime, and number of comparisons to standard error output file
    auto end = chrono::steady_clock::now();
    auto start = chrono::steady_clock::now();
    auto diff = chrono::duration_cast<chrono::milliseconds>(end - start);
    double runtime = diff.count() / 1000.0;
    // std::ofstream err_file("output.err");
    // std::cerr.rdbuf(err_file.rdbuf());

    cerr << "weight\t" << cost << endl;
    cerr << "runtime\t" << fixed << setprecision(2) << runtime << endl;
    cerr << "comparisons\t" << num_comparisons << endl;
    // err_file.close();

    // open the output file
    // ofstream outfile;
    // outfile.open("output.out");

    // output results to file
    cout << "c MST generated by Kruskal's Algorithm using Quick Sort" << endl;
    cout << "g " << V - 1 << " " << num_edges << endl;
    if (V - 1 != num_edges + 1)
        throw std::invalid_argument("Graph is not connected");
    for (int i = 0; i < mstEdges.size(); i++)
    {
        int u = mstEdges[i].second.first + 1;
        int v = mstEdges[i].second.second + 1;
        int w = mstEdges[i].first;
        cout << "e " << u << " " << v << " " << w << endl;
    }

    // close the output file
    // outfile.close();
}