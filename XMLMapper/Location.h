#pragma once
#include <atlstr.h>

class Location
{
	public :
		CString name;
		CString latitude;
		CString longitude;
		CString heading;


		Location();
		Location(CString name, CString latitude, CString longitude, CString heading);
		
};

