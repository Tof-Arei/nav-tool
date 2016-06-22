#pragma once




struct GraphNode
{
	NavEntry* node;
	GraphNode* previous;
	bool visited;
	double best;
};

struct Edge
{
	GraphNode* nodeFrom;
	GraphNode* nodeTo;
	double weight;
};

class Route
{
public:
	Route(void);
	~Route(void);
	double jumpWeight;
	
	void BuildEdges(NavData* inUniverse);
	void Calculate(NavEntry* navStart, NavEntry* navFinish);
	GraphNode* FindNode(NavEntry* navSearch);
	std::vector<NavEntry*> GetPath(NavEntry* inDestination);
	private:
	NavData* currentUniverse;
	std::vector<Edge> edges;
	std::vector<GraphNode*> graphNodes;
	
	GraphNode* GetClosest(void);
	int NumberUnvisited(void);

};
