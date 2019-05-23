//============================================================================
// Name        : Proba.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <malloc.h>
#include <fstream>
#include <math.h>


using namespace std;


void insertionSort(long tab[], long left[], long right[])
{
    int i, key, j;
    for (i = 1; i < (right-left); i++)
    {
        key = tab[i];
        j = i - 1;


        while (j >= 0 && tab[j] > key) {
            tab[j + 1] = tab[j];
            j = j - 1;
        }
        tab[j + 1] = key;
    }
}

//template <typename object_t>
void MergeSort(long tab[], long left, long right, bool odwr)
{
    long l, mid, r;
    long _tmp1, _tmp2, _tmp3;

    mid = (left + right) / 2;                            //Wyznaczenie œrodkowego indeksu

    if(left != right)                                        //Sprawdzenie czy można jeszcze podzieliĉ tablice
    {
        MergeSort(tab, left, mid, odwr);            //Rekurencyjne wywo³anie funkcji dla pierwszej ("lewej") po³ówki tablicy
        MergeSort(tab, mid+1, right, odwr);  //Rekurencyjne wywo³anie funkcji dla drugiej ("prawej") po³ówki tablicy

        long* tab_tmp = new long[right-left + 1];

        //long* tab_tmp = new long[right - left +1];    //Utworzenie tablicy roboczej
        _tmp1 = 0;
        l = left;
        r = mid+1;

        while(l <= mid && r <= right)
        {
            if(odwr? (tab[l] > tab[r]):(tab[l] < tab[r]))
                tab_tmp[_tmp1] = tab[l++];
            else
                tab_tmp[_tmp1] = tab[r++];
            _tmp1++;
        }

        while(l <= mid)
            tab_tmp[_tmp1++] = tab[l++];

        while(r <= right)
            tab_tmp[_tmp1++] = tab[r++];

        for(_tmp2 = left, _tmp3 = 0; _tmp2 <= right; _tmp2++, _tmp3++)
            tab[_tmp2] = tab_tmp[_tmp3];

        delete tab_tmp;                                                //Zwolnienie pamiêci
    }
}
//template < typename object_t >
void QuickSort(long tab[], long left, long right)
{
    long l = left; //element tablicy najbardziej po lewej
    long r = right; //element tablicy najbardziej po prawej
    long a = (l+r)/2; //pivot - granica postawiona na œrodku tablicy
    long p = tab[a];

    while( l <= r )
    {
    	//dopóki l jest mniejsze od granicy
        while( tab[l] < p ) l++; //przesuwamy l w prawo
        //dopóki r jest wiêksze od granicy
        while( tab[r] > p ) r--; //przesuwamy r w lewo

        if( l <= r ) //jeœli l jest mniejsze lub równe r
        {
            long tmp = tab[l];
            tab[l] = tab[r];
            tab[r] = tmp; //zamieniamy l z r

            l++; // l przesuwamy w prawo
            r--; // r przesuwamy w lewo
        }
    };
    //jeœli nie ma ju¿ czego zamieniac, czyli jeœli zawsze napotkane l > r,
    //to dzielimy tablice na dwie mniejsze i robimy z nimi to samo.
    if( left < r ) QuickSort( tab, left, r );
    if( l < right ) QuickSort( tab, l, right );
}

//template < typename object_t >
void ShellSort(long tab[], long left, long right)
{
    long length = right;
    long pivot = length / 2;

    while(pivot > 0){

        long j = 0;
        for(long i = pivot; i < length; i++){

            long temp = tab[i];

            for(j = i; j >= pivot && tab[j - pivot] > temp; j -= pivot)
            {
                tab[j] = tab[j - pivot];
            }
            tab[j] = temp;
        }

        pivot = pivot / 2;

    }

}

template < typename object_t >
void BubbleSort(object_t tab[], int tabLength)
{
    for (int j = 0; j < tabLength-1; j++)
    {
        for(int i = 0; i < tabLength-1; i++)
        {
            if(tab[i] > tab[i+1])
            {
                object_t tmp = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = tmp;
            }
        }
    }

}

void MaxHeap(long tab[], long length, long parent_idx)
{
	int max_idx = parent_idx;
	int child_left = parent_idx *2 + 1;
	int child_right = parent_idx *2 + 2;

	if(child_left < length && tab[child_left] > tab[max_idx]) max_idx = child_left;
	if(child_right < length && tab[child_right] > tab[max_idx]) max_idx = child_right;
	if(max_idx != parent_idx)
	{
		long tmp = tab[parent_idx];
		tab[parent_idx] = tab[max_idx];
		tab[max_idx] = tab[tmp];
		MaxHeap(tab, length, max_idx);
	}
}


