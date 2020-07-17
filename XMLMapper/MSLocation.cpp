#include "pch.h"
#include "MSLocation.h"

MSLocation::MSLocation() {

}

MSLocation::MSLocation(CStringA name, CStringA latitude, CStringA longitude, CStringA heading,
	CStringA alt, CStringA pitch, CStringA bank, CStringA imageComplexity,
	CStringA altitudeIsAgl, CStringA snapToGround, CStringA snapToNormal, 
	CStringA library_name, CStringA library_scale) {

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