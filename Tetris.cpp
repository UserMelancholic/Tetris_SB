#pragma once

#include <afxwin.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"
#include "math.h"

// #include"Header.h"
#include "DialogTop10.h"

enum ShapeType { line, square, rightL, leftL, pyramide, leftZ, rightZ};	// ������ ����� ����� (������������)

#define TOP_HEIGHT 40	// ������ ����� (�������������� ������, ����������� ��� ������� �����)
//#define TOP_COLOR  RGB(128,192,255)	// ���� �����
#define TOP_COLOR  RGB(128,128,255)	// ���� �����

#define CELL_SIZE 23	// ������ ������� ������ (��������� 20�20 ��������) �� ������� ������� ������ (����� 30,25,20,15)
#define MAP_X 10	// ������ ���� �� X		(10, 15)
#define MAP_Y 20	// ������ ���� �� Y		(20, 30)

//LeaderInfo leaders[10];
char GamerName[30];  // ��� ���������� ������, ������� �������� � ������� ������ �����������

void GetInfo();		// ��������� ���������� ���������� � ������ ������� �� ����� � ������
void WriteInfo();	// ��������� ������ ���������� � ������ ������� �� ������� � ����

//--------------------------------
// class Shape 
// ����� "������"
//--------------------------------

class Shape
{
public:
	bool		cells[4][4];	// 4x4 �������, ���������� ������
	ShapeType	curType;		// ������� ������ (�� ��������� ������)

	void	NewShape( ShapeType ); 
	void	RotateLeft();		// ������� ������ ������ ������� �������
	void	RotateRight();		// ������� ������ �� ������� �������
	void	ClearShape( bool c[4][4] ); // ������� ������� 4�4
};


// ������� ������� 4�4
void Shape::ClearShape( bool c[4][4] )
{
	for( int i=0; i<4; i++)
		for( int j=0; j<4; j++)
			c[i][j]=false;
}

// ����� ������
void Shape::NewShape( ShapeType type )
{
	ClearShape(cells);
	int i;
	curType=type;

	switch(curType)	// ������ ���������
	{
	case line:	for(i=0; i<4; i++)			// �����	
					cells[0][i]=true;
				break;

	case square: for(i=0; i<2; i++)			// �������� (�� ������ �������� ����)
					for(int j=0; j<2; j++)
						cells[i][j]=true;	
//	case square: for (i = 1; i<3; i++)			// �������� �� ������ �������
//		for (int j = 1; j<3; j++)
//			cells[i][j] = true;
		break;

	case leftL:	for(i=0; i<3; i++)			// "������" � ������ �����
					cells[0][i]=true;
				cells[1][2]=true;
				break;

	case rightL: for(i=0; i<3; i++)			// "������" � ������ ������
					cells[0][i]=true;
				cells[1][0]=true;
				break;

	case pyramide: for(i=0; i<3; i++)		// �-�������� ������, ����� �����
						cells[1][i]=true;
				cells[0][1]=true;
				break;

	case leftZ:	cells[0][0]=true; cells[1][0]=true;		// Z-�������� "�����" ������
				cells[1][1]=true; cells[2][1]=true;
				break;

	case rightZ: cells[0][1]=true; cells[1][0]=true;	// Z-�������� "������" ������
				cells[1][1]=true; cells[2][0]=true;
				break;
	}  

}  // Shape::NewShape


