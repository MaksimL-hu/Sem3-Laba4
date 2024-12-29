#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <optional>

#include "HashTable.h"
#include "Edge.h"
#include "DynamicArray.h"

template <typename TKey>
class UndirectedGraph {
private:
    int vertexCount;
    HashTable<TKey, DynamicArray<Edge>> adjacencyList;

public:
    UndirectedGraph(int vertexCount = 0)
    {
        if (vertexCount < 0)
            vertexCount = 0;

        this->vertexCount = vertexCount;
        adjacencyList = HashTable<TKey, DynamicArray<Edge>>(vertexCount);
    }

    void AddEdge(TKey vertex1, TKey vertex2, int weight)
    {
        if (adjacencyList.GetValue(vertex1) == std::nullopt || adjacencyList.GetValue(vertex2) == std::nullopt)
            return;

        for (int i = 0; i < adjacencyList.GetValue(vertex1).value().GetLength(); i++)
            if (adjacencyList.GetValue(vertex1).value()[i].vertex == vertex2)
                return;

        DynamicArray<Edge> array1 = adjacencyList.GetValue(vertex1).value();
        array1.Append(Edge(vertex2, weight));
        DynamicArray<Edge> array2 = adjacencyList.GetValue(vertex2).value();
        array2.Append(Edge(vertex1, weight));
        adjacencyList.Add(vertex1, array1);
        adjacencyList.Add(vertex2, array2);
    }

    void AddVertex()
    {
        DynamicArray<Edge> newAdjacencyList;

        adjacencyList.Add(vertexCount, newAdjacencyList);
        vertexCount++;
    }

    int GetVertexCount() const
    {
        return vertexCount;
    }

    DynamicArray<Edge> GetAdjacentVertices(TKey vertex) const
    {
        auto result = adjacencyList.GetValue(vertex);

        if (result.has_value())
            return result.value();
        else
            return DynamicArray<Edge>();
    }

    bool AreConnected(TKey vertex1, TKey vertex2) const
    {
        if (adjacencyList.GetValue(vertex1) == std::nullopt || adjacencyList.GetValue(vertex2) == std::nullopt)
            return false;

        DynamicArray<Edge> adjacentVertices = GetAdjacentVertices(vertex1);

        for (int i = 0; i < adjacentVertices.GetLength(); i++)
            if (adjacentVertices[i].vertex == vertex2)
                return true;

        return false;
    }

    DynamicArray<int> ColorGraph()
    {
        DynamicArray<int> colors(vertexCount);

        for (int i = 0; i < vertexCount; i++)
            colors.Set(i, -1); 

        colors.Set(0, 0);

        DynamicArray<bool> availableColors(vertexCount);

        for (int i = 1; i < vertexCount; i++)
        {
            for (int j = 0; j < vertexCount; j++)
                availableColors.Set(j, true);

            DynamicArray<Edge> adjacentEdges = GetAdjacentVertices(i);

            for (int j = 0; j < adjacentEdges.GetLength(); j++)
            {
                int neighbor = adjacentEdges[j].vertex;

                if (colors.GetElement(neighbor) != -1)
                    availableColors.Set(colors.GetElement(neighbor), false);
            }

            for (int color = 0; color < vertexCount; color++)
            {
                if (availableColors.GetElement(color))
                {
                    colors.Set(i, color);
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

        if (startVertex < 0 || startVertex> vertexCount || GetAdjacentVertices(startVertex) == DynamicArray<Edge>())
            return distances;

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

            DynamicArray<Edge> adjacentEdges = GetAdjacentVertices(minVertex);
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