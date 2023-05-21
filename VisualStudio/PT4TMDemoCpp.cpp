#include <string>
#include <fstream>
#include "pt4taskmaker.h"

void MakerDemo3()
{
  CreateTask("Ввод и вывод данных, оператор присваивания");
  TaskText("Даны стороны прямоугольника~{a} и~{b}.", 0, 2);
  TaskText("Найти его площадь {S}~=~{a}\\*{b} и периметр {P}~=~2\\*({a}\\;+\\;{b}).", 0, 4);
  double a = RandomN(1, 99) / 10.0,
    b = RandomN(1, 99) / 10.0;
  DataR("a = ", a, xLeft, 3, 4);
  DataR("b = ", b, xRight, 3, 4);
  ResultR("S = ", a * b, 0, 2, 4);
  ResultR("P = ", 2 * (a + b), 0, 4, 4);
  SetTestCount(3);
}

void MakerDemo4()
{
  CreateTask("Двумерные массивы (матрицы): вывод элементов");
  TaskText("Дана матрица размера~{M}\\;\\x\\;{N} и целое число~{K} (1~\\l~{K}~\\l~{M}).", 0, 2);
  TaskText("Вывести элементы {K}-й строки данной матрицы.", 0, 4);
  int m = RandomN(2, 5), n = RandomN(4, 8), k = 1;
  if (m == 5) 
    k = 0;
  DataN("M = ", m, 3, 1, 1);
  DataN("N = ", n, 10, 1, 1);
  double a[5][8];
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
    {
      a[i][j] = RandomR(-9.99, 9.99);
      DataR(a[i][j], Center(j+1, n, 5, 1), i + k + 1, 5);
    }
  k = RandomN(1, m);
  DataN("K = ", k, 68, 5, 1);
  for (int j = 0; j < n; j++)
    ResultR(a[k-1][j], Center(j+1, n, 5, 1), 3, 5);
  SetTestCount(5);
}

void MakerDemo5()
{
  CreateTask("Символы и строки: основные операции");
  TaskText("Дана непустая строка~{S}.", 0, 2);
  TaskText("Вывести ее первый и последний символ.", 0, 4);
  char* s = WordSample(RandomN(0, WordCount() - 1));
  if (CurrentTest() == 3)
    while (s[0] == s[strlen(s)-1])
      s = WordSample(RandomN(0, WordCount() - 1));
  DataS("S = ", s, 0, 3);
  ResultC("Первый символ: ", s[0], xLeft, 3);
  ResultC("Последний символ: ", s[strlen(s)-1], xRight, 3);
  SetTestCount(4);
}

const string c = "0123456789abcdefghijklmnopqrstuvwxyz";

string FileName(int Len)
{
  string result = "";
  int L = c.length();
  for (int i = 0; i < Len; i++)
    result = result + c[RandomN(0, L - 1)];
  return result;
}

void ConvertToPascalStr(string s, char buf[256])
{
  buf[0] = (char)s.length();
  for (size_t i = 1; i <= s.length(); i++)
    buf[i] = s[i-1];
}

