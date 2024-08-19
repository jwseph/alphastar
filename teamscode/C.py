
mod = 10**9+7
dp = [[0, 0] for _ in range(10**6+5)]
for i in range(1, 10**6+5):
    for p in range(2):
        dp[i][p] = pow(i, mod-2, mod) * ((int(p == 0) + dp[i-1][1]) + (i-1)*dp[i-1][0]) % mod

nt = int(input())
for _ in range(nt):
    n = int(input())
    print(dp[n][0])