#include <iostream>
#include <fstream>
#include<sstream>
#include<string>
#include<vector>
#include <iterator> 
#include<cmath>
using namespace std;
std::ifstream infile("C:\\Users\\ZEYNEP\\Desktop\\INPUT.txt");
vector<vector<int>>locc;
vector<string>locs;
int temp = 0;
vector<int>v1;
vector<string>entloc;
class Habitat {
public:
string status="normal";
string dna;
string name;
int end = 5 ;
int deadline = 7;
int surv;

int count = 1;
string lastloc;

};
vector<Habitat>entity;
 

bool can_infected(string str) {
	bool flag = false;
	int tem = 0;
	for (char each : str) {
		if (each == 'A' || each == 'B') tem++;

	}
	if (tem > 0) {
		flag = true;
	}
	return flag;
}
bool can_die(string str) {
	bool flag = false;
	int counter = 0;
	for (int i = 0;i < 5;i++) {
		if (str[i] == 'A' || str[i] == 'B' || str[i] == 'C' || str[i] == 'D')counter++;
	}
	if (counter >= 3) flag = true;
	return flag;
}

void convert(string loca) {
	vector<int>v;
	int z2 = 0;
	for (int ii = 0;ii < loca.size();ii++) {
		if (loca[ii] == 'x') {
			v.push_back(z2);
			z2 = 0;
		}
		else {
			int z1 = 0;
			z1 = loca[ii];
			z1 = z1 - 48;
			z2 = z2 * 10 + z1;
		}
		if (ii == loca.size() - 1) {
			v.push_back(z2);
		}
	}
	locc.push_back(v);
	v.pop_back();
	v.pop_back();


}
void controlA(int entcount) {
	for (int i = 0;i < entcount;i++) {
		if (entity[i].status == "infected") {
			entity[i].end--;
			
		}
		if (entity[i].end <= 0) {entity[i].status = "infectious";}
	}
}
void controlD(int entcount) {
	for (int i = 0;i < entcount;i++) {
		if (entity[i].end <= 0&&entity[i].status!="dead")entity[i].status = "infectious";
	}
}
void controlC(int entcount,int turnnu) {
	for (int i = 0;i < entcount;i++) {
		if(entity[i].status=="infected"|| entity[i].status == "infectious"){
		entity[i].surv--; 
		if (entity[i].dna == "candie"){
		if (entity[i].surv <= 0) {
			entity[i].status = "deadd";
			entity[i].count--;
			if (entity[i].count == 0) {
			entity[i].lastloc = locs[((turnnu) * entcount )+ i ];
			}
		
		
			
		
		}
	}
		else
			if (entity[i].surv < 0) {
				entity[i].status = "immune";
				
				
			}
		}
	 if (entity[i].status == "deadd") {
				entity[i].deadline--;
			if (entity[i].deadline <= 0) {
				entity[i].status = "dead";
			}
		}
	}
}

void controlB( int entcount) {
	for (int i = temp;i <temp+entcount;i++) {
		convert(locs[i]);
	}

	temp += entcount;
	
	for (int i = 0;i <  entcount;i++) {
		if (entity[i].status == "infectious") {
			for (int j = 0;j< entcount;j++) {
				int x1, x2;
				x1 = abs(locc[i][0] - locc[j][0]);
				x2 = abs(locc[i][1] - locc[j][1]);

					if ((pow(x1, 2) + pow(x2, 2)) <= 18) {
						if (entity[j].status != "immune"&&entity[j].status!="deadd"&&entity[j].dna!="strong"&& entity[j].status != "dead"&&entity[i].status!="infectious") {
							entity[j].status = "infected";
							

						}

					}
					
				


			}
		}
		
		else if (entity[i].status == "deadd") {
			std::stringstream ss(entity[i].lastloc);
			for (int a; ss >> a;) {
				v1.push_back(a);
				if (ss.peek() == 'x')
					ss.ignore();
			}
			for (int j = 0;j < entcount;j++) {
				int x1, x2;
				x1 = abs( v1[0]- locc[j][0]);
				x2 = abs( v1[1]- locc[j][1]);

				if ((pow(x1, 2) + pow(x2, 2)) <= 18) {
					if (entity[j].status != "immune" && entity[j].status != "deadd" && entity[j].dna != "strong" && entity[j].status != "dead") {
						entity[j].status = "infected";
						

					}

				}




			}
			v1.clear();
		}
	}
	
}
	

