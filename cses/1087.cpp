#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {  // TODO: UPDATE TO USE willy108 VERS https://pastebin.com/JEAuS8a2
    string str; int n;
    vector<int> sa, isa;
    Tree<int> lcp;
    SuffixArray(string str_): str(str_+'$'), n(str.size()), sa(n), isa(n), lcp(n-1) {
        // sa has size sz(S)+1, starts with sz(S)
        iota(all(sa), 0);
        sort(all(sa), [&](int i, int j) { return str[i] < str[j]; });
        for (int i = 1; i < n; ++i) {
            int l = sa[i-1], r = sa[i];
            isa[r] = i > 1 && str[l] == str[r] ? isa[l] : i;
        }
        for (int k = 1; k < n; k *= 2) {
            // currently sorted by first k chars
            vector<int> s(sa), is(isa), pos(n);
            iota(all(pos), 0);
            for (int t: s) {
                int T = t-k;  // verify that nothing goes out of bounds
                if (T >= 0) sa[pos[isa[T]]++] = T;
            }
            for (int i = 1; i < n; ++i) {
                int l = sa[i-1], r = sa[i];
                isa[r] = is[l] == is[r] && is[l+k] == is[r+k] ? isa[l] : i;
            }
        }
        int k = 0;  // Kasai's Algo
        for (int r = 0; r < n-1; ++r) {
            int l = sa[isa[r]-1];
            while (l+k < n-1 && str[l+k] == str[r+k]) ++k;
            lcp.update(isa[r]-1, k);
            if (k) k--;
        }
		// if we cut off first chars of two strings
		// with lcp k then remaining portions still have lcp k-1
    }
    int getLCP(int i, int j) {
        if (i == j) return n-1-i;
        int l = isa[i], r = isa[j];
        if (l > r) swap(l, r);
        return lcp.query(l, r);
    }
};

string s;

int main() {
    cin >> s;
}