// ������� ������ �� 90 �������� ������ ������� ������� (�����)
void Shape::RotateLeft()
{

	switch(curType)		
	{
	case line:			// �����
		{
			int k;
			if(cells[0][0]==true)	// ���� �������������� ��������� �����
			{
				ClearShape(cells);		// �������� �������
				for(k=0; k<4; k++)		// ���������� ����� ����������� � ������� 1 (��������� � 0)
					cells[k][1]=true;
			}
			else					// ����� (������������ ��������� �����)
			{
				ClearShape(cells);
				for(k=0; k<4; k++)
					cells[0][k]=true;	// ���������� ����� �������������
			}
		}

	case square: return;	// �������, ��� ������� �� ������ �����������
	}

	// ������� ������ ����� �����
	bool tempShape[4][4];    // �������� ������� 
	ClearShape(tempShape);

	// ��������� � ������� tempShape ���������� �� 90 �������� ������ ������� ������� ���� 3�3 ������� cells
	for(int j=3-1 , c=0; j>=0 ; j-- , c++)
		for(int i=0; i<3; i++)
			tempShape[c][i] = cells[i][j];

	ClearShape(cells);

	// ��������� � �������� ������� cells ���������� ������� tempShape
	for(int f=0; f<3; f++)
		for(int d=0; d<3; d++)
			cells[f][d] = tempShape[f][d];

}  //Shape::RotateLeft


// ������� ������ �� 90 �������� �� ������� ������� (������)
void Shape::RotateRight()
{

	switch (curType)
	{
	case line:			// �����
	{
		int k;
		if (cells[0][0] == true)	// ���� �������������� ��������� �����
		{
			ClearShape(cells);		// �������� �������
			for (k = 0; k<4; k++)		// ���������� ����� ����������� � ������� 1 (��������� � 0)
				cells[k][1] = true;
		}
		else					// ����� (������������ ��������� �����)
		{
			ClearShape(cells);
			for (k = 0; k<4; k++)
				cells[0][k] = true;	// ���������� ����� �������������
		}
	}

	case square: return;	// �������, ��� ������� �� ������ �����������
	}

	// ������� ������ ����� �����
	bool tempShape[4][4];    // �������� ������� 
	ClearShape(tempShape);

	// ��������� � ������� tempShape ���������� �� 90 �������� �� ������� ������� ���� 3�3 ������� cells
	for (int i=0, c=2;  i < 3;  i++, c--)
		for (int j=0;  j < 3;  j++)
			tempShape[j][c] = cells[i][j];

	ClearShape(cells);

	// ��������� � �������� ������� cells ���������� ������� tempShape
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			cells[i][j] = tempShape[i][j];

}  //Shape::RotateRight



//-----------------------------------
// Tetris window class
// ����� "���� �������"
//-----------------------------------

class TetrisWnd : public CFrameWnd
{
public:
	TetrisWnd();
	void NewShape();		// ��������� ����� ������ � ����� �������� ����
	COLORREF ShapeColor(int color); // ��������� �������� ����� �����
	void SetLevel(int);		// ��������� ������ ����
	bool CheckLeft(int delta);		// �������� ����������� ����������� ������ �����
	bool CheckRight(int delta);		// �������� ����������� ����������� ������ ������
	void ShowTitle();		// ����� ��������� ����
	void CheckForLine();	// �������� ������ �����
	bool IsAtBottom();		// �������� ����������� ����������� ������ ����
	void ClearStock();		// ������� �������� ����
	CRect GetRect();		// ��������� �������������� � ����������� ������ �������
	int color;				// ������� ����� ����� 0..5

private:
	CMenu	menu;	// ���� ����
	Shape	shape;	// ���������� � ������� ���� ������
	short	stock[MAP_Y][MAP_X];	// ������� ���� MAP_Y x MAP_X  (20�10)
	int	curY;	// ������� ���������� Y  ������ �������� ���� ���������� ������
	int	curX;   // ������� ���������� X	 ������ �������� ���� ���������� ������
	bool	bGame;	// ��������� ����
	bool	bPause;	// ������� ����� � ����
//	int	score;	// ���� (���-�� ��������� �����)
//	int	lines;	// ���-�� ��������� �����
//	int	level;	// ������� ������� ���� (���������� �������� ������� �������) 
//				// �� ������� �������������� ��������� ����� ��������� ������ �� 1 ������ ����
//				// interval = 800 / level + 200
//				// ��� ���� �������, ��� ������ �������� (��� ���� �������� ������� �������)
	int	interval;	// �������� - �������� � ������������ ����� ��������� ������ �� 1 ������ ����
	
protected:
	//{{AFX_VIRTUAL(TetrisWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);	// ��������, ����������� �� �������� ����
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(TetrisWnd)

