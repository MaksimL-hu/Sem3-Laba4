#include <iostream>

#include "UndirectedGraph.h"
#include "Generator.h"
#include "Printer.h"
#include "FileWorker.h"
#include "Commands.h"
#include "Tests.h"

void DisplayMenu()
{
    std::cout << addVertex << ". Add vertex\n";
    std::cout << deleteVertex << ". Delete vertex\n";
    std::cout << addEdge << ". Add edge\n";
    std::cout << deleteEdge << ". Delete edge\n";
    std::cout << generateGraph << ". Generate graph\n";
    std::cout << saveGraphToFile << ". Save graph to the file\n";
    std::cout << uploadGraphFromFile << ". Upload graph from the file\n";
    std::cout << colorGraph << ". Color graph\n";
    std::cout << calculateMinimumDistances << ". Calculate minimum distances\n";
    std::cout << printGraph << ". Print graph\n";
    std::cout << runTests << ". Run tests\n";
    std::cout << close << ". Exit\n";
}

void OpenMenu()
{
    bool isWork = true;
    UndirectedGraph<int> graph;
    std::string command;

    while (isWork)
    {
        DisplayMenu();

        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == close)
        {
            std::cout << "Exiting the program.\n";
            break;
        }
        else if (command == addVertex)
        {
            int vertex;
            std::cout << "Enter the vertex: ";
            std::cin >> vertex;
            graph.AddVertex(vertex);
            std::cout << "A vertex has been added.\n";
        }
        else if (command == deleteVertex)
        {
            int vertex;
            std::cout << "Enter the vertex to delete: ";
            std::cin >> vertex;
            graph.RemoveVertex(vertex);
            std::cout << "A vertex has been deleted.\n";
        }
        else if (command == addEdge)
        {
            int vertex1, vertex2, weight;
            std::cout << "Enter the first vertex, the second vertex, and the edge weight: ";
            std::cin >> vertex1 >> vertex2 >> weight;
            graph.AddEdge(vertex1, vertex2, weight);
            std::cout << "An edge has been added.\n";
        }
        else if (command == deleteEdge)
        {
            int vertex1, vertex2;
            std::cout << "Enter the first vertex, the second vertex: ";
            std::cin >> vertex1 >> vertex2;
            graph.RemoveEdge(vertex1, vertex2);
            std::cout << "An edge has been added.\n";
        }
        else if (command == generateGraph)
        {
            int vertexCount, edgeCount, minWeight, maxWeight;
            std::cout << "Enter the number of vertices, the number of edges, the minimum weight and the maximum weight: ";
            std::cin >> vertexCount >> edgeCount >> minWeight >> maxWeight;
            graph = std::move(GenerateGraph(vertexCount, edgeCount, minWeight, maxWeight));
            std::cout << "The graph is generated.\n";
        }
        else if (command == saveGraphToFile)
        {
            std::string filename;
            std::cout << "Enter the file name to save the graph: ";
            std::cin >> filename;
            SaveGraphToFile(graph, filename);
        }
        else if (command == uploadGraphFromFile)
        {
            std::string filename;
            std::cout << "Enter the file name to upload the graph: ";
            std::cin >> filename;
            LoadGraphFromFile(graph, filename);
        }
        else if (command == colorGraph)
        {
            DynamicArray<int> colors = graph.ColorGraph();
            PrintGraphColor(graph, colors, std::cout);
        }
        else if (command == calculateMinimumDistances)
        {
            int startVertex;
            std::cout << "Enter the starting vertex: ";
            std::cin >> startVertex;
            DynamicArray<int> distances = graph.CalculateMinDistances(startVertex);
            PrintGraphDistances(graph, distances, std::cout);
        }
        else if (command == printGraph)
        {
            PrintValue(graph, std::cout);

            std::string dotFilename = "graph.dot";
            std::string imageFilename = "graph.png";

            SaveGraphToDot(graph, dotFilename);
            GenerateGraphImage(dotFilename, imageFilename);
            std::cout << "Graph has been saved as " << imageFilename << ".\n";
        }
        else if (command == runTests)
        {
            RunAllTests();
            std::cout << "Tests passed successfully\n";
        }
        else
        {
            std::cout << "The wrong command. Please try again.\n";
        }
    }
}