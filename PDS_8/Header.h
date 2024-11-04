#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <iomanip>
#include <Windows.h>
#include <string>

using namespace std;

bool readGraphFromFile(const string& filePath, vector<vector<unsigned int>>& graph, unsigned int& verticesCount, unsigned int& edgesCount);
void dfs(int start, const vector<vector<unsigned int>>& adjList);
void printStack(const stack<int>& s);