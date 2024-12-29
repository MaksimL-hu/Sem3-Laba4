#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>

#include "UndirectedGraph.h"
#include "Edge.h"
#include "LinkedList.h"

using namespace std;

template <typename T>
void PrintValue(const T& value, ostream& os)
{
    os << value;
}

void PrintValue(const Edge& value, ostream& os);

template <typename T>
void PrintValue(const DynamicArray<T>& value, ostream& os)
{
    os << "[";

    for (int i = 0; i < value.GetLength(); ++i)
    {
        PrintValue(value[i], os);

        if (i < value.GetLength() - 1)
            os << ", ";
    }

    os << "]";
}

template <typename T>
void PrintValue(const LinkedList<T>& list, ostream& os)
{
    os << "[";

    auto begin = list.ToBegin();
    auto end = list.ToEnd();

    while (*begin != *end)
    {
        PrintValue(**begin, os);

        ++(*begin);

        if (*begin != *end)
            os << ", ";
    }

    os << "]";
}

template <typename TValue>
void PrintValue(const UndirectedGraph<TValue>& graph, ostream& os)
{
    for (int index = 0; index < graph.GetVertexCount(); ++index)
    {
        TValue vertex = graph.GetVertex(index);

        if (!graph.GetAdjacentVertices(vertex).GetLength())
        {
            os << "Vertex " << vertex << " []\n";
            continue;
        }

        os << "Vertex " << vertex << ": ";

        auto adjacentVertices = graph.GetAdjacentVertices(vertex);

        PrintValue(adjacentVertices, os);

        os << "\n";
    }
}

template <typename TKey>
void PrintGraphDistances(const UndirectedGraph<TKey>& graph, DynamicArray<int>& distances, std::ostream& os)
{
    for (int i = 0; i < graph.GetVertexCount(); i++)
    {
        TKey vertex = graph.GetVertex(i);
        os << "Minimum distance to vertex ";
        os << vertex;
        os << ": ";

        if (distances.GetElement(i) == std::numeric_limits<int>::max())
        {
            os << "infinity\n";
        }
        else
        {
            os << distances.GetElement(i);
            os << "\n";
        }
    }
}

template <typename TKey>
void PrintGraphColor(const UndirectedGraph<TKey>& graph, DynamicArray<int>& colors, std::ostream& os)
{
    for (int i = 0; i < graph.GetVertexCount(); i++)
    {
        TKey vertex = graph.GetVertex(i);
        os << "Vertex ";
        os << vertex;
        os << " ---> Color ";
        os << colors.GetElement(i);
        os << "\n";
    }
}

#endif