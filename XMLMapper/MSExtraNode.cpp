#include "pch.h"
#include "MSExtraNode.h"

MSExtraNode::MSExtraNode() 
{
	this->name = "";
}

MSExtraNode::MSExtraNode(CStringA name) 
{
	this->name = name;
}

void MSExtraNode::put(string key, string value)
{
	this->attributes.insert(std::make_pair(key, value));
}

