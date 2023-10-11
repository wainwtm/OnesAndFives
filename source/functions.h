#pragma once
#include <vector>
#include<map>
#include <thread>
using namespace std;
double rolllivesprob(int n);
vector<int> countFreq(vector<int> v);
vector<vector<int>> listLegalClaims(vector<int> dice);
void printvector(vector<int> v);
void printvector(vector<double> v);
void printvofv(vector<vector<int>> v);
int rerollifzero(int n);
int scoreclaim(vector<int> claim);
map<int, vector<vector<int>>> getrolllookupdice();
map<int, vector<int>> getrolllookupfrequency();
void testeverything();
double bankinggain(int numberofdice, int score);
double scoringgain(int numberofdice, int score, vector<int> roll);
double oneplayergame();
void setwins(int goal);
double checkwinprob(int playerscore, int opponentscore, int dice, int tempscore);
double bankingwinprob(int playerscore, int opponentscore, int numberofdice, int tempscore, bool lookup = false);
double scoringwinprob(int playerscore, int opponentscore, int numberofdice, int tempscore, vector<int> roll);
double threadsweep(int goal, int dice);
double sweep(int goal);
void valueiterate(double tolerance,int goal);
map<vector<int>, vector<pair<int,int>>> getreasonableclaimmap();
void writetofile2dim();
void readfromfile();