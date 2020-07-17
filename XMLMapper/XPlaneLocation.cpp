#include "pch.h"
#include "XPlaneLocation.h"

XPlaneLocation::XPlaneLocation() {

	this->name = this->latitude = this->longitude = this->heading = "";
}

XPlaneLocation::XPlaneLocation(CStringA name, CStringA latitude, CStringA longitude, CStringA heading) {

	this->name		= name;
	this->latitude	= latitude;
	this->longitude = longitude;
	this->heading	= heading;
}

