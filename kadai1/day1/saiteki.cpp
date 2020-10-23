#include <bits/stdc++.h>
using namespace std;
template <class T>
inline bool chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
inline bool chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
        return 1;
    }
    return 0;
}

using pll = pair<long long, long long>;
pll sub(long long h, long long w)
{
    if (h % 2 == 0 || w % 2 == 0)
        return {h * w / 2, h * w / 2};
    if (h > w)
        swap(h, w);
    return {h * (w + 1) / 2, h * (w - 1) / 2};
}

int main()
{
    long long H, W;
    cin >> H >> W;
    long long res = H * W;

    for (long long h = 1; h < H; ++h)
    {
        vector<long long> a(3);
        a[0] = h * W;
        auto p = sub(H - h, W);
        a[1] = p.first, a[2] = p.second;
        sort(a.begin(), a.end());
        chmin(res, a.back() - a[0]);
    }
    for (long long w = 1; w < W; ++w)
    {
        vector<long long> a(3);
        a[0] = H * w;
        auto p = sub(H, W - w);
        a[1] = p.first, a[2] = p.second;
        sort(a.begin(), a.end());
        chmin(res, a.back() - a[0]);
    }
    cout << res << endl;
}