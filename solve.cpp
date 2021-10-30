//
// Created by Sammy on 10/30/2021.
//
#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>
using namespace std;
#include "solve.h"

class directedGraph{
private:




    unordered_map<string, Vertex*> vertexMap;

    //Bread crumb trail, computed by BFS,
    //providing shortest path from some source vertex
    unordered_map<Vertex*, Vertex*> breadCrumbs;

    void breadthFirstSearch(Vertex* S)
    {
        //Setup
        queue<Vertex*> Q;
        breadCrumbs.clear();

        //Step 0:

        Q.push(S);

        //Step 1: BFS loop!
        while (! Q.empty())
        {
            //Step 1.1
            Vertex* x;
            x = Q.front();
            Q.pop();

            //step 1.2: visit x's univisted neighbors
            for (int i=0; i<x->neighs.size(); i++)    //all x's neighbors y)
            {
                Vertex* y = x->neighs[i];
                if (!y->marked) //y not marked)
                {
                    //y->marked = true;
                    y->marked = true; //mark y;
                    Q.push(y); //put y in Q;

                    //Augmentation: keep track of breadcrumb pointers
                    //y->breadCrumb = x;
                    breadCrumbs[y] = x;
                }
            }
        }
    }

public:
    directedGraph()
    {

    }

    string shortestPath(string start, string destination,string maze,int length)
    {
        //Step 0: get the vertices of start and destination
        Vertex* sVert = vertexMap[start];
        Vertex* dVert = vertexMap[destination];

        //Step 1: use BFS to compute shoretest paths from source sVert
        //Shortest paths get encoded in the breadCrumbs map.
        breadthFirstSearch(sVert);
        int row = 0;
        int col = 0;
        int row_x_length = 0;
        int index = 0;
        //Step 2: Follow bread crumbs trail from dVert to sVert
        Vertex* current = dVert;

        while (current != sVert)
        {
            row = current->row;
            row_x_length = row * length;
            col = current->col;
            index = row_x_length+col;
            maze[index] = 'o';

            current = breadCrumbs[current];
        }

        row = length * current->row;
        col = current->col;
        index = row+col;
        maze[index] = 'o';

        //Done, return it
        return maze;
    }

    void addVertex(int i, int j)
    {
        Vertex* babyVertex = new Vertex(i,j);
        vertexMap[to_string(i) + "," + to_string(j)] = babyVertex;
    }

    //Add a directed conncection going from x to y
    void addDirectedEdge(string X, string Y )
    {
        Vertex* xVert = vertexMap[X];
        Vertex* yVert = vertexMap[Y];

        xVert->neighs.push_back(yVert);
    }

    //Add a bidirectional connection between x and y
    void addBasicEdge(string X, string Y )
    {
        if(vertexMap.find(Y) == vertexMap.end()){
            return;
        }
        addDirectedEdge(X, Y);
        addDirectedEdge(Y, X);
    }
};


string solve(string maze) {
    directedGraph G;
    int length_comparison = 0;
    int i = 0;
    int j = 0;
    int length = 0;
    int height = 0;
    string start = "";
    string end = "";
    unordered_map<Vertex*, Vertex*> shortest;

    while (length_comparison < maze.length()){
        j =0;
        while((maze[length_comparison] != '\n')) {
            if (maze[length_comparison] == '#'){
                //do nothing
            }else{
                G.addVertex(i,j);
                G.addBasicEdge(to_string(i) + "," + to_string(j), to_string(i-1) + "," + to_string(j));
                G.addBasicEdge(to_string(i) + "," + to_string(j), to_string(i) + "," + to_string(j-1));

                if(i==0){
                    if(start == ""){
                        start = to_string(i) + "," + to_string(j);
                    }else{
                        if(end == ""){
                            end = to_string(i) + "," + to_string(j);
                        }
                    }
                }else if(maze[length_comparison + 1]== '\n'){
                    if(start == ""){
                        start = to_string(i) + "," + to_string(j);
                    }else{
                        if(end == ""){
                            end = to_string(i) + "," + to_string(j);
                        }
                    }
                }else if(j ==0){
                    if(start == ""){
                        start = to_string(i) + "," + to_string(j);
                    }else{
                        if(end == ""){
                            end = to_string(i) + "," + to_string(j);
                        }
                    }
                }else if(length_comparison + length >= maze.length()){
                    if(start == ""){
                        start = to_string(i) + "," + to_string(j);
                    }else{
                        if(end == ""){
                            end = to_string(i) + "," + to_string(j);
                        }
                    }
                }
            }

            length_comparison++;
            j++;
        }
        length = j;
        height =  maze.length()/length;
        i++;
        length_comparison++;
    }

   return G.shortestPath(start,end,maze,length+1);

}
