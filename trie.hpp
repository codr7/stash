#include <vector>

using namespace std;

template <typename T>
struct Trie {
  using Links = vector<Trie>;
  using LinkIter = typename Links::iterator;
  
  T key;
  Links links;
  bool stop = false;

  Trie(T key = T()): key(move(key)) {}
  
  template <typename InT>
  Trie *find(const InT &in) { return find(in.begin(), in.end()); }
      
  template <typename InT>
  Trie *find(InT beg, InT end) {
    Trie *t(this);
    
    for (auto i(beg); i != end; i++) {
      auto l(t->get_link(*i));
      if (l == t->links.end()) { return nullptr; }
      t = &*l;
    }
    
    return t;
  }

  LinkIter get_link(const T &key) {
    for (auto i(links.begin()); i != links.end(); i++) {
      if (i->key >= key) { return i; }
    }
    
    return links.end();
  }

  template <typename InT>
  Trie &insert(const InT &in) { return insert(in.begin(), in.end()); }
    
  template <typename InT>
  Trie &insert(InT beg, InT end) {
    Trie *t(this);
    
    for (auto i(beg); i != end; i++) {
      const auto &k(*i);
      auto l(t->get_link(k));

      t = (l == t->links.end() || l->key != k)
        ? &*t->links.emplace(l, k)
        : &*l;
    }
    
    return *t;
  }
};
