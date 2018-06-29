#pragma once

#include <afxwin.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"
#include "math.h"

// #include"Header.h"
#include "DialogTop10.h"

enum ShapeType { line, square, rightL, leftL, pyramide, leftZ, rightZ};	// список типов фигур (перечисление)

#define TOP_HEIGHT 40	// высота Табло (информационный раздел, размещенный над игровым полем)
//#define TOP_COLOR  RGB(128,192,255)	// цвет Табло
#define TOP_COLOR  RGB(128,128,255)	// цвет Табло

#define CELL_SIZE 23	// размер стороны ячейки (квадратик 20х20 пикселей) из которых состоит фигура (можно 30,25,20,15)
#define MAP_X 10	// размер поля по X		(10, 15)
#define MAP_Y 20	// размер поля по Y		(20, 30)

//LeaderInfo leaders[10];
char GamerName[30];  // Имя последнего игрока, который попадает в таблицу лучших результатов

void GetInfo();		// процедура считывания информации о лучших игроках из файла в массив
void WriteInfo();	// процедура записи информации о лучших игроках из массива в файл

//--------------------------------
// class Shape 
// Класс "Фигура"
//--------------------------------

class Shape
{
public:
	bool		cells[4][4];	// 4x4 матрица, содержащая фигуру
	ShapeType	curType;		// текущая фигура (из заданного списка)

	void	NewShape( ShapeType ); 
	void	RotateLeft();		// поворот фигуры против часовой стрелки
	void	RotateRight();		// поворот фигуры по часовой стрелке
	void	ClearShape( bool c[4][4] ); // очистка матрицы 4х4
};


// Очистка матрицы 4х4
void Shape::ClearShape( bool c[4][4] )
{
	for( int i=0; i<4; i++)
		for( int j=0; j<4; j++)
			c[i][j]=false;
}

// Новая фигура
void Shape::NewShape( ShapeType type )
{
	ClearShape(cells);
	int i;
	curType=type;

	switch(curType)	// анализ вариантов
	{
	case line:	for(i=0; i<4; i++)			// линия	
					cells[0][i]=true;
				break;

	case square: for(i=0; i<2; i++)			// квардрат (от левого верхнего угла)
					for(int j=0; j<2; j++)
						cells[i][j]=true;	
//	case square: for (i = 1; i<3; i++)			// квардрат по центру матрицы
//		for (int j = 1; j<3; j++)
//			cells[i][j] = true;
		break;

	case leftL:	for(i=0; i<3; i++)			// "клюшка" с ручкой влево
					cells[0][i]=true;
				cells[1][2]=true;
				break;

	case rightL: for(i=0; i<3; i++)			// "клюшка" с ручкой вправо
					cells[0][i]=true;
				cells[1][0]=true;
				break;

	case pyramide: for(i=0; i<3; i++)		// Т-образная фигура, ножка вверх
						cells[1][i]=true;
				cells[0][1]=true;
				break;

	case leftZ:	cells[0][0]=true; cells[1][0]=true;		// Z-образная "левая" фигура
				cells[1][1]=true; cells[2][1]=true;
				break;

	case rightZ: cells[0][1]=true; cells[1][0]=true;	// Z-образная "правая" фигура
				cells[1][1]=true; cells[2][0]=true;
				break;
	}  

}  // Shape::NewShape


// Поворот фигуры на 90 градусов против часовой стрелки (влево)
void Shape::RotateLeft()
{

	switch(curType)		
	{
	case line:			// линия
		{
			int k;
			if(cells[0][0]==true)	// если горизонтальное положение линии
			{
				ClearShape(cells);		// очистить матрицу
				for(k=0; k<4; k++)		// разместить линию вертикально в столбце 1 (нумерация с 0)
					cells[k][1]=true;
			}
			else					// иначе (вертикальное положение линии)
			{
				ClearShape(cells);
				for(k=0; k<4; k++)
					cells[0][k]=true;	// разместить линию горизонтально
			}
		}

	case square: return;	// квадрат, его поворот не меняет отображение
	}

	// Поворот других типов фигур
	bool tempShape[4][4];    // временая матрица 
	ClearShape(tempShape);

	// сохранить в матрице tempShape повернутый на 90 градусов против часовой стрелки блок 3х3 матрицы cells
	for(int j=3-1 , c=0; j>=0 ; j-- , c++)
		for(int i=0; i<3; i++)
			tempShape[c][i] = cells[i][j];

	ClearShape(cells);

	// сохранить в основной матрице cells содержимое матрицы tempShape
	for(int f=0; f<3; f++)
		for(int d=0; d<3; d++)
			cells[f][d] = tempShape[f][d];

}  //Shape::RotateLeft


