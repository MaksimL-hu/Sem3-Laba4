#include <cstdlib>
#include <iostream>

#include "UndirectedGraph.h"

void GenerateGraph(UndirectedGraph& graph, int edgeCount, int minWeight, int maxWeight)
{
    int vertexCount = graph.GetVertexCount();

    if (vertexCount == 0) 
    {
        std::cerr << "Graph is empty. Please add vertices before generating edges." << std::endl;
        return;
    }

    int maxEdges = vertexCount * (vertexCount - 1) / 2;
    edgeCount = std::min(edgeCount, maxEdges);

    int edgesAdded = 0;

    while (edgesAdded < edgeCount) 
    {
        int vertex1 = rand() % vertexCount;
        int vertex2 = rand() % vertexCount;

        if (vertex1 == vertex2) continue;

        int weight = rand() % (maxWeight - minWeight + 1) + minWeight;

        bool edgeExists = false;
        auto begin = graph.GetAdjacentVertices(vertex1).ToBegin();
        auto end = graph.GetAdjacentVertices(vertex1).ToEnd();

        while (*begin != *end) 
        {
            if ((**begin).vertex == vertex2) 
            {
                edgeExists = true;
                break;
            }

            ++(*begin);
        }

        if (!edgeExists) 
        {
            graph.AddEdge(vertex1, vertex2, weight);
            edgesAdded++;
        }
    }
}