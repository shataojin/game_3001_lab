#include "PathManager.h"

void PathManager::GetShortestPath(PathNode* start, PathNode* goal)
{

}

NodeRecord* PathManager::GetSmallestNode()
{
	auto smallest = s_open.begin();
	auto current = s_open.begin();

	while (++current != s_open.end())
	{
		if ((*current)->m_costSoFar < (*smallest)->m_costSoFar)
			smallest = current;
		else if ((*current)->m_costSoFar == (*smallest)->m_costSoFar) // If equal, flip a coin!
			smallest = (rand() % 2 ? current : smallest);
	}
	return (*smallest);
}

std::vector<NodeRecord*>& PathManager::GetOpenList()
{
	return s_open;
}

std::vector<NodeRecord*>& PathManager::GetClosedList()
{
	return s_closed;
}

bool PathManager::ContainsNode(const std::vector<NodeRecord*>& list, const PathNode* n)
{
	for (auto i : list)
		if (i->m_node == n)
			return true;
	return false;
}

NodeRecord* PathManager::GetNodeRecord(const std::vector<NodeRecord*>& list, const PathNode* n)
{
	for (const auto i : list)
		if (i->m_node == n)
			return i;
	return nullptr;
}

std::vector<NodeRecord*> PathManager::s_open;
std::vector<NodeRecord*> PathManager::s_closed;