#pragma once
#include <afxwin.h>

// This struct store information for each item in listbox
typedef struct _LISTBOX_COLOR_
{
    CString strText; // text content, default value is _T("")
    COLORREF fgColor; // foreground color, default color is black
    COLORREF bgColor; // background color, default color is white
    _LISTBOX_COLOR_() // constructor
    {
        strText.Empty();
        fgColor = RGB(0, 0, 0);
        bgColor = RGB(255, 255, 255);
    }
}LISTBOX_COLOR, * PLISTBOX_COLOR;


class CMultiLineListBox :
    public CListBox
{
    public void AppendString(LPCSTR lpszText, COLORREF fgColor, COLORREF bgColor);
};

