#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    int vertex;
    int weight;

    Edge(int v = 0, int w = 0) : vertex(v), weight(w) {}

    bool operator==(const Edge& other) const 
    {
        return vertex == other.vertex && weight == other.weight;
    }

    bool operator!=(const Edge& other) const
    {
        return !(*this == other);
    }
};

#endif