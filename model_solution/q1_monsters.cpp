#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define fi first
#define se second
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#endif
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, k, A[200005], H[200005], X[200005], dn[200005];
pi B[200005];

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++)cin >> A[i] >> H[i];
	for(int i = 1; i <= k; i++)cin >> X[i];
	{
	    assert(1 <= n && n <= 200000);
	    assert(1 <= k && k <= 200000);
	    for(int i = 1; i <= n; i++){
	        assert(1 <= A[i] && A[i] <= (int)1e9);
	        assert(1 <= H[i] && H[i] <= (int)1e9);
	    }
    	set <int> s; for(int i = 1; i <= n; i++)s.insert(A[i]);
    	assert((int)s.size() == n);
    	s.clear();
	    for(int i = 1; i <= k; i++){
	        assert(1 <= X[i] && X[i] <= 1e9);
	        s.insert(X[i]);
	    }
	    assert((int)s.size() == k);
	}
	sort(X + 1, X + k + 1);
	int ans = 0;
	vector <pi> v;
	for(int i = 1; i <= n; i++){
		int lb = lower_bound(X + 1, X + k + 1, A[i]) - X;
		int mn1 = 1e18, mn2 = 1e18;
		if(lb != k + 1)mn1 = min(mn1, abs(X[lb] - A[i]));
		if(lb != 1)mn2 = min(mn2, abs(A[i] - X[lb - 1]));
		if(H[i] <= min(mn1, mn2)){
			ans += H[i];
		}
		else{
			if(mn1 == mn2)ans += mn1, v.push_back({A[i], lb});
			else {
				if(mn1 < mn2){
					ans += mn1;
					ans += !dn[lb];
					dn[lb] = 1;
				}
				else{
					ans += mn2;
					ans += !dn[lb - 1];
					dn[lb - 1] = 1;
				}
			}
		}
	}
	sort(v.begin(), v.end());
	for(auto [i, j] : v){
		if(dn[j] || dn[j - 1])continue;
		dn[j] = 1;
		ans++;
	}
	cout << ans;
}

main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int tc = 1;
	//cin >> tc;
	for(int tc1=1;tc1<=tc;tc1++){
		// cout << "Case #" << tc1 << ": ";
		solve();
	}
}
