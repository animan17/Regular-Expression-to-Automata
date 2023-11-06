#pragma once

#include <bits/stdc++.h>
using namespace std;

tuple<map<int,multimap<char,int>>,map<int,multimap<char,int>>,int,int> automata(string);
void drawGraph(map<int,multimap<char,int>> &adjList, string dotName);