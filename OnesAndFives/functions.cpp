#include <iostream>
#include <vector>
#include<cmath>
#include<map>
#include <algorithm>
#include <fstream>
#include <string>
#include <thread>
#include <future>
using namespace std;





double rolllivesprob(int n) {
	if (n == 1) {
		return (double) 1/3;
	}
	else if (n == 2) {
		return (double) 5/9;
	}
	else if (n == 3) {
		return (double) 13/18;
	}
	else if (n == 4) {
		return (double) 91/108;
	}
	else if (n == 5) {
		return (double) 299/324;
	}
	else if (n == 6) {
		return (double) 157/162;
	}
	else {
		return 0;
	}
}

vector<int> countFreq(vector<int> v){
	vector<int> frequencies;
	for (int i = 1; i <= 6; i++) {
		int freq = std::count(v.begin(), v.end(), i);
		frequencies.push_back(freq);
	}
	return frequencies;
}


vector<vector<int>> listLegalClaims(vector<int> dice) {
	vector<vector<int>> legalclaims;
	vector<int> frequencies = countFreq(dice);
	if (frequencies == vector<int> {1, 1, 1, 1, 1, 1}) {
		return vector<vector<int>> {{1, 2, 3, 4, 5, 6}, { 1 }, { 5 }};
	}
	else {
		vector<vector<int>> legalonesclaims = { {} };
		vector<vector<int>> legalfivesclaims = { {} };
		vector<vector<int>> legalsetclaims = { {} };

		if (frequencies[0] > 0) {
			for (int i = 1; i <= frequencies[0]; i++) {
				vector<int> onesclaim(i, 1);
				legalonesclaims.push_back(onesclaim);
			}
		}
		if (frequencies[4] > 0) {
			for (int i = 1; i <= frequencies[4]; i++) {
				vector<int> fivesclaim(i, 5);
				legalfivesclaims.push_back(fivesclaim);
			}
		}
		int other_numbers[4] = { 2,3,4,6 };
		for (int i = 0; i < 4; i++) {
			int dicevalue = other_numbers[i];
			int frequencyofvalue = frequencies[(dicevalue - 1)];
			if (frequencyofvalue >= 3) {
				for (int j = 3; j <= frequencyofvalue; j++) {
					vector<int> setclaim(j, dicevalue);
					legalsetclaims.push_back(setclaim);
				}
			}
		}
		if ((legalsetclaims.size() == 3) and legalsetclaims[1][1] != legalsetclaims[2][1]) {
			vector<int> claim1 = legalsetclaims[1];
			vector<int> claim2 = legalsetclaims[2];

			claim1.insert(claim1.end(),claim2.begin(),claim2.end());
			legalsetclaims.push_back(claim1);
		}

		int oneclaimlength = legalonesclaims.size();
		int fiveclaimlength = legalfivesclaims.size();
		int setclaimlength = legalsetclaims.size();

		for (int i = 0; i < oneclaimlength; i++) {
			for (int j = 0; j < fiveclaimlength; j++) {
				for (int k = 0; k < setclaimlength; k++) {
					vector<int> legalclaim;
					vector<int> oneclaim = legalonesclaims[i];
					vector<int> fiveclaim = legalfivesclaims[j];
					vector<int> setclaim = legalsetclaims[k];
					


					legalclaim.insert(legalclaim.end(), oneclaim.begin(), oneclaim.end());
					legalclaim.insert(legalclaim.end(), fiveclaim.begin(), fiveclaim.end());
					legalclaim.insert(legalclaim.end(), setclaim.begin(), setclaim.end());
					legalclaims.push_back(legalclaim);
				}
			}
		}
		legalclaims.erase(legalclaims.begin());


		return legalclaims;
	}
}

void printvector(vector<int> v) {
	int lengthoflist = v.size();
	for (int k = 0; k < lengthoflist; k++) {
		std::cout << v[k];
		std::cout << " ";
	}
	std::cout << "\n";
}
void printvector(vector<double> v) {
	int lengthoflist = v.size();
	for (int k = 0; k < lengthoflist; k++) {
		std::cout << v[k];
		std::cout << " ";
	}
	std::cout << "\n";
}

void printvofv(vector<vector<int>> v) {
	int numberofelements = v.size();
	for (int i = 0; i < numberofelements; i++) {
		printvector(v[i]);
	}
}

