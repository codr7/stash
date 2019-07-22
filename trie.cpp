#include <cassert>
#include <string>

#include "trie.hpp"

int main() {
  Trie<char> t;
  t.insert(string("foo")).insert(string("bar"));
  t.insert(string("baz"));
  auto n(t.find(string("foob")));
  assert(n && n->key == 'b');
  return 0;
}