void MakerDemo6()
{
  CreateTask("Символьные и строковые файлы");
  TaskText("Дано целое число~{K} (>\\,0) и строковый файл.\n"
  "Создать два новых файла: строковый, содержащий первые {K}~символов\n"
  "каждой строки исходного файла, и символьный, содержащий {K}-й символ\n"
  "каждой строки (если длина строки меньше~{K}, то в строковый файл\n"
  "записывается вся строка, а в символьный файл записывается пробел).");
  string s1 = "1" + FileName(5) + ".tst",   
    s2 = "2" + FileName(5) + ".tst",
    s3 = "3" + FileName(5) + ".tst";
  fstream fs1(s1.c_str(), ios_base::binary | ios_base::out),
    fs2(s2.c_str(), ios::binary | ios_base::out),
    fc3(s3.c_str(), ios::binary | ios_base::out);
  int k = RandomN(2, 11), jmax = 0, n = RandomN(10, 20);
  for (int i = 0; i < n; i++)
  {
    char buf[256];
    int j = RandomN(2, 16);
    if (jmax < j)
      jmax = j;
    string s = FileName(j);
    ConvertToPascalStr(s, buf);
    fs1.write(buf, 256);
    char c = ' ';
    if (j >= k)
    {
      c = s[k-1];
      buf[0] = (char)k;
    }
    fs2.write(buf, 256);
    fc3.write((char*) &c, 1);
  }
  fs1.close();
  fs2.close();
  fc3.close();            
  DataN("K = ", k, 0, 1, 1);
  DataS("Имя исходного файла: ", s1.c_str(), 3, 2);
  DataS("Имя результирующего строкового файла:  ", s2.c_str(), 3, 4);
  DataS("Имя результирующего символьного файла: ", s3.c_str(), 3, 5);
  DataComment("Содержимое исходного файла:", xRight, 2);
  DataFileS(s1.c_str(), 3, jmax + 3);
  ResultComment("Содержимое результирующего строкового файла:", 0, 2);
  ResultComment("Содержимое результирующего символьного файла:", 0, 4);
  ResultFileS(s2.c_str(), 3, k + 3);
  ResultFileC(s3.c_str(), 5, 4);
}

void MakerDemo7()
{
  CreateTask("Текстовые файлы: основные операции");
  TaskText("Дан текстовый файл.", 0, 2);
  TaskText("Удалить из него все пустые строки.", 0, 4);
  string s1 = FileName(6) + ".tst",
    s2 = "#" + FileName(6) + ".tst", 
    s = TextSample(RandomN(0, TextCount() - 1));
  ofstream t2(s2.c_str()), t1(s1.c_str());
  t2 << s << endl;
  t2.close();
  char* s0 = const_cast < char*>("\r\n\r\n");
  size_t p = s.find(s0);
  while (p != string::npos)
  {
    s.erase(p, 2);
    p = s.find(s0);
  }
  t1 << s << endl;
  t1.close();
  ResultFileT(s1.c_str(), 1, 5);
  rename(s2.c_str(), s1.c_str());
  DataFileT(s1.c_str(), 2, 5);
  DataS("Имя файла: ", s1.c_str(), 0, 1);
  SetTestCount(3);
}

TNode WrongNode;

void MakerDemo8Data()
{
  int n = 1;
  if (RandomN(1, 4) != 1)
    n = RandomN(2, 9);
  switch (CurrentTest())
  {
  case 2:
    n = 1;
    break;
  case 4:
    n = RandomN(2, 9);
    break;
  }
  PNode p1 = new TNode;
  p1->Data = RandomN(10, 99);
  p1->Prev = NULL;
  PNode p2 = p1, p;
  for (int i = 2; i <= n; i++)
  {
    p = new TNode;
    p->Data = RandomN(10, 99);
    p->Prev = p2;
    p2->Next = p;
    p2 = p;
  }
  p2->Next = NULL;
  SetPointer(1, p1);
  SetPointer(2, p2);
  ResultP("Последний элемент: ", 2, 0, 2);
  ResultList(1, 0, 3);
  ShowPointer(2);
  DataP(1, 0, 2);
  p = p1;
  for (int i = 1; i <= n; i++)
  {
    p->Prev = &WrongNode;
    p = p->Next;
  }
  DataList(1, 0, 3);
  ShowPointer(1);
}

