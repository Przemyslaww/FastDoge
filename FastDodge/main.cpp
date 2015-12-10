#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <ctime>
#include <iostream>
#define SZYBKOSC 1000000
#define ILOSC_TOROW 10
#define DLUGOSC 90
#define RUCH 20000

using namespace std;

struct Klocek
    {
        bool istnieje = false;
        int xgora_lewy = 0;
        int ygora_lewy = 0;
        int xdol_prawy = xgora_lewy + DLUGOSC;
        int ydol_prawy = ygora_lewy + DLUGOSC;
        int rodzaj = 0;
        /*
            Bitmapy przygotować.
            Wgrać je. uzależnić bitmapy od rodzaju. rozważyć spadające serca dające zycia
            dodać obsługę punktów Zycia

        */
         //  Drewniany = 0
         //  Metalowy  = 1
         //  Asfaltowy = 2
         //  Szklany   = 3
    };

struct Ludzik
    {
        int ilosc_zyc = 3;
        int xgora = getmaxwidth()/2-40;
        int ygora = getmaxheight()-200;
        int xdol = getmaxwidth()/2+40;
        int ydol = getmaxheight()-51;
    };
void Punkty(int &punkty)
{
        char aktualne_punkty[15];
        sprintf(aktualne_punkty,"%d",punkty);
        setcolor(WHITE);
        outtextxy(getmaxwidth()/2-50,getmaxheight()-40, "Punkty");
        outtextxy(getmaxwidth()/2,getmaxheight()-40, aktualne_punkty);

}
void Rysuj_zycia(Ludzik ludek)
{

    if(ludek.ilosc_zyc == 2)
      {
            setcolor(BLACK);
            rectangle(20 * 3, getmaxheight()-40 , 20 * 3 + 10 , getmaxheight()-20 );
      }
    if(ludek.ilosc_zyc == 1)
      {
            setcolor(BLACK);
            rectangle(20 * 2, getmaxheight()-40 , 20 * 2 + 10 , getmaxheight()-20 );
      }
    if(ludek.ilosc_zyc == 0)
      {
            setcolor(BLACK);
            rectangle(20 * 1, getmaxheight()-40 , 20 * 1 + 10 , getmaxheight()-20 );
      }
}

int Sprawdzanie( Klocek tablica_klockow[], int ilosc_klockow) //SPRAWDZANIE CZY KLOCEK ISTNIEJE
{
    for(int i = 0; i <= ilosc_klockow-1; i++)
    {
       if(tablica_klockow[i].istnieje == false)
       {
           return i;
       }
    }
    return -1;
}

void Tworzenie( Klocek tablica_klockow[], int wolne_miejsce, int Tory[] )
{
    int losowanie_klocka = rand()%4;
    int losowanie_toru =  rand()%10;
    tablica_klockow[wolne_miejsce].rodzaj = losowanie_klocka;
    tablica_klockow[wolne_miejsce].xgora_lewy = Tory[losowanie_toru];
    tablica_klockow[wolne_miejsce].ygora_lewy = 0;
    tablica_klockow[wolne_miejsce].xdol_prawy = Tory[losowanie_toru] + DLUGOSC;
    tablica_klockow[wolne_miejsce].ydol_prawy = DLUGOSC;
    tablica_klockow[wolne_miejsce].istnieje = true;
    setcolor(WHITE);
    rectangle(tablica_klockow[wolne_miejsce].xgora_lewy, tablica_klockow[wolne_miejsce].ygora_lewy, tablica_klockow[wolne_miejsce].xdol_prawy,tablica_klockow[wolne_miejsce].ydol_prawy);

}

void Usowanie( Klocek tablica_klockow[], int i)
{
      setcolor(BLACK);
      rectangle(tablica_klockow[i].xgora_lewy, tablica_klockow[i].ygora_lewy,tablica_klockow[i].xdol_prawy,tablica_klockow[i].ydol_prawy);
      tablica_klockow[i].istnieje = false;
      tablica_klockow[i].rodzaj = 0;
      tablica_klockow[i].xgora_lewy = 0;
      tablica_klockow[i].ygora_lewy = 0;
      tablica_klockow[i].xdol_prawy = DLUGOSC;
      tablica_klockow[i].ydol_prawy = DLUGOSC;
}