int rerollifzero(int n) {
	if (n == 0) {
		return 6;
	}
	else {
		return n;
	}
}

int scoreclaim(vector<int> claim) {
	int score = 0;
	vector<int> frequencies = countFreq(claim);

	if (frequencies == vector<int> {1, 1, 1, 1, 1, 1}) {
		score += 2000;
	}

	else {
		for (int i = 0; i < 6; i++) {
			int frequency = frequencies[i];
			if (frequency >= 3) {
				if (i == 0) {
					int basescore = 1000;
					int multiplier = pow(2, frequency - 3);
					score+= basescore*multiplier;
				}
				else {
					int basescore = 100 * (i+1);
					int multiplier = pow(2, frequency - 3);
					score += basescore * multiplier;
				}
				
			}
			else {
				if (i == 0) {
					score += 100 * frequency;
				}
				if (i == 4) {
					score += 50 * frequency;
				}
			}
		}
	}
	return score;



}

map<int, vector<vector<int>>> getrolllookupdice() {
	map<int, vector<vector<int>>> rolllookupdice;
	rolllookupdice[1] = { {1}, {0}, {5} };
	rolllookupdice[2] = { {1, 1}, {1, 0}, {1, 5}, {0, 0}, {5, 0}, {5, 5} };
	rolllookupdice[3] = { {1, 1, 1}, {1, 1, 0}, {1, 1, 5}, {1, 0, 0}, {1, 5, 0}, {1, 5, 5}, {2, 2, 2}, {0, 0, 0}, {5, 0, 0}, {5, 5, 0}, {3, 3, 3}, {4, 4, 4}, {5, 5, 5}, {6, 6, 6} };
	rolllookupdice[4] = { {1, 1, 1, 1}, {1, 1, 1, 0}, {1, 1, 1, 5}, {1, 1, 0, 0}, {1, 1, 5, 0}, {1, 1, 5, 5}, {1, 2, 2, 2}, {1, 0, 0, 0}, {1, 5, 0, 0}, {1, 5, 5, 0}, {1, 3, 3, 3}, {1, 4, 4, 4}, {1, 5, 5, 5}, {1, 6, 6, 6}, {2, 2, 2, 2}, {2, 2, 2, 0}, {2, 2, 2, 5}, {0, 0, 0, 0}, {5, 0, 0, 0}, {5, 5, 0, 0}, {3, 3, 3, 0}, {4, 4, 4, 0}, {5, 5, 5, 0}, {6, 6, 6, 0}, {3, 3, 3, 3}, {3, 3, 3, 5}, {4, 4, 4, 4}, {4, 4, 4, 5}, {5, 5, 5, 5}, {5, 6, 6, 6}, {6, 6, 6, 6} };
	rolllookupdice[5] = { {1, 1, 1, 1, 1}, {1, 1, 1, 1, 0}, {1, 1, 1, 1, 5}, {1, 1, 1, 0, 0}, {1, 1, 1, 5, 0}, {1, 1, 1, 5, 5}, {1, 1, 2, 2, 2}, {1, 1, 0, 0, 0}, {1, 1, 5, 0, 0}, {1, 1, 5, 5, 0}, {1, 1, 3, 3, 3}, {1, 1, 4, 4, 4}, {1, 1, 5, 5, 5}, {1, 1, 6, 6, 6}, {1, 2, 2, 2, 2}, {1, 2, 2, 2, 0}, {1, 2, 2, 2, 5}, {1, 0, 0, 0, 0}, {1, 5, 0, 0, 0}, {1, 5, 5, 0, 0}, {1, 3, 3, 3, 0}, {1, 4, 4, 4, 0}, {1, 5, 5, 5, 0}, {1, 6, 6, 6, 0}, {1, 3, 3, 3, 3}, {1, 3, 3, 3, 5}, {1, 4, 4, 4, 4}, {1, 4, 4, 4, 5}, {1, 5, 5, 5, 5}, {1, 5, 6, 6, 6}, {1, 6, 6, 6, 6}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 0}, {2, 2, 2, 2, 5}, {2, 2, 2, 0, 0}, {2, 2, 2, 5, 0}, {2, 2, 2, 5, 5}, {3, 3, 3, 0, 0}, {0, 0, 0, 0, 0}, {5, 0, 0, 0, 0}, {5, 5, 0, 0, 0}, {4, 4, 4, 0, 0}, {5, 5, 5, 0, 0}, {6, 6, 6, 0, 0}, {3, 3, 3, 3, 0}, {3, 3, 3, 5, 0}, {4, 4, 4, 4, 0}, {4, 4, 4, 5, 0}, {5, 5, 5, 5, 0}, {5, 6, 6, 6, 0}, {6, 6, 6, 6, 0}, {3, 3, 3, 3, 3}, {3, 3, 3, 3, 5}, {3, 3, 3, 5, 5}, {4, 4, 4, 4, 4}, {4, 4, 4, 4, 5}, {4, 4, 4, 5, 5}, {5, 5, 5, 5, 5}, {5, 5, 6, 6, 6}, {5, 6, 6, 6, 6}, {6, 6, 6, 6, 6} };
	rolllookupdice[6] = { {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 5}, {1, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 5, 0}, {1, 1, 1, 1, 5, 5}, {1, 1, 1, 2, 2, 2}, {1, 1, 1, 0, 0, 0}, {1, 1, 1, 5, 0, 0}, {1, 1, 1, 5, 5, 0}, {1, 1, 1, 3, 3, 3}, {1, 1, 1, 4, 4, 4}, {1, 1, 1, 5, 5, 5}, {1, 1, 1, 6, 6, 6}, {1, 1, 2, 2, 2, 2}, {1, 1, 2, 2, 2, 0}, {1, 1, 2, 2, 2, 5}, {1, 1, 0, 0, 0, 0}, {1, 1, 5, 0, 0, 0}, {1, 1, 5, 5, 0, 0}, {1, 1, 3, 3, 3, 0}, {1, 1, 4, 4, 4, 0}, {1, 1, 5, 5, 5, 0}, {1, 1, 6, 6, 6, 0}, {1, 1, 3, 3, 3, 3}, {1, 1, 3, 3, 3, 5}, {1, 1, 4, 4, 4, 4}, {1, 1, 4, 4, 4, 5}, {1, 1, 5, 5, 5, 5}, {1, 1, 5, 6, 6, 6}, {1, 1, 6, 6, 6, 6}, {1, 2, 2, 2, 2, 2}, {1, 2, 2, 2, 2, 0}, {1, 2, 2, 2, 2, 5}, {1, 2, 2, 2, 0, 0}, {1, 2, 2, 2, 5, 0}, {1, 2, 2, 2, 5, 5}, {1, 3, 3, 3, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 5, 0, 0, 0, 0}, {1, 5, 5, 0, 0, 0}, {1, 4, 4, 4, 0, 0}, {1, 5, 5, 5, 0, 0}, {1, 6, 6, 6, 0, 0}, {1, 3, 3, 3, 3, 0}, {1, 3, 3, 3, 5, 0}, {1, 2, 3, 4, 5, 6}, {1, 4, 4, 4, 4, 0}, {1, 4, 4, 4, 5, 0}, {1, 5, 5, 5, 5, 0}, {1, 5, 6, 6, 6, 0}, {1, 6, 6, 6, 6, 0}, {1, 3, 3, 3, 3, 3}, {1, 3, 3, 3, 3, 5}, {1, 3, 3, 3, 5, 5}, {1, 4, 4, 4, 4, 4}, {1, 4, 4, 4, 4, 5}, {1, 4, 4, 4, 5, 5}, {1, 5, 5, 5, 5, 5}, {1, 5, 5, 6, 6, 6}, {1, 5, 6, 6, 6, 6}, {1, 6, 6, 6, 6, 6}, {2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 0}, {2, 2, 2, 2, 2, 5}, {2, 2, 2, 2, 0, 0}, {2, 2, 2, 2, 5, 0}, {2, 2, 2, 2, 5, 5}, {2, 2, 2, 3, 3, 3}, {2, 2, 2, 0, 0, 0}, {2, 2, 2, 5, 0, 0}, {2, 2, 2, 5, 5, 0}, {2, 2, 2, 4, 4, 4}, {2, 2, 2, 5, 5, 5}, {2, 2, 2, 6, 6, 6}, {3, 3, 3, 3, 0, 0}, {3, 3, 3, 0, 0, 0}, {3, 3, 3, 5, 0, 0}, {0, 0, 0, 0, 0, 0}, {5, 0, 0, 0, 0, 0}, {5, 5, 0, 0, 0, 0}, {4, 4, 4, 0, 0, 0}, {5, 5, 5, 0, 0, 0}, {6, 6, 6, 0, 0, 0}, {4, 4, 4, 4, 0, 0}, {4, 4, 4, 5, 0, 0}, {5, 5, 5, 5, 0, 0}, {5, 6, 6, 6, 0, 0}, {6, 6, 6, 6, 0, 0}, {3, 3, 3, 3, 3, 0}, {3, 3, 3, 3, 5, 0}, {3, 3, 3, 5, 5, 0}, {4, 4, 4, 4, 4, 0}, {4, 4, 4, 4, 5, 0}, {4, 4, 4, 5, 5, 0}, {5, 5, 5, 5, 5, 0}, {5, 5, 6, 6, 6, 0}, {5, 6, 6, 6, 6, 0}, {6, 6, 6, 6, 6, 0}, {3, 3, 3, 3, 3, 3}, {3, 3, 3, 3, 3, 5}, {3, 3, 3, 3, 5, 5}, {3, 3, 3, 4, 4, 4}, {3, 3, 3, 5, 5, 5}, {3, 3, 3, 6, 6, 6}, {4, 4, 4, 4, 4, 4}, {4, 4, 4, 4, 4, 5}, {4, 4, 4, 4, 5, 5}, {4, 4, 4, 5, 5, 5}, {4, 4, 4, 6, 6, 6}, {5, 5, 5, 5, 5, 5}, {5, 5, 5, 6, 6, 6}, {5, 5, 6, 6, 6, 6}, {5, 6, 6, 6, 6, 6}, {6, 6, 6, 6, 6, 6} };
	return rolllookupdice;
}	

