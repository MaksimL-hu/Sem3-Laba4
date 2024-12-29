#include <iostream>

#include "UndirectedGraph.h"

using namespace std;

void PrintValue(const Edge& value, ostream& os)
{
    os << "(";
    os << value.vertex;
    os << ", weight: ";
    os << value.weight;
    os << ")";
}