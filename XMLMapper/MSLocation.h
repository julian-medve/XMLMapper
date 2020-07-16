#pragma once
#include <atlstr.h>

class MSLocation
{
public:
	CString name;
	CString latitude;
	CString longitude;
	CString heading;

	CString alt;
	CString pitch;
	CString bank;
	CString imageComplexity;
	CString altitudeIsAgl;
	CString snapToGround;
	CString snapToNormal;
	CString library_name;
	CString library_scale;


	MSLocation();
	MSLocation(CString name, CString latitude, CString longitude, CString heading,
		CString alt, CString pitch, CString bank, CString imageComplexity,
		CString altitudeIsAgl, CString snapToGround, CString snapToNormal, CString library_name, CString library_scale);

};

