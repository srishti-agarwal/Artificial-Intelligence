/*This is the entry application which generates the problem to be fed
to the BlocksWorld and provide the final result for the final steps*/

#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <random>
#include "BlocksWorld.h"

using namespace std;

void mockGenerator(int stacks, int blocks, blockGameState & goal, blockGameState &start)
{
	for (int i = 0; i < stacks; i++)
	{
		vector<char> s;
		goal.push_back(s);
		start.push_back(s);
	}
	cout << "Goal State" << endl;
	for (int n = 0; n < blocks; ++n)
		goal[0].push_back('A' + n);

	for (int k = 0; k< goal.size(); k++)
	{
		cout << "|" << " ";
		for (int in = 0; in < goal[k].size(); in++)
			cout << goal[k][in] << " ";
		cout << endl;
	}
	cout << endl << "Mock Gen" << endl;

	//3 stacks
	start[0].push_back('B');
	start[1].push_back('C');
	start[1].push_back('E');
	start[2].push_back('A');
	start[2].push_back('D');
	

	/*start[0].push_back('E');
	start[0].push_back('C');
	start[1].push_back('B');
	start[2].push_back('A');
	start[2].push_back('D');
	start[2].push_back('F');*/

	//5 stacks
	/*start[0].push_back('D');
	start[1].push_back('E');
	start[1].push_back('F');
	start[1].push_back('I');
	start[1].push_back('J');
	start[2].push_back('B');
	start[2].push_back('G');
	start[3].push_back('C');
	start[3].push_back('H');
	start[4].push_back('A');*/

	//5 stacks
	/*start[0].push_back('C');
	start[1].push_back('D');
	start[1].push_back('E');
	start[1].push_back('I');
	start[1].push_back('K');
	start[2].push_back('A');
	start[2].push_back('J');
	start[3].push_back('B');
	start[3].push_back('F');
	start[4].push_back('G');
	start[4].push_back('H');*/

	/*start[0].push_back('G');
	start[0].push_back('K');
	start[0].push_back('D');
	start[1].push_back('H');
	start[1].push_back('I');
	start[1].push_back('C');
	start[2].push_back('L');
	start[2].push_back('F');
	start[2].push_back('B');
	start[2].push_back('E');
	start[4].push_back('A');
	start[4].push_back('J');

	*/
	
	/*start[0].push_back('L');
	start[1].push_back('H');
	start[1].push_back('F');
	start[1].push_back('I');
	start[1].push_back('B');
	start[2].push_back('C');
	start[2].push_back('G');
	start[3].push_back('E');
	start[3].push_back('A');
	start[4].push_back('J');
	start[5].push_back('K');
	start[5].push_back('D');*/

	/*start[0].push_back('M');
	start[1].push_back('P');
	start[1].push_back('R');
	start[1].push_back('H');
	start[2].push_back('L');
	start[2].push_back('B');
	start[2].push_back('E');
	start[3].push_back('N');
	start[3].push_back('I');
	start[4].push_back('J');
	start[5].push_back('D');
	start[6].push_back('A');
	start[6].push_back('K');
	start[6].push_back('T');
	start[7].push_back('Q');
	start[8].push_back('F');
	start[8].push_back('C');
	start[9].push_back('O');
	start[9].push_back('G');*/

	cout << "Starting State:" << endl;
	for (int k = 0; k< start.size(); k++)
	{
		cout << "|" << " ";
		for (int in = 0; in < start[k].size(); in++)
			cout << start[k][in] << " ";
		cout << endl;
	}

}
void problemGenerator(int stacks, int blocks, blockGameState & goal, blockGameState &start)
{
	for (int i = 0; i < stacks; i++)
	{
		vector<char> s;
		goal.push_back(s);
		start.push_back(s);
	}
	for (int n = 0; n < blocks; ++n)
		goal[0].push_back('A' + n);
	
	for (int k = 0; k< goal.size(); k++)
	{
		cout << "|" << " ";
		for (int in = 0; in < goal[k].size(); in++)
			cout << goal[k][in] << " ";
		cout << endl;
	}
	cout <<endl<< "After Scramble" << endl;

	char c = 'A';
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dist(0, stacks-1); // distribute results between 1 and 6 inclusive.  

	for (int i = 0; i < blocks; ++i) {
		start[dist(gen)].push_back(c++);
	}

	for (unsigned ex = 0; ex < start.size(); ex++)
	{
		cout << "|" << " ";
		for (int in = 0; in < start[ex].size(); in++)
			cout << start[ex][in] << " ";
		cout << endl;
	}	
}

int main(int argc, char * argv[])
{
	int stacks = 0, blocks = 0;
	cout << "Enter the number of stacks" << endl;
	cin >> stacks;
	cout << "Enter the number of blocks" << endl;
	cin >> blocks;
	vector<vector<char>> goalState;
	vector <vector<char>>startState;
	problemGenerator(stacks, blocks, goalState, startState);
	//This cam be used for testing different combinations
	//mockGenerator(stacks, blocks, goalState, startState);
	BlocksWorld bw(goalState, startState);
	bw.startTheMovement();
}