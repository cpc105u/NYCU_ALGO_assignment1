/*
*

3
3
0 0
0 1
1 0
4
6 4
9 2
8 7
3 7
5
7.377359 3.113089
8.899004 4.047913
3.929112 9.695250
8.377879 7.799725
5.508218 2.498832


1.000000
3.605551
1.785861
*
*
*/

#include <math.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

typedef struct _POS
{
    double x;
    double y;
} POS;


// --------------------------------------------------
// fast sorting
void merge_sort_recursive( POS arr[], POS reg[], int start, int end ) {
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2)
    {
        if( arr[start1].x <= arr[start2].x )
            reg[k++] =  arr[start1++] ;
        else
            reg[k++] = arr[start2++];

    }
    while (start1 <= end1)
    {
        reg[k++] = arr[start1++];
    }

    while (start2 <= end2)
    {
        reg[k++] = arr[start2++];
    }
    for (k = start; k <= end; k++)
    {
        arr[k] = reg[k];
    }
}


double combine(POS a[], int low, int mid, int high, double &d )
{
    int i , k ;
    double dx , dy ;
    double temp ;
    double line = (double)(a[mid].x + a[mid + 1].x) * 0.5; //line:the x axis of middle line of left set and right set
    double &min_D = d;

    for ( i = mid + 1; a[i].x < line + d && i <= high; i++)
    {
        //list all point of left set and right set range in line+-d
        for ( k = mid; a[k].x > line - d && k >= low; k--)
        {
            dx = a[i].x - a[k].x ;
            dy = a[i].y - a[k].y ;
            temp = dx * dx + dy * dy ;
            if (temp < min_D)
                min_D = temp;
        }
    }
    return min_D ;
}

double divide(POS a[], int low, int high, POS* tempPos, double &minValue)
{
    if (low >= high) return minValue;
    
    int mid = (low + high) / 2;
    double min_left = divide(a, low, mid, tempPos, minValue);
    double min_right = divide(a, mid + 1, high, tempPos, minValue);
    // find the smallest
    return combine(a, low, mid, high,  minValue );
}



int main()
{
    int rounds ;
    int nums_of_point;
    POS *point = new POS[100001];
    POS *tempPos = new POS[100001];
    double dis ;

    cin >> rounds;
    for( ; rounds > 0 ; --rounds )
    {
        cin >> nums_of_point ;
        for (int i = 0; i < nums_of_point; i++)
            cin >> point[i].x >> point[i].y ;

        merge_sort_recursive( point , tempPos , 0 , nums_of_point - 1 );
        dis = INFINITY;
        dis = sqrt( divide(point, 0, nums_of_point - 1, tempPos, dis));

        cout << setprecision(6) <<  fixed <<dis <<endl ;

    }

    return 0;
}

