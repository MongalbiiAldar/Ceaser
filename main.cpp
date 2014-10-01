#include <vector>
#include <iostream>
#include <fstream>
#include "des.h"

using namespace std;

// считать байты из файла filename в вектор
vector<unsigned char> readFile(char* fileName)
{
	vector<unsigned char> input;
	ifstream ifst(fileName, ios::binary);
	if (ifst.fail())
		return input;

	ifst.seekg(0, ios::end);
	int size = ifst.tellg();
	ifst.seekg(0, ios::beg);

	input.resize(size);
	ifst.read((char*)&input.front(), size);
	ifst.close();

	return input;
}


int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Wrong arguments!" << endl;
		cout << "des <input file> <output file> <key file> {d | e}" << endl;
		cout << "\t d - decode" << endl;
		cout << "\t e - encode" << endl;
		return 1;
	}

	// считываем входные данные
	vector<unsigned char> input = readFile(argv[1]);
	if (input.empty())
	{
		cerr << "Can't read input file" << endl;
		return 1;
	}

	// считываем ключ, который должен быть ровно 8 байтным
	vector<unsigned char> key = readFile(argv[3]);
	if (key.size() != 8)
	{
		cerr << "Key must be 8 byte!" << endl;
		return 1;
	}

	vector<unsigned char> output;
	bool encode = (argv[4][0] == 'e'); // что необходимо - шифрование или дешифрование?
	if (encode)
	{
		// шифрование происходит по 8 байт
		// поэтому надо в конце выровнять нулями длинну до кратного 8
		// а сколько нулей пришлось добавить - запишем в начало выходного файла
		output.push_back(8 - input.size() % 8);
		input.insert(input.end(), 8 - input.size() % 8, 0);

		// разбиваем на блоки по 8 байт
		for (int i = 0; i < input.size() / 8; i++)
		{
			vector<unsigned char> input8; 
			input8.insert(input8.end(), input.begin() + i * 8, input.begin() + (i + 1) * 8);

			vector<unsigned char> crypted = des(input8, key, encode); // само шифрование

			output.insert(output.end(), crypted.begin(), crypted.end());
		}
	}
	else
	{
		// аналогично шифрованию
		// только в первом байте записано количество нулей, которые были добавлены при шифровании
		int num0 = input[0];
		vector<unsigned char> temp;
		temp.insert(temp.begin(), input.begin() + 1, input.end());
		input = temp;

		for (int i = 0; i < input.size() / 8; i++)
		{
			vector<unsigned char> input8;
			input8.insert(input8.end(), input.begin() + i * 8, input.begin() + (i + 1) * 8);

			vector<unsigned char> decrypted = des(input8, key, encode);
			output.insert(output.end(), decrypted.begin(), decrypted.end());
		}

		// избавляемся от лишних нулей в конце сообщения
		for (int i = 0; i < num0; i++)
			output.pop_back();
	}

	ofstream outStream(argv[2], ios::binary);
	outStream.write((char*)&output.front(), output.size());
	outStream.close();

	return 0;
}