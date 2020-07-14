
// XMLMapper.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CXMLMapperApp:
// See XMLMapper.cpp for the implementation of this class
//

class CXMLMapperApp : public CWinApp
{
public:
	CXMLMapperApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CXMLMapperApp theApp;
