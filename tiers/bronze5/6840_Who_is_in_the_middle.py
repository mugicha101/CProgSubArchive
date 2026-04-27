"""Bronze 5
6840 - Who is in the middle?
meta: {"problemId": 6840, "titleKo": "Who is in the middle?", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Who is in the middle?", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 6547, "level": 1, "votedUserCount": 180, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.3454999923706055, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}], "metadata": {}}
"""

a = [ int(input()) for _ in range(3) ]
print(sorted(a)[1])