void HeapSort(long tab[], long left, long right)
{
	long length = right - left;

	for (long i = length/2; i > 0; i--) MaxHeap(tab, length, i);
	for (long j = length - 1; j > 0; j--)
	{
		long tmp = tab[0];
		tab[0] = tab[j];
		tab[j] = tmp;
		length--;
		MaxHeap(tab, length, 0);
	}
}


template <typename object_t>
static void swap(object_t array[], int idx1, int idx2)		//Swapping two choosen elements of array
{
	object_t tmp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = tmp;
}


template <typename object_t>
int isplit(object_t tab[], long left, long right)
{
	object_t pivot_value;			int pivot_idx;
	int idx_tmp1, idx_tmp2;

	pivot_idx = left + rand()%(right - left);	//Losowy wybór pivota
	pivot_value = tab[pivot_idx];
	swap(tab, pivot_idx, right);
	idx_tmp1 = left;

	for(idx_tmp2 = left; idx_tmp2 <= right -1; idx_tmp2++)
	{
		if(tab[idx_tmp2] < pivot_value)
		{
			swap(tab, idx_tmp2, idx_tmp1);
			idx_tmp1++;
		}
	}
	swap(tab, idx_tmp1, right);
	return idx_tmp1;
}

template <typename object_t>
void _IntroSort(object_t array[], int start_idx, int end_idx, int max_depth )
{
    if ( start_idx < end_idx )
    {
        if( !max_depth  )
        {
            HeapSort(array, start_idx, end_idx);
            return;
        }
        int n = isplit(array, start_idx, end_idx);
        _IntroSort(array, start_idx, n-1, max_depth-1 );
        _IntroSort(array, n+1, end_idx, max_depth-1 );
    }
}

template <typename object_t>
void IntroSort(object_t array[], int start_idx, int end_idx )
{
	int n = start_idx - end_idx;
	int m = int(2*log(double(n)));
	_IntroSort<object_t>(array, start_idx, end_idx, m);
	//qS(array, start_idx, end_idx);
}


void prep_tab(long* tab, long size, float sort_factor, bool inv)
{
	if (inv == 0)
	{
	    for(long i = 0; i < (size*sort_factor); i++)
	    {
	        tab[i] = i;
	    }

	    for(long j = (size*sort_factor); j < size; j++)
	    {
	        tab[j] = rand();
	    }
	}else
	{
	    for(long i = 0; i < (size*sort_factor); i++)
	    {
	        tab[i] = (size*sort_factor)-i;
	    }
	    for(long j = (size*sort_factor); j < size; j++)
	    {
	        tab[j] = rand();
	    }
	}

}

int main() {

    fstream plik;
    clock_t start;
    clock_t stop;
    double time;


    long* merge_tab = (long*)malloc(1000000*sizeof(long));
    long* tab = (long*)malloc(1000000*sizeof(long));
    plik.open("F://Programowanie//Eclipse_Workspace//PAMSI1//src//wyniki.txt", ios::out);
    //10k,50k,100k,500k,1M
    int tab_s[] = {1,5,10,50,100};
    float tab_f[] = {0, 0.25, 0.50, 0.75, 0.95, 0.990, 0.997, 0};

    for(int sort_type = 0; sort_type < 3; sort_type++)
    {
        switch(sort_type)
        {
        	case 0:
        		plik << "--------------------------- QUICK ---------------------------\n";
        		break;
        	case 1:
        		plik << "--------------------------- MERGE ---------------------------\n";
        		break;
        	case 2:
        	    plik << "--------------------------- INTRO ---------------------------\n";

        }

        for(int tab_si = 0; tab_si < 5; tab_si++)
        {
            plik << "----------- size " << tab_s[tab_si] << "------------ " << "\n";

            for(int tab_sf = 0; tab_sf < 8; tab_sf++)
            {
                plik << "------------- sorted: " << tab_f[tab_sf] << " --------------\n";
                if(tab_sf == 7) plik << "--------- INVERTED --------- \n";

                for(int j = 0; j<100; j++)
                {
                	if(tab_sf == 7)prep_tab(tab, 10000*tab_s[tab_si], tab_f[tab_sf],1);
                	else prep_tab(tab, 10000*tab_s[tab_si], tab_f[tab_sf],0);



                    start = clock();

                    switch(sort_type)
                    {
                        case 0:
                            QuickSort(tab, 0, 10000* tab_s[tab_si]);
                        break;

                        case 1:
                        	MergeSort(tab, merge_tab, 0, 10000* tab_s[tab_si], 0);
                        break;

                        case 2:
                            IntroSort<long>(tab, 0, 10000* tab_s[tab_si]);
                    }
                    stop = clock();

                    time = (double)(stop-start) / CLOCKS_PER_SEC;
                    plik << time << endl;

                    cout << "->";
                }
            }

        }
    }



    plik.close();

    cout << endl << "wykonano wszystko" << endl;

    return 0;
}


