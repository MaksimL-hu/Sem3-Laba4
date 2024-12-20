#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    int vertex;
    int weight;

    Edge(int v, int w) : vertex(v), weight(w) {}
};

#endif