	// ������� ��������� ��������� ��� TetrisWnd
	// (������������ afx_msg �������� ���������� ����������� ���������, ���� ��� ������ ������, �� ��� ����� ���������) 
	afx_msg void OnPaint();		// �������� ��� ����������� ����
	afx_msg void OnTimer(UINT nIDEvent);	// ���������� �������
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// ���������� ������� ������
	afx_msg void OnLButtonDown(UINT Flags, CPoint Loc);
	afx_msg void OnRButtonDown(UINT Flags, CPoint Loc);
	afx_msg void OnGameNew();	// ����� ����
	afx_msg void OnGameExit();	// ����� �� ����	
	afx_msg void OnClose();		// �������� ����
	afx_msg void OnInfoTop10();	// ����� ���� "������ ����������"
	afx_msg void OnHelpAbout();	// ����� ���� "� ���������"
	//}}AFX_MSG

	//{{AFX_DATA_MAP(TetrisWnd)
	//}}AFX_DATA_MAP

	//{{AFX_DATA(TetrisWnd)
	//}}AFX_DATA

	// �������������� ����� �������� �� ���������
	DECLARE_MESSAGE_MAP()  
public:
	afx_msg void OnEnChangeEdit1();
};  // class TetrisWnd

// ���������� ����� ��������� �������� ����
BEGIN_MESSAGE_MAP(TetrisWnd /* ��� ����� */,
				  CFrameWnd /* ������� ����� */)
	//{{AFX_MSG_MAP(TetrisWnd)
	ON_WM_PAINT()	// ������ �� ���������� ���� ����������
	ON_WM_TIMER()	// ��������� ���������� ���������� ��������� Window
	ON_WM_KEYDOWN()	// ��������� � ������� ������
	ON_WM_LBUTTONDOWN()  // ��������� � ������� ����� ������ ����
	ON_WM_RBUTTONDOWN()  // ��������� � ������� ������ ������ ����
	ON_COMMAND(ID_GAME_NEW, OnGameNew)
	ON_COMMAND(ID_GAME_EXIT, OnGameExit)
	ON_WM_CLOSE()
	ON_COMMAND(ID_HELP_TOP10, OnInfoTop10)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ����������� ������ TetrisWnd
TetrisWnd::TetrisWnd()  
{

	GetInfo(); // ��������� ���������� � ������ ������� �� ����� � ������

	// ������� ���������� ���� � ��������� ���������� "s"
	CString s = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW ,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		AfxGetApp()->LoadIcon(IDI_ICON1));

//	AfxGetApp()->LoadIcon(IDI_IC));

//	(HBRUSH)GetStockObject(BLACK_BRUSH),

	Create(s, "SB Tetris");  // �������� ���� � ��������� �����������

	// �������� ���� ����
	menu.LoadMenu(IDR_MENU);
	SetMenu(&menu);

	score = 0;		// �������� ���� (����)
	lines = 0;		// �������� ���������� ��������� �����
	level = 1;		// ��������� �������

	// ������� ���� �� ��������� (1-�)
	SetLevel(1);

	// ������������� ���������� ��������� �����
	srand(time(0));
	
	ClearStock();	// ������� �������� ����

} // TetrisWnd::TetrisWnd()


/////////////////////////////////////////////////////////////////
// ����� ����������
class MyApp : public CWinApp	// "��� ����������"
{
public:
	virtual BOOL InitInstance()		// ������������� ���������� ����������
	{
		m_pMainWnd = new TetrisWnd;		// ������� ����� ������ ������ TetrisWnd
		m_pMainWnd->ShowWindow(SW_SHOWNORMAL);	// ����� ����������� ����
		return TRUE;
	}
};
MyApp app;	// ��������� ������ "��� ����������"
		


//////////////////////////////////////////////////////////////////


