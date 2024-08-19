from functools import cache, cached_property
from math import gcd, lcm, sqrt, isqrt, inf, ceil, prod, factorial
from collections import Counter, deque, defaultdict
from heapq import heappush, heappop
from bisect import bisect_left, bisect_right
from fractions import Fraction
from itertools import combinations, permutations
from copy import deepcopy
from time import perf_counter
import math
import sys
import random

from utils_ext import *

sys.setrecursionlimit(10**6)

MOD = 10**9+7

class DSU:
    def __init__(self, n):
        self.p = [-1]*n
    def find(self, i):
        if self.p[i] < 0: return i
        self.p[i] = self.find(self.p[i])
        return self.p[i]
    def unite(self, i, j):
        i, j = self.find(i), self.find(j)
        if i == j: return False
        if self.p[i] > self.p[j]: i, j = j, i
        self.p[i] += self.p[j]
        self.p[j] = i
        return True
    def size(self, i):
        return -self.p[self.find(i)]
    def sizes(self):
        return [-s for s in self.p if s < 0]

class Mod:
    def __init__(self, N, mod=MOD):
        self.fac = fac = [0]*(N+1)
        self.inv = inv = [0]*(N+1)
        self.mod = mod
        fac[0] = 1
        for i in range(1, N+1):
            fac[i] = i*fac[i-1] % mod
        inv[N] = pow(fac[N], mod-2, mod)
        for i in range(N)[::-1]:
            inv[i] = (i+1)*inv[i+1] % mod
        return fac, inv

    def choose(self, n, k):
        return self.fac[n]*self.inv[k] % self.mod * self.inv[n-k] % self.mod

class Trie(dict):
    def __init__(self, A=()):
        super().__init__()
        self.end = False
        for s in A: self.add(s)
    def add(t, s):
        for c in s:
            t[c] = t = t.get(c, Trie())
        t.end = True
    def find(t, s):
        if t.end: yield 0
        for i, c in enumerate(s):
            if c not in t: return
            t = t[c]
            if t.end: yield i+1

class RabinKarp:  # awice
    def __init__(self, A):
        if isinstance(A, str):
            A = (ord(c)-ord('a')+7 for c in A)
        self.MOD = MOD = 344555666677777
        self.pre = pre = [0]
        self.pinvs = pinvs = [1]
        pwr = 1
        P = 37
        Pinv = pow(P, MOD-2, MOD)
        for x in A:
            pwr = pwr*P % MOD
            pre.append((pre[-1] + x*pwr) % MOD)
            pinvs.append(pinvs[-1]*Pinv % MOD)
    def query(self, i, j):
        return (self.pre[j] - self.pre[i]) * self.pinvs[i] % self.MOD

class KMP:
    def __init__(self, A):
        N = len(A)
        self.P = [0]*N
        j = 0
        for i in range(1, N):
            while j and A[i] != A[j]: j = self.P[j-1]
            j = self.P[i] = j + (A[i] == A[j])
        self.Z = [0]*N
        l = r = -1
        for i in range(1, N):
            j = 0 if i >= r else min(r-i, self.Z[i-l])
            while i+j < N and A[i+j] == A[j]: j += 1
            if i+j > r: l, r = i, i+j
            self.Z[i] = j
        self.Z[0] = N

class Primes:  # ty 小羊肖恩, https://codeforces.com/blog/entry/54090
    def __init__(self, n):  # O(N)
        self.n = n
        self.primes = primes = []
        self.lp = lp = [0]*(n+1)
        self.phi = phi = [0]*(n+1)

        lp[1] = phi[1] = 1  # sig[1] = 1
        for i in range(2, n+1):
            if lp[i] == 0:
                lp[i] = i
                primes.append(i)
                phi[i] = i-1  # sig[i] = i+1
            for p in primes:
                if i*p > n: break
                lp[i*p] = p
                if lp[i] == p:
                    phi[i*p] = phi[i]*p  # sig[i*p] = sig[i]*(1+p) - sig[i//p]*p
                    break
                phi[i*p] = phi[i]*phi[p]

    def __getitem__(self, x):
        if isinstance(x, slice):  # O((W+sqR)lglgR)
            l, r = x.start or 0, x.stop
            P = [True]*(r-l)
            for i in range(2-l): P[i] = False
            for p in self.primes:
                if p*p > r: break
                for j in range(max(p*p, (l+p-1)//p*p), r, p):
                    P[j-l] = False
            return P
        if x < 2: return False
        if x <= self.n: return self.lp[x] == x  # O(1)
        for p in self.primes:  # O(sqX)
            if p*p > x: break
            if x%p == 0: return False
        return True

    def factorization(self, x):
        for p in self.primes:
            if p*p > x: break
            if x <= self.n: break
            if x%p == 0:
                cnt = 0
                while x%p == 0: cnt += 1; x //= p
                yield p, cnt
        while 1 < x <= self.n:
            p, cnt = self.lp[x], 0
            while x%p == 0: cnt += 1; x //= p
            yield p, cnt
        if x >= self.n and x > 1:
            yield x, 1

    def factors(self, x):
        res = [1]
        for p, b in self.factorization(x):
            n = len(res)
            for j in range(1, b+1):
                for d in res[:n]:
                    res.append(d * p**j)
        return res

    # def phi2(self, x, n):
    #     # Count integers <= x relatively prime to n
    #     # O(2^distinct_pf * distinct_pf)
    #     P = [p for p, k in self.factorization(n)]
    #     res = 0
    #     for k in range(0, len(P)+1):
    #         for pf in combinations(P, k):
    #             res += x//prod(pf) * (-1)**k
    #     return res

class Tree:
    def __init__(self, E):
        self.A = defaultdict(list)
        for i, j in E:
            self.A[i].append(j)
            self.A[j].append(i)
    def farthest(self, i, p=-1):
        res = 0, i
        for j in self.A[i]:
            if j == p: continue
            d, k = self.farthest(j, i)
            res = max(res, (d+1, k))
        return res
    def diameter(self):
        if not self.A: return 0
        return self.farthest(self.farthest(0)[1])[0]

# ORDERED SET
# from sortedcontainers import SortedList
# sl = SortedList(); sl.add(5); sl.index(5) == 1; sl.discard(5)