void MakerDemo8()
{
  CreateTask("Динамические структуры данных: двусвязный список");
  TaskText("Дан указатель~{P}_1 на начало непустой цепочки элементов-записей типа TNode,", 0, 1);
  TaskText("связанных между собой с помощью поля Next. Используя поле Prev записи TNode,", 0, 2);
  TaskText("преобразовать исходную (\\Iодносвязную\\i) цепочку в \\Iдвусвязную\\i, в которой каждый", 0, 3);
  TaskText("элемент связан не только с последующим элементом (с помощью поля Next),", 0, 4);
  TaskText("но и с предыдущим (с помощью поля Prev). Поле Prev первого элемента положить", 0, 5);
  TaskText("равным \\N. Вывести указатель на последний элемент преобразованной цепочки.", 0, 0);
  MakerDemo8Data();
}

void MakerDemo8Obj()
{
  CreateTask("Динамические структуры данных: двусвязный список");
  TaskText(
  "Дана ссылка~{A}_1 на начало непустой цепочки элементов-объектов типа Node,\n"
  "связанных между собой с помощью своих свойств Next. Используя свойства Prev\n"
  "данных объектов, преобразовать исходную (\\Iодносвязную\\i) цепочку в \\Iдвусвязную\\i,\n"
  "в которой каждый элемент связан не только с последующим элементом (с помощью\n"
  "свойства Next), но и с предыдущим (с помощью свойства Prev). Свойство Prev\n"
  "первого элемента положить равным \\O. Вывести ссылку~{A}_2 на последний\n"
  "элемент преобразованной цепочки."
  );
  SetObjectStyle();
  MakerDemo8Data();
}

void _stdcall InitTask(int num)
{
  switch (num)  
  {
    case 1:
      UseTask("Begin", num); break;
    case 2:
      UseTask("Begin", num); break;
    case 3:
      MakerDemo3(); break;
    case 4:
      MakerDemo4(); break;
    case 5:
      MakerDemo5(); break;
    case 6:
      MakerDemo6(); break;
    case 7:
      MakerDemo7(); break;
    case 8:
      if ((CurrentLanguage() & lgWithPointers) != 0)
        MakerDemo8();
      else
        MakerDemo8Obj();
      break;
    case 9:
      MakerDemo8Obj(); break;
  }
}

void _stdcall inittaskgroup()
{
  int n = 7;
  if (CurrentLanguage() == lgPascalABCNET)
    n = 9;
  else
  if ((CurrentLanguage() & (lgWithPointers | lgWithObjects)) != 0)
    n = 8;
  CreateGroup("TMDemoCpp", "Примеры различных задач (конструктор для языка C++)", 
    "М. Э. Абрамян, 2014", "qwqfsdf13dfttd", n, InitTask);
  CommentText("Данная группа демонстрирует различные возможности");
  CommentText("\\Iконструктора учебных заданий\\i \\MPT4TaskMaker\\m для языка C++. ");
  Subgroup("Ввод и вывод данных, оператор присваивания");
  CommentText("В этой подгруппе содержатся задания, импортированные");
  CommentText("из группы Begin.\\PПриводимый ниже абзац преамбулы");
  CommentText("также импортирован из данной группы.\\P");
  UseComment("Begin");
  Subgroup("Двумерные массивы (матрицы): вывод элементов");
  CommentText("Данное задание дублирует задание Matrix7.");
  Subgroup("Символьные и строковые файлы");
  CommentText("Данное задание дублирует задание File63.");
  CommentText("Оно демонстрирует особенности, связанные с двоичными");
  CommentText("\\Iстроковыми\\i файлами. ");
  Subgroup("Текстовые файлы: основные операции");
  CommentText("Данное задание дублирует задание Text16. ");
  Subgroup("Динамические структуры данных: двусвязный список");
  CommentText("Данное задание дублирует задание Dynamic30.");
  CommentText("\\PЗадание реализовано в двух вариантах: основанном на использовании указателей");
  CommentText("(для языков Pascal и C++) и основанном на использовании объектов (для языков платформы");
  CommentText(".NET, а также Python, Java и Ruby). Для языка Visual Basic это задание недоступно.");
  CommentText("В системе PascalABC.NET доступны оба варианта задания.");
}
