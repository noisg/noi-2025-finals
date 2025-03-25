#include <bits/stdc++.h>

using namespace std;
const int n_max = 500'000;
const int h_max = 500'000;
int p2k[h_max][21];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,h;
    cin >> h >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) {
        cin>>a[i];
    }
    vector<int> down(h+2);
    vector<int> up(h+2);
    down[h+1] = h+2;
    up[h+1] = h+2;

    vector<int> freq(h+2);
    for(int i=1; i<=h; i++) {
        freq[i] = 1;
    }
    for(auto p: a) {
        int f = 0;
        freq[p-1] += freq[p];
        freq[p] = 0;
    }
    int i = 1;
    for(int j=0; j<=h+1; j++) {
        while(freq[j]) {
            freq[j]--;
            down[i] = j;
            i++;
        }
    }
    for(int i=1; i<=h; i++) {
        freq[i] = 1;
    }
    for(auto p: a) {
        int f = 0;
        freq[p+1] += freq[p];
        freq[p] = 0;
    }
    i = 1;
    for(int j=0; j<=h+1; j++) {
        while(freq[j]) {
            freq[j]--;
            up[i] = j;
            i++;
        }
    }


    int hi = 0;
    for(int lo = 1; lo <= h; lo++) {
        while(up[lo]>=down[hi]) hi++;
        p2k[lo][0] = hi;
    }
    p2k[h+1][0] = h+1;
    for(int k=1; k<=20; k++) {
        for(int i=1; i<=h+1; i++) {
            p2k[i][k] = p2k[p2k[i][k-1]][k-1];
        }
    }

    int q; cin>>q;
    while(q--) {
        int l,r; cin>>l>>r;
        int l3 = l;
        int ans = 1;
        for(int k=20; k>=0; k--) {
            int l2 = p2k[l][k];
            if(l2 <= r) {
                ans += (1<<k);
                l = l2;
            }
        }
        cout << ans << "\n";
    }
}
