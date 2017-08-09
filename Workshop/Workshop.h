
// Workshop.h : main header file for the Workshop application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWorkshopApp:
// See Workshop.cpp for the implementation of this class
//

class CWorkshopApp : public CWinApp
{
public:
	CWorkshopApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


private:
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
};

extern CWorkshopApp theApp;
