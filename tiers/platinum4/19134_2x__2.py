"""Platinum 4
19134 - $2x + 2$
meta: {"problemId": 19134, "titleKo": "$2x + 2$", "titles": [{"language": "en", "languageDisplayName": "en", "title": "$2x + 2$", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 243, "level": 17, "votedUserCount": 86, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.3703999519348145, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "arbitrary_precision", "isMeta": false, "bojTagId": 117, "problemCount": 314, "displayNames": [{"language": "ko", "name": "임의 정밀도 / 큰 수 연산", "short": "임의 정밀도 / 큰 수 연산"}, {"language": "en", "name": "arbitrary precision / big integers", "short": "arbitrary precision / big integers"}, {"language": "ja", "name": "高精度または大きな数の演算", "short": "高精度または大きな数の演算"}], "aliases": [{"alias": "빅인티저"}, {"alias": "빅데시멀"}, {"alias": "biginteger"}, {"alias": "bigdecimal"}]}], "metadata": {}}
"""

n = int(input())
if n == 1:
  print(1)
  exit()

# chain len = floor(lg((n+2)/(x+2))) for root x
# roots: { 2, all odds <= n }
# can bsearch to find # roots of length k
# handle 1 and 2 separately just in case

# floor lg
def fllg(x):
  return x.bit_length() - 1
#   r = 0
#   while (1 << r) <= x:
#     r += 1
#   return r-1

def p2(x):
  return 1 << x

# 1 + max k s.t. 2^kx + 2^{k+1} - 2 <= n
# this formula represents a chain of 2x+2
def chain_len(n,x):
   return fllg((n+2)//(x+2))+1

# max roots to pick from chain
# since if x picked cannot pick 2x+2 aka next on chain, can pick at most ceil(len/2)
# if x not odd or 2 then is suffix of another chain
# (chain_len(n,x)+1)//2
def chain_picks(n,x):
  return (((n+2)//(x+2)).bit_length()+1)//2

def brute(n):
  res = chain_picks(n,1) + chain_picks(n,2)
  for x in range(3, n+1, 2):
    # print(x, chain_picks(x))
    res += chain_picks(n,x)
  return res

# num chains with odd root >= 3 with k picks
cached = n
def num_chains(n,k):
  global cached
  # find lower bound (first x <= k)
  l = 3
  r = cached
  while l != r:
    m = (l+r)//2
    if chain_picks(n,m) <= k:
      r = m
    else:
      l = m+1
  left = l
  if chain_picks(n,left) != k:
    return 0

  # find upper bound (last x >= k)
  l = 3
  r = cached
  while l != r:
    m = (l+r+1)//2
    if chain_picks(n,m) >= k:
      l = m
    else:
      r = m-1
  right = l
  # if right >= left:
    # print(k, left, right)
  cached = right
  # print(k, left, right)
  left = left | 1
  right = (right-1) | 1
  return max(0, (right-left)//2 + 1)

def faster_num_chains(n,k):
  right = (n+2)//p2(k*2-2)-2
  left = (n+2)//p2(k*2)-1
  # print(k, left, right)
  left = max(min(left | 1, n), 3)
  right = max(min((right-1) | 1, n), 3)
  return max(0, (right-left)//2 + 1) if chain_picks(n,left) == k else 0

# keep raising k, to avoid potential edge cases just raise to lg(n) < 300
def solve(n):
  res = chain_picks(n,1) + chain_picks(n,2)
  for k in range(1, max(10,fllg(n))):
    # c = num_chains(n,k)
    c = faster_num_chains(n,k)
    res += c*k
  return res

print(solve(n))
# print(brute(n))
# for i in range(1, n+1):
#   s = solve(i)
#   b = brute(i)
#   if s != b:
#     print(i, s, b)