#pragma once
#ifndef DIALOGTOP10_H
#define DIALOGTOP10_H


#include"resource.h"

#include"Header.h"
#include "afxwin.h"

// диалоговое окно CDialogTop10

class CDialogTop10 : public CDialog
{
	DECLARE_DYNAMIC(CDialogTop10)

public:
	CDialogTop10(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CDialogTop10();
	BOOL CDialogTop10::OnInitDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOP10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit1;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeEdit1();
	CListBox m_list1;
};
#pragma once


// диалоговое окно DialogSetName

class DialogSetName : public CDialog
{
	DECLARE_DYNAMIC(DialogSetName)

public:
	DialogSetName(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~DialogSetName();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETNAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_SetName;
};


#endif