// Поворот фигуры на 90 градусов по часовой стрелке (вправо)
void Shape::RotateRight()
{

	switch (curType)
	{
	case line:			// линия
	{
		int k;
		if (cells[0][0] == true)	// если горизонтальное положение линии
		{
			ClearShape(cells);		// очистить матрицу
			for (k = 0; k<4; k++)		// разместить линию вертикально в столбце 1 (нумерация с 0)
				cells[k][1] = true;
		}
		else					// иначе (вертикальное положение линии)
		{
			ClearShape(cells);
			for (k = 0; k<4; k++)
				cells[0][k] = true;	// разместить линию горизонтально
		}
	}

	case square: return;	// квадрат, его поворот не меняет отображение
	}

	// Поворот других типов фигур
	bool tempShape[4][4];    // временая матрица 
	ClearShape(tempShape);

	// сохранить в матрице tempShape повернутый на 90 градусов по часовой стрелки блок 3х3 матрицы cells
	for (int i=0, c=2;  i < 3;  i++, c--)
		for (int j=0;  j < 3;  j++)
			tempShape[j][c] = cells[i][j];

	ClearShape(cells);

	// сохранить в основной матрице cells содержимое матрицы tempShape
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			cells[i][j] = tempShape[i][j];

}  //Shape::RotateRight



//-----------------------------------
// Tetris window class
// Класс "окно Тетриса"
//-----------------------------------

class TetrisWnd : public CFrameWnd
{
public:
	TetrisWnd();
	void NewShape();		// появление новой фигуры в верху игрового поля
	COLORREF ShapeColor(int color); // некоторые заданные цвета фигур
	void SetLevel(int);		// установка уровня игры
	bool CheckLeft(int delta);		// проверка возможности перемещения фигуры влево
	bool CheckRight(int delta);		// проверка возможности перемещения фигуры вправо
	void ShowTitle();		// вывод заголовка окна
	void CheckForLine();	// проверка полной линии
	bool IsAtBottom();		// проверка возможности перемещения фигуры вниз
	void ClearStock();		// очистка игрового поля
	CRect GetRect();		// получение прямоугольника с размещенной внутри фигурой
	int color;				// текущий номер цвета 0..5

private:
	CMenu	menu;	// меню окна
	Shape	shape;	// движущаяся в игровом поле фигура
	short	stock[MAP_Y][MAP_X];	// игровое поле MAP_Y x MAP_X  (20х10)
	int	curY;	// текущая координата Y  левого верхнего угла движущейся фигуры
	int	curX;   // текущая координата X	 левого верхнего угла движущейся фигуры
	bool	bGame;	// состояние игры
	bool	bPause;	// признак Паузы в игре
//	int	score;	// Счет (кол-во набранных очков)
//	int	lines;	// Кол-во собранных линий
//	int	level;	// текущий уровень игры (определяет скорость падения фигурок) 
//				// он обратно пропорционален интервалу между смещением фигуры на 1 клетку вниз
//				// interval = 800 / level + 200
//				// чем выше уровень, тем меньше интервал (тем выше скорость падения фигурки)
	int	interval;	// интервал - значение в милисекундах между смещением фигуры на 1 клетку вниз
	
protected:
	//{{AFX_VIRTUAL(TetrisWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);	// действия, выполняемые до создания окна
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(TetrisWnd)

	// Функции обработки сообщений для TetrisWnd
	// (спецификатор afx_msg означает объявление обработчика сообщения, пока єто пустой макрос, но его нужно указывать) 
	afx_msg void OnPaint();		// действия при перерисовке окна
	afx_msg void OnTimer(UINT nIDEvent);	// обработчик таймера
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// обработчик нажатий клавиш
	afx_msg void OnLButtonDown(UINT Flags, CPoint Loc);
	afx_msg void OnRButtonDown(UINT Flags, CPoint Loc);
	afx_msg void OnGameNew();	// новая игра
	afx_msg void OnGameExit();	// выход из игры	
	afx_msg void OnClose();		// закрытие окна
	afx_msg void OnInfoTop10();	// вызов окна "Лучшие результаты"
	afx_msg void OnHelpAbout();	// вызов окна "О программе"
	//}}AFX_MSG

