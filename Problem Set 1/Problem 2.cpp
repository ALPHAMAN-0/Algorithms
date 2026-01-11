#include <iostream>
using namespace std;

int queue[1000];
int front = 0, rear = 0;

void enqueue(int x)
{
    queue[rear++] = x;
}

int dequeue()
{
    return queue[front++];
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

    cout << "Number of Edges: ";
    cin >> edges;

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }

    int source;
    cout << "Source Vertex: ";
    cin >> source;

    bfs(source, vertices);

    cout << "Distances from source " << source << ":" << endl;
    for (int i = 1; i <= vertices; i++)
    {
        cout << "Node " << i << ": " << dist[i] << endl;
    }

    return 0;
}
