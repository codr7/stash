#include <cassert>
#include <string>
#include <vector>

using namespace std;

template <typename T>
struct Trie {
  struct Node;
  using Nodes = vector<Node>;
  using NodeIter = typename Nodes::iterator;
  
  struct Node {
    T key;
    Nodes children;
    bool is_end = false;
    
    Node(T key): key(move(key)) {}

    NodeIter find_key(const T &key) {
      for (auto i(children.begin()); i != children.end(); i++) {
        if (i->key >= key) { return i; }
      }

      return children.end();
    }

    template <typename InT>
    Node *insert(const InT &in) { return insert(in.begin(), in.end()); }
    
    template <typename InT>
    Node *insert(InT beg, InT end) {
      Node *n(this);
      
      for (auto i(beg); i != end; i++) {
        const auto &k(*i);
        auto cn(n->find_key(k));
        
        n = (cn == n->children.end() || cn->key != k)
          ? &*n->children.emplace(cn, k)
          : &*cn;
      }

      n->is_end = true;
      return n;
    }

    template <typename InT>
    Node *search(const InT &in) { return search(in.begin(), in.end()); }
      
    template <typename InT>
    Node *search(InT beg, InT end) {
      Node *n(this);
      
      for (auto i(beg); i != end; i++) {
        auto cn(n->find_key(*i));
        if (cn == n->children.end()) { return nullptr; }
        n = &*cn;
      }

      return n;
    }
  };

  Node root;

  Trie(T root_key = T()): root(move(root_key)) {}
};

int main() {
  Trie<char> t;
  t.root.insert(string("foo"))->insert(string("bar"));
  t.root.insert(string("baz"));
  auto n(t.root.search(string("foob")));
  assert(n && n->key == 'b');
  return 0;
}