	//{{AFX_DATA_MAP(TetrisWnd)
	//}}AFX_DATA_MAP

	//{{AFX_DATA(TetrisWnd)
	//}}AFX_DATA

	// Декларирование карты откликов на сообщения
	DECLARE_MESSAGE_MAP()  
public:
	afx_msg void OnEnChangeEdit1();
};  // class TetrisWnd

// Реализация карты сообщений главного окна
BEGIN_MESSAGE_MAP(TetrisWnd /* наш класс */,
				  CFrameWnd /* базовый класс */)
	//{{AFX_MSG_MAP(TetrisWnd)
	ON_WM_PAINT()	// запрос на обновление окна приложения
	ON_WM_TIMER()	// разрешить приложению обработать сообщение Window
	ON_WM_KEYDOWN()	// сообщение о нажатии клавиш
	ON_WM_LBUTTONDOWN()  // сообщение о нажатии Левой кнопки мыши
	ON_WM_RBUTTONDOWN()  // сообщение о нажатии Правой кнопки мыши
	ON_COMMAND(ID_GAME_NEW, OnGameNew)
	ON_COMMAND(ID_GAME_EXIT, OnGameExit)
	ON_WM_CLOSE()
	ON_COMMAND(ID_HELP_TOP10, OnInfoTop10)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Конструктор класса TetrisWnd
TetrisWnd::TetrisWnd()  
{

	GetInfo(); // считываем информацию о лучших игроках из файла в массив

	// задание параметров окна в строковой переменной "s"
	CString s = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW ,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		AfxGetApp()->LoadIcon(IDI_ICON1));

//	AfxGetApp()->LoadIcon(IDI_IC));

//	(HBRUSH)GetStockObject(BLACK_BRUSH),

	Create(s, "SB Tetris");  // создание окна с заданными параметрами

	// загрузка меню окна
	menu.LoadMenu(IDR_MENU);
	SetMenu(&menu);

	score = 0;		// обнуляем очки (счет)
	lines = 0;		// обнуляем количество собранных линий
	level = 1;		// начальный уровень

	// уровень игры по умолчанию (1-й)
	SetLevel(1);

	// инициализация генератора случайных чисел
	srand(time(0));
	
	ClearStock();	// очистка игрового поля

} // TetrisWnd::TetrisWnd()


/////////////////////////////////////////////////////////////////
// Класс приложения
class MyApp : public CWinApp	// "Мое приложение"
{
public:
	virtual BOOL InitInstance()		// инициализация экземпляра приложения
	{
		m_pMainWnd = new TetrisWnd;		// создаем новый объект класса TetrisWnd
		m_pMainWnd->ShowWindow(SW_SHOWNORMAL);	// метод отображения окна
		return TRUE;
	}
};
MyApp app;	// экземпляр класса "Мое приложение"
		


//////////////////////////////////////////////////////////////////


// Метод вызвается Перед созданием окна Windows
BOOL TetrisWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~WS_MAXIMIZEBOX;		// запретить разворачивание окна
	cs.style &= ~WS_THICKFRAME;			// запретить изменение размеров окна 
//	cs.cx = 220;	// ширина окна
	cs.cx = MAP_X*CELL_SIZE+20;	// ширина окна
//	cs.cy = 462;	// высота окна
//	cs.cy = 462+TOP_HEIGHT;	// высота окна
	cs.cy = MAP_Y*CELL_SIZE + TOP_HEIGHT + 62;	// высота окна
	return CFrameWnd::PreCreateWindow(cs);
}

//--------------------------------------------------------------------------------
// Реализация функций отклика на сообщения

