#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define eb emplace_back
#define mt make_tuple
 
using ll = long long;
using ii = pair<int, int>;
using iiii = tuple<int, int, int, int>;

int h, w, rects_idx, lft_lim[5005], rig_lim[5005], down[5005][5005], cl_right[5005][5005], ans[5005][5005], prv_col[5005], nxt_col[5005], lnk[5005][5005], rep[5005][5005];
ll output;
char a[5005][5005];
vector<int> cols_vec, bucket[5005], vec[5005];

int get_next(int lft, int rig) {
	int lo = 0, hi = (int)vec[lft].size() - 1, ans = -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (cl_right[vec[lft][mid]][lft] > rig) {
			ans = vec[lft][mid];
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	assert(ans != -1);
	return ans;
}

int find(int row, int x) {
	if (x == lnk[row][x]) {
		return x;
	}
	return lnk[row][x] = find(row, lnk[row][x]);
}

void unite(int row, int a, int b) {
	a = find(row, a);
	b = find(row, b);
	assert(a != b);
	lnk[row][a] = b;
}

void fill_row(int row, int lft, int rig, int area) {
	for (int i = rep[row][find(row, lft)]; i <= rig; i = rep[row][find(row, i + 1)]) {
		ans[row][i] = area;
		unite(row, i, i + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> h >> w;
	for (int i = 1; i <= h; i++) {
		iota(lnk[i] + 1, lnk[i] + w + 2, 1);
		iota(rep[i] + 1, rep[i] + w + 2, 1);
		for (int j = 1; j <= w; j++) {
			cin >> a[i][j];
			if (a[i][j] == '1') {
				unite(i, j, j + 1);
			}
		}
	}
	for (int i = 0; i <= h + 1; i++) {
		a[i][0] = a[i][w + 1] = '1';
	}
	for (int i = 0; i <= w + 1; i++) {
		a[0][i] = a[h + 1][i] = '1';
	}
	for (int i = h + 1; i >= 0; i--) {
		for (int j = w + 1; j >= 0; j--) {
			if (a[i][j] == '0') {
				down[i][j] = 0;
				cl_right[i][j] = j;
			} else {
				down[i][j] = (i == h + 1 ? 0 : down[i + 1][j]) + 1;
				cl_right[i][j] = (j == w + 1 ? w + 2 : cl_right[i][j + 1]);
			}
		}
	}
	for (int j = 1; j <= w; j++) {
		vec[j].pb(h + 1);
	}
	for (int top = h; top >= 1; top--) {
		fill(lft_lim, lft_lim + w + 2, 0);
		fill(rig_lim, rig_lim + w + 2, 0);
		for (int col = 1; col <= w; col++) {
			while (!vec[col].empty() && cl_right[vec[col].back()][col] <= cl_right[top][col]) {
				vec[col].pop_back();
			}
			vec[col].pb(top);
		}
		int tmp_prv = -1;
		for (int col = 0; col <= w + 1; col++) {
			if (a[top][col] == '1') {
				bucket[down[top][col]].pb(col);
				if (tmp_prv != -1 && tmp_prv + 1 < col && cl_right[top - 1][tmp_prv + 1] >= col) {
					int nxt_row = get_next(tmp_prv + 1, col - 1);
					if (nxt_row > top && nxt_row - top <= min(down[top][col], down[top][tmp_prv])) {
						rig_lim[tmp_prv] = lft_lim[col] = nxt_row;
						int area = (nxt_row - top) * (col - tmp_prv - 1);
						for (int i = top; i < nxt_row; i++) {
							fill_row(i, tmp_prv + 1, col - 1, area);
						}
					}
				}
				prv_col[col] = tmp_prv;
				nxt_col[col] = -1;
				if (tmp_prv != -1) {
					nxt_col[tmp_prv] = col;
				}
				tmp_prv = col;
			}
		}
		cols_vec.clear();
		for (int i = 0; i <= h; i++) {
			for (auto j : bucket[i]) {
				cols_vec.pb(j);
			}
			bucket[i].clear();
		}
		for (auto col : cols_vec) {
			int cur_nxt_col = nxt_col[col];
			int cur_prv_col = prv_col[col];
			if (cur_prv_col != -1) {
				nxt_col[cur_prv_col] = cur_nxt_col;
			}
			if (cur_nxt_col != -1) {
				prv_col[cur_nxt_col] = cur_prv_col;
			}
			rig_lim[cur_prv_col] = lft_lim[cur_nxt_col] = min(lft_lim[col], rig_lim[col]);
			if (cur_nxt_col != -1 && cur_prv_col != -1) {
				if (cur_prv_col + 1 < cur_nxt_col && cl_right[top - 1][cur_prv_col + 1] >= cur_nxt_col) {
					int nxt_row = get_next(cur_prv_col + 1, cur_nxt_col - 1);
					if (nxt_row > top && nxt_row - top <= min(down[top][cur_prv_col], down[top][cur_nxt_col]) && nxt_row - top > down[top][col]) {
						int area = (nxt_row - top) * (cur_nxt_col - cur_prv_col - 1);
						for (int i = max(top, rig_lim[cur_prv_col]); i < nxt_row; i++) {
							fill_row(i, cur_prv_col + 1, cur_nxt_col - 1, area);
						}
						rig_lim[cur_prv_col] = lft_lim[cur_nxt_col] = nxt_row;
					}
				}
			}
		}
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (a[i][j] == '0') {
			    output += ans[i][j];
			}
		}
	}
	cout << output << '\n';
}
