#pragma once
#include <atlstr.h>

class XPlaneLocation
{
	public :
		CStringA name;
		CStringA latitude;
		CStringA longitude;
		CStringA heading;

		XPlaneLocation();
		XPlaneLocation(CStringA name, CStringA latitude, CStringA longitude, CStringA heading);
};