void Ruszanie( Klocek tablica_klockow[], int &punkty)
{
    for(int i = 0; i <= 19; i++)   //obsluga klockow ( poruszanie , detekcja podlogi)
       {
          if(tablica_klockow[i].istnieje)
          {
              if(tablica_klockow[i].ydol_prawy >= getmaxheight()-50)
              {
                    Usowanie(tablica_klockow, i);
                    punkty+= 100;
                    Punkty(punkty);

              }
              else
              {
                setcolor(BLACK);
                rectangle(tablica_klockow[i].xgora_lewy, tablica_klockow[i].ygora_lewy,tablica_klockow[i].xdol_prawy,tablica_klockow[i].ydol_prawy);

                tablica_klockow[i].ygora_lewy = tablica_klockow[i].ygora_lewy + 1;
                tablica_klockow[i].ydol_prawy = tablica_klockow[i].ydol_prawy + 1;

                setcolor(WHITE);
                rectangle(tablica_klockow[i].xgora_lewy, tablica_klockow[i].ygora_lewy,tablica_klockow[i].xdol_prawy,tablica_klockow[i].ydol_prawy);
                //usuwanie starych klocków
              }
          }
        }
}

void czysciciel_buff()
{
   while (kbhit())
   {
      getch();
   }
}

int main(){
    int max_width = getmaxwidth();
    int max_height = getmaxheight();
    srand(time(NULL));
    int  window1 =  initwindow(getmaxwidth(),getmaxheight(),"FastDodge");
    int window3;
    int window2;
    setcurrentwindow(window1);
    //setcolor(BLUE);
    setbkcolor(GREEN);
    setcolor(WHITE);
    rectangle(0,getmaxheight()-49,getmaxwidth()-1,getmaxheight()-1);   //trawa
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(1,getmaxheight()-48,WHITE);
    setcolor(WHITE);
    rectangle(60, getmaxheight()-40 , 70 , getmaxheight()-20 );  //zycia
    rectangle(40, getmaxheight()-40 , 50 , getmaxheight()-20 );  //zycia
    rectangle(20, getmaxheight()-40 , 30 , getmaxheight()-20 );  //zycia

    int xlewo = -40;
    int xprawo =  40;

    int Tory[ILOSC_TOROW];
    int tor =  getmaxwidth()/ILOSC_TOROW;
    for(int i = 0 ; i < ILOSC_TOROW; i++)
    {
       Tory[i] = tor*i;
    }
        unsigned long long int czestotliwosc = 0;
        unsigned long int czestotliwosc_ruchu = 0;
        bool flaga_stop = false;
        //bool koniec = true;
        bool juz_otwarte = false;

        int punkty = 0;
        Punkty(punkty);

        int wolne_miejsce = 0;
        Klocek tablica_klockow[20];
        int ilosc_klockow = sizeof(tablica_klockow)/sizeof(tablica_klockow[0]);

        for(int i = 0; i <= 19 ; i++)
        {
            tablica_klockow[i].istnieje = false;
        }

        Ludzik Marian;
        readimagefile("Marian1Prawy.bmp",Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);     //nie wiem jak zrobić te grafiki, ponieważ dokumentacja tej wspaniałej biblioteki
      //  getimage(Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol,);                             //nie jest wystarczajaco zrozumiala
       // putimage(Marian.xgora,Marian.ygora,)
       // rectangle(Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
       // putimage(Marian.xgora,Marian.ygora,)

        while(1)
        {
            bool koniec = true;
            czestotliwosc++;
            if(czestotliwosc%SZYBKOSC == 0)
            {
                wolne_miejsce = Sprawdzanie(tablica_klockow, ilosc_klockow);
                if( wolne_miejsce != -1)                                        //zabezpieczenie przed iloscia klockow powyzej 19
                {
                    if(flaga_stop ==false)
                     Tworzenie(tablica_klockow, wolne_miejsce, Tory);           //tworzenie nowych klockow
                }
                czestotliwosc = 0;
            }
            czestotliwosc_ruchu++;
            if(czestotliwosc_ruchu%RUCH == 0)
            {
                if(flaga_stop == false)
                    Ruszanie(tablica_klockow, punkty);              //Ruszanie klockow
                    czestotliwosc_ruchu = 0;
            }

            if(kbhit())
            {
                char znak;
                znak = getch();
                switch(znak)
                {
                    case 'a':
                    case 'A':
                    if(Marian.xgora > 0)
                    {

                        readimagefile("czarne.bmp",Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                        //rectangle(Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                        //setcolor(RED);
                        //rectangle(Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                        //setfillstyle(SOLID_FILL, BLACK);
                        //floodfill(Marian.xgora+1,Marian.ygora+1,RED);
                        Marian.xgora = Marian.xgora + xlewo;
                        Marian.xdol = Marian.xdol + xlewo;
                        readimagefile("Marian1Lewy.bmp",Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                        //rectangle(Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                    }
                    break;

                    case 'd':
                    case 'D':
                    if(Marian.xdol < max_width)
                    {
                        readimagefile("czarne.bmp",Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                        //setcolor(BLACK);
                        //rectangle(Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                        //setcolor(WHITE);
                        Marian.xgora = Marian.xgora + xprawo;
                        Marian.xdol = Marian.xdol + xprawo;
                        //rectangle(Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                        readimagefile("Marian1Prawy.bmp",Marian.xgora,Marian.ygora,Marian.xdol,Marian.ydol);
                    }
                    break;

                    case 59:
                    {
                            juz_otwarte = true;
                            if(kbhit())
                            {
                                if(getch()== 59)
                                {
                                    juz_otwarte = false;
                                }
                            }
                            if(juz_otwarte == true)
                            {
                                flaga_stop = true;
                                window2 = initwindow(getmaxwidth()/2,getmaxheight()/3,"HILFE!!",300,100);
                                setcurrentwindow(window2);
                                outtextxy(10, 10, "Cel gry:     Unikaj klockow, aby zdobywac punkty");
                                outtextxy(10, 30, "Sterowanie:");
                                outtextxy(10, 50, "            A    - poruszanie Marianem w lewo");
                                outtextxy(10, 70, "            D    - poruszanie Marianem w prawo");
                                outtextxy(10, 90, "            F1   - HELP");
                                outtextxy(10, 110, "            P    - Zapis");
                                outtextxy(10, 130, "            Esc  - Wyjscie");
                            }
                           if(getch() == 27)                                                     //problem z logika, jeszcze nad tym pomysle
                            {
                                closegraph(window2);
                                setcurrentwindow(window1);
                                flaga_stop = false;
                                juz_otwarte = false;
                            }
                    }
                    break;

                    case 27:     //escape
                    {
                        juz_otwarte = true;
                        if(juz_otwarte == true)
                        {
                            flaga_stop = true;
                            window3 = initwindow(getmaxwidth()/6, getmaxheight()/6 , "Wyjscie", getmaxwidth()/2 - getmaxwidth()/12  , getmaxheight()/2 - getmaxheight()/12);
                            setcurrentwindow(window3);
                            outtextxy(60, 60, "Y - Tak         N - Nie");
                            char znak;
                            while(koniec)
                            {
                                znak = getch();
                                switch(znak)
                                case 'y':                       //nie dziala.dziala tylko za pierwsztm razem
                                {
                                    czysciciel_buff();           // czysci bufor
                                    closegraph(window3);
                                    juz_otwarte = false;
                                    setcurrentwindow(window1);
                                    flaga_stop = false;
                                    return 2137;
                                    koniec = false;
                                }

                                case 'n':
                                {
                                    czysciciel_buff();           //czysci bufor
                                    closegraph(window3);
                                    setcurrentwindow(window1);
                                    flaga_stop = false;
                                    juz_otwarte = false;
                                    koniec = false;
                                }
                            }
                        }
                    }
                }
            }

            for(int i = 0; i <= 19; i++)            //detekcja kolizji Mariana z klockami
                {

                    if(tablica_klockow[i].istnieje == true)
                    {

                        if(Marian.ygora <= tablica_klockow[i].ydol_prawy  && Marian.xgora <= tablica_klockow[i].xdol_prawy && Marian.xdol >= tablica_klockow[i].xgora_lewy)
                        {
                            Marian.ilosc_zyc--;
                            Rysuj_zycia(Marian);   //rysowanie aktualnego stanu zyc mariana
                            Usowanie(tablica_klockow, i);  //usowanie klocka w ktory uderzyslismy
                                                                //co sie dzieje jak uderzy
                            if(Marian.ilosc_zyc == 0)
                            {
                                printf("Uderzyl!");
                                return 1488;
                            }
                        }

                    }
                }
        }
    return 0;
}
