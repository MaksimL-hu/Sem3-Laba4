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
    DynamicArray<TKey> vertexes;
    HashTable<TKey, DynamicArray<Edge>> adjacencyList;

public:
    UndirectedGraph(int vertexCount = 0)
    {
        if (vertexCount < 0)
            vertexCount = 0;

        this->vertexCount = vertexCount;
        adjacencyList = HashTable<TKey, DynamicArray<Edge>>(vertexCount);
        vertexes = DynamicArray<TKey>(0);
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

    void AddVertex(TKey vertex)
    {
        for (int i = 0; i < vertexes.GetLength(); i++)
            if (vertexes[i] == vertex)
                return;

        DynamicArray<Edge> newAdjacencyList;

        adjacencyList.Add(vertex, newAdjacencyList);
        vertexes.Append(vertex);
        vertexCount++;
    }

    int GetVertexCount() const
    {
        return vertexCount;
    }

    TKey GetVertex(int index) const
    {
        if (index < 0 || index > vertexCount)
            return TKey();

        return vertexes[index];
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

    void RemoveEdge(TKey vertex1, TKey vertex2)
    {
        if (adjacencyList.GetValue(vertex1) == std::nullopt || adjacencyList.GetValue(vertex2) == std::nullopt)
            return;

        DynamicArray<Edge> array1 = adjacencyList.GetValue(vertex1).value();
        for (int i = 0; i < array1.GetLength(); i++)
        {
            if (array1[i].vertex == vertex2)
            {
                array1.Remove(i);
                break;
            }
        }

        adjacencyList.Add(vertex1, array1);

        DynamicArray<Edge> array2 = adjacencyList.GetValue(vertex2).value();

        for (int i = 0; i < array2.GetLength(); i++)
        {
            if (array2[i].vertex == vertex1)
            {
                array2.Remove(i);
                break;
            }
        }

        adjacencyList.Add(vertex2, array2);
    }

    void RemoveVertex(TKey vertex)
    {
        if (adjacencyList.GetValue(vertex) == std::nullopt)
            return;

        DynamicArray<Edge> adjacentEdges = GetAdjacentVertices(vertex);

        for (int i = 0; i < vertexes.GetLength(); i++)
        {
            if (vertexes[i] == vertex)
            {
                vertexes.Remove(i);
                break;
            }
        }

        for (int i = 0; i < adjacentEdges.GetLength(); i++)
        {
            TKey adjacentVertex = adjacentEdges[i].vertex;
            RemoveEdge(vertex, adjacentVertex);
        }

        adjacencyList.Remove(vertex);
        vertexCount--;
    }

    DynamicArray<int> ColorGraph()
    {
        DynamicArray<int> colors(vertexes.GetLength());

        for (int i = 0; i < vertexes.GetLength(); i++)
            colors.Set(i, -1);

        for (int i = 0; i < vertexes.GetLength(); i++)
        {
            TKey currentVertex = vertexes[i];
            DynamicArray<bool> availableColors(vertexes.GetLength());

            for (int j = 0; j < availableColors.GetLength(); j++)
                availableColors.Set(j, true);

            DynamicArray<Edge> adjacentEdges = GetAdjacentVertices(currentVertex);

            for (int j = 0; j < adjacentEdges.GetLength(); j++)
            {
                TKey neighbor = adjacentEdges[j].vertex;

                for (int k = 0; k < vertexes.GetLength(); k++)
                {
                    if (vertexes[k] == neighbor && colors.GetElement(k) != -1)
                    {
                        availableColors.Set(colors.GetElement(k), false);
                        break;
                    }
                }
            }

            for (int color = 0; color < availableColors.GetLength(); color++)
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

    DynamicArray<int> CalculateMinDistances(TKey startVertex)
    {
        DynamicArray<int> distances(vertexes.GetLength());
        DynamicArray<bool> visited(vertexes.GetLength());

        for (int i = 0; i < vertexes.GetLength(); i++)
        {
            distances.Set(i, std::numeric_limits<int>::max());
            visited.Set(i, false);
        }

        int startIndex = -1;
        for (int i = 0; i < vertexes.GetLength(); i++)
        {
            if (vertexes[i] == startVertex)
            {
                startIndex = i;
                break;
            }
        }

        if (startIndex == -1)
            return distances;

        distances.Set(startIndex, 0);

        for (int i = 0; i < vertexes.GetLength(); i++)
        {
            int minDistance = std::numeric_limits<int>::max();
            int minIndex = -1;

            for (int j = 0; j < vertexes.GetLength(); j++)
            {
                if (!visited.GetElement(j) && distances.GetElement(j) < minDistance)
                {
                    minDistance = distances.GetElement(j);
                    minIndex = j;
                }
            }

            if (minIndex == -1)
                break;

            visited.Set(minIndex, true);

            TKey minVertex = vertexes[minIndex];
            DynamicArray<Edge> adjacentEdges = GetAdjacentVertices(minVertex);

            for (int j = 0; j < adjacentEdges.GetLength(); j++)
            {
                TKey neighbor = adjacentEdges[j].vertex;
                int neighborIndex = -1;

                for (int k = 0; k < vertexes.GetLength(); k++)
                {
                    if (vertexes[k] == neighbor)
                    {
                        neighborIndex = k;
                        break;
                    }
                }

                if (neighborIndex != -1)
                {
                    int weight = adjacentEdges[j].weight;

                    if (!visited.GetElement(neighborIndex) &&
                        distances.GetElement(minIndex) != std::numeric_limits<int>::max() &&
                        distances.GetElement(minIndex) + weight < distances.GetElement(neighborIndex))
                    {
                        distances.Set(neighborIndex, distances.GetElement(minIndex) + weight);
                    }
                }
            }
        }

        return distances;
    }

};

#endif