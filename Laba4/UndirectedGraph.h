#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include "DynamicArray.h"
#include "Edge.h"
#include "LinkedList.h"

class UndirectedGraph {
private:
    int vertexCount;
    DynamicArray<LinkedList<Edge>> adjacencyList;

public:
    UndirectedGraph(int vertexCount = 0)
    {
        if (vertexCount < 0)
            vertexCount = 0;

        this->vertexCount = vertexCount;
        adjacencyList = DynamicArray<LinkedList<Edge>>(vertexCount);
    }

    void AddEdge(int vertex1, int vertex2, int weight)
    {
        if (vertex1 < 0 || vertex2 < 0 || vertex1 >= vertexCount || vertex2 >= vertexCount)
            throw std::out_of_range("Vertex index out of range");

        for (int i = 0; i < adjacencyList[vertex1].GetLength(); i++)
        {
            auto begin = adjacencyList[vertex1].ToBegin();
            auto end = adjacencyList[vertex1].ToEnd();

            while (*begin != *end)
            {
                if ((**begin).vertex == vertex2)
                    return;

                ++(*begin);
            }
        }

        adjacencyList[vertex1].Append(Edge(vertex2, weight));
        adjacencyList[vertex2].Append(Edge(vertex1, weight));
    }

    void AddVertex()
    {
        LinkedList<Edge> newAdjacencyList;

        adjacencyList.Append(newAdjacencyList);
        vertexCount++;
    }

    int GetVertexCount() const
    {
        return vertexCount;
    }

    LinkedList<Edge>& GetAdjacentVertices(int vertex) const
    {
        if (vertex < 0 || vertex >= vertexCount)
            throw std::out_of_range("Vertex index out of range");

        return adjacencyList[vertex];
    }

    DynamicArray<int> ColorGraph()
    {
        DynamicArray<int> colors(vertexCount);

        for (int i = 0; i < vertexCount; i++) 
            colors.Set(i, 0);

        colors.Set(0, 1);

        for (int i = 1; i < vertexCount; i++) 
        {
            DynamicArray<bool> availableColors(vertexCount);

            for (int j = 0; j < vertexCount; j++)
                availableColors.Set(j, true);

            auto begin = GetAdjacentVertices(i).ToBegin();
            auto end = GetAdjacentVertices(i).ToEnd();

            while (*begin != *end) {
                int edge = (**begin).vertex;

                if (colors.GetElement(edge) != 0)
                    availableColors.Set(colors.GetElement(edge) - 1, false);

                ++(*begin);
            }

            for (int color = 0; color < vertexCount; color++) 
            {
                if (availableColors.GetElement(color)) 
                {
                    colors.Set(i, color + 1);
                    break;
                }
            }
        }

        return colors;
    }

    DynamicArray<int> CalculateMinDistances(int startVertex) 
    {
        DynamicArray<int> distances(vertexCount);
        DynamicArray<bool> visited(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            distances.Set(i, std::numeric_limits<int>::max());
            visited.Set(i, false);
        }

        distances.Set(startVertex, 0);

        for (int i = 0; i < vertexCount - 1; i++) {
            int minDistance = std::numeric_limits<int>::max();
            int minVertex = -1;

            for (int j = 0; j < vertexCount; j++) 
            {
                if (!visited.GetElement(j) && distances.GetElement(j) < minDistance) 
                {
                    minDistance = distances.GetElement(j);
                    minVertex = j;
                }
            }

            visited.Set(minVertex, true);

            LinkedList<Edge>& adjacentEdges = GetAdjacentVertices(minVertex);
            auto begin = adjacentEdges.ToBegin();
            auto end = adjacentEdges.ToEnd();

            while (*begin != *end) 
            {
                int neighbor = (**begin).vertex;
                int weight = (**begin).weight;

                if (!visited.GetElement(neighbor) && distances.GetElement(minVertex) != std::numeric_limits<int>::max() &&
                    distances.GetElement(minVertex) + weight < distances.GetElement(neighbor)) 
                {
                    distances.Set(neighbor, distances.GetElement(minVertex) + weight);
                }

                ++(*begin);
            }
        }

        return distances;
    }
};

#endif