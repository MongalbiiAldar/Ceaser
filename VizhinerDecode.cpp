#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include <fstream>
#include <iostream>
using namespace std;
#include <string.h>
#include <string>
char key[300];//����
char tmp[300];//��� ���������� �����
struct koord
{
	int a;
	int b;
};

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);//����������� �������� �����
	SetConsoleOutputCP(1251);//����������� �������� �����
	char line[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char tabula_recta[26][26];//������� ��������
	char vhod[300];//������� ���������
	int count=0;//����� �������� ���������
	int LenOfKey=0;//����� �����
	int ProverkaKey=0;//�������� ����� ��� ��� ����������
	
	
	//-������ �����������
	int TmpRect=0;
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			TmpRect=i+j;
			if (TmpRect >= 26) TmpRect = TmpRect % 26;
			tabula_recta[i][j]=line[TmpRect];
		}
	}

	//-���������� ������ �����
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			cout<<tabula_recta[i][j];
		}
		cout<<"\n";
	}
	
	//-------���������� �������� �����
	FILE *file;
	char *infile="infile.txt";
	file = fopen(infile,"r");
	
	//----����� �� ���������, ���� ���� �������� �����
	if (file==0) {
		cout<<"�������� ����� �� ����������\n";
		getch();
		return 0;
	}
	//-������,������� ����� �����
	char ch=0;
	int i=0;
	while(ch!=EOF)
	{
		ch=getc(file);
		if (ch!='\n' && ch!=EOF)
		{
			vhod[i]=ch;
			i++;
		}
	}
	cout<<"����� ����� �����: "<<i;
	count=i;

	//--�������� ��������� ������ ������ ���-�� �������� � ������� �����
	char* a=0;
	a=new char[i];

	//--��������� ��������� �������� ������� ����� �� ������ ����� � ������� ������� fseek
	fseek(file,0,SEEK_SET);
	
	//--���� � ������������ �����
	
	cout<<"������� ����:";
	gets(key);
	LenOfKey=strlen(key);
	for (int i = 0; i < LenOfKey; i++)
	{
		tmp[i]=key[i];
	}
	
	
	while(ProverkaKey<count)
	{
		for (int i = 0; i < LenOfKey; i++)
		{
			key[i+ProverkaKey]=tmp[i];
		}
		ProverkaKey=strlen(key);
	}


	
	
	
	//���������� ���������
	koord nabor[100];
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<26;j++)
		{
			if (line[j]==key[i])
			{
				nabor[i].a=j;
			}
		}
	}
	
	
	char Coding[100];
	for(int ii=0;ii<count;ii++)
	{
		for(int i=0;i<26;i++)
		{
			if (i==nabor[ii].a)
			{
				for(int j=0;j<26;j++)
				{
					if (tabula_recta[i][j]==vhod[ii])
					{
						//cout<<tabula_recta[i][j];
						Coding[ii]=j;
					}
				}
			}
		}
	}

	//�������� ��������� �����
	//-------���������� �������� �����
	FILE *file2;
	char *outfile="outfile.txt";
	file2 = fopen(outfile,"w");
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<26;j++)
		{
			if (Coding[i]==j)
			{
				putc(line[j],file2);
			}
		}
	}
	
	getch();
	return 0;
}

