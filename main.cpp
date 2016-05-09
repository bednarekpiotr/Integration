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
        wynik=x*sin(x);
        break;

    }
    return wynik;
}

double waga(double x)
{
    return 1.0/(sqrt(-x*x+1));
}


double newtonCotess(int wybor)
{
    double wartosc=0,poczatekPrzedzialu,koniecPrzedzialu,wartoscStara,epsilon;
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


    do
    {
        //ilePunktow=2*iloscPrzedzialow+1;
        cout<<"ilosc przedzialow : "  << iloscPrzedzialow<<"\n";
        wartoscStara=wartosc;
        cout <<"stara wartosc to: "<<wartoscStara<<"\n";
        wartosc=0;
        cout<<"nowa wartosc to : "<<wartosc<<"\n";
        double h = (koniecPrzedzialu-poczatekPrzedzialu)/iloscPrzedzialow;
        cout<<"wartosc h wynosi : "<<h<<"\n";
        wartosc = wartoscFunkcji( wybor , poczatekPrzedzialu ) + wartoscFunkcji( wybor , koniecPrzedzialu );
        for (int i=0; i < iloscPrzedzialow; i++)
        {

            if ( i % 2 == 0)
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

double simposonGranica(int wybor, double epsilon)
{

    double x1Left=0.0;
    double x2Left;
    double x2Right;
    double x1Right=0.0;
    double temp;
    text("Podaj poczatek przedzialu");
    cin>>x2Left;
    cout<<x2Left;
    text("Podaj koniec przedzialu");
    cin>>x2Right;
    cout<<x2Right;
    x2Left/=2;
    x2Right/=2;



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

            cout<<setprecision(p)<<"Po: x1_left = "<<x1Left<<" x2_left = "<<x2Left<<"\n";
            cout<<setprecision(p)<<"Po: x1_right = "<<x1Right<<" x2_right = "<<x2Right<<"\n";
        }

        if(it==1)
        {
            cout<<setprecision(p)<<"Po: x1_left = "<<x1Left<<" x2_left = "<<x2Left<<"\n";
            cout<<setprecision(p)<<"Po: x1_right = "<<x1Right<<" x2_right = "<<x2Right<<"\n";
        }
        wartoscLewa=0;
        wartoscPrawa=0;
        h_right=(x2Right-x1Right);
        h_left=(x2Left-x1Left);
        temp=(x2Right-x1Right);
        wartoscPrawa=abs(((x2Right-x1Right)/6))*((wartoscFunkcji(wybor,x1Right))+4*wartoscFunkcji(wybor,((x1Right+x2Right)/2))+wartoscFunkcji(wybor,x2Right));
        wartoscLewa=((x2Left-x1Left)/6)*(wartoscFunkcji(wybor,x1Left)+(4*wartoscFunkcji(wybor,((x1Left+x2Left)/2)))+wartoscFunkcji(wybor,x2Left));
        if (wartoscPrawa>epsilon)
        {
            wartoscPrawaNowa+=wartoscPrawa;
        }
        if (wartoscLewa>epsilon)
        {
            wartoscLewaNowa+=wartoscLewa;
        }
        cout<<"iterator :"<<it<<"\n";
        cout<<"Wartosc lewa nowa : " <<wartoscLewaNowa<<"\n";
        cout<<"Wartosc Prawa nowa: "<<wartoscPrawaNowa<<"\n";
        it++;


    }
    while((wartoscLewa)>epsilon && (wartoscPrawa)>epsilon);

    return wartoscPrawaNowa-wartoscLewaNowa;

}



int main()
{
    int wybor;
    text("Podaj funkcje do calkowania\n");
    text("1) x^3-x^2+7");
    text("2) x*sinx");
    cin>>wybor;
//cout<<"Wynik calkowania \n"<<simpson(wybor);



    //cout<<simposonGranica(wybor,0.001);
    cout<<"Wynik calkowania"<<newtonCotess(wybor);

    return 0;

}
