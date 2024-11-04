#include "pch.h"
#include "CppUnitTest.h"
#include "..\PDS_8\Header.h"
#include "..\PDS_8\Source.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestReadGraphFromFile_Success)
        {
            std::ofstream outFile("test_graph_1.txt");
            outFile << "4 4\n1 2\n1 3\n2 4\n3 4\n";
            outFile.close();

            std::vector<std::vector<unsigned int>> graph;
            unsigned int verticesCount, edgesCount;

            bool result = readGraphFromFile("test_graph_1.txt", graph, verticesCount, edgesCount);

            Assert::IsTrue(result);
            Assert::AreEqual(static_cast<unsigned long>(verticesCount), 4ul);
            Assert::AreEqual(static_cast<unsigned long>(edgesCount), 4ul);
            Assert::AreEqual(static_cast<unsigned long>(graph.size()), 4ul);
            Assert::AreEqual(static_cast<unsigned long>(graph[0].size()), 2ul); // Вершина 1 має 2 сусідів
            Assert::AreEqual(static_cast<unsigned long>(graph[1].size()), 2ul); // Вершина 2 має 2 сусідів
            Assert::AreEqual(static_cast<unsigned long>(graph[2].size()), 2ul); // Вершина 3 має 2 сусідів
            Assert::AreEqual(static_cast<unsigned long>(graph[3].size()), 2ul); // Вершина 4 має 2 сусідів

            std::remove("test_graph_1.txt");
        }

        TEST_METHOD(TestReadGraphFromFile_FileNotFound)
        {
            std::vector<std::vector<unsigned int>> graph;
            unsigned int verticesCount, edgesCount;

            bool result = readGraphFromFile("wrong_file.txt", graph, verticesCount, edgesCount);
            Assert::IsFalse(result);
        }

        TEST_METHOD(TestReadGraphFromFile_InvalidFormat)
        {
            std::ofstream outFile("test_graph_2.txt");
            outFile << "4 4\n1 2\n1 3\n2\n";
            outFile.close();

            std::vector<std::vector<unsigned int>> graph;
            unsigned int verticesCount, edgesCount;

            bool result = readGraphFromFile("test_graph_2.txt", graph, verticesCount, edgesCount);
            Assert::IsFalse(result);

            std::remove("test_graph_2.txt");
        }
    };
}