// ����� ��������� ����� ��������� ���� Windows
BOOL TetrisWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~WS_MAXIMIZEBOX;		// ��������� �������������� ����
	cs.style &= ~WS_THICKFRAME;			// ��������� ��������� �������� ���� 
//	cs.cx = 220;	// ������ ����
	cs.cx = MAP_X*CELL_SIZE+20;	// ������ ����
//	cs.cy = 462;	// ������ ����
//	cs.cy = 462+TOP_HEIGHT;	// ������ ����
	cs.cy = MAP_Y*CELL_SIZE + TOP_HEIGHT + 62;	// ������ ����
	return CFrameWnd::PreCreateWindow(cs);
}

//--------------------------------------------------------------------------------
// ���������� ������� ������� �� ���������

// ����� ���������� ����
void TetrisWnd::OnPaint()
{
	// �������� �������� ���������� "dc" ��� ��������� WM_PAINT
	CPaintDC dc(this);		// (������� ��������� ������ CPaintDC ��� ����������� ������ ������� � ���� ����� ���� ������)
	int i, j;

	CBrush brush;	// ������� ����� ��� ������������
	CBrush brush2;	// ������� ����� ��� ������������ ����������


//brush.DeleteObject();
// ����� �����
brush.CreateSolidBrush(TOP_COLOR);	// ������ ���� �����
dc.SelectObject(&brush);	// ������� ��������� ����� ��� ��������� ��
dc.Rectangle(0, 0, MAP_X*CELL_SIZE, TOP_HEIGHT);
brush.DeleteObject();

dc.SelectObject( CreateClientFont("Arial", 16, true, false) );

CString mess;
mess = "����    �����     �������";
// dc.SetTextColor(RGB(120, 120, 120) );  // ���� ������
dc.SetBkColor(TOP_COLOR);			// ���� ����
dc.SetTextColor(RGB(255,255,255));  // ���� ������
dc.TextOut(20, 2, mess);

dc.SetTextColor(RGB(255,255,0) );  // ���� ������
mess.Format("%i", score);
dc.TextOut(30, 21, mess);
mess.Format("%i", lines);
dc.TextOut(85, 21, mess);
mess.Format("%i", level);
dc.TextOut(150, 21, mess);

	brush.CreateSolidBrush( ShapeColor(color) );	// ������ ���� ��� �������� �����
	dc.SelectObject(&brush);	// ������� ��������� ����� ��� ��������� ��
	
	// ������� ��������� �������� �������� ������ � �� ������� ���������
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if( shape.cells[i][j] == true )		// �������� ���� ���������
				dc.Rectangle(curX+j*CELL_SIZE, curY+i*CELL_SIZE, curX+(j+1)*CELL_SIZE, curY+(i+1)*CELL_SIZE);
		}
	}

	// ����� ��������� �������� ����������� � ������� ���� �����������
	for(i=0; i < MAP_Y; i++)		// ����� ����� �������� ����
	{
		for(j=0; j < MAP_X; j++)		// ����� ������� �������� ����
		{
			if(stock[i][j] != -1)	// ���� �� -1 (�� ���), �.�. �������� ������� ������, �� ����������� �� �������� ������
			{
				brush.DeleteObject();
				brush.CreateSolidBrush( ShapeColor(stock[i][j]) );	// ������ ���� �����
//				brush.CreateHatchBrush(HS_DIAGCROSS, ShapeColor(stock[i][j]));		

				dc.SelectObject(&brush);	// ������� �����
				dc.Rectangle(j*CELL_SIZE,i*CELL_SIZE+TOP_HEIGHT, (j+1)*CELL_SIZE,(i+1)*CELL_SIZE+TOP_HEIGHT);	
											// ��������� ������� �������� ����������� �������� ������
			}
		}
	}
}  // TetrisWnd::OnPaint()

// �������� ������������� (�������) ����������� �������� ������
// ������ ����� �������� 6�6 ������
CRect TetrisWnd::GetRect()
{
	CRect r;
	r.left=curX-CELL_SIZE;
	r.right=curX+CELL_SIZE*5;
	r.top=curY-CELL_SIZE;
	r.bottom=curY+CELL_SIZE*5;
	return r;
}