// Метод прорисовки окна
void TetrisWnd::OnPaint()
{
	// Создадим контекст устройства "dc" для обработки WM_PAINT
	CPaintDC dc(this);		// (создаем экземпляр класса CPaintDC для дальнейшего вывода графики в окно через этот объект)
	int i, j;

	CBrush brush;	// создаем кисть для закрашивания
	CBrush brush2;	// создаем кисть для закрашивания штриховкой


//brush.DeleteObject();
// Вывод табло
brush.CreateSolidBrush(TOP_COLOR);	// задать цвет кисти
dc.SelectObject(&brush);	// выбрать созданную кисть для рисования ею
dc.Rectangle(0, 0, MAP_X*CELL_SIZE, TOP_HEIGHT);
brush.DeleteObject();

dc.SelectObject( CreateClientFont("Arial", 16, true, false) );

CString mess;
mess = "Счет    Линий     Уровень";
// dc.SetTextColor(RGB(120, 120, 120) );  // цвет текста
dc.SetBkColor(TOP_COLOR);			// цвет фона
dc.SetTextColor(RGB(255,255,255));  // цвет текста
dc.TextOut(20, 2, mess);

dc.SetTextColor(RGB(255,255,0) );  // цвет текста
mess.Format("%i", score);
dc.TextOut(30, 21, mess);
mess.Format("%i", lines);
dc.TextOut(85, 21, mess);
mess.Format("%i", level);
dc.TextOut(150, 21, mess);

	brush.CreateSolidBrush( ShapeColor(color) );	// задать цвет для сплошной кисти
	dc.SelectObject(&brush);	// выбрать созданную кисть для рисования ею
	
	// Сначала прорисуем клеточки падающей фигуры в ее текущем положении
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if( shape.cells[i][j] == true )		// клеточку надо закрасить
				dc.Rectangle(curX+j*CELL_SIZE, curY+i*CELL_SIZE, curX+(j+1)*CELL_SIZE, curY+(i+1)*CELL_SIZE);
		}
	}

	// Затем прорисуем клеточки выстроенной в игровом поле конструкции
	for(i=0; i < MAP_Y; i++)		// обход строк игрового поля
	{
		for(j=0; j < MAP_X; j++)		// обход колонок игрового поля
		{
			if(stock[i][j] != -1)	// если не -1 (не фон), т.е. клеточка какойто фигуры, то закрашиваем ее заданным цветом
			{
				brush.DeleteObject();
				brush.CreateSolidBrush( ShapeColor(stock[i][j]) );	// задать цвет кисти
//				brush.CreateHatchBrush(HS_DIAGCROSS, ShapeColor(stock[i][j]));		

				dc.SelectObject(&brush);	// выбрать кисть
				dc.Rectangle(j*CELL_SIZE,i*CELL_SIZE+TOP_HEIGHT, (j+1)*CELL_SIZE,(i+1)*CELL_SIZE+TOP_HEIGHT);	
											// закрасить текущую клеточку конструкции заданным цветом
			}
		}
	}
}  // TetrisWnd::OnPaint()

// Получить прямоугольник (квадрат) обрамляющий падающую фигуру
// размер этого квадрата 6х6 клеток
CRect TetrisWnd::GetRect()
{
	CRect r;
	r.left=curX-CELL_SIZE;
	r.right=curX+CELL_SIZE*5;
	r.top=curY-CELL_SIZE;
	r.bottom=curY+CELL_SIZE*5;
	return r;
}

// Обработчик таймера
// (таймер через регулярные заранее указанные промежутки времени будет посылать сообщение WM_TIMER
//  OnTimer - это наш обратотчик этого сообщения)
void TetrisWnd::OnTimer(UINT nIDEvent)
{
	if(nIDEvent==1 && bGame==true)	// состояние окна в режиме "Игра"
	{
		if(IsAtBottom())	// падающая фигурка достигла "низа" 
							// это или "дно" игрового поля, или фигурка уперлась в выстроенную ранее кострукцию
		{
			for(int i=0; i<4; i++)		// обход матрицы cells, содержащей фигуру
				for(int j=0; j<4; j++)
				{
					if(shape.cells[i][j] == true)	// если текущая клеточка матрицы cells закрашена
						stock[(curY-TOP_HEIGHT)/CELL_SIZE + i][curX/CELL_SIZE + j] = color;
													// цвет фигурки запоминаем в соответствующей ячейке матрицы stock
				}
			NewShape();	// создаем Новую фигурку, которая будет спускаться сверху
			if(IsAtBottom())	// Новая фигурка сразу "уперлась" в построенную "конструкцию" (мы "засыпались")
			{
				bGame=false;	// установить статус окончания игры
			}

			InvalidateRect(GetRect());	// функция принудительной перерисовки заданной области
			CheckForLine();
			return;
		}
		curY += CELL_SIZE;  // смещем фигуру на строку вниз
		InvalidateRect(GetRect());
	}	
	else if(bGame==false)	// игра окончена !
	{
		KillTimer(1);	// остановить таймер
		// Вывести количество набранных очков
		CString s;
		s.Format("%d",score);
//		s.Format("%d  %d  %d", score,  curX, curY);
		MessageBox("Игра оконена !\rВаш счет: "+s);

		// Проверка попадания в Топ10
		if (score > leaders[9].score)
		{
			// Окно запроса Имени игрока
			DialogSetName SetName;
			SetName.DoModal();
		}
	}

	CFrameWnd::OnTimer(nIDEvent);

}  // TetrisWnd::OnTimer


