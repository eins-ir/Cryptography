#include "iostream"
#include "fstream"
#include <stdlib.h>

using namespace std;

//файл, содержащий ключ
ifstream in1("inputKey.txt");
//файл, содержащий алфавит
ifstream in2("alphabet.txt");
//файл, содержащий открытый текст
ifstream in3("inputText.txt");
ofstream out("output.txt");

int main()
{
	setlocale(LC_ALL, "rus");
	char *masKey = new char[50];
	int k=0;

	while(in1>>masKey[k])
	{
		k++;
	}
	in1.close();

	int c=k;

	while(c!=0){
		for(int i=0; i<k; i++){
			for(int j=0; j<i; j++){
				if(masKey[i] == masKey[j])
				{
					for (int m=i; m<=k-1; masKey[m+1], m++) masKey[m]=masKey[m+1];
					k--;
				}
			} }
	c--;}

//ключ не более 7
	if(k>7 || k<2){out<<endl<<"Error in key ("<<k<<")"<<endl;}
	else{

		out<<"Key: ";
		for(int i=0; i<k; i++) out<<masKey[i]<<" ";

		char *alphabet = new char[32];
		int t=0;

		while(in2>>alphabet[t])
		{		
			for(int i=0; i<k; i++)
			{
				if(alphabet[t] == masKey[i])
				{
					for (int m=t; m<=t-1; alphabet[m+1], m++) alphabet[m]=alphabet[m+1];
					t--;
				}
			}
			t++;
		}
		in2.close();

		out<<endl<<"New alphabet: ";
		for(int i=0; i<32-k; i++) out<<alphabet[i]<<" ";
		out<<endl;

		char masShifr[10][10];

		out<<endl<<"masShifr: "<<endl<<"  ";
		for(int i=1;i<10;i++)
			out<<i<<" ";
		out<<"0 "<<endl<<"- ";

		for(int i=1; i<=k; i++)
		{masShifr[7][i]=masKey[i-1]; out<<masShifr[7][i]<<" ";}
		out<<endl;
		int s=8, j=0, l=0;

		for(int s=8; s<=10;s++){
			if(s==8 || s==9) out<<s<<" ";
			else out<<0<<" ";
			for(int i=1; i<=10; i++)
			{
				if(j>=32-k) {l=1; break;}
				else{
					masShifr[s][i]=alphabet[j];
					out<<masShifr[s][i]<<" ";
					j++;}
			}
			out<<endl;
			if(l==1) break;
		}


		int shifr;
		in3>>shifr;
		if(shifr==1){		//шифрование

			char *masText = new char[50];
			int x=0;
			out<<endl<<"Text: ";
			while(in3>>masText[x])
			{
				out<<masText[x];
				x++;
			}
			in3.close();

			out<<endl<<"ШИФРОВАНИЕ: ";

			int n=0, y=0;
			while(n<x){
				for(int s=7; s<=10;s++){
					for(int i=1; i<=10; i++){
						if(masShifr[s][i]==masText[n]) {
							if(i!=10){
								if(s==7) {out<<i;}
								else if(s==10) {out<<"0"<<i;}
								else if(s==8 || s==9) {out<<s<<i;}
								}
							else {
								if(s==7) {out<<0;}
								else if(s==10) {out<<"0"<<0;}
								else if(s==8 || s==9) {out<<s<<0;}
								}
							n++;
						}
					}
				}	
			}
		}
		else {
			int *masInt = new int[100];
			int x=0, w=0; char y;
			out<<endl<<"Криптограмма: ";
			while(in3>>y)
			{
				if(y=='-') w=7;
				else if(y=='0') w=0;
				else if(y=='1') w=1;
				else if(y=='2') w=2;
				else if(y=='3') w=3;
				else if(y=='4') w=4;
				else if(y=='5') w=5;
				else if(y=='6') w=6;
				else if(y=='7') w=7;
				else if(y=='8') w=8;
				else if(y=='9') w=9;

				masInt[x]=w;
				out<<masInt[x];
				x++;
			}
			in3.close();
			out<<endl<<"ДЕШИФРОВАНИЕ: ";



			for(int i=0; i<x; i++)
			{
				if(masInt[i]==9 || masInt[i]==8) 
				{
					if(masInt[i+1]==0) 
					{
						out<<masShifr[masInt[i]][10]; 
					}
					else 
					{
						out<<masShifr[masInt[i]][masInt[i+1]]; 
					}
					i++;
				}
				else if (masInt[i]==0)
				{ 
					if(masInt[i+1]==0) 
					{
						out<<masShifr[10][10];
					}
					else 
					{
						out<<masShifr[10][masInt[i+1]]; 
					}
					i++;
				}

				else  if(masInt[i]>=1 && masInt[i]<=7) 
					out<<masShifr[7][masInt[i]];
			}
		}
	}
	out.close();
}