#include "iostream"
#include "fstream"

using namespace std;

//файл, содержащий ключ
ifstream in1("inputKey.txt");
//файл, содержащий алфавит
ifstream in2("alphabet.txt");
//файл, содержащий открытый текст
ifstream in3("inputText.txt");
ofstream zero("zero.txt");
ofstream out("output.txt");

int main()
{
	setlocale(LC_ALL, "rus");
	char *masKey = new char[50];
	int k=0;

	out<<"Key: ";
	while(in1>>masKey[k])
	{
		//out<<masKey[k];
		k++;
	}
	in1.close();


		for(int i=1; i<k; i++){
		for(int j=0; j<i; j++){
			if(masKey[i] == masKey[j])
			{
				for (int m=i; m<=k-1; masKey[m+1], m++) masKey[m]=masKey[m+1];
				k--;
			}
		} }

		for(int i=0; i<k; i++) 
			out<<masKey[i];
		out<<endl;

	char *masText = new char[100];
	int t=0;
	out<<"Text: ";
	while(in3>>masText[t])
	{
		out<<masText[t];
		t++;
	}
	out<<endl;

	char alphabet[6][6];
	char *alph = new char[37];
	int a=0;
	out<<endl<<"Alphabet:"<<endl;
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++)
		{in2>>alphabet[i][j];
		alph[a]=alphabet[i][j];
		a++;
		out<<alphabet[i][j];}
		out<<endl;
	}
	out<<endl;

	int *masIntKey = new int[50];
	int *masIntSortKey = new int[50];

	for(int i=0; i<k;i++){
		for(int j=0;j<=36;j++){
			if(masKey[i]==alph[j]) 
			{masIntKey[i]=j; masIntSortKey[i]=j;}}
	}

	//сортировка ключа по индексу в исходном алфавите. запись отсортированного массива в другой массив.
	for (int i = k - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (masIntSortKey[j] > masIntSortKey[j+1])
			{
				int tmp = masIntSortKey[j];
				masIntSortKey[j] = masIntSortKey[j + 1];
				masIntSortKey[j + 1] = tmp;

			}
		}
	}

	int c=k;
	for(int i=0; i<c; i++){
		for(int j=0; j<i; j++){
			if(masIntSortKey[i] == masIntSortKey[j])
			{
				for (int m=i; m<=c-1; masIntSortKey[m+1], m++) masIntSortKey[m]=masIntSortKey[m+1];
				c--;
			}
		} }

	char *masCrypto = new char[100];
	zero<<"Answer (shifr): "<<endl;

	char *masCode = new char[2*t+1];
	c=0;
	for(int i=0; i<t;i++){
		for(int j=0;j<6;j++){
			for(int l=0;l<6;l++){
				if(masText[i]==alphabet[j][l])
				{
					//masCode[c]=j; 
					//masCode[c+1]=l;

					if(j==0) 
					{
						masCode[c]='A';
						if(l==0) masCode[c+1]='A';
						else if(l==1) masCode[c+1]='D';
						else if(l==2) masCode[c+1]='F';
						else if(l==3) masCode[c+1]='G';
						else if(l==4) masCode[c+1]='V';
						else if(l==5) masCode[c+1]='X';
					}
					else if(j==1)
					{
						masCode[c]='D';
						if(l==0) masCode[c+1]='A';
						else if(l==1) masCode[c+1]='D';
						else if(l==2) masCode[c+1]='F';
						else if(l==3) masCode[c+1]='G';
						else if(l==4) masCode[c+1]='V';
						else if(l==5) masCode[c+1]='X';
					}
					else if(j==2)
					{
						masCode[c]='F';
						if(l==0) masCode[c+1]='A';
						else if(l==1) masCode[c+1]='D';
						else if(l==2) masCode[c+1]='F';
						else if(l==3) masCode[c+1]='G';
						else if(l==4) masCode[c+1]='V';
						else if(l==5) masCode[c+1]='X';
					}
					else if(j==3)
					{
						masCode[c]='G';
						if(l==0) masCode[c+1]='A';
						else if(l==1) masCode[c+1]='D';
						else if(l==2) masCode[c+1]='F';
						else if(l==3) masCode[c+1]='G';
						else if(l==4) masCode[c+1]='V';
						else if(l==5) masCode[c+1]='X';
					}
					else if(j==4)
					{
						masCode[c]='V';
						if(l==0) masCode[c+1]='A';
						else if(l==1) masCode[c+1]='D';
						else if(l==2) masCode[c+1]='F';
						else if(l==3) masCode[c+1]='G';
						else if(l==4) masCode[c+1]='V';
						else if(l==5) masCode[c+1]='X';
					}
					else if(j==5)
					{
						masCode[c]='X';
						if(l==0) masCode[c+1]='A';
						else if(l==1) masCode[c+1]='D';
						else if(l==2) masCode[c+1]='F';
						else if(l==3) masCode[c+1]='G';
						else if(l==4) masCode[c+1]='V';
						else if(l==5) masCode[c+1]='X';
					}//*/
					c+=2;
				}
			}
		}
	}

	out<<"masCode: ";
	for(int i=0;i<t*2;i++)
		out<<masCode[i];
	out<<endl;

	char masBlok[20][20];

	for(int i=0; i<k; i++){
		masBlok[0][i]=masKey[i];
	}

	int control=0, flag=0;

	//блоки шифрования