// ���������� �������
// (������ ����� ���������� ������� ��������� ���������� ������� ����� �������� ��������� WM_TIMER
//  OnTimer - ��� ��� ���������� ����� ���������)
void TetrisWnd::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==1 && bGame==true)	// ��������� ���� � ������ "����"
	{
		if(IsAtBottom())	// �������� ������� �������� "����" 
							// ��� ��� "���" �������� ����, ��� ������� �������� � ����������� ����� ����������
		{
			for(int i=0; i<4; i++)		// ����� ������� cells, ���������� ������
				for(int j=0; j<4; j++)
				{
					if(shape.cells[i][j] == true)	// ���� ������� �������� ������� cells ���������
						stock[(curY-TOP_HEIGHT)/CELL_SIZE + i][curX/CELL_SIZE + j] = color;
													// ���� ������� ���������� � ��������������� ������ ������� stock
				}
			NewShape();	// ������� ����� �������, ������� ����� ���������� ������
			if(IsAtBottom())	// ����� ������� ����� "��������" � ����������� "�����������" (�� "����������")
			{
				bGame=false;	// ���������� ������ ��������� ����
			}

			InvalidateRect(GetRect());	// ������� �������������� ����������� �������� �������
			CheckForLine();
			return;
		}
		curY += CELL_SIZE;  // ������ ������ �� ������ ����
		InvalidateRect(GetRect());
	}	
	else if(bGame==false)	// ���� �������� !
	{
		KillTimer(1);	// ���������� ������
		// ������� ���������� ��������� �����
		CString s;
		s.Format("%d",score);
//		s.Format("%d  %d  %d", score,  curX, curY);
		MessageBox("���� ������� !\r��� ����: "+s);

		// �������� ��������� � ���10
		if (score > leaders[9].score)
		{
			// ���� ������� ����� ������
			DialogSetName SetName;
			SetName.DoModal();
		}
	}

	CFrameWnd::OnTimer(nIDEvent);

}  // TetrisWnd::OnTimer


// ��������� ������� ������
void TetrisWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)	// ������ ������� �������
					// (nChar - ��� ASCII-��� �������, ���������������� ������� ������)
	{
	case VK_CONTROL:
	case VK_UP:		// ������� �����
//		shape.RotateLeft();	break;	// ������������ ������ �� 90 ��������
		shape.RotateRight();		// ������������ ������ �� 90 ��������
		if (CheckRight(1)) shape.RotateLeft(); // ���� ������ ��������, �� ������������ ����� !
		if (CheckLeft(1)) shape.RotateLeft(); // ���� ����� ��������, �� ������������ ����� !
		break;
	case VK_LEFT:	// ������� �����
		if(CheckLeft(0)) return;	// ���� ����� �������� (��� ������ ��� ������� �����������), 
								// �� ������� (�.�. �� ����� ����������) 
		if (bGame != false)
		   curX-=CELL_SIZE;  // ��������� ����� �� 1 �������� 
		break;	
	case VK_RIGHT:	// ������� ������
		if(CheckRight(0)) return; // ���� ������ ��������, �� �������
		if (bGame != false)
  		  curX+=CELL_SIZE;  // ��������� ������ �� 1 �������� 
		break;	
	case VK_DOWN:	// ������� ����, ��������� ����� �������
		KillTimer(1); // ���������� ������� ������
		SetTimer(1,40,NULL); // ������ �������� ������� 40 �� (������� ������� �������)
		break;
	}
	InvalidateRect(GetRect());

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

// ������� ����� ������ ����
afx_msg void TetrisWnd::OnLButtonDown(UINT, CPoint loc)
{
}

