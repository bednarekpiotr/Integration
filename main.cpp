#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>

using namespace std;
int p = 3;


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
        wynik=x*x;
        break;
    case 2:
        wynik=(x-1)*(x*x-4);
        break;
    case 3:
        wynik=x*x*x+x*x-8*x-8;


    }
    return wynik;
}


void daneWejsciowe(double &poczatekPrzedzialu, double &koniecPrzedzialu,int &iloscPrzedzialow, double &epsilon, int &iloscWezlow)
{   text("Podaj poczatek przedzialu: ");
    cin>>poczatekPrzedzialu;
    text("Podaj koniec przedzialu: ");
    cin>>koniecPrzedzialu;
    if(koniecPrzedzialu<poczatekPrzedzialu)
    {
        swap(poczatekPrzedzialu,koniecPrzedzialu);
    }
    text("Podaj parzysta ilosc przedzialow: ");
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
        text("Automatycznie dobrano parzysta ilosc przedzialow = ");
        cout<<iloscPrzedzialow;
    }
    text("Podaj dokladnosc: ");
    cin>>epsilon;


    text("Podaj ilosc wezlow: (2-5) ");
    cin>>iloscWezlow;

}


double newtonCotess(int wybor,double poczatekPrzedzialu, double koniecPrzedzialu, double epsilon,int iloscPrzedzialow)
{
    double wartosc=0,wartoscStara=0;
    do
    {

        wartoscStara=wartosc;
        wartosc=0;
        double h = (koniecPrzedzialu-poczatekPrzedzialu)/iloscPrzedzialow;
        wartosc = wartoscFunkcji( wybor , poczatekPrzedzialu ) + wartoscFunkcji( wybor , koniecPrzedzialu );
        for (int i=0; i < iloscPrzedzialow; i++)
        {

            if ( i % 2 == 0)
            {
                   wartosc=wartosc+2*(wartoscFunkcji(wybor,poczatekPrzedzialu+i*h));

            }
            else
            {
                    wartosc=wartosc+4*(wartoscFunkcji(wybor,poczatekPrzedzialu+i*h));

            }
        }

        iloscPrzedzialow*=2;
        wartosc=(h*wartosc)/3;

    }

    while(abs(wartosc-wartoscStara)>epsilon);
    cout<<"Ilosc przedzialow: "<<iloscPrzedzialow<<"\n";
    return wartosc;
}

double granica(int wybor, double epsilon)
{

    double x1Left=0.0;
    double x2Left=-0.5;
    double x2Right=0.5;
    double x1Right=0.0;
    double temp;
    double h_right,h_left;
    int it=1;
    double wartoscLewa=0,wartoscLewaNowa=0;
    double wartoscPrawa=0,wartoscPrawaNowa=0;
    do
    {
        if(it!=1)
        {

            x1Left=x2Left;
            x2Left=x1Left-(temp*0.5);
            x1Right=x2Right;
            x2Right=x1Right+(temp*0.5);

        }

        if(it==1)
        {

        }
        wartoscLewa=0;
        wartoscPrawa=0;
        temp=(x2Right-x1Right);
        wartoscPrawa=abs(((x2Right-x1Right)/6))*((wartoscFunkcji(wybor,x1Right))+4*wartoscFunkcji(wybor,((x1Right+x2Right)/2))+wartoscFunkcji(wybor,x2Right));
        wartoscLewa=abs((x2Left-x1Left)/6)*(wartoscFunkcji(wybor,x1Left)+(4*wartoscFunkcji(wybor,((x1Left+x2Left)/2)))+wartoscFunkcji(wybor,x2Left));
        if (wartoscPrawa>epsilon)
        {
            wartoscPrawaNowa+=wartoscPrawa;
        }
        if (wartoscLewa>epsilon)
        {
            wartoscLewaNowa+=wartoscLewa;
        }

        it++;


    }
    while((wartoscLewa)>epsilon && (wartoscPrawa)>epsilon);
     return wartoscPrawaNowa+wartoscLewaNowa;

}

double czybyszew (int wybor,double poczatekPrzedzialu, double koniecPrzedzialu, int iloscWezlow)
{
    double a=poczatekPrzedzialu;
    double b=koniecPrzedzialu;
    double suma;
    double wezly[4][5]={{0.577350,-0.577350,0,0,0},{0.707107,0,-0.707107,0,0},{0.794654,0.187592,-0.794654,-0.187592,0},{0.832498,0.374541,0,-0.374541,-0.832498}};

    for (int i=0 ; i< iloscWezlow ; i++)
    {
        suma+=wartoscFunkcji(wybor,((b+a)/2)+((b-a)/2)*wezly[iloscWezlow-2][i]);
    }
    suma=((b-a)/iloscWezlow)*suma;
    return suma;

}



int main()
{
    int wybor=0;
    double poczatekPrzedzialu=0;
    double koniecPrzedzialu=0;
    int iloscPrzedzialow=0;
    double epsilon=0;
    int iloscWezlow=0;

    text("Podaj funkcje do calkowania\n");
    text("1) x^2");
    text("2) (x-1)(x^2-4)");
    text("3) x^3 + x^2 -8x -8 ");
    cin>>wybor;
    daneWejsciowe(poczatekPrzedzialu,koniecPrzedzialu,iloscPrzedzialow,epsilon,iloscWezlow);
    cout<<"NEWTON-COTESS: "<<newtonCotess(wybor,poczatekPrzedzialu,koniecPrzedzialu,epsilon,iloscPrzedzialow)<<"\n";
    cout<<"GRANICA FUNKCJI: "<<granica(wybor,epsilon)<<"\n";
    cout<<"KWADRATURA CZYBYSZEWA: " <<czybyszew(wybor,poczatekPrzedzialu,koniecPrzedzialu,iloscWezlow)<<"\n";

    return 0;

}
