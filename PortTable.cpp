#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <string.h>

//word, word2 - открытый текст и пароль побуквенно	
//text - открытый текст 

using namespace std;

int main()
{


	ofstream out("output.txt");

	fstream sh ("Choose.txt");
	int choose;
	sh >> choose;
	sh.close();

	string word, word2, text, pass;
	int k;
	setlocale(LC_ALL, "Russian");
	
	char alph[32] ={'а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 
					'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ь', 'ы', 'ъ', 'э', 'ю', '€'};
	
	char alph1[16]={'а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п'};
	char alph2[16]={'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ь', 'ы', 'ъ', 'э', 'ю', '€'};

	fstream in ("open.txt");
	while(!in.eof())
	{
		in >> word;
		for(int i = 0; i<word.size(); i ++)
		{
			k = 0;
			for(int j = 0; j < 32; j ++)
			{
				//если буква слова из открытого текст есть в нашем алфавите
				if(alph[j] == word[i]) {k = 1;}
				if(k == 1) {text.push_back(word[i]); k = 0;} //добавл€ем еЄ в вектор text
			}
		}
	}

	out << "ќ“ –џ“џ… “≈ —“: " << text << endl;

	fstream in2 ("password.txt");
	while(!in2.eof())
	{
		in2 >> word2;
		for(int i = 0; i < word2.size(); i ++)
		{
			k = 0;
			for(int j = 0; j < 32; j ++)
			{
				//если символы парол€ - русские буквы, то добавл€ем в вектор pass
				if(alph[j]==word2[i]) {k = 1;}
				if(k == 1) {pass.push_back(word2[i]); k = 0;}
			}
		}
	}

	string password;//делаем пароль размером с ќ“
	int h = 0;
	for(int i = 0; i < text.size(); i ++)
	{
		if(h == pass.size()) {h = 0;}
		password.push_back(pass[h]);
		h++;
	}

	out << endl << "ѕј–ќЋ№: " << password <<endl;

	int num, l;
	string shifr;//ќ“ зашифрованный

	if(choose==0){
	for(int i = 0; i < password.size(); i ++)
	{
		for(int j = 0; j < 32; j ++)
		{
			if(password[i] == alph[j])//если символ парол€ равен символу алфавита
			{
				if(j == 0) {j = 1;} else {l = j / 2;}//определени€ сдвига
				for(int k = 0; k < 16; k ++)
				{
					num = 0;
					//если симол открытого текста находитс€ в первой строке, 
					//то ставим ему в соответствие символ из второй строки
					if(text[i] == alph1[k])
					{
						num = k + l;
						while(num > 15) {num = num - 16;}//сдвиг
						shifr.push_back(alph2[num]);
					}
					if(text[i] == alph2[k])
					{
						num = k + 16 - l;
						while(num > 15) {num = num - 16;}//сдвиг дл€ второй строки
						shifr.push_back(alph1[num]);
					}
				}
			}
		}
	}

	out << endl << "Ў»‘–ќ¬јЌ»≈: " << shifr << endl;
	}
	
	if(choose==1){

	//ƒешифрование
	string deshifr;  //ќ“
	for(int i = 0; i < text.size(); i ++)
	{
		for(int j = 0; j < 32; j ++)
		{
			if(password[i] == alph[j])
			{
				if(j == 0) {j = 1;} else {l = j / 2;}
				for(int k = 0; k < 16; k ++)
				{
					num = 0;
					if(text[i] == alph1[k])
					{
						num = k + l;
						while(num > 15) {num = num - 16;}
						deshifr.push_back(alph2[num]);
					}
					if(text[i] == alph2[k])
					{
						num = k + 16 - l;
						while(num > 15) {num = num - 16;}
						deshifr.push_back(alph1[num]);
					}
				}
			}
		}
	}

	out << endl << "ƒ≈Ў»‘–ќ¬јЌ»E: " << deshifr << endl;
}

	out.close();
}
