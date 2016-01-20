#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <string.h>

//word, word2 - �������� ����� � ������ ����������	
//text - �������� ����� 

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
	
	char alph[32] ={'�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', 
					'�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�'};
	
	char alph1[16]={'�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�'};
	char alph2[16]={'�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�'};

	fstream in ("open.txt");
	while(!in.eof())
	{
		in >> word;
		for(int i = 0; i<word.size(); i ++)
		{
			k = 0;
			for(int j = 0; j < 32; j ++)
			{
				//���� ����� ����� �� ��������� ����� ���� � ����� ��������
				if(alph[j] == word[i]) {k = 1;}
				if(k == 1) {text.push_back(word[i]); k = 0;} //��������� � � ������ text
			}
		}
	}

	out << "�������� �����: " << text << endl;

	fstream in2 ("password.txt");
	while(!in2.eof())
	{
		in2 >> word2;
		for(int i = 0; i < word2.size(); i ++)
		{
			k = 0;
			for(int j = 0; j < 32; j ++)
			{
				//���� ������� ������ - ������� �����, �� ��������� � ������ pass
				if(alph[j]==word2[i]) {k = 1;}
				if(k == 1) {pass.push_back(word2[i]); k = 0;}
			}
		}
	}

	string password;//������ ������ �������� � ��
	int h = 0;
	for(int i = 0; i < text.size(); i ++)
	{
		if(h == pass.size()) {h = 0;}
		password.push_back(pass[h]);
		h++;
	}

	out << endl << "������: " << password <<endl;

	int num, l;
	string shifr;//�� �������������

	if(choose==0){
	for(int i = 0; i < password.size(); i ++)
	{
		for(int j = 0; j < 32; j ++)
		{
			if(password[i] == alph[j])//���� ������ ������ ����� ������� ��������
			{
				if(j == 0) {j = 1;} else {l = j / 2;}//����������� ������
				for(int k = 0; k < 16; k ++)
				{
					num = 0;
					//���� ����� ��������� ������ ��������� � ������ ������, 
					//�� ������ ��� � ������������ ������ �� ������ ������
					if(text[i] == alph1[k])
					{
						num = k + l;
						while(num > 15) {num = num - 16;}//�����
						shifr.push_back(alph2[num]);
					}
					if(text[i] == alph2[k])
					{
						num = k + 16 - l;
						while(num > 15) {num = num - 16;}//����� ��� ������ ������
						shifr.push_back(alph1[num]);
					}
				}
			}
		}
	}

	out << endl << "����������: " << shifr << endl;
	}
	
	if(choose==1){

	//������������
	string deshifr;  //��
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

	out << endl << "�����������E: " << deshifr << endl;
}

	out.close();
}
