#pragma once
#ifndef HEADER_H
#define HEADER_H

// ��������� � ����������� � ������ �������
struct LeaderInfo
{
	int score;
	int lines;
	int level;
	char name[30];
};

// ������ ���������� Top10
extern LeaderInfo leaders[10];

// ����������� ���������, ����� ������� � �������
const LeaderInfo null_leader = { 0,0,0,"noname" };

extern int	score;	// ���� (���-�� ��������� �����)
extern int	lines;	// ���-�� ��������� �����
extern int	level;	// ������� ������� ���� (���������� �������� ������� �������) 

extern char GamerName[30];  // ��� ���������� ������, ������� �������� � ������� ������ �����������


// ���������� ���������� ������� �������� ����������������� ������
// ��������� ������ ��������� (��������), ������ ������ � �������� ������� � ���������� ���������� 
// ���������� ��������� �� ������ ���������� ������
extern CFont *CreateClientFont(CString, int, BOOL, BOOL);   // // ������ ���������� (��� �����������)
// ����������� ������� ������ � ����� DialogTop10.cpp




// ���������� ���� DialogSetLevel

class DialogSetLevel : public CDialog
{
	DECLARE_DYNAMIC(DialogSetLevel)

public:
	DialogSetLevel(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~DialogSetLevel();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETLEVEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_SetLevel;
	afx_msg void OnBnClickedOk();
};

#endif