#include <iostream>
using namespace std;

int bfsQueue[1000];
int front = 0, rear = 0;

void enqueue(int x)
{
    bfsQueue[rear++] = x;
}

int dequeue()
{
    return bfsQueue[front++];
}

bool isEmpty()
{
    return front == rear;
}

int adj[100][100];
int adjSize[100];

void addEdge(int u, int v)
{
    adj[u][adjSize[u]++] = v;
    adj[v][adjSize[v]++] = u;
}

int dist[100];

void bfs(int source, int v)
{
    for (int i = 1; i <= v; i++)
    {
        dist[i] = -1;
    }

    dist[source] = 0;
    enqueue(source);

    while (!isEmpty())
    {
        int curr = dequeue();
        for (int i = 0; i < adjSize[curr]; i++)
        {
            int neighbor = adj[curr][i];
            if (dist[neighbor] == -1)
            {
                dist[neighbor] = dist[curr] + 1;
                enqueue(neighbor);
            }
        }
    }
}

int main()
{
    int vertices, edges;

    cout << "Number of Vertex: ";
    cin >> vertices;
    // dist[], adj[][] and adjSize[] have 100 slots, so only vertex numbers 0..99 fit
    if (!cin || vertices < 0 || vertices >= 100)
    {
        cout << "Invalid input: the number of vertices must be between 0 and 99." << endl;
        return 1;
    }

    cout << "Number of Edges: ";
    cin >> edges;
    if (!cin)
    {
        cout << "Invalid input: the number of edges must be a number." << endl;
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

        // addEdge() stores a self loop twice in the same row of adj[][]
        int slots = (u == v) ? 2 : 1;
        if (adjSize[u] + slots > 100 || adjSize[v] + slots > 100)
        {
            cout << "Invalid edge: a vertex cannot have more than 100 neighbours." << endl;
            return 1;
        }
        addEdge(u, v);
    }

    int source;
    cout << "Source Vertex: ";
    cin >> source;
    if (!cin || source < 0 || source >= 100)
    {
        cout << "Invalid input: the source vertex must be between 0 and 99." << endl;
        return 1;
    }

    bfs(source, vertices);

    cout << "Distances from source " << source << ":" << endl;
    for (int i = 1; i <= vertices; i++)
    {
        cout << "Node " << i << ": " << dist[i] << endl;
    }

    return 0;
}
