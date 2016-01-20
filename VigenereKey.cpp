//Автоключ Виженера

#include "iostream"
#include "fstream"
#include "cmath"

using namespace std;

//файл, содержаший алфавит
ifstream in1("alph.txt");
//файл, содержащий открытый текст
ifstream in2("inputText.txt");
ofstream out("output.txt");


int main()
{
	setlocale(LC_ALL, "rus");
	char first;

	int alph=0;
	char *alphabet = new char[55];

	out<<"Alphabet:"<<endl;
	while(in1>>alphabet[alph])
	{
		out<<alph<<" = "<<alphabet[alph]<<endl;
		alph++;
	}
	in1.close();

	out<<endl;
	char *masText = new char[50];
	int *masIntText = new int[50];

	int txt=0;

	out<<endl<<"Open text:"<<endl;
	while(in2>>masText[txt])
	{
		txt++;
	}
	in2.close();


	for(int j=0; j<txt;j++){
		for(int i=0; i<alph; i++)
		{
			if(masText[j]==alphabet[i]) 
			{masIntText[j]=i;}
		}}

	for(int i=1; i<txt; i++)
	{out<<masText[i]<<" = "<<masIntText[i]<<endl;}
	out<<endl;

	out<<"Key: "<<endl;
	for(int i=0; i<txt-1; i++)
	{out<<masText[i]<<" = "<<masIntText[i]<<endl;}
	out<<endl;

	char *masCrypto = new char[100];
	int *masIntDeText = new int[100];

	out<<"Шифрование:"<<endl;
	int B;
	for(int i=0; i<txt-1; i++)
	{
		B = (masIntText[i]+masIntText[i+1])%(alph-1);
		out<<alphabet[B];
		masCrypto[i]=alphabet[B];
	}
	out<<endl;

	out<<endl<<"Cryptogram"<<endl;
	for(int j=0; j<txt-1;j++){
		for(int i=0; i<alph; i++)
		{
			if(masCrypto[j]==alphabet[i]) 
			{masIntDeText[j]=i; 
			out<<masCrypto[j]<<" = "<<masIntDeText[j]<<endl;}
		}}

	out<<endl<<"Key: "<<endl;
	for(int i=0; i<txt-1; i++)
	{out<<masText[i]<<" = "<<masIntText[i]<<endl;}
	out<<endl;

	out<<endl<<"Дешифрование: "<<endl;
	int A;
	for(int i=0; i<txt-1; i++)
	{
		A = (masIntDeText[i]-masIntText[i])%(alph-1);
		if(A<0){A=A+alph-1;}
		out<<alphabet[A];
	}

	out.close();
}