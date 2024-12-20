#include <fstream>
#include <iostream>

#include "UndirectedGraph.h"

void SaveGraphToFile(const UndirectedGraph& graph, const std::string& filename) 
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
        auto adjacentVertices = graph.GetAdjacentVertices(vertex);
        auto begin = adjacentVertices.ToBegin();
        auto end = adjacentVertices.ToEnd();

        while (*begin != *end) 
        {
            outFile << vertex << " " << (**begin).vertex << " " << (**begin).weight << "\n";
            ++(*begin);
        }
    }

    outFile.close();

    std::cout << "The graph has been successfully saved to a file " << filename << ".\n";
}

void LoadGraphFromFile(UndirectedGraph& graph, const std::string& filename)
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
        graph.AddVertex();

    int vertex1, vertex2, weight;
    while (inFile >> vertex1 >> vertex2 >> weight)
        graph.AddEdge(vertex1, vertex2, weight);

    inFile.close();
    std::cout << "The graph has been successfully loaded from the file " << filename << ".\n";
}