#include <iostream>
#include <string>
using namespace std;

int stack[1000];
int top = -1;
void push(int x)
{
    stack[++top] = x;
}
int pop()
{
    return stack[top--];
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
        int u = stack[top];

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

    cout << "Number of edges: ";
    cin >> edges;

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
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
