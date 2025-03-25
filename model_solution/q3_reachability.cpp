#include <bits/stdc++.h>
using namespace std;

const int maxn=5005;

int n,u,v;
int arr[maxn], sz[maxn];
bool dp[maxn][maxn];
vector<int> adj[maxn];
bool temp[maxn];

void solve(int x, int p){
	dp[x][1] = true; //must take self
	sz[x] = 1;
	for (auto u:adj[x]){
		if (u==p) continue;
		solve(u,x);
		if (arr[u] > arr[x]){ //larger child
			if (!(dp[u][arr[u]] || dp[u][arr[u] - arr[x]])){
				for (int k = 0; k <= sz[x]; k++) dp[x][k] = false;
			}//larger child not fulfulled, whole subtree cannot be fulfilled
			
			for (int k = 0; k <= sz[x]; k++) temp[k] = dp[x][k];
			//just copy over
		}
		if (arr[u] < arr[x]){ //smaller child
			if (!dp[u][arr[u]]){
				for (int k = 0; k <= sz[x]; k++) dp[x][k] = false;
			}
			//smaller child not fulfulled, whole subtree cannot be fulfilled
			
			for (int k = 0; k <= sz[x]; k++){
				temp[k] |= dp[x][k]; //don't take smaller child
				temp[k + arr[u]] |= dp[x][k]; //take smaller child
			}
		}
		if (arr[u] == arr[x]){ //equal child
			for (int k = 0; k <= sz[x]; k++){
				for (int l = 0; l <= sz[u]; l++){
					temp[k + l] |= dp[x][k] && dp[u][l];
				} //take some part of child
			}
			if (dp[u][arr[u]]){
				for (int k = 0; k <= sz[x]; k++){
					temp[k] |= dp[x][k];
				} //dont take child
			}
		}
		sz[x] += sz[u];
		for (int k = 0; k <= sz[x]; k++){
			dp[x][k] = temp[k]; //swap
			temp[k] = 0; //reset
		}
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>arr[i];
	}
	for (int i=1;i<n;i++){
		cin>>u>>v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	solve(1,0);
	cout<<(dp[1][arr[1]]?"YES":"NO");
	return 0;
}