#ifndef _PT4TASKMAKER

#define _PT4TASKMAKER

#include <windows.h>

//------------------------------------------------------------------------------
// Конструктор для электронного задачника Programming Taskbook 4.23
//------------------------------------------------------------------------------
// Заголовочный файл модуля для создания динамических библиотек 
//   с группами заданий на языке C++
//
// Copyright (c) 2013-2023 М.Э.Абрамян
// Электронный задачник Programming Taskbook Copyright (c) М.Э.Абрамян,1998-2023
//------------------------------------------------------------------------------

using namespace std;


#define xCenter 0
#define xLeft 100
#define xRight 200

#define SampleError "#ERROR?"
#define MaxLineCount 50

#define lgPascal       0x0000001 
#define lgPascalABCNET 0x0000401 
#define lgPascalNET    0x0000400
#define lgPascalABCNET_flag 0x0000400 // добавлено в версии 4.14
#define lgVB           0x0000002
#define lgCPP          0x0000004
#define lg1C           0x0000040
#define lgPython       0x0000080 
#define lgPython3      0x1000080 // добавлено в версии 4.14
#define lgPython3_flag 0x1000000 // добавлено в версии 4.14
#define lgCS           0x0000100
#define lgVBNET        0x0000200
#define lgJava         0x0010000 // добавлено в версии 4.11
#define lgRuby         0x0020000 // добавлено в версии 4.12
#define lgWithPointers 0x000003D
#define lgWithObjects  0x0FFFF80 // изменено в версии 4.22
#define lgNET          0x000FF00
#define lgAll          0x0FFFFFF // изменено в версии 4.10
#define lgFS           0x0000800 // добавлено в версии 4.19
#define lgJulia        0x0040000 // добавлено в версии 4.22
#define lgC            0x0000008 // добавлено в версии 4.23

/// Узел динамической структуры
struct TNode
{
	int Data;
	TNode* Next;
	TNode* Prev;
	TNode* Left;
	TNode* Right;
	TNode* Parent;
};

/// Указатель на узел динамической структуры
typedef TNode* PNode;

/// Процедурный тип, используемый при создании групп заданий
typedef void(__stdcall* TInitTaskProc)(int);

/// Добавляет к задачнику новую группу заданий с указанными характеристиками
void CreateGroup(const char* GroupName, const char* GroupDescription,
	const char* GroupAuthor, const char* GroupKey, int TaskCount,
	TInitTaskProc InitTaskProc);

/// Добавляет к создаваемой группе задание из другой группы
void UseTask(const char* GroupName, int TaskNumber);

/// Добавляет к создаваемой группе задание из другой группы
void UseTask(const char* GroupName, int TaskNumber, const char* TopicDescription); // добавлено в версии 4.19

/// Должна указываться первой при определении нового задания
void CreateTask(const char* SubgroupName);

/// Должна указываться первой при определении нового задания
void CreateTask();

/// Должна указываться первой при определении нового задания
/// (вариант для параллельного режима задачника)
void CreateTask(const char* SubgroupName, int* ProcessCount);

//// Должна указываться первой при определении нового задания
/// (вариант для параллельного режима задачника)
void CreateTask(int* ProcessCount);

/// Позволяет определить текущий язык программирования, выбранный для задачника
/// Возвращает значения, связанные с константами lgXXX
int CurrentLanguage();

/// Возвращает двухбуквенную строку с описанием текущей локали
/// (в даной версии возвращается либо "ru", либо "en")
char* CurrentLocale();

/// Возвращает номер текущей версии задачника в формате "d.dd"
/// (для версий, меньших 4.10, возвращает "4.00")
char* CurrentVersion();  // добавлено в версии 4.10

//-----------------------------------------------------------------------------

/// Добавляет к формулировке задания строку
void TaskText(const char* S, int X, int Y);

/// Определяет все строки формулировки задания
/// (в параметре S отдельные строки формулировки
/// должны разделяться символами \r, \n или парой \r\n;
/// начальные и конечные пробелы в строках удаляются,
/// пустые строки в формулировку не включаются)
void TaskText(const char* S); // добавлено в версии 4.11

