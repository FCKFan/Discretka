#include <iostream>
#include <vector>
using namespace std;

const int inf = 1000*1000*1000;


typedef vector<int> graf_line;
typedef vector<graf_line> graf;

typedef vector<int> vint;
typedef vector<vint> vvint;


void push (int u, int v, vvint & f, vint & e, const vvint & c)
{
	int d = min (e[u], c[u][v] - f[u][v]);
	f[u][v] += d;
	f[v][u] = - f[u][v];
	e[u] -= d;
	e[v] += d;
}

void lift (int u, vint & h, const vvint & f, const vvint & c)
{
	int d = inf;
	for (int i = 0; i < (int)f.size(); i++)
		if (c[u][i]-f[u][i] > 0)
			d = min (d, h[i]);
	if (d == inf)
		return;
	h[u] = d + 1;
}


int main()
{
	int n;
	cin >> n;
	vvint c (n, vint(n));
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> c[i][j];
	// ����� - ������� 0, ���� - ������� n-1

	vvint f (n, vint(n));
	for (int i=1; i<n; i++)
	{
		f[0][i] = c[0][i];
		f[i][0] = -c[0][i];
	}

	vint h (n);
	h[0] = n;

	vint e (n);
	for (int i=1; i<n; i++)
		e[i] = f[0][i];

	for ( ; ; )
	{
		int i;
		for (i=1; i<n-1; i++)
			if (e[i] > 0)
				break;
		if (i == n-1)
			break;

		int j;
		for (j=0; j<n; j++)
			if (c[i][j]-f[i][j] > 0 && h[i]==h[j]+1)
				break;
		if (j < n)
			push (i, j, f, e, c);
		else
			lift (i, h, f, c);
	}

	int flow = 0;
	for (int i=0; i<n; i++)
		if (c[0][i])
			flow += f[0][i];

	cout << max(flow,0);

}