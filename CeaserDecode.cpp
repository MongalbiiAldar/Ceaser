// CaesarCode.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include "windows.h"
#include <fstream>
#include "conio.h"
#include <iostream>
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);//����������� �������� �����
	SetConsoleOutputCP(1251);//����������� �������� �����
	char text[100000];
	char  ch;
	//-----������ �����
	std::ifstream f("outfile.txt");
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

	cout<<"���������� ������� ����:";
	cin>>key;
	
	//--�������� ������� ��������������(����� �� ������ ������ ��� ������� �� ���������� �������)
	//������� - ��� asci
	key=(key+256)%256;
	
	f.seekg(0);
	//--������ ������� ����� ������� ������� �� �����, ������� ������ ������������ � �������� ��� ��� � �������
	int count=i;
	for(int i=0;i<count;i++)
	{
		text[i]=text[i]-key;
	}
	
	std::ofstream outfile("OutfileIshod.txt");
	for(int i=0;i<count;i++)
	{
		outfile.put(text[i]);
	}
	
	getch();
	return 0;
}

