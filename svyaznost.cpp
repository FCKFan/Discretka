#include <iostream>
#include <vector>
using namespace std;

/* ����� ����� � ��������� ����: ������ ������ ����� ��������� ���� ���������� ���������. 
� ����� ������ ����� ����������� ����� ������ �������, ������� �������� ���� ���������� ������� ���������.
*/

vector < vector<int> > g, gr;		// ��� ���� � ����������������� ����
vector<bool> used;					// �����
vector<int> order, component;		// ���������� ��������� � 
 
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
	int n, m;					// ���������� ������ � ���������� ����� �������������
	cin >> n >> m;
	g.assign(n, vector<int>());	// �������� ������ ��� ������
	gr.assign(n, vector<int>());
	int u, v;
	for (int i = 0;i < m; ++i) {
		cin >> u >> v;			// �������� �����. ������� ������ � ������� ����� ����� �������������
		g[u].push_back (v);
		gr[v].push_back (u);
	}
 
	used.assign (n, false);		// �����. ����� ����������, ���� �� �������� ��� ����-�� �������
	for (int i=0; i<n; ++i)		// �� ���� ������, ��� ��� �� ����, ��������� DFS
		if (!used[i])
			dfs1 (i);
	used.assign (n, false);		// ��������� �����
	for (int i=0; i<n; ++i) {	// ��� ��� ������ DFS, �� ��� �������� ������� ����� � ������ ������� ����������.
		int v = order[n-1-i];
		if (!used[v]) {
			dfs2 (v);
			for (int i = 0; i < component.size() - 1; ++i)		// ����� ���������� ���������
				cout << component[i] << ", ";
			cout << component[component.size() - 1] << endl;
			component.clear();
		}
	}
	system("pause");
}