int main()
{
	int turn_count = 0, size = 0;
	string sizee, turn;
	vector<string>vec;
	string str;
	while (infile >> str) {

		vec.push_back(str);
	}
	int a = 0;
	for (int i = 0;i < vec.size();i++) {
		if (vec[i] == "size") {
			sizee = vec[i + 1];turn = vec[i + 3];
			stringstream ss(sizee);
			ss >> size;
			stringstream s(turn);
			s >> turn_count;
		}
		if (vec[i] == "entity") {
			entloc.push_back(vec[i + 3]);
			Habitat ent;
			entity.push_back(ent);
			entity[a].name = vec[i + 1];
			if (can_infected(vec[i + 2]) == 1) {
				if (can_die(vec[i + 2]) == 1) {
					entity[a].dna = "candie";
					entity[a].surv = 14;
				}
				else {
					entity[a].dna = "cangood";
					entity[a].surv = 30;
				}
			}
			else {
				entity[a].dna = "strong";
				entity[a].surv = turn_count + 1;

			}
			if (vec[i + 4] == "infected") {
				entity[a].status = "infected";
				entity[a].end = 4;
			}
			else {
				entity[a].status = "normal";
				
			}a++;
		}

	}
	int entcount = entity.size();
	for (int i = 0;i < vec.size();i++) {//locations
		if (vec[i] == "turn") {
			int j = i + 2;
			int temp = entity.size();

			while (temp != 0) {
				locs.push_back(vec[j]);
				j++;
				temp--;
			}
		}

	}
	for (int i = 0;i < entcount;i++) {
		entity[i].lastloc = locs[entcount * (turn_count - 1) + i];
	}
	for (int i = 0;i < entcount;i++) {
		for (int a = 0;a < entcount;a++) {
			convert(entloc[a]);
		}
		if (entity[i].status == "infected") {
			for (int j = 0;j < entcount;j++) {
				int x1, x2;
				x1 = abs(locc[i][0] - locc[j][0]);
				x2 = abs(locc[i][1] - locc[j][1]);

				if ((pow(x1, 2) + pow(x2, 2)) <= 18) {
					if (entity[j].dna != "strong") {
						entity[j].status = "infected";


					}

				}
			}
		}
		locc.clear();
	}vector<int>myvec;
	for (int i = 0;i < turn_count;i++) {
		
		controlA(entcount);
		controlB(entcount);
		controlC(entcount, i);
		controlD(entcount);

		//for(int a=0;a<entcount;a++){ cout << entity[a].status << "*"; }
		cout << "TURN " << i + 1 << endl;
		for (int ii = 0;ii < size + 2;ii++) {
			for (int j = 0;j < size + 2;j++) {
				if ((ii > 0 && ii < size + 1) && (j > 0 && j < size + 1)) {
					for (int k = 0;k < entcount;k++) {
						
						
						if (locc[k][0] == ii && locc[k][1] == j) {
							if (entity[k].status == "infectious" || entity[k].status == "infected")cout << "X";
							else if (entity[k].status == "normal")cout << "O";

						}
						else if (entity[k].status == "deadd") {
							std::stringstream ss(entity[k].lastloc);
							for (int a; ss >> a;) {
								myvec.push_back(a);
								if (ss.peek() == 'x')
									ss.ignore();
							}
							if (myvec[0] == ii && myvec[1] == j)cout << "D";
							myvec.clear();
						}
					}cout << " ";
				}
				else {
					cout << "-";
				}

			}
			cout << endl;
		}
		locc.clear();
	}
	
	int dead = 0, infected = 0, recovered = 0, normal = 0;
	for (int i = 0;i < entcount;i++) {
		if (entity[i].status == "infected" || entity[i].status == "infectious")infected++;
		else if (entity[i].status == "dead" || entity[i].status == "deadd")dead++;
		else if (entity[i].status == "immune")recovered++;
		else if (entity[i].status == "normal")normal++;
		
	}
	cout << endl;
	cout << "Normal: " << normal << endl;
	cout << "Dead: " << dead << endl;
	cout << "Infected: " << infected << endl;
	cout << "Recovered: " << recovered << endl;
	for (int i = 0;i < entcount;i++) {
		cout << "entity " << i + 1 << " " << entity[i].lastloc << " ";
		if (entity[i].status == "infectious") cout << "infected" << endl;
		else if (entity[i].status == "deadd") cout << "dead" << endl;
		else cout << entity[i].status << endl;
	}
	
	return 0;
}
