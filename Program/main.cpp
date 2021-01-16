#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

int generator_Liczb(int tablica[],int n)//Funkcja generujaca pseudolosowe liczby
{
    ofstream plik("dane.txt"); //Otwarcie pliku "dane.txt" do zapisu
//Generator liczb pseudolosowych
    srand(time(NULL));

    for(int i=0; i<n; i++)
    {
        tablica[i]=rand()%100+1;
        plik<<tablica[i]<<" "; //Zapis wygenerej tablicy do pliku
    }
    return tablica[n]; //Zwrocenie tablicy
}

void wczytanie_z_pliku(int tablica[],int n) //Funkcja wczytujaca dane  z pliku
{
    fstream plik; //zadeklarowanie pliku do odczytu
    plik.open("dane.txt");
    if(plik.good()==false) //Sprawdzenie czy plik istnieje
    {
        cout<<"Plik dane.txt nie istnieje"<<endl;
    }
    for(int i=0; i<n; i++) //Zapis tablicy do pliku
    {
        plik>>tablica[i];
    }
}

void zapis_do_pliku(int tab[],int tab_przedsort[],int n) //Funkcja zapisujaca dane do pliku
{
    ofstream zapis; //Otwarcie pliku zapis "wynik.txt"
    zapis.open("wynik.txt");
    zapis<<"Po sortowaniu: ";
    for(int i=0;i<n;i++) //Wypisanie tablicy po posortowaniu
    {
        zapis<<tab[i];
        zapis<<" ";
    }
    zapis<<endl;
    zapis<<"Przed sortowaniem: ";
    for(int j=0;j<n;j++) //Wypisanie tablicy przed sortowaniem
        zapis<<tab_przedsort[j]<<" ";
}

void sortowanie_kopcowe( int tab[], int n ) //Funkcja sortujaca poprzez kopcowanie
{
    int i,j,k,x,m;
    for(i=2; i<=n; i++) //budujemy kopiec
   {
    j = i;
    k = j/2;
    x = tab[i];
    while((k>0) && (tab[k]<x))
    {
      tab[j] = tab[k];
      j=k;
      k=j/2;
    }
    tab[j] = x;
   }

// Rozbieramy kopiec

  for(i=n; i>1; i--)
  {
    swap(tab[1], tab[i]);
    j=1;
    k=2;
    while(k<i)
    {
      if((k+1<i) && (tab[k+1]>tab[k]))
        m=k+1;
      else
        m=k;
      if(tab[m] <= tab[j])
        break;
      swap(tab[j], tab[m]);
      j=m;
      k=j+j;
    }
  }

// Wyswietlamy wynik sortowania

  cout << "Po sortowaniu: \n\n";
  for(i = 1; i <= n; i++)
    cout << setw(6) << tab[i];
  cout << endl;
}
void printTab(int* tab, int n)
{
	cout << endl;
	for (int x = 0; x < n; x++) {
		cout << tab[x] << " | ";
	}
	cout << endl;
}

void merge(int* tab, int l, int m, int r)
{
	int lSize = m - l + 1;
	int rSize = r - m;

	//Tablice pomocnicze
	int* tabL = new int[lSize];
	int* tabR = new int[rSize];

	// Kopiowanie danych do tablic pomocniczych
	for (int x = 0; x < lSize; x++)
		tabL[x] = tab[l + x];
	for (int y = 0; y < rSize; y++)
		tabR[y] = tab[m + 1 + y];

	int indexL = 0;
	int indexR = 0;
	int currIndex;

	//Łączenie tablic R i L
	for (currIndex = l; indexL < lSize && indexR < rSize; currIndex++)
	{
		if (tabL[indexL] <= tabR[indexR])
			tab[currIndex] = tabL[indexL++];
		else
			tab[currIndex] = tabR[indexR++];
	}

	//Jeśli w tablicy tabL pozostały jeszcze jakieś elementy
	//kopiujemy je
	while (indexL < lSize)
		tab[currIndex++] = tabL[indexL++];

	//Jeśli w tablicy tabR pozostały jeszcze jakieś elementy
	//kopiujemy je
	while (indexR < rSize)
		tab[currIndex++] = tabR[indexR++];

	delete[] tabL;
	delete[] tabR;
}


void sortowanie_przez_scalanie(int* tab, int l, int r)
{
	if (r > l) {
		int m = (l + r) / 2;
		sortowanie_przez_scalanie(tab, l, m);
		sortowanie_przez_scalanie(tab, m + 1, r);
		merge(tab, l, m, r);
	}
}

int main()
{
    DWORD t1,t2;
    int n, *tablica, k; //Deklaracja zmiennych

    cout<<"Ile liczb chcesz posortowac?: "<<endl;
    cin>>n;
    tablica=new int[n];

    cout<<"1.Wczytaj liczby z pliku dane.txt"<<endl;
    cout<<"2.Wygenerowanie liczb i zapisanie do dane.txt"<<endl;
    cin>>k;
    //Wybor jaka metoda chcesz posortowac

    switch(k)
    {
        case 1:
        {
            wczytanie_z_pliku(tablica,n); //Wywolanie funkcji wczytanie_z_pliku
            break;
        }
        case 2:
        {
            generator_Liczb(tablica,n); //Wyowolanie funkcji generator_Liczb
            break;
        }
        default:
            {
                cout<<"Bledny wybor";
                return 0;
            }
    }

    int tablica_przedsort[n];
    for(int j=0;j<=n;j++)
    {
        tablica_przedsort[j]=tablica[j]; //Stoworzenie tablicy z wartosciami tablicy przed posortowaniem
    }
    cout<<"Liczby to :"<<endl; //Wypisanie ciagu
    for(int l=0;l<n;l++)
        {
            cout<<tablica[l]<<" ";
        }
        //Wybor rodzaju sorotwoania
    cout<<endl<<endl;
    cout<<"-----Ktora metoda chcesz posortowac----"<<endl;
    cout<<"1.Kopcowe"<<endl;
    cout<<"2.Scalanie"<<endl;
    cout<<endl<<endl;
    int wybor;
    cin>>wybor;
    switch(wybor)
    {
        case 1:
        {
            cout<<"Po posortowaniu przez kopcowanie: "<<endl;
            t1=GetTickCount();
            sortowanie_kopcowe(tablica,n); // Wywolanie funkcji sortujacej przez kopcowanie
            t2=GetTickCount()-t1;
            cout<<"Czas wykonania algorytmu sortowania:"<<t2<<"[ms]";
            break;
        }
        case 2:
        {
            // wywolanie funkcji sortujacych algorytmem scalania
            cout << endl << "Tablica przed posortowaniem: \n" << endl;
            printTab(tablica, n);
            cout << endl << "Rozpoczecie sortowania... \n" << endl;
            sortowanie_przez_scalanie(tablica, 0, n-1);
            cout << endl << "Oto tablica po sortowaniu: \n" << endl;
            printTab(tablica, n);
            delete[] tablica;
            break;
        }
        default:
            {
                cout<<"Bledny wybor";
                return 0;
            }
    }
    zapis_do_pliku(tablica,tablica_przedsort,n); //Wywolanie funkcji zapisujacej dane do pliku
    return 0;
}
