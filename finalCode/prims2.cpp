#include "Heap.h"
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <chrono>

using namespace std;
/*
Defines en Edge of the graph. It has information
such as source Node, Destination Node and the weight of
the edge.

*/
class Edge
{
private:
    int source;
    int destination;
    int weight;

public:
    Edge() = default;
    Edge(int _src, int _dst, int _wt)
    {
        source = _src;
        destination = _dst;
        weight = _wt;
    }

    int getweight()
    {
        return weight;
    }

    int getnode()
    {
        return destination;
    }
    friend ostream &operator<<(ostream &os, Edge *E);
};

/*
Defines the Graph. It also handles the adjecacncy List
Each element of the List is an object if class  Edge.
*/
class Graph
{
private:
    vector<vector<Edge *>> adj_list;
    int size;

public:
    Graph() = default;
    Graph(int _size)
    {
        size = _size;
        adj_list.resize(size);
    }

    void resize(int _size)
    {
        size = _size;
        adj_list.resize(size);
    }
    void addEdge(int _src, int _dst, int _wt)
    {
        Edge *E1 = new Edge(_src, _dst, _wt);
        adj_list[_src].push_back(E1);
        Edge *E2 = new Edge(_dst, _src, _wt);
        adj_list[_dst].push_back(E2);
    }

    vector<Edge *>::iterator begin(int node)
    {
        return adj_list[node].begin();
    }

    vector<Edge *>::iterator end(int node)
    {
        return adj_list[node].end();
    }
};

ostream &operator<<(ostream &os, Edge *E)
{
    if (E->source < E->destination)
        std::cout << "e " << E->source + 1 << " " << E->destination + 1 << " " << E->weight << endl;
    else
        std::cout << "e " << E->destination + 1 << " " << E->source + 1 << " " << E->weight << endl;
    return os;
}

vector<string> splitString(string str)
{
    char *arr = new char[100];

    char separator = ' ';
    int i = 0;
    vector<string> strVec;
    strcpy(arr, str.c_str());

    string s;
    while (arr[i] != '\0')
    {
        if (arr[i] != separator)
        {

            s += arr[i];
        }
        else
        {
            strVec.push_back(s);

            s.clear();
        }
        i++;
    }
    strVec.push_back(s);

    return strVec;
}

int main(int argc, char *argv[])
{
    /*
    Create the Graph
    */

    Graph G;

    int V = 0;
    fstream newfile;
    Graph *graph;
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
                break;
            }
        }

        G.resize(V);

        while (getline(newfile, tp))
        {
            strVec = splitString(tp);
            if (strVec.at(0) == "e")
            {
                G.addEdge(stoi(strVec.at(1)) - 1, stoi(strVec.at(2)) - 1, stoi(strVec.at(3)));
            }
        }
    }
    newfile.close();

    map<int, bool> seen;
    map<int, bool> visited;
    long comparison = 0;

    /*
    Lambda function which defines the comparisons
    that take place in the heap. this is passed as
    a parameter to the heap.
    */
    auto cmp = [&comparison](Edge *E1, Edge *E2)
    {
        comparison++;

        return E1->getweight() > E2->getweight();
    };

    int runtime;
    Heap<Edge *, decltype(cmp)> h(cmp);

    vector<Edge *>::iterator it = G.begin(0);
    auto start = chrono::high_resolution_clock::now();
    for (; it != G.end(0); it++)
    {
        h.push(*it);
    }

    visited[0] = true;
    int count = 1;
    long sum = 0;
    vector<Edge *> MST;

    /*
    Get the edge with the least weight and add all the edges
    that are adjecant to the destination of this edge. repeat this
    till all the nodes are visited or till the heap is empty whichever
    happens first.
    */
    while (!h.empty() && count < V)
    {
        Edge *D = h.top();
        h.pop();
        int node = D->getnode();
        int wt = D->getweight();
        if (visited[node])
            continue;
        count++;
        MST.push_back(D);
        visited[node] = true;
        sum += wt;
        vector<Edge *>::iterator it = G.begin(node);
        for (; it != G.end(node); it++)
            h.push(*it);
    }
    auto end = chrono::high_resolution_clock::now();
    auto diff = chrono::duration_cast<chrono::seconds>(end - start);
    runtime = diff.count();
    if (count < V - 1)
        throw std::invalid_argument("Graph is not connected");
    else
    {
        cout << "g " << V - 1 << " " << MST.size() << endl;
        for (Edge *I : MST)
            cout << I;

        cerr << "weight " << sum << endl;
        cerr << "comaprisons " << comparison << endl;
        cerr << "runtime " << runtime << endl;
    }

    return 0;
}
