//-----------------------------------------------------------------------
//
// Name: Dylan Huff
//
// Course: CMPS-5243-270, Spring 2022, Johnson
//
// Purpose: The purpose of this program is to implement three different
// sorting algorithms and use a counter within the algorithms so that you
// can compare the results of each algorithm. The three algorithms will
// each come from a different runtime category: one from O(n squared),
// one from O(n log n), and one from O(n). The algorithms will be ran 20
// times each and the time and counter results for that algorithm will be
// averaged and compared against each other. I will be using bubble sort,
// merge sort, and radix sort. I tested that algorithms using arrays of
// size 20, after that I changed the size to 5000 for the actual testing.
// ----------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <string.h>
#include <time.h>
#include <cmath>

using namespace std;

// Making the counter for merge sort a global variable
int mergecount = 0;

const int SIZE = 5000;
const int cSIZE = 5001;
//const int K = 10000;
//const int KD = 10;


//Prototypes
void makeArray(int arr[], int d);
void copyArray(int arr1[], int arr2[]);
void copyArrayRadix(int arr1[], int arr2[]);
void copyArrayIndexChange(int arr1[], int arr2[]);
void printArray(int arr[]);
void printArrayRadix(int arr[]);
void swap(int &x, int &y);
int bubbleSort(int arr[]);
void printHeading(ofstream& outfile);
void merge(int lft[], int rt[], int a[], int n);
void mergeSort(int a[], int n);
int countingSortDigit(int a[], int b[], int d);
int radixSort(int a[], int d);


int main() {
  ofstream outfile;
  clock_t start, finish;
  outfile.open("testresults.txt");
  // Creating the arrays that will be used
  int arr1[SIZE], arr2[SIZE], arr3[cSIZE];
  // Create counter for bubble sort
  int bubblecount = 0;
  // Create counter for radix sort
  int radixcount = 0;
  printHeading(outfile);
  for(int i = 0; i < 20; i++)
    {
      outfile << "******************** Iteration " << i + 1 << "******************"        << '\n';
      makeArray(arr1, i);
      copyArray(arr1, arr2);
      copyArrayIndexChange(arr1, arr3);
      start = clock();
      bubblecount = bubbleSort(arr1);
      finish = clock();
      outfile << "Bubble sort count:  " << bubblecount << '\n' << '\n';
      outfile << "Time for bubble sort (seconds): ";
      outfile << ((double)(finish - start))/CLOCKS_PER_SEC;
      outfile << '\n' << '\n';
      start = clock();
      mergeSort(arr2, SIZE);
      finish = clock();
      outfile << "Merge sort count: " << mergecount << '\n' << '\n';
      outfile << "Time for merge sort (seconds): ";
      outfile << ((double)(finish - start))/CLOCKS_PER_SEC;
      outfile << '\n' << '\n';
      start = clock();
      radixcount = radixSort(arr3, 4);
      finish = clock();
      outfile << "Radix sort count:  " << radixcount << '\n' << '\n';
      outfile << "Time for sort radix (seconds): ";
      outfile << ((double)(finish - start))/CLOCKS_PER_SEC;
      outfile << '\n' << '\n';
      outfile << '\n' << '\n' << '\n';
      mergecount = 0;
    }
  // makeArray(arr1);
  // copyArray(arr1, arr2);
  // copyArrayIndexChange(arr1, arr3);
  // bubblecount = bubbleSort(arr1);
  // cout << "Bubble sort count:  " << bubblecount << endl;
  // mergeSort(arr2, SIZE);
  // cout << "Merge sort count: " << mergecount << endl;
  // radixcount = radixSort(arr3, 4);
  // cout << "Radix sort count:  " << radixcount << endl;
  return 0;
}


// Functions

// Making the first array using random number generator
void makeArray(int arr[], int d)
{
  srand(d);
  for(int i = 0; i < SIZE; i++)
    arr[i] = rand() % 1000;
}

// Copying the first array to another array so that all three algorithms
// will be used on the same array
void copyArray(int arr1[], int arr2[])
{
  for(int i = 0; i < SIZE; i++)
    arr2[i] = arr1[i];
}

void copyArrayRadix(int arr1[], int arr2[])
{
  for(int i = 1; i < cSIZE; i++)
    arr2[i] = arr1[i];
}


void copyArrayIndexChange(int arr1[], int arr2[])
{
  for(int i = 0; i < SIZE; i++)
    arr2[i + 1] = arr1[i];
}

// Function to print the arrays
void printArray(int arr[])
{
  for(int i = 0; i < SIZE; i++)
    cout << setw(4) << arr[i];
  cout << "\n\n";
}


void printArrayRadix(int arr[])
{
  for(int i = 1; i < cSIZE; i++)
    cout << setw(4) << arr[i];
  cout << "\n\n";
}

// Function used to swap numbers in the bubble sort algorithm
void swap(int &x, int &y)
{
  int temp = x;
  x = y;
  y = temp;
}

