#include <bits/stdc++.h>

using namespace std;

struct Edge
{
	int u;
	int v;
	int weight;
	
	Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
	
	bool operator<(const Edge& that)
	{
		return this->weight < that.weight;
	}
};

int Find(int v, int parent[])
{
	if (v != parent[v])
		parent[v] = Find(parent[v], parent);
	
	return parent[v];
}

void Union(int u, int v, int parent[], int rank[])
{
	u = Find(u, parent);
	v = Find(v, parent);
	
	if (parent[u] == parent[v])
		return;
	
	if (rank[u] > rank[v])
		parent[v] = u;
	else if (rank[u] < rank[v])
		parent[u] = v;
	else
	{
		parent[u] = v;
		++rank[v];
	}
}

int kruskal(vector<Edge>& graph, int V, int E)
{
	int parent[V];
	int rank[V];
	
	for (int i = 0; i < V; ++i)
	{
		parent[i] = i;
		rank[i] = 0;
	}
	
	sort(graph.begin(), graph.end());
	
	int mst = 0;
	
	for (int i = 0, edges = 0; i < E && edges < V - 1; ++i)
	{
		int u = graph[i].u;
		int v = graph[i].v;
		int weight = graph[i].weight;
		
		int set_u = Find(u, parent);
		int set_v = Find(v, parent);
		
		if (set_u != set_v)
		{
			mst += weight;
			
			Union(set_u, set_v, parent, rank);
			
			++edges;
		}
	}
	
	return mst;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	int p;
	int V;
	int E;
	int u, v, weight;
	
	cin >> T;
	
	while (T--)
	{
		cin >> p;
		cin >> V;
		cin >> E;
		
		vector<Edge> graph;
		
		for (int i = 0; i < E; ++i)
		{
			cin >> u >> v >> weight;
			
			--u;
			--v;
			
			graph.push_back(Edge(u, v, weight));
		}
		
		int mst = kruskal(graph, V, E);
		
		cout << mst * p << "\n";
	}
	
	return 0;
}