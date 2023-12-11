#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// Структура для узла односвязного списка
struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

// Функция для слияния двух упорядоченных односвязных списков
Node* mergeSortedLists(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    Node* result = nullptr;
    if (l1->data < l2->data) {
        result = l1;
        result->next = mergeSortedLists(l1->next, l2);
    }
    else {
        result = l2;
        result->next = mergeSortedLists(l1, l2->next);
    }

    return result;
}

// Класс для реализации стека на односвязном списке
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return -1; // or throw an exception
        }

        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;

        return value;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1; // or throw an exception
        }

        return top->data;
    }
};

// Функция для обхода графа в глубину
void depthFirstTraversal(vector<vector<int>>& graph, int start, vector<bool>& visited) {
    Stack stack;
    stack.push(start);

    cout << "Depth-First Traversal: ";
    while (!stack.isEmpty()) {
        int vertex = stack.pop();
        if (!visited[vertex]) {
            cout << vertex << " ";
            visited[vertex] = true;

            for (int i = graph.size() - 1; i >= 0; --i) {
                if (graph[vertex][i] == 1 && !visited[i]) {
                    stack.push(i);
                }
            }
        }
    }
    cout << endl;
}

// Функция для обхода графа в ширину
void breadthFirstTraversal(vector<vector<int>>& graph, int start, vector<bool>& visited) {
    queue<int> q;
    q.push(start);

    cout << "Breadth-First Traversal: ";
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        if (!visited[vertex]) {
            cout << vertex << " ";
            visited[vertex] = true;

            for (int i = 0; i < graph.size(); ++i) {
                if (graph[vertex][i] == 1 && !visited[i]) {
                    q.push(i);
                }
            }
        }
    }
    cout << endl;
}

// Функция для топологической сортировки вершин графа
void topologicalSortUtil(vector<vector<int>>& graph, int vertex, vector<bool>& visited, stack<int>& s) {
    visited[vertex] = true;

    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            topologicalSortUtil(graph, i, visited, s);
        }
    }

    s.push(vertex);
}

void topologicalSort(vector<vector<int>>& graph) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);
    stack<int> s;

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, s);
        }
    }

    cout << "Topological Sort: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    // (a) Слияние двух упорядоченных односвязных списков
    Node* list1 = new Node(2);
    list1->next = new Node(8);
    list1->next->next = new Node(10);

    Node* list2 = new Node(3);
    list2->next = new Node(5);
    list2->next->next = new Node(7);

    Node* mergedList = mergeSortedLists(list1, list2);
    cout << "Merged Sorted Lists: ";
    while (mergedList) {
        cout << mergedList->data << " ";
        mergedList = mergedList->next;
    }
    cout << endl;

    // (b) Реализация стека на односвязном списке
    Stack stackExample;
    stackExample.push(15);
    stackExample.push(25);
    stackExample.push(45);

    cout << "Stack Example: ";
    while (!stackExample.isEmpty()) {
        cout << stackExample.pop() << " ";
    }
    cout << endl;

    // (c) Обход графа в глубину и в ширину
    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    vector<vector<int>> adjacencyMatrix(numVertices, vector<int>(numVertices, 0));

    cout << "Enter the adjacency matrix of the graph (1 if there is an edge, 0 otherwise):" << endl;

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            cout << "Enter adjacencyMatrix[" << i << "][" << j << "]: ";
            cin >> adjacencyMatrix[i][j];
        }
    }

    vector<bool> visitedVertices(numVertices, false);

    int startVertex;
    cout << "Enter the starting vertex for traversal(from 0 to the number of vertices in the graph minus 1): ";
    cin >> startVertex;

    depthFirstTraversal(adjacencyMatrix, startVertex, visitedVertices);

    visitedVertices.assign(numVertices, false);
    breadthFirstTraversal(adjacencyMatrix, startVertex, visitedVertices);

    // (d) Топологическая сортировка вершин графа
    topologicalSort(adjacencyMatrix);

    return 0;
}