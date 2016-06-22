#include "StdAfx.h"
#include "navdata.h"
#include "route.h"

Route::Route(void)
{
	currentUniverse = NULL;
	this->jumpWeight = 1;
}

Route::~Route(void)
{
}

void Route::BuildEdges(NavData* inUniverse)
{
	currentUniverse=inUniverse;
	this->edges.clear(); // wipe edge list
	this->graphNodes.clear();
	NavEntry* navCurrent;
	NavEntry* navDest = new NavEntry();
	Edge edgCurrent;
	GraphNode* nodFrom;
	currentUniverse->IndexEntries(); // re-index all entries
	int intEntryCount = currentUniverse->GetEntryCount();
	
	// populate nodes table	
	for (int lngIndex = 0; lngIndex<intEntryCount; lngIndex++)
	{
		// add all jumps to calculation graph
		navCurrent = currentUniverse->GetEntry(lngIndex);
	
		if (strcmp(navCurrent->type, "Jump")==0)
		{
			// create from node
			
			nodFrom = this->FindNode(navCurrent);
			if (nodFrom==NULL)
			{
				nodFrom = new GraphNode;
				nodFrom->best = MAXINT; // = infinity
				nodFrom->node = navCurrent;
				nodFrom->previous = NULL;
				nodFrom->visited = false;
				this->graphNodes.push_back(nodFrom);
			}
			
			// insert zero cost jump
			edgCurrent.nodeFrom = nodFrom;
			navDest->SetPosition(navCurrent->value);
			navDest->SetType("Jump");
			if (navDest->navPos!=NULL && navDest->sectPos!=NULL)
			{ // successfully retrieved nav co-ordinates from system
				edgCurrent.nodeTo = this->FindNode(navDest);
				if (edgCurrent.nodeTo==NULL)
				{	// destination is not in nodes array, add it
					edgCurrent.nodeTo = new GraphNode();
					edgCurrent.nodeTo->node = currentUniverse->FindEntry(navDest, NAVPOS+NAVSECTOR);
					if (edgCurrent.nodeTo->node==NULL)
					{	// cannot find node on universe map, add it!
						navDest->SetName("Uncharted Jump Destination");
						navDest->SetType(NAVOUT);
						navDest->SetValue("");
						edgCurrent.nodeTo->node = navDest;
						currentUniverse->AddEntry(navDest);
						navDest = new NavEntry; // replace existing nav entry
					}
					this->graphNodes.push_back(edgCurrent.nodeTo);
				}
				edgCurrent.weight = this->jumpWeight; // minor weighting for jump event
				this->edges.push_back(edgCurrent);
			}		
		}
	}
	
	for (int intIndex=0; intIndex<(int)graphNodes.size(); intIndex++)
	{
		// calculate travel weights
		edgCurrent.nodeFrom = graphNodes[intIndex];
		for (int intSubIndex=0; intSubIndex<(int)(graphNodes.size()); intSubIndex++)
		{
			edgCurrent.nodeTo = graphNodes[intSubIndex];
			if (intIndex!=intSubIndex)
			{ // node is not pointing towards itself
				edgCurrent.weight = edgCurrent.nodeFrom->node->RangeTo(edgCurrent.nodeTo->node);
				this->edges.push_back(edgCurrent);
			}
		}
	}
	delete navDest;
}

