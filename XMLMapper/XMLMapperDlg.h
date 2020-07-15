
// XMLMapperDlg.h : header file
//

#pragma once
#include "Location.h"
#include "rapidxml-1.13/rapidxml.hpp"


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

	
	void InitXPlaneXML();
	void InitMSXML();

public:
	CArray<Location> mlistXPlane;
	CArray<Location> mlistMicrosoft;

	CListBox m_ctlListMicrosoft;
	CListBox m_ctlListXPlane;

	CStatic m_ctlStaticMSLatitude;
	CStatic m_ctlStaticMSLongitude;
	CStatic m_ctlStaticMSHeading;

	CStatic m_ctlStaticXLatitude;
	CStatic m_ctlStaticXLongitude;
	CStatic m_ctlStaticXHeading;

	afx_msg void OnLbnSelchangeListXplane();

private:
	xml_document<> m_xplaneDoc;
};
