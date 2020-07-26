
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

#include "rapidxml-1.13/rapidxml_print.hpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TEMP_PREFIX "SceneryObject name: "


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
	ON_BN_CLICKED(IDC_BUTTON_LINK, &CXMLMapperDlg::OnBnClickedButtonLink)
	ON_BN_CLICKED(IDOK, &CXMLMapperDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_MICROSOFT, &CXMLMapperDlg::OnBnClickedBtnMicrosoft)
	ON_BN_CLICKED(IDC_BTN_XPLANE_XML, &CXMLMapperDlg::OnBnClickedBtnXplaneXml)
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


void CXMLMapperDlg::InitXPlaneXML(CString filepath) {
	
	xml_document<> m_xplaneDoc;

	xml_node<>* root_node;

	// Read the xml file into a vector
	ifstream theFile(filepath);

	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	m_xplaneDoc.parse<parse_comment_nodes>(&buffer[0]);
	// Find our root node
	root_node = m_xplaneDoc.first_node("doc")->first_node("objects");


	
	mlistXPlane.RemoveAll();
	m_ctlListXPlane.ResetContent();

	
	// Iterate over the brewerys
	
	CStringA tempSuffix(".obj");

	for (xml_node<>* node_object = root_node->first_node("object"); node_object; node_object = node_object->next_sibling())
	{
		xml_node<>* node_hierarchy = node_object->first_node("hierarchy");
		xml_node<>* node_point = node_object->first_node("point");

		CStringA name, latitude, longitude, heading;
		
		if (node_hierarchy != NULL) {

			name = CStringA(node_hierarchy->first_attribute("name")->value());

			if (name.Find(tempSuffix) != -1) {
				name = name.Left(name.GetLength() - tempSuffix.GetLength());
				int lastIndex = name.ReverseFind('/');

				if (lastIndex != -1)
					name = name.Right(name.GetLength() - lastIndex - 1);
			}
			else
				continue;
		}
		else
			continue;

		if (node_point != NULL) {

			if (node_point->first_attribute("latitude") != NULL)
				latitude = CStringA(node_point->first_attribute("latitude")->value());
			else
				latitude = "";

			if (node_point->first_attribute("longitude") != NULL)
				longitude = CStringA(node_point->first_attribute("longitude")->value());
			else
				longitude = "";

			if (node_point->first_attribute("heading") != NULL)
				heading = CStringA(node_point->first_attribute("heading")->value());
			else
				heading = "";
		}
		else
		{
			latitude = longitude = heading = "";
		}
		

		XPlaneLocation tempLocation(name, latitude, longitude, heading);
		mlistXPlane.Add(tempLocation);

		m_ctlListXPlane.AddString(CString(name));
	}

	InitListbox();
}


CString CXMLMapperDlg::GetObjectName(CStringA name) {

	CStringA tempPrefix = "SceneryObject name: ";
	return CString(name.Right(name.GetLength() - tempPrefix.GetLength()));
}

