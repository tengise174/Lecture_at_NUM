#include "my_qsort.h"
#include <stdio.h>
/*
  quicksort эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
*/
#ifndef CUTOFF
#define CUTOFF 10
#endif

static int init_seed = 0; // Random seed 1 удаа эхлүүлнэ

/*
  Оруулан эрэмбэлэх функц.
  [lo, hi] завсрах тоонуудыг оруулан эрэмбэлэх аргаар эрэмбэлнэ.
*/
static void insertion_sort(int a[], int lo, int hi)
{
        /* Оруулан эрэмбэлэх аргыг хэрэгжүүл */
        int i, j;
        for (i = lo + 1; i <= hi; i++)
        {
                int tmp = a[i];
                for (j = i; j > lo && tmp < a[j - 1]; j--)
                        a[j] = a[j - 1];
                a[j] = tmp;
        }
}

/*
  Хоёр утгыг хооронд солих функц
*/
static void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

/*
  [lo, hi] завсрыг санамсаргүйгээр холих функц.
*/
static void random_shuffle(int a[], int lo, int hi)
{
        if (init_seed == 0)
        {
                srand(time(NULL));
                init_seed = 1;
        }
        int i, j;
        for (i = lo; i <= hi; i++)
        {
                j = rand() % (hi - lo) + lo;
                swap(&a[i], &a[j]);
        }
}

/*
  1-pivot хурдан эрэмбэлэх функц.
*/
static void _single_pivot_qsort(int a[], int lo, int hi)
{
        /* Энд quicksort хэрэгжүүл */
        if (hi <= lo + CUTOFF)
        {
                insertion_sort(a, lo, hi);
                return;
        }

        int i = lo, j = hi + 1;
        int pivot = a[lo];
        while (1)
        {
                while (a[++i] < pivot)
                        if (i == hi)
                                break;
                while (a[--j] > pivot)
                        if (j == lo)
                                break;
                if (i >= j)
                {
                        break;
                }
                swap(&a[i], &a[j]);
        }
        swap(&a[lo], &a[j]);
        _single_pivot_qsort(a, lo, j - 1);
        _single_pivot_qsort(a, j + 1, hi);
}

/*
  wrapper function for _single_pivot_qsort
  _single_pivot_qsort-ыг дуудахад ашиглах функц
 */
void single_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _single_pivot_qsort(a, lo, hi);
}

/*
  Dual-pivot хурдан эрэмбэлэх функц
*/
static void _dual_pivot_qsort(int a[], int lo, int hi)
{
        /*
          Энд dual-pivot quicksort хэрэгжүүл
        */
        if (hi <= lo + CUTOFF)
        {
                insertion_sort(a, lo, hi);
                return;
        }

        if (a[lo] > a[hi])
        {
                swap(&a[lo], &a[hi]);
        }
        int pivot1 = a[lo];
        int pivot2 = a[hi];

        int i = lo + 1, j = hi - 1;
        int k = i;
        while (k <= j)
        {
                if (a[k] < pivot1)
                {
                        swap(&a[i++], &a[k++]);
                }
                else if (a[k] > pivot2)
                {
                        swap(&a[k], &a[j--]);
                }
                else
                {
                        k++;
                }
        }
        swap(&a[lo], &a[--i]);
        swap(&a[hi], &a[++j]);
        _dual_pivot_qsort(a, lo, i - 1);
        if (pivot1 < pivot2)
        {
                _dual_pivot_qsort(a, i + 1, j - 1);
        }
        _dual_pivot_qsort(a, j + 1, hi);
}
/*
  wrapper function for _dual_pivot_qsort
  _dual_pivot_qsort-ыг дуудахад ашиглах функц
*/
void dual_pivot_qsort(int a[], int lo, int hi)
{
        random_shuffle(a, lo, hi);
        _dual_pivot_qsort(a, lo, hi);
}
