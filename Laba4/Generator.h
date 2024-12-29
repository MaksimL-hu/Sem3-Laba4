#ifndef CREATOR_H
#define CREATOR_H

#include "UndirectedGraph.h"

UndirectedGraph<int> GenerateGraph(int vertexCount, int edgeCount, int minWeight, int maxWeight);
void GenerateGraphImage(const std::string& dotFilename, const std::string& outputFilename);

#endif
