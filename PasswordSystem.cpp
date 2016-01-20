#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include "md5.h"
#include "windows.h"
#include "stddef.h"

using namespace std;

int main()
{
	MD5 md5;

	int choose;

	cout << "1 - registration;" << endl << "2 - logon" << endl << endl;
	cin >> choose;

	//РЕГИСТРАЦИЯ НОВОГО ПОЛЬЗОВАТЕЛЯ
	if(choose==1)
	{
		std::string login, password, passwordAgain;
		cout << "Enter login: ";
		cin >> login;
		cout << endl << "Enter password: ";
		cin >> password;
		cout << endl << "Enter password again: ";
		cin >> passwordAgain;
		cout << endl;

		if(password!=passwordAgain) cout << "ERROR: password!" << endl;
		else
		{

			char* log = &login[0];
			char* pass = &password[0];

			ifstream DataBase("login.txt", ios_base::in); // открываем файл для чтения

			std::string l;
			int flagLogin=1;
			while(DataBase.peek()!=EOF)
			{
				std::getline(DataBase, l);
				if(md5.digestString(log)==l) flagLogin=0;
			}
			DataBase.close();

			if(flagLogin==0) cout << "ERROR: choose other login!" << endl;
			else
			{
				ofstream DataBaseLog("login.txt", ios_base::app); // открываем файл для записи в конец
				DataBaseLog << md5.digestString(log) << endl << endl;
				DataBaseLog.close();

				ofstream DataBasePas("password.txt", ios_base::app); // открываем файл для записи в конец
				DataBasePas << md5.digestString(pass) << endl << endl;
				DataBasePas.close();

				cout << "REGISTRATION COMPLETE!" << endl;
			}

		}

	}

	//ВХОД В СИСТЕМУ ЗАРЕГИСТРОВАННОГО ПОЛЬЗОВАТЕЛЯ
	else if(choose==2)
	{
		std::string login, password;
		cout << "Enter login: ";
		cin >> login;
		cout << endl << "Enter password: ";
		cin >> password;

		char* log = &login[0];
		char* pass = &password[0];

		ifstream DataBaseR("login.txt", ios_base::in); // открываем файл для чтения

		std::string l;
		int flagLogin=0, k, i=0;
		while(DataBaseR.peek()!=EOF)
		{
			std::getline(DataBaseR, l);
			if(md5.digestString(log)==l) 
			{
				k=i;
				flagLogin=1;
			}
			i++;
		}
		DataBaseR.close();

		if(flagLogin==0) cout << "ERROR: login!" << endl;
		else
		{
			ifstream DataBaseP("password.txt", ios_base::in); // открываем файл для чтения

			std::string p;
			int flagP=0;
			i=0;
			while(DataBaseP.peek()!=EOF)
			{
				std::getline(DataBaseP, p);
				if(md5.digestString(pass)==p) 
				{
					if(i==k)
					flagP=1;
				}
				i++;
			}
			DataBaseP.close();

			if(flagP==0) cout << "ERROR: password!" << endl << endl;
			else
			{
				//SetFileAttributes("D:\\Testing",!FILE_ATTRIBUTE_HIDDEN); //Сделали видимым
				//дешифрование файлов
							ofstream out ("out.txt");
							WIN32_FIND_DATA FindFileData;
							HANDLE hf;
							int k=0, kol=0;
							hf=FindFirstFile("D:\\Testing\\*", &FindFileData);
							if (hf!=INVALID_HANDLE_VALUE){
								do
								{
									k++;
									if(k>2)
									{
										out << FindFileData.cFileName << " - " << "\n";
										kol++;
									}

								}
								while (FindNextFile(hf,&FindFileData)!=0);
								FindClose(hf);
							}
							out.close();

							ifstream in("out.txt");

							char cc;
							std::string filename; 
							filename+="D:\\Testing\\";
							while(in >> cc)
							{
								if(cc=='-')
								{
									//std::printf("%s", filename.c_str());
									//cout << endl;
									ifstream inputF(filename.c_str(),ios_base::in);
									ofstream outputF("temp.txt", ios_base::trunc);

									unsigned char ci;
									int count=0;
									while(inputF >> ci)
									{
										ci = ci - 1;
										outputF << ci;
									}
									outputF.close();
									inputF.close();

									ofstream outp(filename.c_str(),ios_base::out | ios_base::trunc);
									ifstream inp("temp.txt");

									while (inp >> ci)
										outp << ci;

									inp.close();
									outp.close();
									filename="";
									filename+="D:\\Testing\\";
								}
								else filename+=cc;

							}
							in.close();

				cout << endl << "You are log on!" << endl << "/Data are available and decrypted/" << endl << endl
					<< "press 0 to exit from the system" << endl;
				std::string closer="1";
		
			flag:
				std::scanf("%s", closer.c_str());
				if(closer=="0")
				{
				//шифрование файлов
								ofstream out ("out.txt");
								WIN32_FIND_DATA FindFileData;
								HANDLE hf;
								int k=0, kol=0;
								hf=FindFirstFile("D:\\Testing\\*", &FindFileData);
								if (hf!=INVALID_HANDLE_VALUE){
									do
									{
										k++;
										if(k>2)
										{
											out << FindFileData.cFileName << " - " << "\n";
											kol++;
										}

									}
									while (FindNextFile(hf,&FindFileData)!=0);
									FindClose(hf);
								}
								out.close();

								ifstream in("out.txt");

								char cc;
								std::string filename; 
								filename+="D:\\Testing\\";
								while(in >> cc)
								{
									if(cc=='-')
									{
										//std::printf("%s", filename.c_str());
										//cout << endl;
										ifstream inputF(filename.c_str(),ios_base::in);
										ofstream outputF("temp.txt", ios_base::trunc);

										unsigned char ci;
										int count=0;
										while(inputF >> ci)
										{
											ci = ci + 1;
											outputF << ci;
										}
										outputF.close();
										inputF.close();

										ofstream outp(filename.c_str(),ios_base::out | ios_base::trunc);
										ifstream inp("temp.txt");

										while (inp >> ci)
											outp << ci;

										inp.close();
										outp.close();
										filename="";
										filename+="D:\\Testing\\";
									}
									else filename+=cc;

								}
								in.close();

				//SetFileAttributes("D:\\Testing",FILE_ATTRIBUTE_HIDDEN); //Скрыли
				cout << endl << "You are logged off" << endl << endl;
				}
				else 
				{
					cout <<endl << "ERROR! Press 0 to exit!" << endl;
					closer="1";
					goto flag;
				}
			}
		}
	}

	else cout << "ERROR: incorrect number!" << endl << endl;
	system("pause");
	return 0;
}