#pragma once
#include <afxwin.h>
class CColoredListBox :
    public CListBox
{
public:
    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};