// ������� ������ ������ ���� - ����������� ��������� ��� ������ ���� � �����
afx_msg void TetrisWnd::OnRButtonDown(UINT, CPoint loc)
{
	if (bPause)  // ���� �� �����
	{	// ������������ ���� (������� ���� � �����)
		bPause = false;
		KillTimer(1);	// ��������� �������
		SetTimer(1, interval, NULL);	 // ��������� ������ � Id=1 � ���������� interval
	}
	else {  // ������������� ����� � ����
		bPause = true;
		KillTimer(1);	// ��������� �������
	}
}


// ����� �������� ����� ����
void TetrisWnd::OnGameNew()
{
	ClearStock();	// ������� �������� ����
	score = 0;		// �������� ���� (����)
	lines = 0;		// �������� ���������� ��������� �����
	level = 1;		// ��������� �������
	bGame=true;		// ������ ���� true
	bPause = false; // ������ ����� false

	// ���� ������� ���������� ������ ����
	DialogSetLevel dSetLevel;
	dSetLevel.DoModal();

	SetLevel(level);	// ��������� ������� ���������
	NewShape();		// ������� ����� �������, ���������� �� �������
//	ShowTitle();	// ����� ��������� ����
	Invalidate();
}

// ������� �������� ����
void TetrisWnd::ClearStock()
{
	for(int i=0; i < MAP_Y; i++)
		for(int j=0; j < MAP_X; j++)
			stock[i][j] = -1;
}

// �������� �� ��, ��� �������� ������� �������� "����"
// ��� ��� "���" �������� ����, ��� ������� �������� � ����������� ����� ����������
bool TetrisWnd::IsAtBottom()
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(shape.cells[i][j] == true)		// �������� cells[i][j] ������� ���������  
			{	// ����������� ��� �� ����������� ����� ��� ���� �������� 
				if(((curY-TOP_HEIGHT)/CELL_SIZE + i) >= (MAP_Y-1) || stock[(curY-TOP_HEIGHT)/CELL_SIZE + i+1][curX/CELL_SIZE + j] != -1)
					// ����������� ��������� �������� ������ �� �������� � "���" �������� ����
					// ��� ����� �� ����������� �������� �������� ������ ��������� �������� ����������� ����� �����������
					return true;
			}
		}
	}
	return false;
}

// �������� �� ����������� (��������) �����
void TetrisWnd::CheckForLine()
{
	int i,j,k,c=0;
	bool flag;
	
	for(i=0; i < MAP_Y; i++)  // ������ �� ������� �������� ����
	{
		flag=true;

		for(j=0; j < MAP_X; j++)	// ������ �� �������� (��������� ������� ������)
			flag &= (stock[i][j] != -1);	// ���� �������� ��������� (������������ �������, � �� ��� ���� ���� (-1) �������� ����)
											// �� ������� (stock[i][j] != -1) ���������� true

		if(flag==true && j!=0)	// ���� ��� �������� i-� ������ ���������
		{
			c++;		// ����������� ������� ����������� ����� � ������� ������� ������
			lines++;	// ����������� ������� ������ ���������� ��������� �����
			score += (1 + level / 3) * 5; 	// ����������� ���� ����
			if (lines % 3 == 0) { // ���� ������� 3 ������ �����, �� ��������� �� ��������� �������
				level++;
				SetLevel(level);
				Invalidate();  // ����� ��������� WM_PAINT (������������ ����)
			}
//			ShowTitle();	// ��������� ��������� ���� (� ��������� ��������� ����)

			// ���, ��� ���� i-� ������ �������� ���� �� ����� i-� ������
			for(k=i; k>0; k--)
			{
				for(j=0; j < MAP_X; j++)
				{
					stock[k][j] = stock[k-1][j];	// ��������� ���������� ������ ���� � k-� ������
				}
			}
		}
	}

	// ��������� �������� ���� �� ���������� ����������� ����� �� 2 �� 4
	switch (c)
	{
		case 2: score += 10; break;		// �� 2 ����� +10 �����
		case 3: score += 30; break;		// �� 3 ����� +30 �����
		case 4: score += 50; break;		// �� 4 ����� +40 �����
	}

	// �� ���������� ����������� ����� (�� ���-�� � ���������� "c") 
	// ������ �������� ���� ��������� ������� ���-�� ������� ����� 
	for(k=0; k<c; k++)
		for(j=0; j < MAP_X; j++)
			stock[k][j] =- 1;
	
	Invalidate();  // ����� ��������� WM_PAINT (������������ ����)

} // CheckForLine()