map<int, vector<int>> getrolllookupfrequency() {
	map<int, vector<int>> rolllookupfrequency;
	rolllookupfrequency[1] = { 1,4,1 };
	rolllookupfrequency[2] = { 1, 8, 2, 16, 8, 1 };
	rolllookupfrequency[3] = { 1, 12, 3, 48, 24, 3, 1, 60, 48, 12, 1, 1, 1, 1 };
	rolllookupfrequency[4] = { 1, 16, 4, 96, 48, 6, 4, 240, 192, 48, 4, 4, 4, 4, 1, 12, 4, 204, 240, 96, 12, 12, 16, 12, 1, 4, 1, 4, 1, 4, 1 };
	rolllookupfrequency[5] = { 1, 20, 5, 160, 80, 10, 10, 600, 480, 120, 10, 10, 10, 10, 5, 60, 20, 1020, 1200, 480, 60, 60, 80, 60, 5, 20, 5, 20, 5, 20, 5, 1, 15, 5, 90, 60, 10, 90, 600, 1020, 600, 90, 160, 90, 15, 60, 15, 60, 20, 60, 15, 1, 5, 10, 1, 5, 10, 1, 10, 5, 1 };
	rolllookupfrequency[6] = { 1, 24, 6, 240, 120, 15, 20, 1200, 960, 240, 20, 20, 20, 20, 15, 180, 60, 3060, 3600, 1440, 180, 180, 240, 180, 15, 60, 15, 60, 15, 60, 15, 6, 90, 30, 540, 360, 60, 540, 3600, 5400, 3600, 540, 960, 540, 90, 360, 720, 90, 360, 120, 360, 90, 6, 30, 60, 6, 30, 60, 6, 60, 30, 6, 1, 18, 6, 135, 90, 15, 20, 480, 540, 180, 20, 20, 20, 135, 480, 540, 1440, 3600, 3060, 480, 1200, 480, 135, 540, 240, 540, 135, 18, 90, 180, 18, 90, 180, 24, 180, 90, 18, 1, 6, 15, 20, 20, 20, 1, 6, 15, 20, 20, 1, 20, 15, 6, 1 };
	return rolllookupfrequency;
}

