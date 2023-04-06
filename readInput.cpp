#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <array>
using namespace std;

struct Edge
{
    int start;
    int end;
    int weight;
};

struct Vertex
{
    // int key;
    vector<Edge *> edges;
};

struct Graph
{
    int size;
    Vertex **adjList;
};

struct Graph *createGraph(int size)
{
    Graph *graph = new Graph;
    graph->size = size;
    Vertex *adjListTemp[size];
    graph->adjList = adjListTemp;
    for (int i = 0; i < size; i++)
    {
        graph->adjList[i] = new Vertex;
    }
    return graph;
};

vector<string> splitString(string str)
{
    char *arr = new char[100];

    char separator = ' ';
    int i = 0;
    vector<string> strVec;
    strcpy(arr, str.c_str());

    // Temporary string used to split the string.
    string s;
    while (arr[i] != '\0')
    {
        if (arr[i] != separator)
        {
            // Append the char to the temp string.
            s += arr[i];
        }
        else
        {
            strVec.push_back(s);
            // cout << s << endl;
            s.clear();
        }
        i++;
    }
    strVec.push_back(s);

    // To print the vector
    /*
    for(int i=0; i < strVec.size(); i++) {
        std::cout << strVec.at(i) << ' ';
    }
    */

    return strVec;
}

void printAdjList(vector<Edge *> adjList[], int n)
{
    for (int i = 0; i < n; i++)
    {
        // for(auto edgeList: adjList) {
        cout << "Entry " << i << "\t";
        vector<Edge *> edgeList = adjList[i];
        for (int j = 0; j < edgeList.size(); j++)
        {
            cout << edgeList.at(j)->start << edgeList.at(j)->end << edgeList.at(j)->weight << "\t";
        }
        cout << endl;
    }
}

struct Edge *createNewEdge(Graph *graph, int s, int e, int w)
{
    struct Edge *newEdge = new Edge;
    newEdge->start = s;
    newEdge->end = e;
    newEdge->weight = w;

    cout << "d" << endl;
    graph->adjList[s]->edges.push_back(newEdge);
    cout << "d" << endl;

    graph->adjList[e]->edges.push_back(newEdge);

    return newEdge;
}

Graph *buildAdjacencyList(string fileName)
{
    int V = 0;
    fstream newfile;
    Graph *graph;
    newfile.open(fileName, ios::in); // open a file to perform read operation using file object
    if (newfile.is_open())
    { // checking whether the file is open
        string tp;
        vector<string> strVec;
        while (getline(newfile, tp))
        { // read data from file object and put it into string.
            strVec = splitString(tp);

            if (strVec.at(0) == "g")
            {
                V = stoi(strVec.at(1)) + 1;
                break;
            }
        }
        // Create graph (vertices array)
        graph = createGraph(V);
        // vector<Edge *> adjList[V];
        while (getline(newfile, tp))
        {
            strVec = splitString(tp);
            if (strVec.at(0) == "e")
            {
                // Create Edge and store it to vertices
                
                
                // Edge *newEdge = createNewEdge(graph, stoi(strVec.at(1)) - 1, stoi(strVec.at(2)) - 1, stoi(strVec.at(3)) - 1);
            }
        }
        // printAdjList(adjList, sizeof(adjList)/sizeof(adjList[0]));
        newfile.close(); // close the file object.
    }
    return graph;
}

int main(int argc, char *argv[])
{
    std::cout << argv[1] << std::endl;
    Graph *graph = buildAdjacencyList(argv[1]);
}