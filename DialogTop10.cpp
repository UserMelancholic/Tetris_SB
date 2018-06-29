// DialogTop10.cpp: ���� ����������
//

#include "stdafx.h"
#include "DialogTop10.h"
#include "afxdialogex.h"
#pragma once

#include"resource.h"

LeaderInfo leaders[10];

int	score;	// ���� (���-�� ��������� �����)
int	lines;	// ���-�� ��������� �����
int	level;	// ������� ������� ���� (���������� �������� ������� �������) 
			// �� ������� �������������� ��������� ����� ��������� ������ �� 1 ������ ����
			// interval = 800 / level + 200
			// ��� ���� �������, ��� ������ �������� (��� ���� �������� ������� �������)

// ������� �������� ����������������� ������
// ��������� ������ ��������� (��������), ������ ������ � �������� ������� � ���������� ���������� 
// ���������� ��������� �� ������ ���������� ������
CFont *CreateClientFont(
	CString Typeface,	// ��������� (��������) ������
	int Size,			// ������ ������ � �������
	BOOL Bold = false,	// ������� ������� ����������
	BOOL Italic = false	// ������� ���������� ����������
	)
{
	int Weight = FW_NORMAL;
	if (Bold)
		Weight = FW_BOLD;

	CFont *m_pFont = new CFont;   // ������� ��������� m_pFont �� ����� ������ ����� CFont

								  // �������� ������. ����������� ���������� �� ������������.
	m_pFont->CreateFont(Size, 0, 0, 0, Weight, Italic, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, Typeface);

	return m_pFont;
}


// ���������� ���� CDialogTop10

IMPLEMENT_DYNAMIC(CDialogTop10, CDialog)

CDialogTop10::CDialogTop10(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TOP10, pParent)
	, m_edit1(_T(""))
{
//	m_edit1 = _T("First Line\r\rSecond Line\r\n");
//	m_edit1 =_T("First Line\r\nSecond Line\r\n...\r\n");

//	UpdateData(1);
}

CDialogTop10::~CDialogTop10()
{
}

//------------------------------
BOOL CDialogTop10::OnInitDialog()
{
	CDialog::OnInitDialog();

	//------------------------

	// ���������� ����� ��� �������� ���������� � �� = IDC_STATIC
	CStatic* pS = (CStatic*)GetDlgItem(IDC_STATIC);
	pS->SetFont(CreateClientFont("Arial", 16, true, false), true);

	// ���������� ����� ��� �������� ���������� � �� = IDC_EDIT1
//	CStatic* pE = (CStatic*)GetDlgItem(IDC_EDIT1);
//	pE->SetFont(CreateClientFont("Courier New", 16, false, false), true);

	// ���������� ����� ��� �������� ���������� � �� = IDC_LIST1
	CStatic* pL = (CStatic*)GetDlgItem(IDC_LIST1);
	pL->SetFont(CreateClientFont("Courier New", 16, false, false), true);

	//------------------------

	//	m_edit1 = _T("First Line\r\nSecond Line\r\n...\r\n");
	m_edit1 = _T("");
	CString curLine = "";
	char curName[31];

	for (int i = 0; i < 10; i++)
	{
		//		curLine.Format("%d. %d %d %d %s\r\n", i+1, leaders[i].score, leaders[i].lines, leaders[i].level, leaders[i].name);
		//		m_edit1 += curLine;
		//		curLine.Format("{0}. {1} {2} {3} {4}\r\n", i + 1, leaders[i].score, leaders[i].lines, leaders[i].level, leaders[i].name);

		strcpy(curName, leaders[i].name);
 		strncat(curName, "..............................", 30-strlen(leaders[i].name) );

//		curLine.Format("%3d. %s %7d %7d %7d \r\n", i+1, curName, leaders[i].score, leaders[i].lines, leaders[i].level);
		curLine.Format("%3d. %s %7d %7d %7d", i+1, curName, leaders[i].score, leaders[i].lines, leaders[i].level);
//		m_edit1 += curLine+"\r\n";

		m_list1.AddString(curLine);
	}

	UpdateData(0);   // ����������� ����������� ���������� ��������� � ���������� ���� (� ����� ������ � �������� IDC_EDIT1)

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}





void CDialogTop10::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CDialogTop10, CDialog)
	ON_WM_ACTIVATE()
	ON_EN_CHANGE(IDC_EDIT1, &CDialogTop10::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ����������� ��������� CDialogTop10


void CDialogTop10::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: �������� ���� ��� ����������� ���������
}




void CDialogTop10::OnEnChangeEdit1()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
}
// D:\Prog\C++\KursRab\Tetris\DialogTop10.cpp: ���� ����������
//


// ���������� ���� DialogSetName

IMPLEMENT_DYNAMIC(DialogSetName, CDialog)

DialogSetName::DialogSetName(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SETNAME, pParent)
	, m_SetName(_T(""))
{

}

DialogSetName::~DialogSetName()
{
}

void DialogSetName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_SetName);
	DDX_Text(pDX, IDC_EDIT1, m_SetName);
}


BEGIN_MESSAGE_MAP(DialogSetName, CDialog)
	ON_BN_CLICKED(IDOK, &DialogSetName::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� DialogSetName

// ��������� ������� ������ [ �� ] � ���� ������� ����� ������
void DialogSetName::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	// ������� ������� �� �����
	UpdateData(true); //����� ��� ���������� ������ �� ��������� ����
	
//	MessageBox("��� ������: " + m_SetName);

// ������� ��������� � ������� ��������
	
	// ����� ������� ������� � ������� ��������
	int n = -1; // �������
	for (int i = 0; i < 10; i++)
		if (score > leaders[i].score)  // ����� ����� ����� ������
		{
			n = i;  // ���������� �������
			break;  // � ���������� �����
		}

	if (n > -1)  // �������� ��������� �� ����� n
	{
		CString s;
		s.Format("%d", n + 1);
		MessageBox("���� ������� � ��� 10: " + s);

		// ����������� ������ ���� �� 1 �������
		for (int i = 9; i > n; i--)
			leaders[i] = leaders[i-1];
		// ������� ����� ������
		leaders[n].score = score;
		leaders[n].lines = lines;
		leaders[n].level = level;
		StrCpy(leaders[n].name, m_SetName);
	}

	CDialog::OnOK();
}