double bankingdatabase[6][2000];
double winprobdatabase[200][200][6][200];
map<int, vector<vector<int>>> rolllookupdice = getrolllookupdice();
map<int, vector<int>> rolllookupfrequency = getrolllookupfrequency();
int goal = 10000;



map<vector<int>, vector<pair<int,int>>> getreasonableclaimmap() {
	map<vector<int>, vector<pair<int, int>>> reasonableclaimmap;
	for (int dice = 1; dice <= 6; dice++) {
		vector<vector<int>> rolllist = rolllookupdice[dice];
		for (int i = 0; i < rolllist.size(); i++) {
			vector<int> roll = rolllist[i];
			vector<vector<int>> legalclaims = listLegalClaims(roll);
			vector<pair<int,int>> reasonableclaims;
			int scores[6] = { 0 };
			for (int j = 0; j < legalclaims.size(); j++) {
				vector<int> claim = legalclaims[j];
				int claimsize = claim.size();
				int claimscore = scoreclaim(claim);
				if (claimscore > scores[claimsize - 1]) {
					scores[claimsize - 1] = claimscore;
				}
			}
			for (int j = 0; j < 6; j++) {
				if (scores[j] > 0) {
					pair<int, int> reasonableclaim(j+1,scores[j]);
					reasonableclaims.push_back(reasonableclaim);
				}
			}
			reasonableclaimmap[roll] = reasonableclaims;
		}
	}
	return reasonableclaimmap;
}


