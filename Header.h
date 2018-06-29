#pragma once
#ifndef HEADER_H
#define HEADER_H

// Стурктура с информацией о лучших игроках
struct LeaderInfo
{
	int score;
	int lines;
	int level;
	char name[30];
};

// Лучшие результаты Top10
extern LeaderInfo leaders[10];

// Минимальный результат, чтобы попасть в таблицу
const LeaderInfo null_leader = { 0,0,0,"noname" };

extern int	score;	// Счет (кол-во набранных очков)
extern int	lines;	// Кол-во собранных линий
extern int	level;	// текущий уровень игры (определяет скорость падения фигурок) 

extern char GamerName[30];  // Имя последнего игрока, который попадает в таблицу лучших результатов


// Объявление Глобальной Функции Создания Пользовательского шрифта
// Позволяет задать гарнитуру (название), размер шрифта и признаки жирного и наклонного начертания 
// Возвращает указатель на объект Созданного шрифта
extern CFont *CreateClientFont(CString, int, BOOL, BOOL);   // // просто объявление (без определения)
// Определение функции задано в файле DialogTop10.cpp




// диалоговое окно DialogSetLevel

class DialogSetLevel : public CDialog
{
	DECLARE_DYNAMIC(DialogSetLevel)

public:
	DialogSetLevel(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~DialogSetLevel();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETLEVEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_SetLevel;
	afx_msg void OnBnClickedOk();
};

#endif