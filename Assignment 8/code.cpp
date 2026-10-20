#include <iostream>

#include <vector>

#include <queue>

#include <iomanip>

using namespace std;


#define INF 99999

struct Node {

	vector<int> path;

	vector<vector<int>> mat;

	vector<bool> used;

	int cost, bound, time;

};

struct cmp {

	bool operator()(Node a, Node b) {

    	return a.bound > b.bound;

	}

};

int reduce(vector<vector<int>>& m) {

	int n = m.size(), sum = 0, x;

	for (int i = 0; i < n; i++) {

    	x = INF;

    	for (int j = 0; j < n; j++)

        	x = min(x, m[i][j]);

    	if (x != INF) {

        	sum += x;

        	for (int j = 0; j < n; j++)

            	if (m[i][j] != INF)

                	m[i][j] -= x;

    	}

	}


	for (int j = 0; j < n; j++) {

    	x = INF;

    	for (int i = 0; i < n; i++)

        	x = min(x, m[i][j]);


    	if (x != INF) {

        	sum += x;

        	for (int i = 0; i < n; i++)

            	if (m[i][j] != INF)

                	m[i][j] -= x;

    	}

	}

	return sum;

}


void TSP(vector<vector<int>> cost,

     	vector<vector<int>> time,

     	int maxTime) {

	int n = cost.size();

	priority_queue<Node, vector<Node>, cmp> pq;


	Node root;

	root.path = {0};

	root.used.assign(n, false);

	root.used[0] = true;

	root.mat = cost;

	root.cost = root.time = 0;


	for (int i = 0; i < n; i++)

    	root.mat[i][i] = INF;


	root.bound = reduce(root.mat);

	pq.push(root);


	int best = INF, bestTime = 0;

	vector<int> answer;


	while (!pq.empty()) {

    	Node cur = pq.top();

    	pq.pop();


    	if (cur.bound >= best)

        	continue;


    	int u = cur.path.back();


    	if (cur.path.size() == n) {

        	int totalCost = cur.cost + cost[u][0];

        	int totalTime = cur.time + time[u][0];


        	if (totalTime <= maxTime && totalCost < best) {

            	best = totalCost;

            	bestTime = totalTime;

            	answer = cur.path;

            	answer.push_back(0);

        	}

        	continue;

    	}


    	for (int v = 1; v < n; v++) {

        	if (cur.used[v] || cost[u][v] == INF)

            	continue;


        	if (cur.time + time[u][v] > maxTime)

            	continue;


        	Node next = cur;


        	next.path.push_back(v);

        	next.used[v] = true;

        	next.cost += cost[u][v];

        	next.time += time[u][v];


        	for (int k = 0; k < n; k++) {

            	next.mat[u][k] = INF;

            	next.mat[k][v] = INF;

        	}


        	next.mat[v][0] = INF;

        	next.bound = next.cost + reduce(next.mat);


        	if (next.bound < best)

            	pq.push(next);

    	}

	}


	if (answer.empty()) {

    	cout << "\nNo feasible route found within the time limit.\n";

    	return;

	}


	cout << "\n========== OPTIMAL ROUTE ==========\n";

	cout << "Route: ";


	for (int i = 0; i < answer.size(); i++) {

    	cout << "City " << answer[i] + 1;

    	if (i + 1 < answer.size())

        	cout << " -> ";

	}
	cout << fixed << setprecision(2);
	cout << "\nTotal Cost : " << best;
	cout << "\nTotal Time : " << bestTime;
	cout << "\nTime Limit : " << maxTime;
	cout << "\n===================================\n";

}

int main() {

	vector<vector<int>> cost = {
    	{INF,20,30,10,11},
    	{15,INF,16,4,2},
    	{3,5,INF,2,4},
    	{19,6,18,INF,3},
    	{16,4,7,8,INF}
	};

	vector<vector<int>> time = {
    	{0,2,3,1,2},
    	{2,0,2,1,1},
    	{1,1,0,1,2},
    	{2,1,2,0,1},
    	{2,1,2,1,0}
	};

	int maxTime = 10;
	TSP(cost, time, maxTime);
	return 0;
}
