"""Bronze 5
5717 - Og
meta: {"problemId": 5717, "titleKo": "상근이의 친구들", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "상근이의 친구들", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Og", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 16226, "level": 1, "votedUserCount": 200, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.312999963760376, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "arithmetic", "isMeta": false, "bojTagId": 121, "problemCount": 1374, "displayNames": [{"language": "ko", "name": "사칙연산", "short": "사칙연산"}, {"language": "en", "name": "arithmetic", "short": "arithmetic"}, {"language": "ja", "name": "算数", "short": "算数"}], "aliases": [{"alias": "덧셈"}, {"alias": "뺄셈"}, {"alias": "곱셈"}, {"alias": "나눗셈"}, {"alias": "더하기"}, {"alias": "빼기"}, {"alias": "곱하기"}, {"alias": "나누기"}]}], "metadata": {}}
"""

while True:
  x, y = [ int(x) for x in input().split() ]
  if x == 0 and y == 0:
    break
  print(x+y)
