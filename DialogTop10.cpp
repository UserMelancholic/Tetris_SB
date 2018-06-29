// DialogTop10.cpp: файл реализации
//

#include "stdafx.h"
#include "DialogTop10.h"
#include "afxdialogex.h"
#pragma once

#include"resource.h"

LeaderInfo leaders[10];

int	score;	// Счет (кол-во набранных очков)
int	lines;	// Кол-во собранных линий
int	level;	// текущий уровень игры (определяет скорость падения фигурок) 
			// он обратно пропорционален интервалу между смещением фигуры на 1 клетку вниз
			// interval = 800 / level + 200
			// чем выше уровень, тем меньше интервал (тем выше скорость падения фигурки)

// Функция Созданий Пользовательского шрифта
// Позволяет задать гарнитуру (название), размер шрифта и признаки жирного и наклонного начертания 
// Возвращает указатель на объект Созданного шрифта
CFont *CreateClientFont(
	CString Typeface,	// Гарнитура (название) шрифта
	int Size,			// Размер шрифта в пунктах
	BOOL Bold = false,	// Признак жирного начертания
	BOOL Italic = false	// Признак наклонного начертания
	)
{
	int Weight = FW_NORMAL;
	if (Bold)
		Weight = FW_BOLD;

	CFont *m_pFont = new CFont;   // создать указатель m_pFont на Новый объект класс CFont

								  // Создание шрифта. Большинство параметров не используются.
	m_pFont->CreateFont(Size, 0, 0, 0, Weight, Italic, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, Typeface);

	return m_pFont;
}


// диалоговое окно CDialogTop10

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

	// Установить шрифт для элемента управления с ИД = IDC_STATIC
	CStatic* pS = (CStatic*)GetDlgItem(IDC_STATIC);
	pS->SetFont(CreateClientFont("Arial", 16, true, false), true);

	// Установить шрифт для элемента управления с ИД = IDC_EDIT1
//	CStatic* pE = (CStatic*)GetDlgItem(IDC_EDIT1);
//	pE->SetFont(CreateClientFont("Courier New", 16, false, false), true);

	// Установить шрифт для элемента управления с ИД = IDC_LIST1
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

	UpdateData(0);   // отображение содержимого визуальных элементов в диалоговом окне (в нашем случае в элементе IDC_EDIT1)

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


// обработчики сообщений CDialogTop10


void CDialogTop10::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: добавьте свой код обработчика сообщений
}




void CDialogTop10::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
// D:\Prog\C++\KursRab\Tetris\DialogTop10.cpp: файл реализации
//


// диалоговое окно DialogSetName

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


// обработчики сообщений DialogSetName

// Обработка нажатия кнопки [ Ок ] в окне запроса Имени игрока
void DialogSetName::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	// считать символы из эдита
	UpdateData(true); //метод для считывания данных из контролов окна
	
//	MessageBox("Имя игрока: " + m_SetName);

// Занести результат в таблицу рекордов
	
	// Поиск позиции вставки в таблицу рекордов
	int n = -1; // позиция
	for (int i = 0; i < 10; i++)
		if (score > leaders[i].score)  // нашли место среди лучших
		{
			n = i;  // запоминаем позицию
			break;  // и прекращаем поиск
		}

	if (n > -1)  // Записать результат на место n
	{
		CString s;
		s.Format("%d", n + 1);
		MessageBox("Ваша позиция в ТОП 10: " + s);

		// переместить список вниз на 1 позицию
		for (int i = 9; i > n; i--)
			leaders[i] = leaders[i-1];
		// вставим новые данные
		leaders[n].score = score;
		leaders[n].lines = lines;
		leaders[n].level = level;
		StrCpy(leaders[n].name, m_SetName);
	}

	CDialog::OnOK();
}