void CXMLMapperDlg::InitMSXML(CString filepath) {

	xml_document<> m_microsoftDoc;

	xml_node<>* root_node;

	// Read the xml file into a vector
	ifstream theFile(filepath);

	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	m_microsoftDoc.parse<parse_comment_nodes>(&buffer[0]);
	// Find our root node
	root_node = m_microsoftDoc.first_node("FSData");

	
	mlistMicrosoft.RemoveAll();
	m_ctlListMicrosoft.ResetContent();

	// Iterate over the brewerys
	for (xml_node<>* node_SceneryObject = root_node->first_node("SceneryObject"); node_SceneryObject; node_SceneryObject = node_SceneryObject->next_sibling())
	{

		if (node_SceneryObject->type() == node_comment)
			continue;

		CStringA name, latitude, longitude, heading, alt, pitch, bank, imageComplexity, altitudeIsAgl, snapToGround, snapToNormal, library_name, library_scale;
		
		name				= CStringA(node_SceneryObject->previous_sibling()->value());
		
		heading				= CStringA(node_SceneryObject->first_attribute("heading")->value());
		latitude			= CStringA(node_SceneryObject->first_attribute("lat")->value());
		longitude			= CStringA(node_SceneryObject->first_attribute("lon")->value());

		alt					= CStringA(node_SceneryObject->first_attribute("alt")->value());
		pitch				= CStringA(node_SceneryObject->first_attribute("pitch")->value());
		bank				= CStringA(node_SceneryObject->first_attribute("bank")->value());
		imageComplexity		= CStringA(node_SceneryObject->first_attribute("imageComplexity")->value());

		altitudeIsAgl		= CStringA(node_SceneryObject->first_attribute("altitudeIsAgl")->value());
		snapToGround		= CStringA(node_SceneryObject->first_attribute("snapToGround")->value());
		snapToNormal		= CStringA(node_SceneryObject->first_attribute("snapToNormal")->value());

		library_name		= CStringA(node_SceneryObject->first_node("LibraryObject")->first_attribute("name")->value());
		library_scale		= CStringA(node_SceneryObject->first_node("LibraryObject")->first_attribute("scale")->value());
		

		MSLocation tempLocation(name, CStringA(node_SceneryObject->first_attribute("lat")->value()), longitude, heading, alt, pitch, bank, imageComplexity, altitudeIsAgl, snapToGround, snapToNormal, library_name, library_scale);
		mlistMicrosoft.Add(tempLocation);

		
		m_ctlListMicrosoft.AddString(GetObjectName(name));
	}

	InitListbox();
}

void CXMLMapperDlg::InitListbox() {

	for(int i = 0; i < mlistMicrosoft.GetCount(); i++)
		for (int j = 0; j < mlistXPlane.GetCount(); j++) {
		
			MSLocation msLocation = mlistMicrosoft.GetAt(i);
			XPlaneLocation xLocation = mlistXPlane.GetAt(j);

			if (msLocation.latitude.Compare(xLocation.latitude) == 0
				&& msLocation.longitude.Compare(xLocation.longitude) == 0
				&& msLocation.heading.Compare(xLocation.heading) == 0) {
			
				m_ctlListMicrosoft.SetItemData(i, 1);
				m_ctlListXPlane.SetItemData(j, 1);

				continue;
			}
		}

	m_ctlListMicrosoft.Invalidate();
	m_ctlListXPlane.Invalidate();
}

void CXMLMapperDlg::OnLbnSelchangeListXplane()
{
	// TODO: Add your control notification handler code here
	int i = m_ctlListXPlane.GetCurSel();

	if (i >= mlistXPlane.GetCount())
		return;


	m_nSelectedXplane = i;

	XPlaneLocation locationSelected =	mlistXPlane.GetAt(i);

	this->m_ctlStaticXObjectName.SetWindowTextW(CString(locationSelected.name));
	this->m_ctlStaticXLongitude.SetWindowTextW(CString(locationSelected.longitude));
	this->m_ctlStaticXLatitude.SetWindowTextW(CString(locationSelected.latitude));
	this->m_ctlStaticXHeading.SetWindowTextW(CString(locationSelected.heading));
}


void CXMLMapperDlg::OnLbnSelchangeListMs()
{
	// TODO: Add your control notification handler code here
	int i = m_ctlListMicrosoft.GetCurSel();

	if (i >= m_ctlListMicrosoft.GetCount())
		return;

	m_nSelectedMicrosoft = i;

	MSLocation locationSelected = mlistMicrosoft.GetAt(i);

	this->m_ctlStaticMSObjectName.SetWindowTextW(GetObjectName(locationSelected.name));
	this->m_ctlStaticMSLongitude.SetWindowTextW(CString(locationSelected.longitude));
	this->m_ctlStaticMSLatitude.SetWindowTextW(CString(locationSelected.latitude));
	this->m_ctlStaticMSHeading.SetWindowTextW(CString(locationSelected.heading));
}


