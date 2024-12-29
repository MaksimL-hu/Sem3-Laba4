#include <cassert>
#include <string>

#include "HashTable.h"
#include "DynamicArray.h"
#include "UndirectedGraph.h"
#include "Edge.h"
#include "Printer.h"
#include "FileWorker.h"
#include "Generator.h"

namespace HashTableTests
{
    const std::string key1 = "one";
    const std::string key2 = "two";
    const std::string key3 = "three";
    const int value1 = 1;
    const int value2 = 2;
    const int value3 = 3;

    void SetUp(HashTable<std::string, int>& table)
    {
        table.Add(key1, value1);
        table.Add(key2, value2);
        table.Add(key3, value3);
    }

    void AddElements()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        assert(table.ContainsKey(key1));
        assert(table.ContainsKey(key2));
        assert(table.ContainsKey(key3));
        assert(table.GetValue(key1).value() == value1);
        assert(table.GetValue(key2).value() == value2);
        assert(table.GetValue(key3).value() == value3);
    }

    void UpdateValue()
    {
        int newValue1 = 10;

        HashTable<std::string, int> table;
        SetUp(table);

        table.Add(key1, newValue1);

        assert(table.GetValue(key1).value() == newValue1);
    }

    void ContainsKey()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        assert(table.ContainsKey(key2));
        assert(!table.ContainsKey("four"));
    }

    void RemoveElement()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        table.Remove(key2);
        assert(!table.ContainsKey(key2));
        assert(table.GetCount() == 2);
    }

    void ResizeUp()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        for (int i = 0; i < 100; ++i)
            table.Add("key" + std::to_string(i), i);

        assert(table.GetCount() == 103);
        assert(table.GetCapacity() > 20);
    }

    void IsEmpty()
    {
        HashTable<std::string, int> emptyTable;

        assert(emptyTable.IsEmpty());
        assert(emptyTable.GetCount() == 0);
    }

    void ResizeDown()
    {
        HashTable<std::string, int> table;
        SetUp(table);

        for (int i = 0; i < 100; ++i)
            table.Add("key" + std::to_string(i), i);

        for (int i = 0; i < 100; ++i)
            table.Remove("key" + std::to_string(i));

        assert(table.GetCount() == 3);
        assert(table.GetCapacity() < 100);
    }

    void Collisions()
    {
        HashTable<int, int> table(5);

        table.Add(1, 100);
        table.Add(6, 200);

        assert(table.GetValue(1).value() == 100);
        assert(table.GetValue(6).value() == 200);
    }
}


namespace DynamicArrayTests
{
    void AddElements()
    {
        DynamicArray<int> array;
        array.Append(1);
        array.Append(2);
        array.Append(3);
        assert(array.GetLength() == 3);
        assert(array[0] == 1);
        assert(array[1] == 2);
        assert(array[2] == 3);
    }

    void RemoveElement()
    {
        DynamicArray<int> array;
        array.Append(1);
        array.Append(2);
        array.Remove(0);
        assert(array.GetLength() == 1);
        assert(array[0] == 2);
    }

    void InsertAt()
    {
        DynamicArray<int> array;
        array.Append(1);
        array.Append(3);
        array.InsertAt(2, 1);
        assert(array.GetLength() == 3);
        assert(array[0] == 1);
        assert(array[1] == 2);
        assert(array[2] == 3);
    }
}


namespace UndirectedGraphTests
{
    void AddVertexAndEdge()
    {
        UndirectedGraph<int> graph;
        graph.AddVertex(1);
        graph.AddVertex(2);
        graph.AddEdge(1, 2, 5);
        assert(graph.GetVertexCount() == 2);
        assert(graph.AreConnected(1, 2));
    }

    void RemoveVertex()
    {
        UndirectedGraph<int> graph;
        graph.AddVertex(1);
        graph.AddVertex(2);
        graph.AddEdge(1, 2, 5);
        graph.RemoveVertex(1);
        assert(graph.GetVertexCount() == 1);
        assert(!graph.AreConnected(1, 2));
    }

    void ColorGraph()
    {
        UndirectedGraph<int> graph;
        graph.AddVertex(1);
        graph.AddVertex(2);
        graph.AddVertex(3);
        graph.AddEdge(1, 2, 1);
        graph.AddEdge(2, 3, 1);
        DynamicArray<int> colors = graph.ColorGraph();
        assert(colors.GetLength() == 3);
        assert(colors.GetElement(0) != colors.GetElement(1)); 
    }

    void CalculateMinDistances()
    {
        UndirectedGraph<int> graph;
        graph.AddVertex(0);
        graph.AddVertex(1);
        graph.AddVertex(2);
        graph.AddEdge(0, 1, 1);
        graph.AddEdge(1, 2, 2);
        DynamicArray<int> distances = graph.CalculateMinDistances(0);
        assert(distances.GetElement(0) == 0);
        assert(distances.GetElement(1) == 1);
        assert(distances.GetElement(2) == 3);
    }
}


void TestHashTable()
{
    HashTableTests::AddElements();
    HashTableTests::UpdateValue();
    HashTableTests::ContainsKey();
    HashTableTests::RemoveElement();
    HashTableTests::ResizeUp();
    HashTableTests::IsEmpty();
    HashTableTests::ResizeDown();
    HashTableTests::Collisions();
}

void TestDynamicArray()
{
    DynamicArrayTests::AddElements();
    DynamicArrayTests::RemoveElement();
    DynamicArrayTests::InsertAt();
}

void TestUndirectedGraph()
{
    UndirectedGraphTests::AddVertexAndEdge();
    UndirectedGraphTests::RemoveVertex();
    UndirectedGraphTests::ColorGraph();
    UndirectedGraphTests::CalculateMinDistances();
}

void RunAllTests()
{
    TestHashTable();
    TestDynamicArray();
    TestUndirectedGraph();
}