// Обработка нажатия клавиш
void TetrisWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)	// анализ нажатой клавиши
					// (nChar - это ASCII-код символа, соответствующего нажатой клавиш)
	{
	case VK_CONTROL:
	case VK_UP:		// стрелка Вверх
//		shape.RotateLeft();	break;	// поворачиваем фигуру на 90 градусов
		shape.RotateRight();		// поворачиваем фигуру на 90 градусов
		if (CheckRight(1)) shape.RotateLeft(); // если справа преграда, то поворачиваем назад !
		if (CheckLeft(1)) shape.RotateLeft(); // если слева преграда, то поворачиваем назад !
		break;
	case VK_LEFT:	// стрелка Влево
		if(CheckLeft(0)) return;	// если слева преграда (или стенка или фигурки конструкции), 
								// то выходим (т.к. не можем сместиться) 
		if (bGame != false)
		   curX-=CELL_SIZE;  // смещаемся влево на 1 клеточку 
		break;	
	case VK_RIGHT:	// стрелка Вправо
		if(CheckRight(0)) return; // если справа преграда, то выходим
		if (bGame != false)
  		  curX+=CELL_SIZE;  // смещаемся вправо на 1 клеточку 
		break;	
	case VK_DOWN:	// стрелка Вниз, выполняем сброс фигурки
		KillTimer(1); // остановить текущий таймер
		SetTimer(1,40,NULL); // задать интервал таймера 40 мс (быстрое падение фигурки)
		break;
	}
	InvalidateRect(GetRect());

	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Нажатие Левой кнопки мыши
afx_msg void TetrisWnd::OnLButtonDown(UINT, CPoint loc)
{
}

// Нажатие Правой кнопки мыши - чередование установки или снятия игры с Паузы
afx_msg void TetrisWnd::OnRButtonDown(UINT, CPoint loc)
{
	if (bPause)  // игра на Паузе
	{	// возобновляем игру (снимаем игру с Паузы)
		bPause = false;
		KillTimer(1);	// остановка таймера
		SetTimer(1, interval, NULL);	 // запускаем таймер с Id=1 и интервалом interval
	}
	else {  // устанавливаем Паузу в игре
		bPause = true;
		KillTimer(1);	// остановка таймера
	}
}


// Метод создания Новой игры
void TetrisWnd::OnGameNew()
{
	ClearStock();	// очистка игрового поля
	score = 0;		// обнуляем очки (счет)
	lines = 0;		// обнуляем количество собранных линий
	level = 1;		// начальный уровень
	bGame=true;		// статус игры true
	bPause = false; // статус паузы false

	// Окно запроса Начального уровня игры
	DialogSetLevel dSetLevel;
	dSetLevel.DoModal();

	SetLevel(level);	// начальный уровень сложности
	NewShape();		// создаем новую фигурку, начинается ее падение
//	ShowTitle();	// вывод заголовка окна
	Invalidate();
}

// Очистка игрового поля
void TetrisWnd::ClearStock()
{
	for(int i=0; i < MAP_Y; i++)
		for(int j=0; j < MAP_X; j++)
			stock[i][j] = -1;
}

// Проверка на то, что падающая фигурка достигла "низа"
// это или "дно" игрового поля, или фигурка уперлась в выстроенную ранее кострукцию
bool TetrisWnd::IsAtBottom()
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(shape.cells[i][j] == true)		// клеточка cells[i][j] матрицы закрашена  
			{	// анализируем нет ли препятствия снизу для этой клеточки 
				if(((curY-TOP_HEIGHT)/CELL_SIZE + i) >= (MAP_Y-1) || stock[(curY-TOP_HEIGHT)/CELL_SIZE + i+1][curX/CELL_SIZE + j] != -1)
					// закрашенной клеточкой падающей фигуры мы уперлись в "дно" игрового поля
					// или Снизу от закрашенной клеточки падающей фигуры находится клеточка выстроенной ранее конструкции
					return true;
			}
		}
	}
	return false;
}

