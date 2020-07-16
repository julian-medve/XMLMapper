#include "pch.h"
#include "Location.h"

Location::Location() {

	this->name = this->latitude = this->longitude = this->heading = "";
}

Location::Location(CString name, CString latitude, CString longitude, CString heading) {

	this->name		= name;
	this->latitude	= latitude;
	this->longitude = longitude;
	this->heading	= heading;
}