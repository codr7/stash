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

    template <typename InT>
    Node *find(const InT &in) { return find(in.begin(), in.end()); }
      
    template <typename InT>
    Node *find(InT beg, InT end) {
      Node *n(this);
      
      for (auto i(beg); i != end; i++) {
        auto cn(n->get_child(*i));
        if (cn == n->children.end()) { return nullptr; }
        n = &*cn;
      }

      return n;
    }

    NodeIter get_child(const T &key) {
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
        auto cn(n->get_child(k));
        
        n = (cn == n->children.end() || cn->key != k)
          ? &*n->children.emplace(cn, k)
          : &*cn;
      }

      n->is_end = true;
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
  auto n(t.root.find(string("foob")));
  assert(n && n->key == 'b');
  return 0;
}
