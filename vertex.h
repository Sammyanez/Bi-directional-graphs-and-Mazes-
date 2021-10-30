//
// Created by Sammy on 10/30/2021.
//

#ifndef MZ1_VERTEX_H
#define MZ1_VERTEX_H

#include <vector>

using namespace std;

// A helper class implementing a vertex in
// an adjacency-list-based graph.
class Vertex
{
public:
    Vertex(int r, int c)
    {
        row = r;
        col = c;
        marked = false;
    }

    // Corresponding row and column location in maze
    int row;
    int col;
    bool marked;

    // List of neighboring vertices
    vector<Vertex*> neighs;

};
#endif //MZ1_VERTEX_H
