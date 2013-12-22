#include <iostream>
#include <vector>
using namespace std;

/* ¬ывод будет в следующем виде: кажда€ строка будет описывать одну компоненту св€зности. 
¬ одной строке будут перечислены через зап€ту вершины, которые образуют одну компоненту сильной св€зности.
*/

vector < vector<int> > g, gr;		// сам граф и транспонированный граф
vector<bool> used;					// метки
vector<int> order, component;		// компоненты св€зности и 
 
void dfs1 (int v) {
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!used[ g[v][i] ])
			dfs1 (g[v][i]);
	order.push_back (v);
}
 
void dfs2 (int v) {
	used[v] = true;
	component.push_back (v);
	for (size_t i=0; i<gr[v].size(); ++i)
		if (!used[ gr[v][i] ])
			dfs2 (gr[v][i]);
}
 
int main() {
	int n, m;					// количество вершин и количество ребер соответсвенно
	cin >> n >> m;
	g.assign(n, vector<int>());	// выдел€ем пам€ть дл€ графов
	gr.assign(n, vector<int>());
	int u, v;
	for (int i = 0;i < m; ++i) {
		cin >> u >> v;			// описание ребра. вершина выхода и вершина входа ребра соответсвенно
		g[u].push_back (v);
		gr[v].push_back (u);
	}
 
	used.assign (n, false);		// метка. здесь отмечаетс€, если мы достигли уже како-то вершины
	for (int i=0; i<n; ++i)		// из всех вершин, где еще не были, запускаем DFS
		if (!used[i])
			dfs1 (i);
	used.assign (n, false);		// обнуление меток
	for (int i=0; i<n; ++i) {	// еще раз запуск DFS, но уже учитыва€ времена входа и выхода сильных св€зностей.
		int v = order[n-1-i];
		if (!used[v]) {
			dfs2 (v);
			for (int i = 0; i < component.size() - 1; ++i)		// вывод компоненты св€зности
				cout << component[i] << ", ";
			cout << component[component.size() - 1] << endl;
			component.clear();
		}
	}
	system("pause");
}