// Проверка на заполненную (сплошную) линию
void TetrisWnd::CheckForLine()
{
	int i,j,k,c=0;
	bool flag;
	
	for(i=0; i < MAP_Y; i++)  // проход по строкам игрового поля
	{
		flag=true;

		for(j=0; j < MAP_X; j++)	// проход по колонкам (клеточкам текущей строки)
			flag &= (stock[i][j] != -1);	// если клеточка заполнена (принадлежела фигурке, а не код цвет фона (-1) игрового поля)
											// то условие (stock[i][j] != -1) возвращает true

		if(flag==true && j!=0)	// если Все клеточки i-й строки заполнены
		{
			c++;		// увеличиваем счетчик заполненных линий в текущей игровой момент
			lines++;	// увеличиваем счетчик Общего количества собранных линий
			score += (1 + level / 3) * 5; 	// увеличиваем счет игры
			if (lines % 3 == 0) { // если собрали 3 полных линии, то переходим на следующий уровень
				level++;
				SetLevel(level);
				Invalidate();  // вызов сообщения WM_PAINT (перерисовать окно)
			}
//			ShowTitle();	// обновляем заголовок окна (в заголовке выводится счет)

			// все, что выше i-й строки опускаем вниз на место i-й строки
			for(k=i; k>0; k--)
			{
				for(j=0; j < MAP_X; j++)
				{
					stock[k][j] = stock[k-1][j];	// переносим содержимое строки выше в k-ю строку
				}
			}
		}
	}

	// Добавляем Бонусные очки за Количество заполненных линий от 2 до 4
	switch (c)
	{
		case 2: score += 10; break;		// за 2 линии +10 очков
		case 3: score += 30; break;		// за 3 линии +30 очков
		case 4: score += 50; break;		// за 4 линии +40 очков
	}

	// по количеству заполненных линий (их кол-во в переменной "c") 
	// сверху игрового поля добавляем такоеже кол-во фоновых линий 
	for(k=0; k<c; k++)
		for(j=0; j < MAP_X; j++)
			stock[k][j] =- 1;
	
	Invalidate();  // вызов сообщения WM_PAINT (перерисовать окно)

} // CheckForLine()


// Обновление заголовка окна (в заголовке выводится счет)
void TetrisWnd::ShowTitle()
{
	CString title;
	title.Format("Tetris счет: %d", score);
	SetWindowText(title);
}


// Проверка преграды справа
bool TetrisWnd::CheckRight(int delta)
// delta - корректировка условия проверки
//   = 0 - для проверки смещения вправо (если перед нажатием стрелки вправо уже упираемся в преграду, то не смещаемся)
//   = 1 - для проверки возможности поворота (если после поворота упираемся, но не "врезаемся" в преграду, то даем повернуть)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(shape.cells[i][j] == true)	// клеточка cells[i][j] матрицы закрашена
			{	// анализируем нет ли препятствия справа для этой клеточки 
				if((curX/CELL_SIZE + j) >= (MAP_X-1)+delta || stock[(curY-TOP_HEIGHT)/CELL_SIZE + i][curX/CELL_SIZE + j+1] != -1)
					// закрашенной клеточкой падающей фигуры мы уперлись в стенку Справа
					// или Справа от закрашенной клеточки падающей фигуры находится клеточка выстроенной ранее конструкции
					return true;
			}
		}
	}
	return false;
}

// Проверка преграды слева
bool TetrisWnd::CheckLeft(int delta)
// delta - корректировка условия проверки
//   = 0 - для проверки смещения влево (если перед нажатием стрелки влево уже упираемся в преграду, то не смещаемся)
//   = 1 - для проверки возможности поворота (если после поворота упираемся, но не "врезаемся" в преграду, то даем повернуть)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(shape.cells[i][j] == true)		// клеточка cells[i][j] матрицы закрашена
			{
				if((curX/CELL_SIZE + j) <= 0-delta || stock[(curY-TOP_HEIGHT)/CELL_SIZE + i][curX/CELL_SIZE + j-1] !=- 1)
					// закрашенной клеточкой падающей фигуры мы уперлись в стенку Слева
					// или Слева от закрашенной клеточки падающей фигуры находится клеточка выстроенной ранее конструкции
					return true;
			}
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
// Menu commands
////////////////////////////////////////////////////////////////////////////////
// Пункт меню "Выход"
void TetrisWnd::OnGameExit()
{
	OnClose();
}