// Prints a heading to the console that contains my name, class information
// and program description.
void printHeading(ofstream& outfile)
{
  outfile << "****************************************************************" << endl;
  outfile << "Dylan Huff" << endl;
  outfile << "Course: CMPS-5243-270, Spring 2022, Johnson" << endl; 
  outfile << "Program 2: Sorting Algorithm Comparison" << endl;
  outfile << "-----------------------------Purpose----------------------------" << endl;
  outfile << "The purpose of this program is to implement three different" << endl;
  outfile << "sorting algorithms and use a counter within the algorithms " << endl;
  outfile << "so that you can compare the results of each algorithm. The three " << endl;
  outfile << "algorithms will each come from a different runtime category: one from " << endl;
  outfile << "O(n squared), one from O(n log n), and one from O(n). The " << endl;
  outfile << "algorithms will be ran 20 times each and the time and counter " << endl;
  outfile << "results for that algorithm will be averaged and compared " << endl;
  outfile << "against each other. I will be using bubble sort, merge sort, " << endl;
  outfile << "and radix sort." << endl;
  outfile << "****************************************************************" << endl;
  outfile << '\n';
}


int bubbleSort(int arr[])
{
  bool swapped = true;
  int j = 0, c = 0;
  // Continue to loop until
  // no swaps have occurred. 
  while (swapped)
  {
    // Reset boolean flag
    swapped = false;
    // Because bubbleSort puts the last value in the 
    // correct position eachtime through the loop, the 
    // limit of the inner loop decreases by one each
    // iteration of the outer loop (SIZE -j)
    for(int i = 1; i < SIZE - j; i++)
    {
      c++;
      // compare two side-by-side values
      // and swap if they are out of order
      if(arr[i-1] > arr[i])
      {
        swapped = true;
        swap(arr[i-1], arr[i]);
      }
    }
    j++;
  }
  return c;
}


/***************************************************
Given a left and right array, values are copied
into larger array, a, of size n in sorted order.
****************************************************/
void merge(int lft[], int rt[], int a[], int n)
{
  int i = 0, j = 0, k = 0;
  int lenLft = n / 2;
  int lenRt = n - lenLft;
  // Copy values in ascencing order into array a
  // until end of either left or right array is 
  // reached.
  while (i < lenLft && j < lenRt)
  {
    if (lft[i] < rt[j])
    {
      a[k] = lft[i];
      i++;
      k++;
    }
    else
    {
      a[k] = rt[j];
      j++;
      k++;
    }
  }
  // Copy any remaining values from the
  // left array.
  while(i < lenLft)
  {      
    a[k] = lft[i];
    i++;
    k++; 
  }
  // Copy any remaining values from the
  // right array. 
  while(j < lenRt)
  {
    a[k] = rt[j];
    j++;
    k++;    
  }  
}



void mergeSort(int a[], int n) 
{ 
  int i, mid, *left, *right;
  mergecount++;
  if (n >= 2) 
  {
    mid = n / 2;
    // Dynamically create two new arrays to
    // store the left and right halves of array.
    left = new int[mid];
    right = new int[n - mid];
    // Copy into left and right arrays
    for (i = 0; i < mid; i++)
      left[i] = a[i];
    for (i = mid; i < n; i++)
      right[i-mid] = a[i];
    // Recursively sort the left half of the array.
    mergeSort(left, mid);
    // Recursively sort the right half of the array.
    mergeSort(right, n-mid);
    // Merge the array halves.
    merge(left, right, a, n);
  }
}


int countingSortDigit(int a[], int b[], int d)
{
  int i, j, *c = new int[10];
  // Creating the counter for the radix sort, naming it count instead of c
  // because c is already being used
  int count = 0;
  // Determine place value based on the digit.
  // 1's place = 10^0; 10's place = 10^1; etc.
  int place = pow(10, (d-1));
  // Initialize array c to zero
  for (i = 0; i < 10; i++)
      c[i] = 0;
  // Fill array c with the count of the digits 0-9
  // for the specified digit location, d, of array a.
  // Ex. c[2] = 5 indicates that the array contains     
  // 5 values that have the digit 2 in location d.
  for (i = 1; i < cSIZE; i++)
    {
      c[a[i]/place % 10]++;
      count++;
    }

  // Convert array c to a partial sum array, which
  // indicates the number of elements with the digit
  // value less than or equal to the specified digit.
  for (i = 1; i < 10; i++)
      c[i] += c[i-1];
    

  // Scan array a from the right and copy values
  // into array b based on digit value location 
  // indicated by array c.
  for (j = cSIZE - 1; j > 0; j--)
  {
    b[c[a[j]/place % 10]] = a[j];
    c[a[j]/place % 10]--;
  }
  return count;
}


int radixSort(int a[], int d)
{
  int b[cSIZE];
  int i = 1;
  int c = countingSortDigit(a, b, i);
  for(int i = 1; i <= d; i++)
  {
    countingSortDigit(a, b, i);
    // cout << "Array sorted after digit " << i << ": \n";
    // printArray inside radix sort to show
    // intermediate steps
    // printArrayRadix(b);
    copyArrayRadix(b, a);
    c++;
  }
  return c;
}
