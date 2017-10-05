#pragma once

#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
typedef vector<vector<char>> blockGameState;

class Node
{
public:


	Node(blockGameState state, Node *parent, int depth) :
		m_state(state), m_depth(depth), m_parent(parent), m_funcScore(0), m_hueristicScore(0)
	{
	}

	~Node() {}

	int getHueristicScore() { return m_hueristicScore; }
	int getDepth() const { return m_depth; }
	void setFuncScore() { m_funcScore = m_depth + m_hueristicScore; }
	int getFuncScore() const { return m_funcScore; }
	blockGameState getState()const { return m_state; }

	Node* getParent() const
	{
		return m_parent;
	}
	/* This is the simple hueristic which is used for benchmark only
	h is here total blocks out of place in the stack 
	void Simplehueristic(blockGameState goalState)
	{
		int blocksOutofPlace = goalState[0].size();
		vector<char> heur;
		for (int i = 0; i < m_state[0].size(); i++)
		{
			if (goalState[0][i] == m_state[0][i])
			{
				blocksOutofPlace--;
				heur.push_back(m_state[0][i]);
			}
			else {
				break;
			}
		}
		m_hueristicScore = blocksOutofPlace;
		setFuncScore();
	}
	*/

	void analyzeForwardStep(int stList, blockGameState &goalState)
	{
		auto topIndex = m_state[stList].size() - 1;
		auto topCh = m_state[stList][topIndex];
		auto pos = find(goalState[0].begin(), goalState[0].end(), topCh) -
			goalState[0].begin();

		auto iter = 0;
		if (m_state[0].empty() && topCh == goalState[0][0])
		{
			m_hueristicScore += -2;
		}
		else if (!m_state[0].empty())
		{
			auto iter = 0;
			auto match = true;
			while (iter < m_state[0].size())
			{
				if (m_state[0][iter] == goalState[0][iter])
				{
					iter++;
					continue;
				}
				else
				{
					match = false;
					break;
				}

				iter++;
			}
			if (match && iter == pos)
			{
				m_hueristicScore += -2;
			}
		}
	}

	void calculateHueristicScore(blockGameState goalState)
	{
		for (auto stList = 0; stList < m_state.size(); stList++)
		{
			//Case 1: goalState is empty and the currentState is non-empty for a stack 
			if (goalState[stList].empty() && !m_state[stList].empty())
			{
				//get the reward for being in this state depending upon the next move
				analyzeForwardStep(stList, goalState);
				//increase the hueristic score by the number of blocks need to be removed
				m_hueristicScore += m_state[stList].size();
			}
			//Case 2: goalstate is non-empty but the current state is empty
			else if (!goalState[stList].empty() && m_state[stList].empty())
			{
				m_hueristicScore += goalState[stList].size();
			}
			//Case 3: Goal and current state both are non-empty
			else if (!goalState[stList].empty() && !m_state[stList].empty())
			{
				//Case 3(a) : if the lower block does not matches
				if (goalState[stList][0] != m_state[stList][0])
				{
					m_hueristicScore += goalState[stList].size() + m_state[stList].size();
				}
				else
				{
					// Case 3(b) : if there is a match on the stack
					auto ele = 1;
					while (ele < m_state[stList].size() && ele < goalState[stList].size())
					{
						if (m_state[stList][ele] == goalState[stList][ele])
						{
							ele++;
							m_hueristicScore--;
							continue;
						}
						else {
							break;
						}
						ele++;
					}
					if (ele < m_state[stList].size()) {
						m_hueristicScore += m_state[stList].size() - ele;
					}
				}
			}
		}
		setFuncScore();
	}


private:
	int m_hueristicScore;
	int m_depth;
	int m_funcScore;
	blockGameState m_state;
	Node* m_parent;
};