//-----------------------------------------------------------------------------

/// Добавляет к исходным данным элемент логического типа с комментарием
void DataB(const char* Cmt, bool B, int X, int Y);

/// Добавляет к исходным данным элемент логического типа
void DataB(bool B, int X, int Y); // добавлено в версии 4.11

/// Добавляет к исходным данным целочисленный элемент с комментарием
void DataN(const char* Cmt, int N, int X, int Y, int W);

/// Добавляет к исходным данным целочисленный элемент
void DataN(int N, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к исходным данным два целочисленных элемента с общим комментарием
void DataN2(const char* Cmt, int N1, int N2, int X, int Y, int W);

/// Добавляет к исходным данным два целочисленных элемента
void DataN2(int N1, int N2, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к исходным данным три целочисленных элемента с общим комментарием
void DataN3(const char* Cmt, int N1, int  N2, int  N3, int X, int Y, int W);

/// Добавляет к исходным данным три целочисленных элемента
void DataN3(int N1, int  N2, int  N3, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к исходным данным вещественный элемент с комментарием
void DataR(const char* Cmt, double R, int  X, int Y, int W);

/// Добавляет к исходным данным вещественный элемент
void DataR(double R, int  X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к исходным данным два вещественных элемента с общим комментарием
void DataR2(const char* Cmt, double R1, double R2, int X, int Y, int W);

/// Добавляет к исходным данным два вещественных элемента
void DataR2(double R1, double R2, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к исходным данным три вещественных элемента с общим комментарием
void DataR3(const char* Cmt, double R1, double R2, double R3, int  X, int Y, int W);

/// Добавляет к исходным данным три вещественных элемента
void DataR3(double R1, double R2, double R3, int  X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к исходным данным символьный элемент с комментарием
void DataC(const char* Cmt, char C, int  X, int Y);

/// Добавляет к исходным данным символьный элемент
void DataC(char C, int  X, int Y); // добавлено в версии 4.11

/// Добавляет к исходным данным строковый элемент с комментарием
void DataS(const char* Cmt, const char* S, int X, int Y);

/// Добавляет к исходным данным строковый элемент
void DataS(const char* S, int X, int Y); // добавлено в версии 4.11

/// Добавляет к исходным данным элемент типа PNode с комментарием
void DataP(const char* Cmt, int NP, int X, int Y);

/// Добавляет к исходным данным элемент типа PNode
void DataP(int NP, int X, int Y); // добавлено в версии 4.11

/// Добавляет комментарий в область исходных данных
void  DataComment(const char* Cmt, int  X, int Y);

//-----------------------------------------------------------------------------

/// Добавляет к результирующим данным логический элемент с комментарием
void ResultB(const char* Cmt, bool B, int X, int Y);

/// Добавляет к результирующим данным логический элемент
void ResultB(bool B, int X, int Y); // добавлено в версии 4.11

/// Добавляет к результирующим данным целочисленный элемент с комментарием
void ResultN(const char* Cmt, int N, int X, int Y, int W);

/// Добавляет к результирующим данным целочисленный элемент
void ResultN(int N, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к результирующим данным два целочисленных элемента с общим комментарием
void ResultN2(const char* Cmt, int N1, int N2, int X, int Y, int W);

/// Добавляет к результирующим данным два целочисленных элемента
void ResultN2(int N1, int N2, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к результирующим данным три целочисленных элемента с общим комментарием
void ResultN3(const char* Cmt, int N1, int N2, int N3, int X, int Y, int W);

/// Добавляет к результирующим данным три целочисленных элемента
void ResultN3(int N1, int N2, int N3, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к результирующим данным вещественный элемент с комментарием
void ResultR(const char* Cmt, double R, int X, int Y, int W);

/// Добавляет к результирующим данным вещественный элемент
void ResultR(double R, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к результирующим данным два вещественных элемента с общим комментарием
void ResultR2(const char* Cmt, double R1, double R2, int X, int Y, int W);

/// Добавляет к результирующим данным два вещественных элемента
void ResultR2(double R1, double R2, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к результирующим данным три вещественных элемента с общим комментарием
void ResultR3(const char* Cmt, double R1, double R2, double R3, int X, int Y, int W);

/// Добавляет к результирующим данным три вещественных элемента
void ResultR3(double R1, double R2, double R3, int X, int Y, int W); // добавлено в версии 4.11

/// Добавляет к результирующим данным символьный элемент с комментарием
void ResultC(const char* Cmt, char C, int X, int Y);

/// Добавляет к результирующим данным символьный элемент
void ResultC(char C, int X, int Y); // добавлено в версии 4.11

/// Добавляет к результирующим данным строковый элемент с комментарием
void ResultS(const char* Cmt, const char* S, int X, int Y);

/// Добавляет к результирующим данным строковый элемент
void ResultS(const char* S, int X, int Y); // добавлено в версии 4.11

/// Добавляет к результирующим данным элемент типа PNode с комментарием
void ResultP(const char* Cmt, int NP, int X, int Y);

/// Добавляет к результирующим данным элемент типа PNode
void ResultP(int NP, int X, int Y); // добавлено в версии 4.11

/// Добавляет комментарий в область результирующих данных
void ResultComment(const char* Cmt, int X, int Y);

//-----------------------------------------------------------------------------

/// Задает число дробных знаков при отображении вещественных чисел
void SetPrecision(int N);

/// Задает число исходных данных, минимально необходимое
/// для нахождения правильных результирующих данных
void SetRequiredDataCount(int N);

/// Задает число тестовых испытаний (от 2 до 9), при успешном
/// прохождении которых задание будет считаться выполненным
void SetTestCount(int N);

/// Возвращает горизонтальную координату, начиная с которой следует выводить I-й элемент из набора,
/// содержащего N элементов, при условии, что ширина каждого элемента равна W, а между элементами
/// надо указывать B пробелов (элементы нумеруются от 1)
int Center(int I, int  N, int  W, int B);

/// Возвращает псевдослучайное целое число, лежащее
/// в диапазоне от M до N включительно. Если указанный
/// диапазон пуст, то возвращает M.
int RandomN(int M, int N); // добавлено в версии 4.11

/// Возвращает псевдослучайное вещественное число, лежащее
/// на полуинтервале [A, B). Если указанный полуинтервал
/// пуст, то возвращает A.
double RandomR(double A, double B); // добавлено в версии 4.11

/// Возвращает порядковый номер текущего тестового запуска
/// (учитываются только успешные тестовые запуски). Если ранее успешных
/// запусков не было, то возвращает 1. Если задание уже выполнено
/// или запущено в демонстрационном режиме, то возвращает 0.
/// При использовании предыдущих версий задачника (до 4.10 включительно)
/// всегда возвращает 0.
int CurrentTest(); // добавлено в версии 4.11

//-----------------------------------------------------------------------------

/// Добавляет к исходным данным двоичный файл с целочисленными элементами
void DataFileN(const char* FileName, int Y, int W);

/// Добавляет к исходным данным двоичный файл с вещественными элементами
void DataFileR(const char* FileName, int Y, int W);

/// Добавляет к исходным данным двоичный файл с символьными элементами
void DataFileC(const char* FileName, int Y, int W);

/// Добавляет к исходным данным двоичный файл со строковыми элементами
void DataFileS(const char* FileName, int Y, int W);

/// Добавляет к исходным данным текстовый файл
void DataFileT(const char* FileName, int Y1, int Y2);

//-----------------------------------------------------------------------------

/// Добавляет к результирующим данным двоичный файл с целочисленными элементами
void ResultFileN(const char* FileName, int Y, int W);

/// Добавляет к результирующим данным двоичный файл с вещественными элементами
void ResultFileR(const char* FileName, int Y, int W);

/// Добавляет к результирующим данным двоичный файл с символьными элементами
void ResultFileC(const char* FileName, int Y, int W);

/// Добавляет к результирующим данным двоичный файл со строковыми элементами
void ResultFileS(const char* FileName, int Y, int W);

/// Добавляет к результирующим данным текстовый файл
void ResultFileT(const char* FileName, int Y1, int Y2);

//-----------------------------------------------------------------------------

/// Связывает номер NP с указателем P
void SetPointer(int NP, PNode P);

/// Добавляет к исходным данным линейную динамическую структуру
void DataList(int NP, int X, int Y);

/// Добавляет к результирующим данным линейную динамическую структуру
void ResultList(int NP, int X, int Y);

/// Добавляет к исходным данным бинарное дерево
void DataBinTree(int NP, int X, int Y1, int Y2);

/// Добавляет к результирующим данным бинарное дерево
void ResultBinTree(int NP, int X, int Y1, int Y2);

/// Добавляет к исходным данным дерево общего вида
void DataTree(int NP, int X, int Y1, int Y2);

/// Добавляет к результирующим данным дерево общего вида
void ResultTree(int NP, int X, int Y1, int Y2);

/// Отображает в текущей динамической структуре указатель с номером NP
void ShowPointer(int NP);

/// Помечает в текущей результирующей динамической структуре указатель, требующий создания
void SetNewNode(int NNode);

/// Помечает в текущей исходной динамической структуре указатель, требующий удаления
void SetDisposedNode(int NNode);

//-----------------------------------------------------------------------------

/// Возвращает количество слов-образцов для языка, соответствующего текущей локали
int WordCount(); //116

/// Возвращает количество предложений-образцов для языка, соответствующего текущей локали
int SentenceCount(); //61

/// Возвращает количество текстов-образцов для языка, соответствующего текущей локали
int TextCount(); //85

/// Возвращает слово-образец с номером N (нумерация от 0) для языка, соответствующего текущей локали
char* WordSample(int N);

/// Возвращает предложение-образец с номером N (нумерация от 0) для языка, соответствующего текущей локали
char* SentenceSample(int N);

/// Возвращает текст-образец с номером N (нумерация от 0) для языка, соответствующего текущей локали,
/// между строками текста располагаются символы \r\n, в конце текста эти символы отсутствуют,
/// число строк не превышает MaxLineCount, между абзацами текста помещается одна пустая строка
char* TextSample(int N);

//-----------------------------------------------------------------------------

/// Возвращает количество английских слов-образцов
int EnWordCount(); //116

/// Возвращает количество английских предложений-образцов
int EnSentenceCount(); //61

/// Возвращает количество английских текстов-образцов
int EnTextCount(); //85

/// Возвращает английское слово-образец с номером N (нумерация от 0)
char* EnWordSample(int N);

/// Возвращает английское предложение-образец с номером N (нумерация от 0)
char* EnSentenceSample(int N);

/// Возвращает английский текст-образец с номером N (нумерация от 0),
/// между строками текста располагаются символы \r\n, в конце текста эти символы отсутствуют,
/// число строк не превышает MaxLineCount, между абзацами текста помещается одна пустая строка
char* EnTextSample(int N);

//-----------------------------------------------------------------------------

/// Добавляет строку комментария к текущей группе или подгруппе заданий
void CommentText(const char* S);

/// Добавляет комментарий из другой группы заданий (или ее подгруппы,
/// если ее второй параметр не является пустой строкой)
void UseComment(const char* GroupName, const char* SubgroupName);

/// Добавляет комментарий из другой группы заданий
void UseComment(const char* GroupName);

/// Устанавливает режим добавления комментария к подгруппе заданий
void Subgroup(const char* SubgroupName);

//-----------------------------------------------------------------------------

/// Процедура, обеспечивающая отображение динамических структур данных
/// в "объектном стиле" при выполнении заданий в среде PascalABC.NET
/// (при использовании других сред не выполняет никаких действий)
void SetObjectStyle();

//-----------------------------------------------------------------------------

/// Процедура для внутреннего использования при разработке заданий
extern "C" void __stdcall activate(const char* DllName);
extern "C" void __stdcall inittaskgroup();


//-----------------------------------------------------------------------------

/// Устанавливает текущий процесс для последующей передачи ему данных 
/// числовых типов (при выполнении задания в параллельном режиме)
void SetProcess(int ProcessRank);

//-----------------------------------------------------------------------------

#endif
