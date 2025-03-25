#include <bits/stdc++.h>

using namespace std;

#define MAXN 500000
#define MAXM 500000

typedef pair<int,int> pi;

pi rowcol_to_URDR(int r, int c){
    return pi(r+c,r-c);
}

pi URDR_to_rowcol(int u, int d){
    return pi((u+d)/2,(u-d)/2);
}

int N, M, R[MAXN + 5], C[MAXN + 5], T[MAXM + 5];
int thump_counter[MAXN + 5], ur_end[MAXN + 5], dr_end[MAXN + 5];
vector<pi> UR, DR;

void count_thumps(vector<pi> sorted_diag, int diag[], int sig = 1){
    int pt = 0;
    int thumps = 0;
    while (pt < sorted_diag.size()){
        int dnum = sorted_diag[pt].first;
        int cur_thumps = 0;
        while (pt < sorted_diag.size() && dnum == sorted_diag[pt].first){
            int idx = sorted_diag[pt].second;
            cur_thumps += thump_counter[idx];
            diag[idx] += 2 * (sig) * thumps;
            pt++;
        }
        thumps += cur_thumps;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    assert(N <= 500000);
    assert(M <= 500000);
    for (int i = 1; i <= N; ++i){
        cin >> R[i] >> C[i];
        ur_end[i] = rowcol_to_URDR(R[i],C[i]).first;
        dr_end[i] = rowcol_to_URDR(R[i],C[i]).second;
    }
    for (int j = 1; j <= M; ++j){
        cin >> T[j];
        thump_counter[T[j]]++;
    }
    for (int i = 1; i <= N; ++i){
        UR.push_back(pi(ur_end[i],i));
        DR.push_back(pi(dr_end[i],i));
    }
    sort(UR.begin(),UR.end());
    count_thumps(UR,ur_end,1);
    reverse(UR.begin(),UR.end());
    count_thumps(UR,ur_end,-1);
    sort(DR.begin(),DR.end());
    count_thumps(DR,dr_end,1);
    reverse(DR.begin(),DR.end());
    count_thumps(DR,dr_end,-1);

    for (int i = 1; i <= N; ++i){
        pi rc = URDR_to_rowcol(ur_end[i],dr_end[i]);
        cout << rc.first << ' ' << rc.second << '\n';
    }
}
