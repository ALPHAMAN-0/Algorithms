#include <iostream>
#include <string>
using namespace std;

int dfsStack[1000];
int top = -1;
void push(int x)
{
    dfsStack[++top] = x;
}
int pop()
{
    return dfsStack[top--];
}
bool isEmpty()
{
    return top == -1;
}
int adj[100][100];
int adjSize[100];
int edgeFrom[1000], edgeTo[1000];
int edgeCount = 0;
int color[100];
int discovery[100];
int finish[100];
int timeCounter = 0;
string edgeType[1000];

void addEdge(int u, int v)
{
    adj[u][adjSize[u]++] = v;
    edgeFrom[edgeCount] = u;
    edgeTo[edgeCount] = v;
    edgeCount++;
}
int findEdge(int u, int v)
{
    for (int i = 0; i < edgeCount; i++)
    {
        if (edgeFrom[i] == u && edgeTo[i] == v)
            return i;
    }
    return -1;
}
void classifyEdge(int u, int v)
{
    int idx = findEdge(u, v);
    if (color[v] == 0)
    {
        edgeType[idx] =
            "TE";
    }
    else if (color[v] == 1)
    {
        edgeType[idx] =
            "BE";
    }
    else
    {
        if (discovery[u] < discovery[v])
        {
            edgeType[idx] =
                "FE";
        }
        else
        {
            edgeType[idx] =
                "CE";
        }
    }
}

int neighborIndex[100];

void dfsVisit(int start)
{
    push(start);
    color[start] = 1;
    discovery[start] = ++timeCounter;
    neighborIndex[start] = 0;

    while (!isEmpty())
    {
        int u = dfsStack[top];

        if (neighborIndex[u] < adjSize[u])
        {
            int v = adj[u][neighborIndex[u]];
            neighborIndex[u]++;

            classifyEdge(u, v);

            if (color[v] == 0)
            {
                push(v);
                color[v] = 1;
                discovery[v] = ++timeCounter;
                neighborIndex[v] = 0;
            }
        }
        else
        {
            pop();
            color[u] = 2;
            finish[u] = ++timeCounter;
        }
    }
}

void dfs(int start, int v)
{
    for (int i = 1; i <= v; i++)
    {
        color[i] = 0;
        discovery[i] = 0;
        finish[i] = 0;
        neighborIndex[i] = 0;
    }
    timeCounter = 0;
    for (int i = 1; i <= v; i++)
    {
        if (color[i] == 0)
        {
            dfsVisit(i);
        }
    }
}

int main()
{
    int vertices, edges;

    cout << "Number of vertex: ";
    cin >> vertices;
    // color[], discovery[], finish[] and adj[][] have 100 slots, so only vertex numbers 0..99 fit
    if (!cin || vertices < 0 || vertices >= 100)
    {
        cout << "Invalid input: the number of vertices must be between 0 and 99." << endl;
        return 1;
    }

    cout << "Number of edges: ";
    cin >> edges;
    // edgeFrom[], edgeTo[] and edgeType[] have 1000 slots
    if (!cin || edges > 1000)
    {
        cout << "Invalid input: the number of edges must be a number, at most 1000." << endl;
        return 1;
    }

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        if (!cin || u < 0 || u >= 100 || v < 0 || v >= 100)
        {
            cout << "Invalid edge: vertex numbers must be between 0 and 99." << endl;
            return 1;
        }
        if (adjSize[u] >= 100)
        {
            cout << "Invalid edge: a vertex cannot have more than 100 outgoing edges." << endl;
            return 1;
        }
        addEdge(u, v);
    }

    dfs(1, vertices);

    cout << "Output:" << endl;
    int backEdgeU = -1, backEdgeV = -1;

    for (int i = 0; i < edgeCount; i++)
    {
        cout << "Edge_" << edgeFrom[i] << edgeTo[i] << ": " << edgeType[i] << endl;

        if (edgeType[i] == "BE")
        {
            backEdgeU = edgeFrom[i];
            backEdgeV = edgeTo[i];
        }
    }

    if (backEdgeU != -1)
    {
        cout << "The cycle is created due to the edge " << backEdgeU << backEdgeV << "." << endl;
    }

    return 0;
}