// ���������� ��������� ���� (� ��������� ��������� ����)
void TetrisWnd::ShowTitle()
{
	CString title;
	title.Format("Tetris ����: %d", score);
	SetWindowText(title);
}


// �������� �������� ������
bool TetrisWnd::CheckRight(int delta)
// delta - ������������� ������� ��������
//   = 0 - ��� �������� �������� ������ (���� ����� �������� ������� ������ ��� ��������� � ��������, �� �� ���������)
//   = 1 - ��� �������� ����������� �������� (���� ����� �������� ���������, �� �� "���������" � ��������, �� ���� ���������)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(shape.cells[i][j] == true)	// �������� cells[i][j] ������� ���������
			{	// ����������� ��� �� ����������� ������ ��� ���� �������� 
				if((curX/CELL_SIZE + j) >= (MAP_X-1)+delta || stock[(curY-TOP_HEIGHT)/CELL_SIZE + i][curX/CELL_SIZE + j+1] != -1)
					// ����������� ��������� �������� ������ �� �������� � ������ ������
					// ��� ������ �� ����������� �������� �������� ������ ��������� �������� ����������� ����� �����������
					return true;
			}
		}
	}
	return false;
}

// �������� �������� �����
bool TetrisWnd::CheckLeft(int delta)
// delta - ������������� ������� ��������
//   = 0 - ��� �������� �������� ����� (���� ����� �������� ������� ����� ��� ��������� � ��������, �� �� ���������)
//   = 1 - ��� �������� ����������� �������� (���� ����� �������� ���������, �� �� "���������" � ��������, �� ���� ���������)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(shape.cells[i][j] == true)		// �������� cells[i][j] ������� ���������
			{
				if((curX/CELL_SIZE + j) <= 0-delta || stock[(curY-TOP_HEIGHT)/CELL_SIZE + i][curX/CELL_SIZE + j-1] !=- 1)
					// ����������� ��������� �������� ������ �� �������� � ������ �����
					// ��� ����� �� ����������� �������� �������� ������ ��������� �������� ����������� ����� �����������
					return true;
			}
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
// Menu commands
////////////////////////////////////////////////////////////////////////////////
// ����� ���� "�����"
void TetrisWnd::OnGameExit()
{
	OnClose();
}

void TetrisWnd::OnClose()
{
	KillTimer(1);	// ���������� ������
	WriteInfo();	// �������� � ���� ���������� � ������ �������
	CFrameWnd::OnClose();	// ������� ���� ����� ����� ������ ������������� ������
}


/////////////////////////////////////////////////////////////////////////////////

// ����� ��������� ������ ����, ������� ������ �������� �������
// ��� ������ �������, ��� ������ �������� �������, ��� ������� �������� ������� �������
void TetrisWnd::SetLevel(int lev)
{
//	interval = 1000 / lev + 50;	// ���������� �������� ������� � "��"
	if (lev >= 1 && lev <= 9) {		// �� 10 ������ ��� ���������� ��������� ������ 100 ��
		interval = 1100 - 100 * lev;	// �������� ����������� ��������� �� ������:  y(x) = a - b * x;
		//  �������	 ��������
		//		 1		1000
		//		 2		 900
		//		 3		 800
		//			...
		//		 9		 200
	}
	else {							// � 10 ������
//		interval = 1000 / lev;
		interval = 500/lev * log(50/lev) + 60;  // ��������������� �����������: y(x) = a/x * ln(b/x) + c;
		//  �������	 ��������
		//		10		 140
		//		11		 128
		//		12		 119
		//		13		 111
		//		14		 105
		//		15		 100
		//			...
		//	    20		  82
	}
} // TetrisWnd::SetLevel()


