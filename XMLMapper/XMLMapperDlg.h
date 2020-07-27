
// XMLMapperDlg.h : header file
//

#pragma once
#include "XPlaneLocation.h"
#include "MSLocation.h"
#include "MSExtraNode.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "coloredlistbox.h"


using namespace rapidxml;
using namespace std;


// CXMLMapperDlg dialog
class CXMLMapperDlg : public CDialogEx
{
// Construction
public:
	CXMLMapperDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XMLMAPPER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	void InitXPlaneXML(CString filepath);
	void InitMSXML(CString filepath);
	void InitListbox();
	CString GetObjectName(CStringA);


public:
	CArray<XPlaneLocation> mlistXPlane;
	CArray<MSLocation> mlistMicrosoft;
	CArray<MSExtraNode> mlistMSExtra;

	CColoredListBox m_ctlListMicrosoft;
	CColoredListBox m_ctlListXPlane;

	CStatic m_ctlStaticMSObjectName;
	CStatic m_ctlStaticMSLatitude;
	CStatic m_ctlStaticMSLongitude;
	CStatic m_ctlStaticMSHeading;

	CStatic m_ctlStaticXObjectName;
	CStatic m_ctlStaticXLatitude;
	CStatic m_ctlStaticXLongitude;
	CStatic m_ctlStaticXHeading;


	// Variables for selected item on Xplane and Microsoft XML listbox
	int m_nSelectedXplane;
	int m_nSelectedMicrosoft;

	CString m_strMSXMLFilepath;

private:

public:
	afx_msg void OnLbnSelchangeListMs();
	afx_msg void OnLbnSelchangeListXplane();
	afx_msg void OnBnClickedButtonLink();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnMicrosoft();
	afx_msg void OnBnClickedBtnXplaneXml();
};
