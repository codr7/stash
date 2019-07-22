#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <vector>

#include "trie.hpp"

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
        if (mb == m.begin()) { a.stop = true; }
        a.key.score++;
        ans.push_back(&a);
      }
    }

    A as;
    for (T *an: ans) { get_answers(*an, "", 0, as); }
    for (auto &a: as) { cout << a.second << ' ' << a.first << endl; }
  }
  
  // pick highest scored answer
  // add :load support
}
