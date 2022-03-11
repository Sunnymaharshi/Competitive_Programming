#include<iostream>
#include<queue>
#include<vector>
#define nl "\n"
#define sp " "
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
/*
    Graph that can be coloured using 2 colors such that no two adjacent
    nodes have same color.
    graph having odd length cycle cannot be a bipartite graph.
    graph without even length cycle also a bipartite graph but it should
    not have odd length cycle.
    we color adjacent nodes with color opposite to previous adjacent node.
    if we cannot color the color with 2 colors such that no two adjacent
    nodes have same color then it has odd length cycle and is not bipartite.
    Time Complexity : O(N+E)
*/

bool checkBipartite_BFS(int node,vector<int> &color,vector<int> adj[]){

    queue<int> Q;
    Q.push(node);
    color[node] = 1;            // color the node with 1
    // colors are 0 and 1
    while(!Q.empty()){

        int cur_node = Q.front();
        Q.pop();

        for(int i:adj[cur_node]){

            if(color[i]==-1){       // node is not visited
                // color it with opposite color of previous adjacent node
                color[i] = 1 - color[cur_node];
                Q.push(i);
            }
            // it is colored and it's previous adjacent also have same color
            // odd length cycle i.e not bipartite
            else if(color[i]==color[cur_node])
                return false;            
        }
    }

    // we're able color all nodes such that no two adjacents have same color.
    return true;        
}

int32_t main() {
    fastio();

    int n,m;
    cin>>n>>m;
    vector<int> adj[n+1];
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> color(n+1,-1);           // all nodes are colored with -1
    bool bipartite = true;

    for(int node=1;node<=n;node++){      // traverse through all components
    
        if(color[node]==-1){            // node is not visited
    
            // if any component is not bipartite, stop checking remaining components        
            if(!checkBipartite_BFS(node,color,adj)){
                bipartite=false;
                break;
            }
        }
    }

    if(bipartite)
        cout<<"Bipartite";
    else
        cout<<"Not Bipartite";
    return 0;
}
/*
Output:
5 5
1 2
2 3
3 1
3 4
4 5
Not Bipartite
*/