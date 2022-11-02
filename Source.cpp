#include <iostream>
#include <string.h>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


void bubbleSort(int array[], int size) {
    for (int step = 0; step < (size - 1); ++step) {
        int swapped = 0;

        for (int i = 0; i < (size - step - 1); ++i) {

            if (array[i] > array[i + 1]) {

                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }
}


// -----------------------------------------------------------------------


void insertionSort(int array[], int size) {
    for (int step = 1; step < size; step++) {
        int key = array[step];
        int j = step - 1;


        while (key < array[j] && j >= 0) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}


// ------------------------------------------------------------------------


void merge(int array[], int const left, int const mid,
    int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;


    auto* leftArray = new int[subArrayOne],
        * rightArray = new int[subArrayTwo];


    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne
        = 0, 
        indexOfSubArrayTwo
        = 0; 
    int indexOfMergedArray
        = left; 


    while (indexOfSubArrayOne < subArrayOne
        && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete[] leftArray;
    delete[] rightArray;
}


void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}


// ---------------------------------------------------------------------


void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int low, int high) {


    int pivot = array[high];

    int i = (low - 1);


    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            i++;

            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);

    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {

        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);


        quickSort(array, pi + 1, high);
    }
}

// -------------------------------------------------------------------

void heapify(int arr[], int n, int i) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

 
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}


void heapSort(int arr[], int n) {
    
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        
        heapify(arr, i, 0);
    }
}

// -----------------------------------------------------------


void countsort(int arr[], int n) {
    int max, min, id;
    int i, j;
    //find max, min. 
    max = min = arr[0];
    for (i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    //output array. 
    int range = max - min + 1;
    int* output = new int[range];
    for (i = 0; i < range; i++)
    {
        output[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        output[arr[i] - min] ++;
    }

    id = 0;
    for (i = min; i <= max; i++)
    {
        for (j = 0; j < output[i - min]; j++)
        {
            arr[id++] = i;
        }
    }
    //restore heap. 
    delete[] output;
}

// --------------------------------------------------------------------------------------------------

int maxbit(int data[], int n) 
{
    int d = 1;
    int p = 10;
    for (int i = 0; i < n; ++i)
    {
        while (data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;
}

void radixsort(int data[], int n) 
{
    int d = maxbit(data, n);
    int* tmp = new int[n];
    int* count = new int[10]; 
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) 
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; 
        for (j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; 
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for (j = n - 1; j >= 0; j--) 
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) 
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[]tmp;
    delete[]count;
}



void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << "  " << array[i];
    }
    std::cout << "\n";
}

int main() {

    const int ARRAY_SIZE = 10;

    int rand_array[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        rand_array[i] = rand() % (2 * ARRAY_SIZE);  //Generate number between 0 and 2 * the size of the array
    }

    auto t1 = Clock::now();
    radixsort(rand_array, ARRAY_SIZE);
    auto t2 = Clock::now();

    std::cout << "Sorted Array in Ascending Order:\n";
    printArray(rand_array, ARRAY_SIZE);


    std::cout << "Delta t2-t1: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " milliseconds" << std::endl;
    std::cout << "Delta t2-t1: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanosec" << std::endl;
}