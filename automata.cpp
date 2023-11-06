#include "automata.h"

map< int,multimap<char,int> > graph;
map< int,multimap<char,int> > graph1;

string sym;

t *root;

int nodecnt=0;

vector< set<int> > dstates;

tuple<map<int,multimap<char,int>>,map<int,multimap<char,int>>,int,int> automata(string infexp){
    root = NULL;
    sym = "";
    graph.clear();
    graph1.clear();
    nodecnt = 0;
    dstates.clear();

    int count=0;
    for(int i=0; i<infexp.length(); i++){
        if(isalnum(infexp[i])&&pres(infexp[i])==0){
            sym.insert(count,1,infexp[i]);
            count++;
        }
    }

    string pfexp;
    pfexp=inftopf(infexp);              
    root=conv(pfexp);

    postorder(root);                    //nfa

    // cout << "NFA\n";
    // for(const auto& pair:graph) {
    //     int vert1=pair.first;
    //     multimap<char, int> innerMultiMap=pair.second;
    //     cout<<"Outer Key: "<<vert1<< endl;
    //     for(const auto& innerPair : innerMultiMap) {
    //         char trans= innerPair.first;
    //         int vert2= innerPair.second;
    //         cout <<"Transition: "<<trans<< ", Vertex: "<<vert2<< endl;
    //     }
    // }
    // cout<<endl;

    DFA();                              //dfa

    // cout << "DFA\n";
    // for(const auto& pair:graph1) {
    //     int vert1=pair.first;
    //     multimap<char, int> innerMultiMap=pair.second;
    //     cout<<"Outer Key: "<<vert1<< endl;
    //     for(const auto& innerPair : innerMultiMap) {
    //         char trans= innerPair.first;
    //         int vert2= innerPair.second;
    //         cout <<"Transition: "<<trans<< ", Vertex: "<<vert2<< endl;
    //     }
    // }


    return make_tuple(graph,graph1,root->start,root->end);
}



int oppreced(char op){
    if(op=='*')return 3;
    else if(op=='.')return 2;
    else if(op=='+') return 1;
    else return -1;
}

string inftopf(string infexp){
    stack <char> s;
    string pfexp;
    for (int i=0; i<infexp.length(); i++) {
        char cc=infexp[i];
        if(isalnum(cc)){
            pfexp+=cc;
        } 
        else if(cc=='('){
            s.push('(');
        } 
        else if(cc==')'){
            while(!s.empty()&&s.top()!='('){
                pfexp+=s.top();
                s.pop();
            }
            s.pop(); 
        } 
        else{ 
            while(!s.empty()&&oppreced(cc)<=oppreced(s.top())){
                pfexp+=s.top();
                s.pop();
            }
            s.push(cc);
        }
    }
    while(!s.empty()){
        pfexp+=s.top();
        s.pop();
    }
    return pfexp;
}
t *conv(string s){
    stack <t*> stk;
    for(int i=0; i<s.length(); i++){
        t *node=(t *)malloc(sizeof(t));
        if(isalnum(s[i])){
            node->c=s[i];
            node->left=NULL;
            node->right=NULL;
            stk.push(node);
        }
        else if(s[i]=='*'){
            node->c=s[i];
            node->right=stk.top();
            stk.pop();
            node->left=NULL;
            stk.push(node);
        }
        else if(s[i]=='+'){
            node->c=s[i];
            node->right=stk.top();
            stk.pop();
            node->left=stk.top();
            stk.pop();
            stk.push(node);
        }
        else if(s[i]=='.'){
            node->c=s[i];
            node->right=stk.top();
            stk.pop();
            node->left=stk.top();
            stk.pop();
            stk.push(node);
        }
    }
    t *root1=stk.top();
    stk.pop();
    return root1;
}
void NFA(t *node){
    if(isalnum(node->c)){
        node->start=++nodecnt;
        node->end=++nodecnt;
        graph[node->start].insert(make_pair(node->c,node->end));
    }
    else if(node->c=='+'){
        node->start=++nodecnt;
        node->end=++nodecnt;
        graph[node->start].insert(make_pair('~',node->left->start));
        graph[node->start].insert(make_pair('~',node->right->start));
        graph[node->left->end].insert(make_pair('~',node->end));
        graph[node->right->end].insert(make_pair('~',node->end));
    }
    else if(node->c=='.'){
        node->start=node->left->start;
        node->end=node->right->end;
        graph[node->left->end].insert(make_pair('~',node->right->start));
    }
    else if(node->c=='*'){
        node->start=++nodecnt;
        node->end=++nodecnt;
        graph[node->right->end].insert(make_pair('~',node->right->start));
        graph[node->start].insert(make_pair('~',node->right->start));
        graph[node->right->end].insert(make_pair('~',node->end));
        graph[node->start].insert(make_pair('~',node->end));
    }
}
void postorder(t *node){
    if(node){
        postorder(node->left);
        postorder(node->right);
        NFA(node);
    }
}
set<int> epsclos(int s){
    set<int> a;
    stack<int> b;
    a.insert(s);
    b.push(s);
    while(!b.empty()){
        int c=b.top();
        b.pop();
        auto itr1=graph[c].lower_bound('~');
        auto itr2=graph[c].upper_bound('~');
        while(itr1!=itr2){
            if(a.find(itr1->second)!=a.end()){
                itr1++;
                continue;
            }
            a.insert(itr1->second);
            b.push(itr1->second);
            itr1++;
        }
    }
    return a;
}
set<int> epsclos1(set<int> a){
    set<int> b;
    for(auto p:a){
        set<int> c=epsclos(p);
        b.insert(c.begin(),c.end());
    }
    return b;
}
set<int> move(set<int> a,char c){
    set<int> b;
    for(auto p:a){
        auto itr1=graph[p].lower_bound(c);
        auto itr2=graph[p].upper_bound(c);
        while(itr1!=itr2){
            b.insert(itr1->second);
            itr1++;
        }
    }
    return b;
}
int find(set<int> s){
    for(int i=0; i<dstates.size(); i++){
        if(dstates[i]==s){
            return 1;
            break;
        }
    }
    return 0;
}
int stno(set<int> s){
    for(int i=0; i<dstates.size(); i++){
        if(dstates[i]==s){
            return i;
        }
    }
    return -1;
}
int pres(char c){
    for(int i=0; i<sym.size(); i++){
        if(sym[i]==c){
            return 1;
        }
    }
    return 0;
}
void DFA(){
    stack< set<int> > c;
    set<int> s=epsclos(root->start);
    c.push(s);
    dstates.push_back(s);
    set<int> b,d;
    while(!c.empty()){
        b=c.top();
        c.pop();
        for(int i=0; i<sym.length(); i++){
            if(move(b,sym[i]).empty()){
                continue;
            }
            d=epsclos1(move(b,sym[i]));
            if(find(d)==0){
                c.push(d);
                dstates.push_back(d);
            }
            graph1[stno(b)].insert(make_pair(sym[i],stno(d)));
        }
    }
}