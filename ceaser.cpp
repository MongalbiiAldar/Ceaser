#include "stdafx.h"
#include "windows.h"
#include <fstream>
#include "conio.h"
#include <iostream>
using namespace std;

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);//подключение русского языка
	SetConsoleOutputCP(1251);//подключение русского языка
	char text[100000];
	char  ch;
	//-----чтение файла
	std::ifstream f("infile.txt");
	int i=0;
	if( f )
    {
        
        while( f.get(ch) )
        {
            std::cout << ch;
			text[i]=ch;
			i++;
        }
    }
	
	int key=0;

	cout<<"Пожалуйста введите ключ:";
	cin>>key;
	
	//--согласно формуле преобразования(берем по модулю потому что алфавит не бесконечно большой)
	//алфавит - это asci
	key=(key+256)%256;
	
	f.seekg(0);
	//--теперь сделаем сдвиг каждого символа по ключу, который выбрал пользователь и сохраним все это в массиве
	int count=i;
	for(int i=0;i<count;i++)
	{
		text[i]=text[i]+key;
	}
	
	std::ofstream outfile("outfile.txt");
	for(int i=0;i<count;i++)
	{
		outfile.put(text[i]);
	}
	getch();
	return 0;
}

