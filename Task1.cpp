#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<locale.h>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<numeric>
#include<bitset>

using namespace std;

vector <char> buk = { ' ', 'о', 'е', 'а', 'и', 'т', 'н', 'с', 'р', 'в', 'л', 'к', 'м', 'д', 'п', 'у', 'я', 'ы', 'з', 'ъ', 'б', 'г', 'ч', 'й', 'х', 'ж', 'ю', 'ш', 'ц', 'щ', 'э', 'ф' };

vector <string> bin = { "000", "001", "0100" ,"0101" ,"0110" ,"0111" ,"1000" ,"1001" ,"10100" ,"10101" ,"10110" ,"10111" , "11000" ,"110010" ,"110011" ,"110100" ,"110110" ,"110111" ,"111000" ,"111001" ,"111010" ,"111011" ,"111100" ,"1111010" ,"1111011" ,"1111100" ,"1111101" ,"11111100" ,"11111101" ,"11111110" ,"111111110" ,"111111111" };

string coding(string a, string b = "")
{
	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; j < buk.size(); j++)
		{
			if (a[i] == buk[j])
			{
				b += bin[j];
			}
		}
	}
	return b;
}

string decoding(string a, string c = "", string d = "")
{
	for (size_t i = 0; i < a.size(); i++)
	{
		c += a[i];
		for (size_t j = 0; j < bin.size(); j++)
		{
			if (c == bin[j])
			{
				if (c == "000")
				{
					d += buk[0];
					c = "";
				}
				else
				{
					d += buk[j];
					c = "";
					while (!j)
					{
						a.erase(a.begin());
					}
				}

			}
		}
	}
	return d;
}

string b = "";

void codingang(char a)
{
	bitset<8> bs{ (unsigned char)a };
	b += bs.to_string();
}

void decodingang(char a)
{
	bitset<8> bs{ (unsigned char)a };
	b += bs.to_ulong();
}

int main() {
	setlocale(LC_ALL, "Rus");

	string slovo = "решающее устройство";
	string slovoang = "hello world";
	string binkod = "1000011011111001000011001000001111000101100101110010111110111";
	cout << "\t Задание 1.1" << endl;
	cout << "Алгоритм кодирования Шеннона-Фано, строка для кодирования: " << "<<" << slovo << ">>" 
	    << endl << "Вид после кодирования: " << coding(slovo) << endl 
	    << "Декодирование: " << decoding(coding(slovo));
	
	cout << endl << endl << "\t Задание 1.2" << endl;

	cout << endl << "Декодирование строки: " << binkod;
	cout << endl << "Вид после декодирования: " << decoding(binkod) << endl;

	cout << endl << endl << "\t Задание 1.4" << endl;

	cout << "Английское слово: " << slovoang << endl << "Кодирование: ";
	for_each(slovoang.begin(), slovoang.end(), codingang);
	cout << b << endl;
	b = "";
	cout << "Декодирование: ";
	for_each(slovoang.begin(), slovoang.end(), decodingang);
	cout << b << endl;

	system("pause");
	return 0;
}