void Route::Calculate(NavEntry* navStart, NavEntry* navFinish)
{ // dijkstra it up!
	Edge edgCurrent;
	
	GraphNode* nodeStart = this->FindNode(navStart);
	if (nodeStart==NULL)
	{
		nodeStart = new GraphNode();
		nodeStart->node = navStart;
		int intMax = int(this->graphNodes.size());
		for (int intIndex=0; intIndex<intMax; intIndex++)
		{
			edgCurrent.nodeFrom = nodeStart;
			edgCurrent.nodeTo = graphNodes[intIndex];
			edgCurrent.weight = edgCurrent.nodeFrom->node->RangeTo(edgCurrent.nodeTo->node);
			this->edges.push_back(edgCurrent);
			// add reverse direction, same weight
			edgCurrent.nodeFrom = graphNodes[intIndex];
			edgCurrent.nodeTo = nodeStart;
			// weight does not need to be changed
			this->edges.push_back(edgCurrent);
		}
		this->graphNodes.push_back(nodeStart);
	}
	
	GraphNode* nodeFinish = this->FindNode(navFinish);
	if (nodeFinish==NULL)
	{
		nodeFinish = new GraphNode();
				nodeFinish->node = navFinish;
		int intMax = int(this->graphNodes.size());
		for (int intIndex=0; intIndex<intMax; intIndex++)
		{
			edgCurrent.nodeFrom = nodeFinish;
			edgCurrent.nodeTo = graphNodes[intIndex];
			edgCurrent.weight = edgCurrent.nodeFrom->node->RangeTo(edgCurrent.nodeTo->node);
			this->edges.push_back(edgCurrent);
			// add reverse direction, same weight
			edgCurrent.nodeFrom = graphNodes[intIndex];
			edgCurrent.nodeTo = nodeFinish;
			// weight does not need to be recalculated
			this->edges.push_back(edgCurrent);
		}
		this->graphNodes.push_back(nodeFinish);
	}
		
	// begin Dijkstra algorithm
	GraphNode* nodCurrent = NULL;
	GraphNode* nodNext = NULL;
	bool booBreak = false;
	for (int intIndex=0; intIndex<int(this->graphNodes.size()); intIndex++)
	{ // initialise node data
		graphNodes[intIndex]->best=MAXINT;
		graphNodes[intIndex]->previous=NULL;
		graphNodes[intIndex]->visited=false;
	}
	
	nodeStart->best=0;
	while (this->GetClosest()!=NULL && !booBreak)
	{ // this had better work or will be in eternal loop!
		nodCurrent = this->GetClosest();
		if (nodCurrent!=NULL)
		{
			if (nodCurrent->best<MAXINT)
			{
				nodCurrent->visited = true; // closest match found
				for (int intIndex=0; intIndex<int(this->edges.size());intIndex++)
				{
					edgCurrent = this->edges[intIndex];
					if (
						edgCurrent.nodeFrom == nodCurrent 
						&& !edgCurrent.nodeTo->visited
						&& edgCurrent.nodeFrom->best + edgCurrent.weight < edgCurrent.nodeTo->best)
					{	// better match found
						edgCurrent.nodeTo->best = edgCurrent.nodeFrom->best + edgCurrent.weight;
						edgCurrent.nodeTo->previous = edgCurrent.nodeFrom;
					}
				}
			}
			else // no nodes within range
				booBreak=true;
		}
		else // unable to return closest node - possibly empty set
			booBreak = true;	
	}
}

GraphNode* Route::FindNode(NavEntry* navSearch)
{
	GraphNode* returnValue = NULL;
	for (int intIndex=0; intIndex<int(this->graphNodes.size()) && returnValue==NULL; intIndex++)
	{
		if (graphNodes[intIndex]->node->Equals(navSearch,NAVPOS+NAVSECTOR))
			returnValue = graphNodes[intIndex];
	}
	return returnValue;
}

GraphNode* Route::GetClosest(void)
{ // return the node with the lowest distance
	GraphNode* returnValue = NULL;
	double dblDistance=MAXINT;
	for (int intIndex=0; intIndex<int(this->graphNodes.size());intIndex++)
	{
		if (graphNodes[intIndex]->best<=dblDistance && !graphNodes[intIndex]->visited)
		{ // closer unvisited node found
			dblDistance=graphNodes[intIndex]->best;
			returnValue = graphNodes[intIndex];
		}	
	}
	return returnValue;
}

std::vector<NavEntry*> Route::GetPath(NavEntry* inDestination)
{ // returns path in list order
	std::vector<NavEntry*> returnValue;
	GraphNode* nodCurrent = this->FindNode(inDestination);
	if (nodCurrent!=NULL)
	{
		//returnValue
		while (nodCurrent!=NULL)
		{
			returnValue.push_back(nodCurrent->node);
			nodCurrent=nodCurrent->previous;
		}
	}
	return returnValue;
}

int Route::NumberUnvisited(void)
{
	int returnValue = 0;
	for (int intIndex=0; intIndex<int(this->graphNodes.size()); intIndex++)
	{
		if (!graphNodes[intIndex]->visited) returnValue++;
	}
	return returnValue;
}