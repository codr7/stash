#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>

#include "trie.hpp"

#define MAX_MEMORY 3

int main() {
  Trie<string> db;
  array<string, MAX_MEMORY> m;
  size_t m_len(0);
  string in, w;
  vector<Trie<string> *> ans;
  
  while (getline(cin, in)) {
    istringstream words(in);
    
    while (!words.eof()) {
      words >> w;
      if (words.fail()) { break; }
      
      if (m_len == MAX_MEMORY) {
        auto beg(m.begin());
        rotate(beg, beg+1, m.end());
        m.back() = w;
      } else {
        m[m_len++] = w;
      }
      
      auto a(db.insert(m.begin(), m.begin() + m_len));
      if (!a->stop) { ans.push_back(a); }
    }
  }

  // pick longest answer
  // echo query if none found
}
