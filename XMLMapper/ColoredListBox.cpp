#include "pch.h"
#include "ColoredListBox.h"


void CColoredListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
    CString sText;
    this->GetText(lpDrawItemStruct->itemID, sText);
    LPCTSTR lpszText = sText.GetBuffer();
    DWORD_PTR p = this->GetItemData(lpDrawItemStruct->itemID);
    
    ASSERT(lpszText != NULL);
    CDC dc;

    dc.Attach(lpDrawItemStruct->hDC);

    // Save these value to restore them when done drawing.
    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    // If this item is selected, set the background color
    // and the text color to appropriate values. Also, erase
    // rect by filling it with the background color.
    if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
        (lpDrawItemStruct->itemState & ODS_SELECTED))
    {
        dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
        dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
        dc.FillSolidRect(&lpDrawItemStruct->rcItem,
            ::GetSysColor(COLOR_HIGHLIGHT));
    }
    else
    {
        dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
    }


    if ((int)p == 1) {
        dc.FillSolidRect(&lpDrawItemStruct->rcItem,RGB(0, 255, 0));
    }

    // Draw the text.
    dc.DrawText(
        lpszText,
        (int)_tcslen(lpszText),
        &lpDrawItemStruct->rcItem,
        DT_LEFT | DT_SINGLELINE | DT_VCENTER);

    // Reset the background color and the text color back to their
    // original values.
    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);

    dc.Detach();
}

void CColoredListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) {
	ASSERT(lpMeasureItemStruct->CtlType == ODT_LISTBOX);
	LPCTSTR lpszText = (LPCTSTR)lpMeasureItemStruct->itemData;
	ASSERT(lpszText != NULL);
	CSize sz;
	CDC* pDC = GetDC();

	sz = pDC->GetTextExtent(lpszText);

	ReleaseDC(pDC);

	lpMeasureItemStruct->itemHeight = sz.cy;
}