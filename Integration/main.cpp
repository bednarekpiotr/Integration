#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

void text(string x)
{
    cout<< x<<"\n";
}

double wartoscFunkcji(int wybor,double x)
{
    double wynik;
switch(wybor)
{
case 1:
    wynik=x*x*x-x*x+7;
    break;
case 2:
    wynik=x*sin(x);
    break;

}
return wynik;
}

double waga(double x)
	{
		return 1/sqrt(1-x*x);
	}


double simpson(int wybor)
{   double wartosc=0,poczatekPrzedzialu,koniecPrzedzialu,wartoscStara,epsilon;
    int iloscPrzedzialow,ilePunktow;
    text("Podaj poczatek przedzialu");

    cin>>poczatekPrzedzialu;
    cout<<poczatekPrzedzialu;
    text("Podaj koniec przedzialu");
    cin>>koniecPrzedzialu;
    cout<<koniecPrzedzialu;
    if(koniecPrzedzialu<poczatekPrzedzialu)
        {
            swap(poczatekPrzedzialu,koniecPrzedzialu);
        }
    text("Podaj parzysta ilosc przedzialow");
    cin>>iloscPrzedzialow;
    if (iloscPrzedzialow<2)
    {
        iloscPrzedzialow=2;
        text("Automatycznie dobrano ilosc przedzialow = ");
        cout<<iloscPrzedzialow;
    }
    if (iloscPrzedzialow%2==1)
    {
        iloscPrzedzialow+=1;
        text("Automatycznie dobrano parzysta ilosc przedzialow");
        cout<<iloscPrzedzialow;
    }
    text("Podaj dokaladnosc");
    cin>>epsilon;
    wartosc=0,wartoscStara=0;


    do {
    //ilePunktow=2*iloscPrzedzialow+1;
    cout<<"ilosc przedzialow : "  << iloscPrzedzialow<<"\n";


    wartoscStara=wartosc;
    cout <<"stara wartosc to: "<<wartoscStara<<"\n";
    wartosc=0;
    cout<<"nowa wartosc to : "<<wartosc<<"\n";

    double h = (koniecPrzedzialu-poczatekPrzedzialu)/iloscPrzedzialow;
    cout<<"wartosc h wynosi : "<<h<<"\n";

    wartosc=wartoscFunkcji(wybor,poczatekPrzedzialu)+wartoscFunkcji(wybor,koniecPrzedzialu);
    for (int i=0; i<iloscPrzedzialow;i++)
    {

        if (i%2==0)
        {
            wartosc=wartosc+2*(wartoscFunkcji(wybor,poczatekPrzedzialu+i*h));
            //cout<<wartosc;
            //text("");
        }
        else
        {
            wartosc=wartosc+4*(wartoscFunkcji(wybor,poczatekPrzedzialu+i*h));
            //text("");
        }

    }
    iloscPrzedzialow*=2;
    wartosc=(h*wartosc)/3;
    text("Roznica wynosi \n");
    //cout<<"wartosc stara: "<<wartoscStara<<"wartosc nowa " << wartosc<<"\n";
    cout<<abs(wartosc-wartoscStara);
    }

    while(abs(wartosc-wartoscStara)>epsilon);

    return wartosc;



}

int main()
{
int wybor;
text("Podaj funkcje do calkowania\n");
text("1) x^3+3x^2-6x+8");
text("2) x*sinx");
cin>>wybor;
cout<<"Wynik calkowania \n"<<simpson(wybor);

return 0;

}
