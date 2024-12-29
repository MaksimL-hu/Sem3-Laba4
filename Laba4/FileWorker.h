#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include <fstream>
#include <iostream>

#include "UndirectedGraph.h"

template <typename TValue>
void SaveGraphToFile(const UndirectedGraph<TValue>& graph, const std::string& filename)
{
    std::ofstream outFile(filename);

    if (!outFile)
    {
        std::cerr << "Error opening file for writing\n";
        return;
    }

    int vertexCount = graph.GetVertexCount();
    outFile << vertexCount << "\n";

    for (int vertex = 0; vertex < vertexCount; ++vertex)
    {
        auto adjacentVertices = graph.GetAdjacentVertices(graph.GetVertex(vertex));
        auto begin = adjacentVertices.ToBegin();
        auto end = adjacentVertices.ToEnd();

        while (*begin != *end)
        {
            outFile << graph.GetVertex(vertex) << " " << (**begin).vertex << " " << (**begin).weight << "\n";
            ++(*begin);
        }
    }

    outFile.close();
    std::cout << "The graph has been successfully saved to a file " << filename << ".\n";
}

template <typename TValue>
void LoadGraphFromFile(UndirectedGraph<TValue>& graph, const std::string& filename)
{
    std::ifstream inFile(filename);

    if (!inFile)
    {
        std::cerr << "Error opening file for reading\n";
        return;
    }

    int vertexCount;
    inFile >> vertexCount;

    for (int i = 0; i < vertexCount; ++i)
        graph.AddVertex(i);

    int vertex1, vertex2, weight;
    while (inFile >> vertex1 >> vertex2 >> weight)
        graph.AddEdge(vertex1, vertex2, weight);

    inFile.close();
    std::cout << "The graph has been successfully loaded from the file " << filename << ".\n";
}

template <typename TValue>
void SaveGraphToDot(const UndirectedGraph<TValue>& graph, const std::string& filename)
{
    std::ofstream dotFile(filename);

    if (!dotFile) {
        std::cerr << "Error opening file for writing\n";
        return;
    }

    dotFile << "graph G {\n";

    for (int i = 0; i < graph.GetVertexCount(); ++i)
    {
        TValue vertex = graph.GetVertex(i);
        dotFile << "  \"" << vertex << "\";\n";

        auto adjacentVertices = graph.GetAdjacentVertices(vertex);

        for (int j = 0; j < adjacentVertices.GetLength(); ++j)
        {
            TValue adjacentVertex = adjacentVertices[j].vertex;
            int weight = adjacentVertices[j].weight;

            if (vertex < adjacentVertex)
                dotFile << "  \"" << vertex << "\" -- \"" << adjacentVertex << "\" [label=\"" << weight << "\"];\n";
        }
    }

    dotFile << "}\n";

    dotFile.close();
    std::cout << "Graph has been successfully saved to " << filename << " in DOT format.\n";
}


void GenerateGraphImage(const std::string& dotFilename, const std::string& outputFilename);

#endif