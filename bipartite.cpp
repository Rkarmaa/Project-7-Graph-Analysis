#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Graph
{
private:
    std::unordered_map<int, std::unordered_set<int>> Adj;
    std::vector<int> V;
    void build_graph(const std::string &filename);

public:
    Graph(const std::string &filename) { build_graph(filename); }
    bool is_bipartite();
};

void Graph::build_graph(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        std::string vertex_key, adj_lst;

        if (std::getline(iss, vertex_key, ':') && std::getline(iss, adj_lst))
        {
            int vertex = std::stoi(vertex_key);
            V.push_back(vertex);

            std::istringstream adj_stream(adj_lst);
            std::string neighbor_str;

            while (std::getline(adj_stream, neighbor_str, ','))
            {
                if (!neighbor_str.empty())
                {
                    int neighbor = std::stoi(neighbor_str);

                    // Add both directions (undirected)
                    Adj[vertex].insert(neighbor);
                    Adj[neighbor].insert(vertex);
                }
            }
        }
    }
}



// Pre-condition:
// The Graph has been constructed using build_graph().
// The vector V contains all vertex labels, and Adj stores the adjacency
// list of an undirected graph on these vertices.
//
// Post-condition:
// Returns true if and only if the graph is bipartite. If not bipartite, return false.

bool Graph::is_bipartite()
{
    // color[v] stores the color 0 or 1 assigned to vertex v
    unordered_map<int,int>color;

    // number of vertices stored in V
    int num = (int) V.size();

    // loop over every vertex in V
    for (int i = 0; i<num;i++){
        int initial = V[i];

        // if current vertex already has a color, its connected component, so skip it
        if(color.count(initial)>0){
            continue;
        }
        // Q can store the vertices to process in bfs order
        vector<int> Q;
        int head = 0;

        // start a new bfs from beginning and assign it color 0
        color[initial] = 0;
        Q.push_back(initial);

        // bfs loop processes vertices while there are still unprocessed entries in Q
        while(head < (int) Q.size()){

            // take the next vertex
            int u = Q[head];
            head++;

            // traverse all neighbors of u
            unordered_set<int> :: iterator p = Adj[u].begin();
            while (p != Adj[u].end()){

                // neighbor v has not been colored yet
                int v = *p;

                // assign v the opposite color of u
                if(color.count(v) == 0){
                    color[v] = 1 - color[u];

                    // add v to the queue so we later process its neighbors
                    Q.push_back(v);
                }
                else{   // neighbor v already has a color

                // if v has the same color as u, so graph is not bipartite
                    if (color[v] == color[u]){
                        return false;
                    }
                }
                // move to next neighbor of u
                p++;
            }  
        }
    }
    // the graph is bipartite
    return true;
}