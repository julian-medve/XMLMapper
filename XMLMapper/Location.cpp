#include "pch.h"
#include "Location.h"

Location::Location() {

	this->name = this->latitude = this->longitude = "";
}

Location::Location(CString name, CString latitude, CString longitude) {

	this->name		= name;
	this->latitude	= latitude;
	this->longitude = longitude;
}