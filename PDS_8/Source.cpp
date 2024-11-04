#include"Header.h"

bool readGraphFromFile(const string& filePath, vector<vector<unsigned int>>& graph, unsigned int& verticesCount, unsigned int& edgesCount) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "�� ������� ������� ����. �������� ����." << endl;
        return false;
    }

    if (!(file >> verticesCount >> edgesCount)) {
        cerr << "�� ������� ������� ������� ������ �� �����." << endl;
        return false;
    }

    graph.resize(verticesCount);

    for (unsigned int i = 0; i < edgesCount; ++i) {
        unsigned int u, v;
        if (!(file >> u >> v)) {
            cerr << "������� ��� ��������� �����." << endl;
            return false;
        }
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
    file.close();
    return true;
}

void printGraph(const vector<vector<unsigned int>>& graph) {
    cout << "������ ���������� �����:" << endl;
    for (unsigned int i = 1; i < graph.size(); ++i) {
        cout << i << ": ";
        for (unsigned int neighbor : graph[i]) {
            cout << neighbor + 1 << " ";
        }
        cout << endl;
    }
}

void printStack(const stack<int>& s) {
    stack<int> temp = s;
    cout << "[";
    bool first = true;
    while (!temp.empty()) {
        if (!first) cout << ", ";
        cout << temp.top() + 1;
        temp.pop();
        first = false;
    }
    cout << "]";
}

void dfs(int start, const vector<vector<unsigned int>>& adjList) {
    vector<bool> visited(adjList.size(), false);
    vector<int> dfsNumber(adjList.size(), -1);
    stack<int> s;
    int dfsCount = 0;

    s.push(start);
    visited[start] = true;
    dfsNumber[start] = ++dfsCount;

    cout << setw(20) << "������� �������"
        << setw(20) << "DFS-�����"
        << setw(20) << "����" << endl;

    while (!s.empty()) {
        int current = s.top();
        cout << setw(20) << current + 1
            << setw(20) << dfsNumber[current]
            << setw(20);
        printStack(s);
        cout << endl;

        bool foundUnvisited = false;
        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dfsNumber[neighbor] = ++dfsCount;
                s.push(neighbor);
                foundUnvisited = true;
                break;
            }
        }

        if (!foundUnvisited) {
            s.pop();
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filePath;
    cout << "������ ���� �� �����: ";
    getline(cin, filePath);

    vector<vector<unsigned int>> graph;
    unsigned int verticesCount, edgesCount;

    if (!readGraphFromFile(filePath, graph, verticesCount, edgesCount)) {
        return 1;
    }

    printGraph(graph);

    unsigned int startVertex;
    cout << "������ ����� ��������� �������: ";
    cin >> startVertex;

    if (startVertex < 1 || startVertex > verticesCount) {
        cerr << "�������: ����� ������� ���� ������." << endl;
        return 1;
    }

    cout << "�������� ������ �����:" << endl;
    dfs(startVertex - 1, graph);

    return 0;
}
