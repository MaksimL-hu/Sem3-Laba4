#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include "UndirectedGraph.h"

void SaveGraphToFile(const UndirectedGraph& graph, const std::string& filename);
void LoadGraphFromFile(UndirectedGraph& graph, const std::string& filename);

#endif