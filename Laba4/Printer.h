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

void PrintValue(const Edge& value, ostream& os)
{
    os << "(";
    os << value.vertex;
    os << ", weight: ";
    os << value.weight;
    os << ")";
}

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
    for (int vertex = 0; vertex < graph.GetVertexCount(); ++vertex) 
    {
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

void PrintGraphColor(DynamicArray<int> colors, ostream& os)
{
    for (int i = 0; i < colors.GetLength(); i++)
    {
        os << "Vertex ";
        PrintValue(i, os);
        os << " ---> Color ";
        PrintValue(colors.GetElement(i), os);
        os << "\n";
    }
}

void PrintGraphDistances(DynamicArray<int> distances, ostream& os)
{
    for (int i = 0; i < distances.GetLength(); i++) 
    {
        os << "Minimum distance to vertex ";
        PrintValue(i, os);
        os << ": ";

        if (distances.GetElement(i) == std::numeric_limits<int>::max())
        {
            os << "infinity\n";
        }
        else
        {
            PrintValue(distances.GetElement(i), os);
            os << "\n";
        }
    }
}

#endif