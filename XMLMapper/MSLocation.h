#pragma once
#include <atlstr.h>

class MSLocation
{
public:
	CStringA name;
	CStringA latitude;
	CStringA longitude;
	CStringA heading;

	CStringA alt;
	CStringA pitch;
	CStringA bank;
	CStringA imageComplexity;
	CStringA altitudeIsAgl;
	CStringA snapToGround;
	CStringA snapToNormal;
	CStringA library_name;
	CStringA library_scale;


	MSLocation();
	MSLocation(CStringA name, CStringA latitude, CStringA longitude, CStringA heading,
		CStringA alt, CStringA pitch, CStringA bank, CStringA imageComplexity,
		CStringA altitudeIsAgl, CStringA snapToGround, CStringA snapToNormal, CStringA library_name, CStringA library_scale);

};