map<vector<int>, vector<pair<int,int>>> listreasonableclaims = getreasonableclaimmap();

void testeverything() {
	map<int, vector<vector<int>>> rolllookupdice = getrolllookupdice();
	map<int, vector<int>> rolllookupfrequency = getrolllookupfrequency();
	srand(time(NULL));

	
	while (true) {
		int dicetoroll;
		cout << "How many dice would you like to roll?\n";
		cin >> dicetoroll;
		int numberofpossibilities = pow(6, dicetoroll);
		int random_number = rand() % numberofpossibilities;
		vector<vector<int>> rolldice = rolllookupdice[dicetoroll];
		vector<int> rollfrequency = rolllookupfrequency[dicetoroll];

		int tot = 0;
		int index = 0;
		while (tot < random_number) {
			tot += rollfrequency[index];
			index += 1;
		}
		vector<int> dice = rolldice[index];

		cout << "You rolled ";
		printvector(dice);
		vector<vector<int>> legalclaims = listLegalClaims(dice);
		cout << "Legal claims are:\n";
		printvofv(legalclaims);









	}
}


double scoringgain(int numberofdice, int score, vector<int> roll); //so that c++ knows that everything will be ok
double bankinggain(int numberofdice, int score) {
	double bankinggain;
	double databaselookup = ::bankingdatabase[numberofdice - 1][(score / 50)];

	if (databaselookup != 0) {
		bankinggain = databaselookup;


	}
	else if (score <= 0) {
		int sumofexpectations = 0;
		vector<vector<int>> possiblerolls = ::rolllookupdice[numberofdice];
		vector<int> rollfrequencies = ::rolllookupfrequency[numberofdice];
		for (int i = 0; i < possiblerolls.size(); i++) {
			vector<int>  rolldice = possiblerolls[i];
			printvector(rolldice);
			int rollfrequency = rollfrequencies[i];
			sumofexpectations += rollfrequency * scoringgain(numberofdice, score, rolldice);
		}
		bankinggain = sumofexpectations / pow(6, numberofdice);
	}
	else if (score > 20000) {
		bankinggain = score;
	}
	else {
		int sumofexpectations = 0;
		vector<vector<int>> possiblerolls = ::rolllookupdice[numberofdice];
		vector<int> rollfrequencies = ::rolllookupfrequency[numberofdice];
		for (int i = 0; i < possiblerolls.size(); i++) {
			vector<int>  rolldice = possiblerolls[i];
			int rollfrequency = rollfrequencies[i];
			sumofexpectations += rollfrequency * scoringgain(numberofdice, score, rolldice);
		}
		bankinggain = sumofexpectations / pow(6, numberofdice);
		bankinggain = max(bankinggain, double (score+0.0));
	}
	::bankingdatabase[numberofdice - 1][score / 50] = bankinggain;
	//cout << "Bankinggain of value " << bankinggain << " Found at " << numberofdice <<", "<< score << "\n";
	return bankinggain;
}


double scoringgain(int numberofdice, int score, vector<int> roll) {
	vector<vector<int>> legalclaims = listLegalClaims(roll);
	vector<double> bankinggains;
	double scoringgain;

	if (legalclaims == vector<vector<int>> {}) {
		scoringgain=0;
	}
	else {
		for (int i = 0; i < legalclaims.size(); i++) {
			vector<int> claim = legalclaims[i];
			int newnumberdice = rerollifzero(numberofdice - claim.size());
			int newscore = score + scoreclaim(claim);
			double bank = bankinggain(newnumberdice, newscore);
			bankinggains.push_back(bank);
		}
		/*cout << "Calling max of ";
		printvector(bankinggains);
		cout << "\n";
		cout << "Legal claims are";
		printvofv(legalclaims);
		*/
		scoringgain =*max_element(bankinggains.begin(),bankinggains.end());
	}
	return scoringgain;
}

