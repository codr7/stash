#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <vector>

#include "trie.hpp"

#define MAX_ANS 3
#define MAX_MEM 5

template <typename T>
struct Node {
  T word;
  uint64_t score;

  Node(T word = T()): word(move(word)), score(0) {}
  bool operator !=(const T &y) const { return word != y; }
  bool operator >=(const Node &y) const { return word >= y.word; }
};

using T = Trie<Node<string>>;
using A = vector<pair<string, uint64_t>>;

// finish load
/// .stop at end of sentence
/// lcase
/// drop punctuation
/// move scoring

void load(T &db, const string &path) {
}

void get_answers(T &root, string words, uint64_t score, A &out) {  
  if (root.links.empty()) {
    if (!words.empty()) { out.emplace_back(words, score); }
  } else {
    for (T &l: root.links) {
      if (!words.empty()) { words.push_back(' '); }

      if (l.stop) {
        out.emplace_back(words + l.key.word, score + l.key.score);
      } else {
        get_answers(l, words + l.key.word, score + l.key.score, out);
      }
    }
  }
}

int main() {  
  T db;
  array<string, MAX_MEM> m;
  size_t m_len(0);
  string in, w;
  vector<T *> ans;
  
  while (getline(cin, in)) {
    istringstream words(in);
    ans.clear();
    
    for (;;) {
      words >> w;
      if (words.fail()) { break; }
      
      if (m_len == MAX_MEM) {
        auto beg(m.begin());
        rotate(beg, beg+1, m.end());
        m.back() = w;
      } else {
        m[m_len++] = w;
      }

      for (auto mb(m.begin()), me(mb + m_len); mb != me; mb++) {
        auto &a(db.insert(mb, me));
        a.key.score++;
        ans.push_back(&a);
      }
    }

    ans.back()->stop = true;
    
    A as;
    for (T *an: ans) { get_answers(*an, an->key.word, an->key.score, as); }
    sort(as.begin(), as.end(), [](auto &x, auto &y) { return x.first < y.first; });
    uint64_t n(0);
    
    for (auto i(as.rbegin()); i != as.rend() && n < MAX_ANS; i++, n++) {
      cout << i->second << ' ' << i->first << endl;
    }
  }  
}
