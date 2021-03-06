#pragma once

#include "ViewTree.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class ObjCreatorTree : public CViewTree
{
	DECLARE_MESSAGE_MAP()

public:
	ObjCreatorTree();
	~ObjCreatorTree();

protected:
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	HTREEITEM mDragItem;
	CImageList * mDragImage;
	bool mDragging;
	int mDragTimer;
};

class ObjCreatorView : public CDockablePane
{
	DECLARE_MESSAGE_MAP()

public:
	ObjCreatorView();
	virtual ~ObjCreatorView();

	void AdjustLayout();
	void OnChangeVisualStyle();

protected:
	void _Init(void * param0, void * param1);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnProperties();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnPaint();

protected:
	ObjCreatorTree mCreatorView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

	tEventListener<ObjCreatorView> OnInit;
};