bloc:
	for(int i=1; i<=k; i++){
		for(int j=0; j<k; j++)
		{
			if(flag == (t*2)) masBlok[i][j]='ф';
			else
			{
				masBlok[i][j]=masCode[flag];
				flag++;
			}
		}
	}

	for(int i=0; i<=k; i++){
		for(int j=0; j<k; j++)
		{
			if(masBlok[i][j]=='ф') break;
			out<<masBlok[i][j];
		}
		out<<endl;
	}


	out<<"Шифрование: ";

	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++)
		{
			if(masIntSortKey[i]==masIntKey[j])
			{
				for(int v=1; v<=k; v++)
				{
					masCrypto[control]=masBlok[v][j];
					control++;
					if(masBlok[v][j]!='ф')
						out<<masBlok[v][j];
					zero<<masBlok[v][j];
				}
			}
		}
	}
	out<<endl;
	if(control<(t*2)) goto bloc;





	//ДЕШИФРОВАНИЕ

	zero<<endl<<endl<<"Answer (deshifr):"<<endl;

	out<<endl<<endl<<"Дешифрование:"<<endl<<"masCrypto:";
	for(int i=0;i<control;i++)
		out<<masCrypto[i];

	int x=0, w=0;

	c=0;
debloc:
	//Блоки дешифрования
	char masBlok2[20][20];
	char masBlok3[20][20];

	for(int j=0; j<k; j++)
	{
		masBlok3[0][j]=masKey[j];
	}

	for(int i=0; i<=k; i++){
		for(int j=1; j<=k; j++)
		{
			masBlok2[j][i]=masCrypto[x];
			x++;
		}
	}

	out<<endl;
	for(int i=1; i<=k; i++){
		for(int j=0; j<k; j++)
		{
			{
				out<<masBlok2[i][j];
			}
		}
		out<<endl;
	}
	out<<endl;

	//блок3 как в первом блоке делаю (по ключу записанный)
	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){
			if(masIntKey[i]==masIntSortKey[j])
			{
				for(int v=1; v<=k; v++)
					masBlok3[v][i] = masBlok2[v][j];
				break;	
			}}}
	out<<endl;


	for(int i=0;i<=k; i++){
		for(int j=0; j<k; j++){
			out<<masBlok3[i][j];} out<<endl;}

	out<<endl;
	
	int masInt[100];
	for(int i=1; i<=k; i++){
		for(int j=0; j<k;j++)
		{
			if (masBlok3[i][j]=='A')
			{masInt[c]=0; c++;}
			if (masBlok3[i][j]=='D')
			{masInt[c]=1; c++;}
			if (masBlok3[i][j]=='F')
			{masInt[c]=2; c++;}
			if (masBlok3[i][j]=='G')
			{masInt[c]=3; c++;}
			if (masBlok3[i][j]=='V')
			{masInt[c]=4; c++;}
			if (masBlok3[i][j]=='X')
			{masInt[c]=5; c++;}
			if (masBlok3[i][j]=='ф')
				break;
		}
	}
	
	x=x-k;
	out<<endl;
	if((control-x)>0) goto debloc;

	out<<endl<<"Дешифрование: ";
	int n=0,m=0;
	for(int i=0; i<c; i+=2)
	{
		n=masInt[i];
		m=masInt[i+1];
		out<<alphabet[n][m];
		zero<<alphabet[n][m];
	}

	out.close();
	zero.close();
}