#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <array>
using namespace std;

struct AdjList {

};

struct Edge {
    int start;
    int end;
    int weight;
};

vector<string> splitString(string str) {
    char* arr = new char[100];
    
    char separator = ' ';
    int i = 0;
    vector<string> strVec;
    strcpy(arr, str.c_str());
    
    // Temporary string used to split the string.
    string s; 
    while (arr[i] != '\0') {
        if (arr[i] != separator) {
            // Append the char to the temp string.
            s += arr[i]; 
        } else {
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

void printAdjList(vector<Edge *> adjList[], int n) {
    for(int i=0; i<n; i++) {
    // for(auto edgeList: adjList) {
        cout << "Entry " << i << "\t";
        vector<Edge *> edgeList = adjList[i];
        for(int j=0; j<edgeList.size(); j++) {
            cout << edgeList.at(j)->start << edgeList.at(j)->end << edgeList.at(j)->weight << "\t";
        }
        cout << endl;
    }
}

struct Edge* createNewEdge(int s, int e, int w) {
    struct Edge* newEdge = new Edge;
    newEdge->start = s;
    newEdge->end = e;
    newEdge->weight = w;
    return newEdge;
}

void buildAdjacencyList(string fileName)
{
    int V = 0;
    fstream newfile;
    newfile.open("input.gph", ios::in); // open a file to perform read operation using file object
    if (newfile.is_open())
    { // checking whether the file is open
        string tp;
        vector<string> strVec;
        while (getline(newfile, tp))
        { // read data from file object and put it into string.
            strVec = splitString(tp);
            
            if(strVec.at(0) == "g") {
                V = stoi(strVec.at(1))+1;
                break;
            }
        }
        vector<Edge *> adjList[V];
        while (getline(newfile, tp)) {
            strVec = splitString(tp);
            if(strVec.at(0) == "e") {
                // Create Edge
                Edge* newEdge = createNewEdge(stoi(strVec.at(1)), stoi(strVec.at(2)), stoi(strVec.at(3)));
                
                adjList[stoi(strVec.at(1))].push_back(newEdge);
                adjList[stoi(strVec.at(2))].push_back(newEdge);
                // Add it to adjList
            }
        }
        printAdjList(adjList, sizeof(adjList)/sizeof(adjList[0]));
        newfile.close(); // close the file object.
    }
}

int main(int argc, char *argv[]) {
    buildAdjacencyList("input.gph");
}