double oneplayergame() {
	return bankinggain(6, 0);
}

void setwins(int goal) {
	for (int playerscore = 0; playerscore < (goal/50); playerscore++) {
		for (int tempscore = 0; tempscore < (goal/50); tempscore++) {
			if (50 * (playerscore + tempscore) >= goal) {
				for (int dice = 0; dice < 6; dice++) {
					for (int opponentscore = 0; opponentscore < (goal/50); opponentscore++) {
						::winprobdatabase[playerscore][opponentscore][dice][tempscore] = 1;
					}
				}


			}
		}
	}
}

double checkwinprob(int playerscore, int opponentscore, int dice, int tempscore) {
	return ::winprobdatabase[playerscore][opponentscore][dice][tempscore];
}

double scoringwinprob(int playerscore, int opponentscore, int numberofdice, int tempscore, vector<int> roll);//so that c++ knows that everything will be ok

double bankingwinprob(int playerscore, int opponentscore, int numberofdice, int tempscore, bool lookup = false) {
	double winprob;
	if (playerscore + tempscore >= ::goal) {
		winprob = 1;
	}
	else if (lookup) {
		winprob = ::winprobdatabase[playerscore / 50][opponentscore / 50][numberofdice - 1][tempscore / 50];
	}
	else {
		if (tempscore == 0) {
			double sumofprobabilities = 0;
			vector<vector<int>> rolls = rolllookupdice[numberofdice];
			vector<int> frequencies = rolllookupfrequency[numberofdice];
			for (int i = 0; i < rolls.size(); i++) {
				vector<int> roll = rolls[i];
				int frequency = frequencies[i];

				double rollwinprob = scoringwinprob(playerscore, opponentscore, numberofdice, tempscore, roll);
				sumofprobabilities += frequency * rollwinprob;
			}
			winprob = sumofprobabilities / pow(6, numberofdice);
		}
		else {
			double bankwinprob = 1 - bankingwinprob(opponentscore, playerscore + tempscore, 6, 0, true);
		
			double sumofprobabilities = 0;
			vector<vector<int>> rolls = rolllookupdice[numberofdice];
			vector<int> frequencies = rolllookupfrequency[numberofdice];
			for (int i = 0; i < rolls.size(); i++) {
				vector<int> roll = rolls[i];
				int frequency = frequencies[i];

				double rollwinprob = scoringwinprob(playerscore, opponentscore, numberofdice, tempscore, roll);
				sumofprobabilities += frequency * rollwinprob;
			}
			winprob = sumofprobabilities / pow(6, numberofdice);
			winprob = max(winprob, bankwinprob);
		}
	}
	return winprob;

}


double scoringwinprob(int playerscore, int opponentscore, int numberofdice, int tempscore, vector<int> roll) {
	double winprob;
	//vector<vector<int>> legalclaims = listLegalClaims(roll);
	vector<pair<int, int>> reasonableclaims = ::listreasonableclaims[roll];
	if (reasonableclaims == vector<pair<int,int>> {}) {
		winprob = 1 - bankingwinprob(opponentscore,playerscore,6,0,true);
	}
	else {
		vector<double> bankingprobs;
		for (int i = 0; i < reasonableclaims.size(); i++) {
			pair<int,int> claim = reasonableclaims[i];
			int newnumberdice = rerollifzero(numberofdice - claim.first);
			int newscore = tempscore + claim.second;
			double bankclaimprob = bankingwinprob(playerscore, opponentscore, newnumberdice, newscore, true);
			bankingprobs.push_back(bankclaimprob);	
		}
		winprob = *max_element(bankingprobs.begin(),bankingprobs.end());
	}
	return winprob;

}
double threadsweep(int goal, int dice) {
	double delta = 0;
	int start = goal - 50;
	for (int playerscore = start; playerscore >= 0; playerscore -= 50) {
		for (int opponentscore = start; opponentscore >= 0; opponentscore -= 50) {
			for (int tempscore = start; tempscore >= 0; tempscore -= 50) {
				double oldwinprob = ::winprobdatabase[playerscore / 50][opponentscore / 50][dice - 1][tempscore / 50];
				double winprob = bankingwinprob(playerscore, opponentscore, dice, tempscore);
				::winprobdatabase[playerscore / 50][opponentscore / 50][dice - 1][tempscore / 50] = winprob;
				delta = max(abs(winprob - oldwinprob), delta);
			}
		}
		cout << "I'm in thread" << dice << " !\n";
	}
	cout << "Thread with " << dice << " dice complete!";
	return delta;
}
double sweep(int goal) {
	vector<double> deltalist;
	double delta = 0;
	auto th1 = async(threadsweep, goal, 1);
	auto th2 = async(threadsweep, goal, 2);
	auto th3 = async(threadsweep, goal, 3);
	auto th4 = async(threadsweep, goal, 4);
	auto th5 = async(threadsweep, goal, 5);
	auto th6 = async(threadsweep, goal, 6);
	deltalist.push_back(th1.get());
	deltalist.push_back(th2.get());
	deltalist.push_back(th3.get());
	deltalist.push_back(th4.get());
	deltalist.push_back(th5.get());
	deltalist.push_back(th6.get());
	delta = *max_element(deltalist.begin(), deltalist.end());
	return delta;
}