void TetrisWnd::OnClose()
{
	KillTimer(1);	// остановить таймер
	WriteInfo();	// записать в файл информацию о лучших игроках
	CFrameWnd::OnClose();	// закрыть окно через вызов метода Родительского класса
}


/////////////////////////////////////////////////////////////////////////////////

// Метод установки Уровня игры, который задает Интервал таймера
// Чем Больше Уровень, тем Меньше Интервал таймера, тем быстрее скорость падения фигурки
void TetrisWnd::SetLevel(int lev)
{
//	interval = 1000 / lev + 50;	// установить интервал таймера в "мс"
	if (lev >= 1 && lev <= 9) {		// до 10 уровня шаг уменьшения интервала равень 100 мс
		interval = 1100 - 100 * lev;	// линейная зависимость Интервала от Уровня:  y(x) = a - b * x;
		//  Уровень	 Интервал
		//		 1		1000
		//		 2		 900
		//		 3		 800
		//			...
		//		 9		 200
	}
	else {							// с 10 уровня
//		interval = 1000 / lev;
		interval = 500/lev * log(50/lev) + 60;  // логарифмическая зависимость: y(x) = a/x * ln(b/x) + c;
		//  Уровень	 Интервал
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


// Пункт меню "Лучшие результаті"
void TetrisWnd::OnInfoTop10()
{
	CDialogTop10 top10;
	top10.DoModal();
}


// Пенкт меню "О программе"
void TetrisWnd::OnHelpAbout()
{
	CDialog dlg(IDD_ABOUT);
	dlg.DoModal();
}

// Метод возврата цвета в формате RGB() в виде структуры COLORREF
// Формат RGB() используется для установки цвета кисти для зарисовывания клеточек
// Входной парамет метода - это номер цвета 0..5
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

// Установка параметров Новой падающей фигуры в игровом поле
// (случайный тип, начальная позиция - сверху, по центру)
void TetrisWnd::NewShape()
{
	KillTimer(1);	// остановка таймера
	SetTimer(1, interval, NULL);	 // запросить у системы таймер с Id=1 и интервалом interval
	// начальная позиция левого верхнего угла матрицы с подающей фигуркой (с самого верху, по центру)
//	curY = 0;
	curY = TOP_HEIGHT;
	curX = (MAP_X - 4) / 2 * CELL_SIZE;

	//	подготовка Новой фигуры
	ShapeType t = ShapeType(rand() % 7);	// номер фигры (из 7) - случайное число 0..6
	shape.NewShape(t);
	color = rand() % 6;		// цвет фигры (из 6) - случайное число 0..5
}


// Получение информации о лучших игроках
void GetInfo()
{
	FILE *in;
	if (in = fopen("leaders.dat", "rb"))
	{  // читаем файл
		for (int i = 0; i < 10; i++)
			fread(&leaders[i], sizeof(LeaderInfo), 1, in);
		fclose(in);
	}
	else  
	{  // файла с рекордами нет, инициализируем массив структур начальными значениями
		for (int i = 0; i < 10; i++)
			leaders[i] = null_leader;
	}
}
//Сохранить информацию о лучших игроках
void WriteInfo()
{
	FILE *out;  // определяем файловый дескриптор (указатель на файл)
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

// диалоговое окно DialogSetLevel

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


// обработчики сообщений DialogSetLevel



void DialogSetLevel::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true); //метод для считывания данных из контролов окна
    // значение поля находится в переменной класса m_SetLevel

	if (m_SetLevel < 1)
		m_SetLevel = 1;		// минимальный уровень 1 !
	if (m_SetLevel > 10)
		m_SetLevel = 10;	// максимальный начальный уровень 10 !

	level = m_SetLevel;		// устанавлюем Насальный уровень в глобальной переменой level

	CDialog::OnOK();
}
