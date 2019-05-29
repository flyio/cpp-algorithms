template <int sigma>  // sigma is the alphabet size, assumed to be small
struct trie {
    array<trie*,sigma> children;
    bool is_word;
    
    trie() : is_word(false) { children.fill(nullptr); };
    ~trie() { for(int i=0;i<sigma;++i){ if(children[i]) delete children[i]; } }
    template<class Iterator>
    void add(Iterator begin, Iterator end){
        if(begin==end) { this->is_word=true; return; }
        if(!children[*begin]) children[*begin] = new trie;
        children[*begin]->add(++begin, end);
        return;
    }
    template<class Iterator>
    bool query(Iterator begin, Iterator end){
        auto ptr = this;
        while(begin!=end){
            if(!ptr->children[*begin]) return false;
            ptr = ptr->children[*begin++];
        }
        return ptr->is_word;
    }

};

template <int sigma>
void print(ostream &out, trie<sigma> &root, string blank="") {
    for(int i=0;i<sigma;++i){
        if(root.children[i]) { 
            out << blank << "-> " << (char)i << (root.is_word ? '*' : ' ') << endl;
            print(out, *root.children[i], blank + " ");
        }
    }
}