/*
void savedatabase() {
	FILE* dat = fopen("myfile.dat", "w"); // opens new file for writing
	int max = ::goal / 50;
	if (dat)
	{
		for (int i = 0; i < max; i++)
		{
			for (int j = 0; j < max; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					for (int l = 0; l < max; l++) {
						fprintf(dat, "%f", ::winprobdatabase[i][j][k][l]);
					}
					fprintf(dat, "\n");
				}
				fprintf(dat, "\n");
			}
			fprintf(dat, "\n");
		}
	}
}

void loaddatabase() {
	int max = ::goal / 50;
	FILE* dat = fopen("myfile.dat", "r"); // opens file for reading
	if (dat){
		for (int i = 0; i < max; i++) {
			for (int j = 0; j < max; j++) {
				for (int k = 0; k < 6; k++) {
					for (int l = 0; l < max; l++) {
						fscanf(dat, "%f", &::winprobdatabase[i][j][k][l]);
					}
				}
			}
		}
	}
}
*/

void writetofile2dim() {
	ofstream myfile;
	for (int dice = 0; dice < 6; dice++) {
		for (int playerscore = 0; playerscore < 200; playerscore++) {
			string filename = "winprobdatabase_" + to_string(playerscore) + "_" + to_string(dice) + ".txt";
			myfile.open(filename);
			for (int opponentscore = 0; opponentscore < 200; opponentscore++) {
				for (int tempscore = 0; tempscore < 200; tempscore++) {
					myfile << ::winprobdatabase[playerscore][opponentscore][dice][tempscore] << " ";
				}
			}
			myfile.close();
			cout << "written " << playerscore << "/200 ";

		}
		cout << "written " << dice << "/6 \n ";
	}
}

void readfromfile() {
	ifstream myfile;
	for (int playerscore = 0; playerscore < 200; playerscore++) {
		for (int dice = 0; dice < 6; dice++) {
			string filename = "winprobdatabase_" + to_string(playerscore) + "_" + to_string(dice) + ".txt";
			myfile.open(filename);
			for (int opponentscore = 0; opponentscore < 200; opponentscore++) {
				for (int tempscore = 0; tempscore < 200; tempscore++) {
					myfile >> ::winprobdatabase[playerscore][opponentscore][dice][tempscore];
				}
			}
			myfile.close();


		}
		cout << "read" << playerscore << "/200 ";
	}


}


void valueiterate(double tolerance, int goal) {
	setwins(goal);
	readfromfile();
	double delta = 1;
	while (delta > tolerance) {
		delta = sweep(goal);
		cout << "Completed sweep! Delta = " << delta << "\n";
		cout << "Prob of p1 winning: " << ::winprobdatabase[0][0][5][0];
		cout << "\nProb of winning from state 500 0 3 100: " << ::winprobdatabase[10][0][3][2] << "\n";
		writetofile2dim();
	}
}

void databaselookup(int playerscore, int opponentscore, int numberofdice, int tempscore) {
	cout << ::winprobdatabase[playerscore / 50][opponentscore / 50][numberofdice - 1][tempscore / 50] << "\n";
}