// ����� ���� "������ ���������"
void TetrisWnd::OnInfoTop10()
{
	CDialogTop10 top10;
	top10.DoModal();
}


// ����� ���� "� ���������"
void TetrisWnd::OnHelpAbout()
{
	CDialog dlg(IDD_ABOUT);
	dlg.DoModal();
}

// ����� �������� ����� � ������� RGB() � ���� ��������� COLORREF
// ������ RGB() ������������ ��� ��������� ����� ����� ��� ������������� ��������
// ������� ������� ������ - ��� ����� ����� 0..5
COLORREF TetrisWnd::ShapeColor(int color)
{
	switch(color)
	{
	case 0: return RGB(255,0,0);
	case 1: return RGB(0,255,0);
	case 2: return RGB(0,0,255);
	case 3: return RGB(255,0,255);
	case 4: return RGB(0,255,255);
	case 5: return RGB(255,255,0);
	}
	return RGB(255,255,255);
//	return RGB(0, 0, 0);
}

// ��������� ���������� ����� �������� ������ � ������� ����
// (��������� ���, ��������� ������� - ������, �� ������)
void TetrisWnd::NewShape()
{
	KillTimer(1);	// ��������� �������
	SetTimer(1, interval, NULL);	 // ��������� � ������� ������ � Id=1 � ���������� interval
	// ��������� ������� ������ �������� ���� ������� � �������� �������� (� ������ �����, �� ������)
//	curY = 0;
	curY = TOP_HEIGHT;
	curX = (MAP_X - 4) / 2 * CELL_SIZE;

	//	���������� ����� ������
	ShapeType t = ShapeType(rand() % 7);	// ����� ����� (�� 7) - ��������� ����� 0..6
	shape.NewShape(t);
	color = rand() % 6;		// ���� ����� (�� 6) - ��������� ����� 0..5
}


// ��������� ���������� � ������ �������
void GetInfo()
{
	FILE *in;
	if (in = fopen("leaders.dat", "rb"))
	{  // ������ ����
		for (int i = 0; i < 10; i++)
			fread(&leaders[i], sizeof(LeaderInfo), 1, in);
		fclose(in);
	}
	else  
	{  // ����� � ��������� ���, �������������� ������ �������� ���������� ����������
		for (int i = 0; i < 10; i++)
			leaders[i] = null_leader;
	}
}
//��������� ���������� � ������ �������
void WriteInfo()
{
	FILE *out;  // ���������� �������� ���������� (��������� �� ����)
	if (out = fopen("leaders.dat", "wb"))
	{
		for (int i = 0; i < 10; i++)
			fwrite(&leaders[i], sizeof(LeaderInfo), 1, out);
		fclose(out);
	}
}


//---------------------------------------------------------------------
#include "stdafx.h"
#include "afxdialogex.h"

// ���������� ���� DialogSetLevel

IMPLEMENT_DYNAMIC(DialogSetLevel, CDialog)

DialogSetLevel::DialogSetLevel(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SETLEVEL, pParent)
	, m_SetLevel(1)
{

}

DialogSetLevel::~DialogSetLevel()
{
}

void DialogSetLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LEVEL, m_SetLevel);
}


BEGIN_MESSAGE_MAP(DialogSetLevel, CDialog)
	ON_BN_CLICKED(IDOK, &DialogSetLevel::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� DialogSetLevel



void DialogSetLevel::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	UpdateData(true); //����� ��� ���������� ������ �� ��������� ����
    // �������� ���� ��������� � ���������� ������ m_SetLevel

	if (m_SetLevel < 1)
		m_SetLevel = 1;		// ����������� ������� 1 !
	if (m_SetLevel > 10)
		m_SetLevel = 10;	// ������������ ��������� ������� 10 !

	level = m_SetLevel;		// ����������� ��������� ������� � ���������� ��������� level

	CDialog::OnOK();
}
