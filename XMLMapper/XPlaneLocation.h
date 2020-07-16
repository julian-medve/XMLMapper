#pragma once
#include <atlstr.h>

class XPlaneLocation
{
	public :
		CString name;
		CString latitude;
		CString longitude;
		CString heading;

		XPlaneLocation();
		XPlaneLocation(CString name, CString latitude, CString longitude, CString heading);
};

