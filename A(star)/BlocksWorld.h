#pragma once

/*This is the BlockWorld class which calculates the number of steps
from the startState to goalState. Our BlocksWorld consists of some stacks
and blocks to be placed on the stack in  a state as defined by goal state.
Currently our goal state is to place all the blocks on the first stack
Suppose the startState is:
1 | B
2 | A C E
3 | D
GoalState should be:
1 | A B C D E
2 | 
3 |
*/

#include <queue>
#include "Nodes.h"
#include <map>
struct CustomComparator
{
	bool operator() (const Node* n1, const Node* n2)const
	{
		return n1->getFuncScore() > n2->getFuncScore();
	}
};



class BlocksWorld
{
public:
	BlocksWorld (blockGameState &goalState, blockGameState &startState)
	{
		m_goalState = goalState;
		m_startState = startState;
		m_queueSize = 0;
	}

	void traceback(Node *node) 
	{
		if (node->getParent() != NULL)
		{
			m_solutionPath.push_back(*node);
			traceback(node->getParent());
		}
	}

	void startTheMovement()
	{
		Node *root = new Node (m_startState, NULL, 0);
		root->calculateHueristicScore(m_goalState);
		pq.push(root);
		auto tries = 0;
		while (!pq.empty())
		{
			tries++;
			if (tries > 10000)
			{
				cout << "Sorry! There are no soultions for this block pattern" << endl;
				break;
			}
			else
			{
				m_queueSize = m_queueSize < pq.size() ? pq.size() : m_queueSize;
				Node *node = pq.top();
				pq.pop();
				visitedBlockWorldNodes.push_back(*node);
				cout << "This is the " << tries << " try" << " the f (g+h) score = "<<node->getFuncScore() 
					 <<" at depth = "<< node->getDepth() <<" with queue size = "<< m_queueSize<<endl;
				if (isGoalState(m_goalState, node->getState()))
				{
					cout << "found one" << endl;
					cout << "max queue size = " << pq.size()<<endl;
					traceback(node);
					cout << "Solution path:" << endl;
					while (!m_solutionPath.empty())
					{
						Node &n = m_solutionPath.back();
						printState(n.getState());
						m_solutionPath.pop_back();
					}
					break;
				} 
				else
				{
					generateSuccessor(*node);
					while (!m_list.empty())
					{
						pq.push(m_list.front());
						m_list.pop_front();
					}
				}
			}
		}
	}

	bool isGoalState (blockGameState &b1, const blockGameState &b2)
	{
		bool match = true;
		for (unsigned ex = 0; ex < b1.size(); ex++)
		{
			if (b1[ex] == b2[ex])
				continue;
			else
			{
				match = false;
				break;
			}
		}
		return match;
	}

	bool isVisited(blockGameState &state)
	{
		bool visited = false;
		for (int i = 0; i < visitedBlockWorldNodes.size(); i++)
		{
			blockGameState oldState = visitedBlockWorldNodes[i].getState();
			if (oldState == state)
			{
				visited = true;
				break;
			}  
		}
		return visited;
	}

	void generateSuccessor(Node &blockWorldNode)
	{
		for (unsigned st = 0; st < blockWorldNode.getState().size(); st++)
		{
			for (unsigned j = 0; j < blockWorldNode.getState().size(); j++)
			{
				blockGameState interimState = blockWorldNode.getState();
				if (st == j)
					continue;
				if (!blockWorldNode.getState()[st].empty())
				{
					vector<char> blockStack = blockWorldNode.getState()[st];
					int top = blockStack.size() - 1;
					interimState[st].pop_back();
					interimState[j].push_back(blockStack[top]);
					if (isVisited(interimState))
					{
						continue;
					} 
					else
					{
						Node *newNode =  new Node(interimState, &blockWorldNode, blockWorldNode.getDepth() + 1);
						newNode->calculateHueristicScore(m_goalState);
						m_list.push_back(newNode);
					}
				}
			}
		}
	}

	void printState(const blockGameState &state)
	{
		blockGameState start = state;
		for (unsigned ex = 0; ex < start.size(); ex++)
		{
			cout << "|" << " ";
			for (int in = 0; in < start[ex].size(); in++)
				cout << start[ex][in] << " ";
			cout << endl;
		}
		cout << endl;
	}

	void printTheSuccessors(vector<Node> &v)
	{
		for (int i = 0; i < v.size(); i++)
		{
			blockGameState start = v[i].getState();
			cout << "The f Score =" << v[i].getFuncScore()<<endl;
			for (unsigned ex = 0; ex < start.size(); ex++)
			{
				cout << "|" << " ";
				for (int in = 0; in < start[ex].size(); in++)
					cout << start[ex][in] << " ";
				cout << endl;
			}
			cout << endl;
		}
	}
private: 
	blockGameState m_goalState;
	blockGameState m_startState;
	priority_queue <Node*, vector<Node*>, CustomComparator> pq;
	vector<Node> visitedBlockWorldNodes;
	deque<Node*> m_list;
	int m_queueSize;
	deque<Node> m_solutionPath;
};