#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include <cmath>

using namespace std;

int factor_digits(long long num, int *digits, int limit)
{
    int digits_count = 0;
    // Последовательно извлекаем цифры числа, пока они есть
    while (num > 0 && limit) {
        // Копируем очередную цифру в массив
        digits[digits_count++] = num % 10;
        // Переходим к следующей цифре
        num /= 10;
        // Уменьшаем допустимое количество оставшихся цифр
        limit--;
   }
   return num ? 0 : digits_count;
}

// Алгоритм Евклида. 
// Алгоритм для нахождения наибольшего общего делителя двух целых чисел. 
// Используется для проверки чисел на взаимопростоту
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}


//проверка на простоту чисел p и q
bool isPrime (int a) {
	int i=1;
	bool isPrime=true;
	for (int i=2; i<sqrt((float)a); i++) {
		if (a%i==0) 
		{
			int i=0;
			return false;
			break;
		}
	}
	if(i==1) return true;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	ifstream pq("pq.txt");
	int p,q;
	pq >> p >> q;
	pq.close();

	bool flagP, flagQ;
	flagP=isPrime(p);
	flagQ=isPrime(q);

	if(p==4 || q==4) flagP=false;

	if(flagP==false || flagQ==false)
	{cout << "ОШИБКА: P и Q должны быть простыми!" <<endl;}
	else 
	{
		  int n = p*q;

		//Генерация числа d и проверка его на взаимопростоту
		//с числом ((p-1)*(q-1))
		int d, d_simple = 0;
		while (d_simple !=1)
		{
			d = rand()%100;
			d_simple = gcd (d, ((p-1)*(q-1)));
		}

		//Определение числа e, для которого является истинным
		//соотношение (e*d)%((p-1)*(q-1))=1
		  int e = 0, e_simple = 0;
		while (e_simple !=1)
		{
			e += 1;
			e_simple = (e*d)%((p-1)*(q-1));
		}

		ifstream in("input.txt");
		ofstream out("res.txt");
		//Сгенерированные ключи
		out << "{" << d << ", " << n << "}" << " - Открытый ключ" << endl;
		out << "{" << e << ", " << n << "}" << " - Закрытый ключ" << endl << endl;	

		string inText;
		in >> inText;
		int MAX = inText.size();
		out << "ОТ(символы): " << endl << inText << endl;

		char* Text = &inText[0];
		  int * TextNUM = new   int[100];

		char * alph = new char[70];
		int * alphNum = new int [80];	
		
		ifstream inp("alphabet.txt");
		char cc;
		int tt = 0;
		while (inp >> cc)
		{
			alph[tt] = cc;
			tt++;
		}
		inp.close();

		int t1=0, t2=11;
		while(t2 <= 87) {
			alphNum[t1]=t2;
			t1++;
			t2++;
		}


		for(int i=0; i<MAX; i++)
		{
			for(int j=0; j<tt; j++)
				if(Text[i] == alph[j]) 
					TextNUM[i] = alphNum[j];
		}

		// Деление ОТ на блоки, где m[i]<n
		int * masBlock = new   int [200];
		int t = 0, kt=0;
		long long tempr=TextNUM[0];

		//считываем в одно число
		for(int i=1; i<MAX; i++)
		{
			tempr=tempr*100+TextNUM[i];
			kt+=2;
		}

		int factored_number[100];    // Массив для хранения результата
		int factored_number_len;    // Количество цифр в числе

		int num[100];
		// Выполняем разложение
		factored_number_len = factor_digits(tempr, factored_number, kt+2);


		int a=0;
		for(int i = kt; i >= 0; i--)
		{
			num[a]=factored_number[i];
			a++;
		}

		int ch=num[0], cht=num[0];
		
		int w=ch*10+num[1];
		if(ch < n && w>=n)
		{
			masBlock[t]=ch;
			t++;
		}		

		for(int i = 1; i < a; i++)
		{
			cht=ch;
			ch=ch*10 + num[i];
			if(ch >= n && a>2) 
			{
				i--;
				masBlock[t] = cht;
				ch=0;
				cht=0;
				t++;
			}
		}

		if(cht < n && ch < n)
		{
			masBlock[t]=ch;
			t++;
		}

		out << endl << "ОТ(числа): " << endl;
		for(int i=0; i<MAX; i++)
			out << TextNUM[i] << " ";
		out << endl;

		out << endl << "Блоки ОТ: " << endl;
		for(int i=0; i<t; i++)
			out << masBlock[i] << " ";
		out << endl;

		int *CryptoText = new int [100];
		int *Tdecrypt = new int [100];

		//Шифрование
		for (int j = 0; j < t; j++)
		{
			long long res=1;
			for(int i=0; i<d; i++)
				res *= masBlock[j];
			CryptoText[j] = res%n;
			if(CryptoText[j]<0) CryptoText[j]*=(-1);
		}

		//Дешифрование
		for (int j = 0; j < t; j++)
		{
			long long resD = 1;
			for(int i=0; i<e; i++)
				resD *= CryptoText[j];
			Tdecrypt[j] = resD%n;
			if(Tdecrypt[j]<0) Tdecrypt[j]*=(-1);
		}

		out << endl << "Шифрование: " << endl;
		for (int j = 0; j < t; j++)
		{
			out << CryptoText[j] << " ";
		}

		out << endl << endl << "Дешифрование(числа): " << endl;
		int * DecryptoN = new int [100];
		for (int j = 0; j < t; j++)
		{
			out << Tdecrypt[j] << " ";
		}

		out<< endl << endl;

		//объединить числа в дешифровании
		int tn=Tdecrypt[0];
		int kn=0;
		for(int i=1; i<MAX; i++)
		{
			tn=tn*100+Tdecrypt[i];
			kn+=2;
		}

		int factored_numberD[100];    // Массив для хранения результата
		int factored_number_lenD;    // Количество цифр в числе

		int numD[100];
		// Выполняем разложение
		factored_number_lenD = factor_digits(tn, factored_numberD, kn+2);


		int s=0;
		for(int i = kt; i >= 0; i--)
		{
			numD[s]=factored_number[i];
			s++;
		}

		int v=1;
		DecryptoN[0]=numD[0]*10+numD[1];
		for(int j=1; j<s; j++)
		{
			DecryptoN[v]=numD[j]*10+numD[j+1];
			v++;
			j++;
		}

		out << "Полученные блоки: " << endl;
		for(int i=0; i<v; i++)
			out << DecryptoN[i] << " ";

		out << endl << endl << "Дешифрование(символы): " << endl;
		for(int i=0; i<v; i++)
			for(int j=0; j<=70; j++)
				if(DecryptoN[i]==alphNum[j])
					out << alph[j];
		out << endl;

			in.close();
	out.close();
	}
}