void CXMLMapperDlg::OnBnClickedButtonLink()
{
	// TODO: Add your control notification handler code here

	MSLocation selMSLocation = mlistMicrosoft.GetAt(m_nSelectedMicrosoft);
	XPlaneLocation selXPlaneLocation = mlistXPlane.GetAt(m_nSelectedXplane);

	selMSLocation.heading	= selXPlaneLocation.heading;
	selMSLocation.latitude	= selXPlaneLocation.latitude;
	selMSLocation.longitude	= selXPlaneLocation.longitude;

	mlistMicrosoft.SetAt(m_nSelectedMicrosoft, selMSLocation);
	m_ctlListMicrosoft.SetCurSel(m_nSelectedMicrosoft);
	
	m_ctlListXPlane.SetItemData(m_nSelectedXplane, 1);
	m_ctlListXPlane.Invalidate();

	m_ctlListMicrosoft.SetItemData(m_nSelectedMicrosoft, 1);
	m_ctlListMicrosoft.Invalidate();
}

void CXMLMapperDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	const TCHAR szFilter[] = _T("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||");

	CString filename = CTime::GetCurrentTime().Format( "%Y%m%d_%H%M%S_exported.xml");
	CString filepath;
	filepath.Format(_T("%s\\%s"), m_strMSXMLFilepath, filename);

	CFileDialog dlg(false, _T("xml"), filepath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	
	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		
		// Save changed objects.xml to selected path

		ofstream theFile(filepath);
		xml_document<> doc;
		xml_node<>* decl = doc.allocate_node(node_declaration);
		decl->append_attribute(doc.allocate_attribute("version", "1.0"));
		doc.append_node(decl);

		xml_node<>* root = doc.allocate_node(node_element, "FSData");
		root->append_attribute(doc.allocate_attribute("version", "9.0"));
		doc.append_node(root);


		for (int i = 0; i < mlistMicrosoft.GetCount(); i++) {

			MSLocation location = mlistMicrosoft.GetAt(i);

			xml_node<>* childComment = doc.allocate_node(node_comment);

			childComment->value(location.name);

			xml_node<>* child = doc.allocate_node(node_element, "SceneryObject");


			child->append_attribute(doc.allocate_attribute("lat", location.latitude));
			child->append_attribute(doc.allocate_attribute("lon", location.longitude));
			child->append_attribute(doc.allocate_attribute("alt", location.alt));
			child->append_attribute(doc.allocate_attribute("pitch", location.pitch));

			child->append_attribute(doc.allocate_attribute("bank", location.bank));
			child->append_attribute(doc.allocate_attribute("heading", location.heading));
			child->append_attribute(doc.allocate_attribute("imageComplexity", location.imageComplexity));
			child->append_attribute(doc.allocate_attribute("altitudeIsAgl", location.altitudeIsAgl));

			child->append_attribute(doc.allocate_attribute("snapToGround", location.snapToGround));
			child->append_attribute(doc.allocate_attribute("snapToNormal", location.snapToNormal));

			xml_node<>* childLibrary = doc.allocate_node(node_element, "LibraryObject");
			childLibrary->append_attribute(doc.allocate_attribute("name", location.library_name));
			childLibrary->append_attribute(doc.allocate_attribute("scale", location.library_scale));

			child->append_node(childLibrary);

			root->append_node(childComment);
			root->append_node(child);
		}

		theFile << doc;
		theFile.close();
		doc.clear();
	}

	

	/*CDialogEx::OnOK();*/
}


void CXMLMapperDlg::OnBnClickedBtnMicrosoft()
{
	// TODO: Add your control notification handler code here
	
	const TCHAR szFilter[] = _T("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||");
	CFileDialog dlg(true, _T("xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		InitMSXML(sFilePath);


		// Save Microsoft objects.xml path

		int lastIndex = sFilePath.ReverseFind('\\');
		
		if (lastIndex != -1)
			m_strMSXMLFilepath = sFilePath.Left(lastIndex);
	}
}


void CXMLMapperDlg::OnBnClickedBtnXplaneXml()
{
	// TODO: Add your control notification handler code here
	const TCHAR szFilter[] = _T("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("xml"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		InitXPlaneXML(sFilePath);
	}
}
