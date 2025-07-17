#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
using namespace std;

const int INF = INT_MAX;

//g++ -std=c++11 bellmanFord.cpp -o bellmanFord

bool bellmanFord(int src, int n, vector<vector<int>>& edges, vector<int>& dist, vector<int>& predecessor, vector<int>& negativeCycle){

    dist.assign(n, INF);
    predecessor.assign(n, -1);
    dist[src] = 0;

    for(int i = 0; i < n - 1; i++){
        for(auto& edge : edges){
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            if(dist[u] != INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                predecessor[v] = u;
            }
        }
    }

    //after n - 1 runs
    for(auto& edge : edges){
        int u = edge[0];int v = edge[1];int w = edge[2];
        if(dist[u] != INF && dist[u] + w < dist[v]){
            //negative cycle detect
            int v = edge[1];

            //make cycle be recorded on the predecessor
            for(int i = 0; i < n; i++){
                v = predecessor[v]; 
            }

            //extract the negative cycle from predecessor
            int u = v;
            negativeCycle.clear();
            do{
                negativeCycle.push_back(u);
                u = predecessor[u];
            } while(u != v); 
            negativeCycle.push_back(v);
            reverse(negativeCycle.begin(), negativeCycle.end());

            return true;
        }
    }
    
    return false;
}


int main() {
    vector<int> dist, pred, cycle;

    // Test 1
    {
        int n = 3;
        vector<vector<int>> edges = {{0,1,1},{1,2,-2},{2,0,0}};
        if (bellmanFord(0, n, edges, dist, pred, cycle)) {
            cout << "Test 1: Negative cycle detected: ";
            for (int v : cycle) cout << v << " ";
            cout << endl;
        } else {
            cout << "Test 1: No negative cycle\n";
        }
    }

    // Test 2
    {
        int n = 4;
        vector<vector<int>> edges = {{0,1,1},{1,2,2},{2,3,3},{3,0,4}};
        if (bellmanFord(0, n, edges, dist, pred, cycle)) {
            cout << "Test 2: Negative cycle detected: ";
            for (int v : cycle) cout << v << " ";
            cout << endl;
        } else {
            cout << "Test 2: No negative cycle\n";
        }
    }

    // Test 3
    {
        int n = 6;
        vector<vector<int>> edges = {
            {0,1,3},{1,2,4},
            {3,4,2},{4,5,-10},{5,3,3}
        };
        if (bellmanFord(0, n, edges, dist, pred, cycle)) {
            cout << "Test 3: Negative cycle detected: ";
            for (int v : cycle) cout << v << " ";
            cout << endl;
        } else {
            cout << "Test 3: No negative cycle. ";
            cout << "Because this 3,4,5 are disconnect from src, bellman cannot detect\n";
        }
    }


    // Test 4
    {
        int n = 6;
        vector<vector<int>> edges = {
            {0,1,3},{1,2,4},
            {3,4,2},{4,5,-10},{5,3,3}
        };
        if (bellmanFord(3, n, edges, dist, pred, cycle)) {
            cout << "Test 4: Negative cycle detected: ";
            for (int v : cycle) cout << v << " ";
            cout << endl;
        } else {
            cout << "Test 4: No negative cycle\n";
            cout << "Because this 3,4,5 are disconnect from src\n";
        }
    }


    // Test 5
    {
        int n = 8;
        vector<vector<int>> edges = {
            {0,1,1},{1,2,2},{2,3,3},
            {3,4,4},{4,5,5},{5,2,-46},
            {5,6,7},{6,7,-2}
        };
        if (bellmanFord(0, n, edges, dist, pred, cycle)) {
            cout << "Test 5: Negative cycle detected: ";
            for (int v : cycle) cout << v << " ";
            cout << endl;
        } else {
            cout << "Test 5: No negative cycle\n";
        }
    }


    // Test 6, two negative cycles(previous 8 nodes is same as test5, but src = 6), but only one get detected
    {
        int n = 11;
        vector<vector<int>> edges = {
            {0,1,1},{1,2,2},{2,3,3},
            {3,4,4},{4,5,5},{5,2,-46},
            {5,6,7},{6,7,-2},{7,8,1},
            {8,9,-10},{9,7,-1},{9,10,0}
        };
        if (bellmanFord(6, n, edges, dist, pred, cycle)) {
            cout << "Test 6: Negative cycle detected: ";
            for (int v : cycle) cout << v << " ";
            cout << endl;
        } else {
            cout << "Test 6: No negative cycle\n";
        }
    }
}
