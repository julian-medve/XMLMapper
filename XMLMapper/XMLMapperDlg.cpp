
// XMLMapperDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "XMLMapper.h"
#include "XMLMapperDlg.h"
#include "afxdialogex.h"


#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXMLMapperDlg dialog



CXMLMapperDlg::CXMLMapperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XMLMAPPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXMLMapperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_XPLANE, m_ctlListXPlane);
	DDX_Control(pDX, IDC_LIST_MS, m_ctlListMicrosoft);

	DDX_Control(pDX, IDC_STATIC_MS_OBJECT_NAME, m_ctlStaticMSObjectName);
	DDX_Control(pDX, IDC_STATIC_MS_LATITUDE, m_ctlStaticMSLatitude);
	DDX_Control(pDX, IDC_STATIC_MS_LONGITUDE, m_ctlStaticMSLongitude);
	DDX_Control(pDX, IDC_STATIC_MS_HEADING, m_ctlStaticMSHeading);


	DDX_Control(pDX, IDC_STATIC_X_OBJECT_NAME, m_ctlStaticXObjectName);
	DDX_Control(pDX, IDC_STATIC_X_LATITUDE, m_ctlStaticXLatitude);
	DDX_Control(pDX, IDC_STATIC_X_LONGITUDE, m_ctlStaticXLongitude);
	DDX_Control(pDX, IDC_STATIC_X_HEADING, m_ctlStaticXHeading);
}

BEGIN_MESSAGE_MAP(CXMLMapperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST_XPLANE, &CXMLMapperDlg::OnLbnSelchangeListXplane)
	ON_LBN_SELCHANGE(IDC_LIST_MS, &CXMLMapperDlg::OnLbnSelchangeListMs)
END_MESSAGE_MAP()


// CXMLMapperDlg message handlers

BOOL CXMLMapperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// TODO: Add extra initialization here

	InitXPlaneXML();
	InitMSXML();
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXMLMapperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXMLMapperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXMLMapperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CXMLMapperDlg::InitXPlaneXML() {

	xml_node<>* root_node;

	// Read the xml file into a vector
	ifstream theFile("E:\\____GIT____\\XMLMapper\\earth.wed.xml");

	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	m_xplaneDoc.parse<parse_comment_nodes>(&buffer[0]);
	// Find our root node
	root_node = m_xplaneDoc.first_node("doc")->first_node("objects");


	
	// Iterate over the brewerys
	
	CString tempSuffix(".obj");

	for (xml_node<>* node_object = root_node->first_node("object"); node_object; node_object = node_object->next_sibling())
	{
		xml_node<>* node_hierarchy = node_object->first_node("hierarchy");
		xml_node<>* node_point = node_object->first_node("point");

		CString name, latitude, longitude, heading;
		
		if (node_hierarchy != NULL) {

			name = CString(node_hierarchy->first_attribute("name")->value());

			if (name.Find(tempSuffix) != -1) {
				name = name.Left(name.GetLength() - tempSuffix.GetLength());
			}
			else
				continue;
		}
		else
			continue;

		if (node_point != NULL) {

			if (node_point->first_attribute("latitude") != NULL)
				latitude = CString(node_point->first_attribute("latitude")->value());
			else
				latitude = "";

			if (node_point->first_attribute("longitude") != NULL)
				longitude = CString(node_point->first_attribute("longitude")->value());
			else
				longitude = "";

			if (node_point->first_attribute("heading") != NULL)
				heading = CString(node_point->first_attribute("heading")->value());
			else
				heading = "";
		}
		else
		{
			latitude = longitude = heading = "";
		}
		

		Location tempLocation(name, latitude, longitude, heading);
		mlistXPlane.Add(tempLocation);

		m_ctlListXPlane.AddString(name);
	}
}

void CXMLMapperDlg::InitMSXML() {

	xml_node<>* root_node;

	// Read the xml file into a vector
	ifstream theFile("E:\\____GIT____\\XMLMapper\\objects.xml");

	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	m_microsoftDoc.parse<parse_comment_nodes>(&buffer[0]);
	// Find our root node
	root_node = m_microsoftDoc.first_node("FSData");

	CString tempPrefix("SceneryObject name: ");

	// Iterate over the brewerys
	for (xml_node<>* node_SceneryObject = root_node->first_node("SceneryObject"); node_SceneryObject; node_SceneryObject = node_SceneryObject->next_sibling())
	{

		if (node_SceneryObject->type() == node_comment)
			continue;

		CString name, latitude, longitude, heading;
		
		name = CString(node_SceneryObject->previous_sibling()->value());
		name = name.Right(name.GetLength() - tempPrefix.GetLength());
		heading = CString(node_SceneryObject->first_attribute("heading")->value());
		latitude = CString(node_SceneryObject->first_attribute("lat")->value());
		longitude = CString(node_SceneryObject->first_attribute("lon")->value());

		Location tempLocation(name, latitude, longitude, heading);
		mlistMicrosoft.Add(tempLocation);

		m_ctlListMicrosoft.AddString(name);
	}
}

void CXMLMapperDlg::OnLbnSelchangeListXplane()
{
	// TODO: Add your control notification handler code here
	int i = m_ctlListXPlane.GetCurSel();

	if (i >= mlistXPlane.GetCount())
		return;

	Location locationSelected =	mlistXPlane.GetAt(i);

	this->m_ctlStaticXObjectName.SetWindowTextW(locationSelected.name);
	this->m_ctlStaticXLongitude.SetWindowTextW(locationSelected.longitude);
	this->m_ctlStaticXLatitude.SetWindowTextW(locationSelected.latitude);
	this->m_ctlStaticXHeading.SetWindowTextW(locationSelected.heading);
}


void CXMLMapperDlg::OnLbnSelchangeListMs()
{
	// TODO: Add your control notification handler code here
	int i = m_ctlListMicrosoft.GetCurSel();

	if (i >= m_ctlListMicrosoft.GetCount())
		return;

	Location locationSelected = mlistMicrosoft.GetAt(i);

	this->m_ctlStaticMSObjectName.SetWindowTextW(locationSelected.name);
	this->m_ctlStaticMSLongitude.SetWindowTextW(locationSelected.longitude);
	this->m_ctlStaticMSLatitude.SetWindowTextW(locationSelected.latitude);
	this->m_ctlStaticMSHeading.SetWindowTextW(locationSelected.heading);
}
