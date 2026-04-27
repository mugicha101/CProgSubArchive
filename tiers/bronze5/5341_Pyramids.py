"""Bronze 5
5341 - Pyramids
meta: {"problemId": 5341, "titleKo": "Pyramids", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Pyramids", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 6318, "level": 1, "votedUserCount": 171, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.4038000106811523, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "arithmetic", "isMeta": false, "bojTagId": 121, "problemCount": 1374, "displayNames": [{"language": "ko", "name": "사칙연산", "short": "사칙연산"}, {"language": "en", "name": "arithmetic", "short": "arithmetic"}, {"language": "ja", "name": "算数", "short": "算数"}], "aliases": [{"alias": "덧셈"}, {"alias": "뺄셈"}, {"alias": "곱셈"}, {"alias": "나눗셈"}, {"alias": "더하기"}, {"alias": "빼기"}, {"alias": "곱하기"}, {"alias": "나누기"}]}], "metadata": {}}
"""

while True:
  x = int(input())
  if x == 0:
    break
  print(x * (x+1) // 2)
