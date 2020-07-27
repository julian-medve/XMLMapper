#pragma once
#include <afxcoll.h>
#include <map>
#include <string>

using namespace std;

class MSExtraNode
{
public : 
	CStringA name;
	map<string, string> attributes;

	MSExtraNode();
	MSExtraNode(CStringA name);

	void put(string key, string value);
};

