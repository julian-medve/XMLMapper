#include "pch.h"
#include "MSLocation.h"

MSLocation::MSLocation() {

}

MSLocation::MSLocation(CString name, CString latitude, CString longitude, CString heading,
	CString alt, CString pitch, CString bank, CString imageComplexity,
	CString altitudeIsAgl, CString snapToGround, CString snapToNormal, 
	CString library_name, CString library_scale) {

	this->name				= name;
	this->latitude			= latitude;
	this->longitude			= longitude;
	this->heading			= heading;

	this->alt				= alt;
	this->pitch				= pitch;
	this->bank				= bank;
	this->imageComplexity	= imageComplexity;

	this->altitudeIsAgl		= altitudeIsAgl;
	this->snapToGround		= snapToGround;
	this->snapToNormal		= snapToNormal;
	this->library_name		= library_name;
	this->library_scale		= library_scale;
}