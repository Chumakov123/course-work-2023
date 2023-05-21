#include <string>
#include "pt4taskmaker.h"

void Task1()
{
  CreateTask();
  TaskText("\\SAdd.\\s Write a function that returns the sum of two numbers.\n"
  "\\P\\BExample.\\b For \\Mparam1~=~1\\m and \\Mparam2~=~2\\m, the output should be \\M3\\m."
  );
  int a = RandomN(-99, 100),
    b = RandomN(-99, 100);
  switch (CurrentTest())
  {
  case 1:
      a = 1; b = 2; break;
  }
  DataN("param1 = ", a, xLeft, 1, 1);
  DataN("param2 = ", b, xRight, 1, 1);
  ResultN(a + b, 0, 1, 4);
  SetTestCount(3);
}

void Task2()
{
    CreateTask();
    TaskText("\\SCenturyFromYear.\\s Given a year, return the century it is in.\n"
    "The first century spans from the year 1 up to and including the year 100,\n" 
    "the second \\= from the year 101 up to and including the year 200, etc.\n"
    "\\P\\BExample.\\b For \\Myear~=~1905\\m, the output should be \\M20\\m;\n"
    "for \\Myear~=~1700\\m, the output should be \\M17\\m.\n"
    "\\PA \\Myear\\m is a positive integer, \\M1~\\l~year~\\l~2005\\m."
    );
    int y = RandomN(1, 2005);
    switch (CurrentTest())
    {
    case 1:
        y = 1905;
        break;
    case 2:
        y = 1700;
        break;
    case 5: case 7:
        y = RandomN(1, 20) * 100;
    }
    DataN("year = ", y, 0, 1, 1);
    ResultN((y - 1) / 100 + 1, 0, 1, 4);
    SetTestCount(9);
}

bool isPalindrome(string s)
{
    int n = s.length();
    for (int i = 0; i < n / 2; i++)
        if (s[i] != s[n - 1 - i])
            return false;
    return true;
}

void Task3()
{
    CreateTask();
    TaskText("\\SCheckPalindrome.\\s Given the string, check if it is a palindrome.\n"
"\\P\\BExample.\\b For \\M\"aabaa\"\\m, the output should be \\t; for \\M\"abac\"\\m,\n" 
"the output should be \\f; for \\M\"a\"\\m, the output should be \\t.\n"
"\\PAn \\MinputString\\m is a non-empty string consisting of lowercase characters,\n" 
"\\MinputString.length~<~80\\m."
    );
    string s;
    bool res;
    switch (CurrentTest())
    {
    case 1:
        s = "aabaa";
        res = true;
        break;
    case 2:
        s = "aaac";
        res = false;
        break;
    case 3:
        s = "a";
        res = true;
        break;
    case 5:
        res = true;
        break;
    case 7:
        res = false;
    default:
        res = RandomN(0, 1) == 1;
        break;
    }
    if (s == "")
    {
        int n = RandomN(3, 30);
        string s1, s2;
        for (int i = 0; i < n; i++)
        {
            char c = RandomN('a', 'z');
            s1 = s1 + c;
            s2 = c + s2;
        }
        if (RandomN(0, 1) == 1)
            s = s1 + (char)RandomN('a', 'z') + s2;
        else
            s = s1 + (char)RandomN('a', 'z') + s2;
        n = s.length();
        if (!res)
            while (true)
            {
                for (int i = 0; i < 3; i++)
                    s[RandomN(0, n - 1)] = RandomN('a', 'z');
                if (!isPalindrome(s))
                    break;
            }
    }
    DataS("inputString: ", s.c_str(), 0, 1);
    ResultB(res, 0, 1);
    SetTestCount(9);
}

void __stdcall InitTask(int num)
{
  switch (num)  
  {
    case 1:  
        Task1(); break;
    case 2:
        Task2(); break;
    case 3:
        Task3(); break;
  }
}

void __stdcall inittaskgroup()
{
  CreateGroup("CodeDemo", "Intro. The Journey Begins",
    "", "qwqfsdf13dfttd", 2, InitTask);
}
