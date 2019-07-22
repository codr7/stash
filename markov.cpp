#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>

#include "trie.hpp"

#define MAX_MEM 3

template <typename T>
struct Node {
  T word;
  uint64_t score;

  Node(T word = T()): word(move(word)), score(1) {}
  bool operator !=(const T &y) const { return word != y; }
  bool operator >=(const Node &y) const { return word >= y.word; }
};

int main() {
  using T = Trie<Node<string>>;
  
  T db;
  array<string, MAX_MEM> m;
  size_t m_len(0);
  string in, w;
  vector<T *> ans;
  
  while (getline(cin, in)) {
    istringstream words(in);
    
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
      
      auto a(db.insert(m.begin(), m.begin() + m_len));
      
      if (!a->stop) {
        a->key.score++;
        ans.push_back(a);
      }
    }
  }

  // pick highest scored answer, echo query if none found
  // add :load support
}
