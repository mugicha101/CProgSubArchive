/*
Platinum 2
31310 - Tip of Your Tongue
meta: {"problemId": 31310, "titleKo": "Tip of Your Tongue", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Tip of Your Tongue", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 18, "level": 19, "votedUserCount": 1, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.3889000415802002, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "hashing", "isMeta": false, "bojTagId": 8, "problemCount": 208, "displayNames": [{"language": "ko", "name": "해싱", "short": "해싱"}, {"language": "en", "name": "hashing", "short": "hash"}, {"language": "ja", "name": "ハッシュ化", "short": "ハッシュ"}], "aliases": []}, {"key": "hash_set", "isMeta": false, "bojTagId": 136, "problemCount": 789, "displayNames": [{"language": "ko", "name": "해시를 사용한 집합과 맵", "short": "해시를 사용한 집합과 맵"}, {"language": "en", "name": "set / map by hashing", "short": "hashset"}, {"language": "ja", "name": "ハッシュ化によるセット・マップ", "short": "hashset"}], "aliases": [{"alias": "집합"}, {"alias": "맵"}, {"alias": "셋"}, {"alias": "딕셔너리"}, {"alias": "dictionary"}, {"alias": "map"}, {"alias": "set"}, {"alias": "해싱"}, {"alias": "hashing"}, {"alias": "dict"}]}, {"key": "set", "isMeta": false, "bojTagId": 225, "problemCount": 1619, "displayNames": [{"language": "ko", "name": "집합과 맵", "short": "집합과 맵"}, {"language": "en", "name": "set / map", "short": "set"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;
typedef long double ld;

struct Trie {
    unordered_map<int, Trie*> next;
    int words;
    Trie() {
        words = 0;
    }

    void insert(vector<int>& vals) {
        Trie* curr = this;
        ++curr->words;
        for (int v : vals) {
            if (curr->next.count(v) == 0)
                curr->next[v] = new Trie();
            curr = curr->next[v];
            ++curr->words;
        }
    }

    void erase(vector<int>& vals) {
        Trie* curr = this;
        --curr->words;
        for (int v : vals) {
            if (curr->next.count(v) == 0)
                return;
            curr = curr->next[v];
            --curr->words;
        }
    }

    int count(vector<int>& vals) {
        Trie* curr = this;
        for (int v : vals) {
            if (curr->next.count(v) == 0)
                return 0;
            curr = curr->next[v];
        }
        return curr->words;
    }
};

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(false);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    int n, q;
    cin >> n >> q;
    Trie bothfixTrie;
    Trie prefixTrie;
    Trie suffixTrie;
    for (int _ = 0; _ < n; ++_) {
        string word;
        cin >> word;
        int n = word.size();
        vector<int> prefix;
        prefix.reserve(n);
        for (char c : word)
            prefix.push_back((int)(c-'a'));
        prefixTrie.insert(prefix);
        vector<int> suffix = prefix;
        reverse(suffix.begin(), suffix.end());
        suffixTrie.insert(suffix);
        for (int i = 0; i < n; ++i)
            prefix[i] = prefix[i] * 26 + suffix[i];
        bothfixTrie.insert(prefix);
    }

    for (int _ = 0; _ < q; ++_) {
        string op, p, s;
        cin >> op >> p >> s;
        int n = p.size();
        vector<int> prefix, suffix, bothfix;
        prefix.reserve(n);
        suffix.reserve(n);
        bothfix.reserve(n);
        for (char c : p)
            prefix.push_back(c-'a');
        for (char c : s)
            suffix.push_back(c-'a');
        reverse(suffix.begin(), suffix.end());
        for (int i = 0; i < n; ++i)
            bothfix.push_back(prefix[i] * 26 + suffix[i]);
        int pc = prefixTrie.count(prefix);
        int sc = suffixTrie.count(suffix);
        int bc = bothfixTrie.count(bothfix);
        if (op == "AND") {
            cout << bothfixTrie.count(bothfix) << endl;
        }
        else if (op == "OR")
            cout << (prefixTrie.count(prefix) + suffixTrie.count(suffix) - bothfixTrie.count(bothfix)) << endl;
        else
            cout << (prefixTrie.count(prefix) + suffixTrie.count(suffix) - bothfixTrie.count(bothfix) * 2) << endl;
    }

    return 0;
}
