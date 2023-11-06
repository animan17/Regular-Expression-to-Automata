#pragma once

#include <bits/stdc++.h>
using namespace std;

struct syntree{
    char c;
    int start;
    int end;
    struct syntree *left;
    struct syntree *right;
};
typedef struct syntree t;

int oppreced(char op);
string inftopf(string infexp);
t *conv(string s);
void NFA(t *node);
void postorder(t *node);
set<int> epsclos(int s);
set<int> epsclos1(set<int> a);
set<int> move(set<int> a,char c);
int find(set<int> s);
int stno(set<int> s);
int pres(char c);
void DFA();