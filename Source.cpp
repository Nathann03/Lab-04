#include <iostream>
#include <string.h>
#include <chrono>
#include <string>
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

// --------------------------------------------------------------------------

//Linked List containing student name and mnumber
struct student {
	int mnumber;
	std::string Firstname;
	std::string Lastname;
	student* next;
	//operator overloading to comapre mnumber
	bool operator<(const student& rhs) const {
		return mnumber < rhs.mnumber;
	}
	bool operator>(const student& rhs) const {
		return mnumber > rhs.mnumber;
	}
	bool operator==(const student& rhs) const {
		return mnumber == rhs.mnumber;
	}
};

//linked list 
class linkedList {
private:
	
public:
	student* head, * tail;
	linkedList() {
		head = NULL;
		tail = NULL;
	}

	// pop last node and return pointer to that node
	student* pop() {
		student* temp = head;
		student* prev = NULL;
		while (temp->next != NULL) {
			prev = temp;
			temp = temp->next;
		}
		prev->next = NULL;
		tail = prev;
		return temp;
	}
	
	// add node in sorted order
	void addNode(student* node) {
		student* temp = head;
		student* prev = NULL;
		if (head == NULL) {
			head = node;
			tail = node;
			return;
		}
		while (temp != NULL && *node > *temp) {
			prev = temp;
			temp = temp->next;
		}
		if (prev == NULL) {
			node->next = head;
			head = node;
		}
		else if (temp == NULL) {
			tail->next = node;
			tail = node;
		}
		else {
			prev->next = node;
			node->next = temp;
		}
	}
	
	void createNode(int mnumber, std::string Firstname, std::string Lastname) {
		student* temp = new student;
		temp->mnumber = mnumber;
		temp->Firstname = Firstname;
		temp->Lastname = Lastname;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}
	void display() {
		student* temp = new student;
		temp = head;
		while (temp != NULL) {
			std::cout << temp->mnumber << " " << temp->Firstname << " " << temp->Lastname << std::endl;
			temp = temp->next;
		}
	}
	//insert node at the end of the list and check if the list is empty
	void insertNode(int mnumber, std::string Firstname, std::string Lastname) {
		student* temp = new student;
		temp->mnumber = mnumber;
		temp->Firstname = Firstname;
		temp->Lastname = Lastname;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}


	//sort the list using bubble sort based on mnumber
	void bubbleSort() {
		student* temp = new student;
		student* temp1 = new student;
		for (temp = head; temp != NULL; temp = temp->next) {
			for (temp1 = temp->next; temp1 != NULL; temp1 = temp1->next) {
				if (temp->mnumber > temp1->mnumber) {
					int mnumber = temp->mnumber;
					std::string Firstname = temp->Firstname;
					std::string Lastname = temp->Lastname;
					temp->mnumber = temp1->mnumber;
					temp->Firstname = temp1->Firstname;
					temp->Lastname = temp1->Lastname;
					temp1->mnumber = mnumber;
					temp1->Firstname = Firstname;
					temp1->Lastname = Lastname;
				}
			}
		}
	}

	//sort the list using merge sort based on mnumber
    student* mergeList(student* ll1, student* ll2) { //function for merging two sorted list
        student* newhead = NULL;
        if (ll1 == NULL)
            return ll2;
        if (ll2 == NULL)
            return ll1;
        //recursively merge the lists
        if (ll1->mnumber <= ll2->mnumber) {
            newhead = ll1;
            newhead->next = mergeList(ll1->next, ll2);
        }
        else {
            newhead = ll2;
            newhead->next = mergeList(ll1, ll2->next);
        }
        return newhead;
    }
    void splitList(student* start, student** ll1, student** ll2) {
        //similar to flyod's tortoise algorithm
        student* slow = start;
        student* fast = start->next;
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *ll1 = start;
        *ll2 = slow->next;
        //spliting
        slow->next = NULL;
    }
    void mergeSort(student** start) {
        student* head = *start;
        student* ll1, * ll2;
        //base case
        if (head == NULL || head->next == NULL) {
            return;
        }
        splitList(head, &ll1, &ll2); //split the list in two halves
        //sort left and right sublists
        mergeSort(&ll1);
        mergeSort(&ll2);
        //merge two sorted list
        *start = mergeList(ll1, ll2);
        return;
	}


    void insertionSort(student** head_ref){
	    student* sorted = NULL;
	    student* current = *head_ref;
	    while (current != NULL) {
		    student* next = current->next;
		    sortedInsert(&sorted, current);
		    current = next;
	    }
	    // Update head_ref to point to sorted linked list
	    *head_ref = sorted;
	}
	
	void sortedInsert(student** head_ref, student* new_node) {
		student* current;
		// Special case for the head end
		if (*head_ref == NULL || (*head_ref)->mnumber >= new_node->mnumber) {
			new_node->next = *head_ref;
			*head_ref = new_node;
		}
		else {
			// Locate the node before the point of insertion
			current = *head_ref;
			while (current->next != NULL && current->next->mnumber < new_node->mnumber) {
				current = current->next;
			}
			new_node->next = current->next;
			current->next = new_node;
		}
	}
	
		

};

// test program for the linked list class and sorting
void test_program() {
    bool linked = false;
    std::string input = "";
    std::string prompt = "Select an option: \n1. Use a linked list to store the data (will generate random data) \n2. Use an array to store the data (will generate random data)";
	std::cout << prompt << std::endl;
	std::cin >> input;
    if (input == "1") {
        linked = true;
    }
    else if (input == "2") {
        linked = false;
    }
    else {
		std::cout << "Invalid Input. Input must be 1 or 2" << std::endl;
        return;
    }
	
    if (linked) {

        linkedList list;
        std::cout << "How many students do you want to generate?" << std::endl;
        int num;
        std::cin >> num;
        for (int i = 0; i < num; i++) {
            int mnumber = rand() % 1000000;
            std::string Firstname = "First" + std::to_string(i);
            std::string Lastname = "Last" + std::to_string(i);
            list.insertNode(mnumber, Firstname, Lastname);
        }
		
        std::cout << "Unsorted Linked list:" << std::endl;
        list.display();
		
		std::cout << "Select an option: \n1. Bubble Sort \n2. Merge Sort \n3. Insertion Sort" << std::endl;
		std::cin >> input;
		if (input == "1") {
			std::cout << "Bubble Sort" << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			list.bubbleSort();
			auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed_ms = end - start;
            std::chrono::duration<double, std::nano> elapsed_us = end - start;
            std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
            std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
		}
		else if (input == "2") {
			std::cout << "Merge Sort" << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			list.mergeSort(&list.head);
			auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed_ms = end - start;
            std::chrono::duration<double, std::nano> elapsed_us = end - start;
            std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
            std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
		}
		else if (input == "3") {
			std::cout << "Insertion Sort" << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			list.insertionSort(&list.head);
			auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed_ms = end - start;
            std::chrono::duration<double, std::nano> elapsed_us = end - start;
			std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
            std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
		}
		else {
			std::cout << "Invalid Input. Choose a integer between 1 and 3, inclusive" << std::endl;
			return;
		}

        std::cout << "Sorted Linked list:" << std::endl;
        list.display();

		
	}
	else {
        std::cout << "Note: Current array size is set at 25000, if you want to change, go to line 600." << std::endl;

        const int ARRAY_SIZE = 100;

        int rand_array[ARRAY_SIZE];

        for (int i = 0; i < ARRAY_SIZE; i++) {
            rand_array[i] = rand() % (2 * ARRAY_SIZE);  //Generate number between 0 and 2 * the size of the array
        }

		std::cout << "Unsorted Array:" << std::endl;
		for (int i = 0; i < ARRAY_SIZE; i++) {
			std::cout << rand_array[i] << " ";
		}
        std::cout << std::endl;
		
		
		std::cout << "Select an option: \n1. Bubble Sort \n2. Insertion Sort \n3. Merge Sort \n4. Quick Sort \n5. Heap Sort \n 6. Counting Sort \n 7. Radix sort" << std::endl;
		std::cin >> input;
		if (input == "1") {
			std::cout << "Bubble Sort" << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			bubbleSort(rand_array, ARRAY_SIZE);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed_ms = end - start;
			std::chrono::duration<double, std::nano> elapsed_us = end - start;
			std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
			std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
		}
		else if (input == "2") {
			std::cout << "Insertion Sort" << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			insertionSort(rand_array, ARRAY_SIZE);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed_ms = end - start;
			std::chrono::duration<double, std::nano> elapsed_us = end - start;
			std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
			std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
		}
		else if (input == "3") {
			std::cout << "Merge Sort" << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			mergeSort(rand_array, 0, ARRAY_SIZE - 1);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed_ms = end - start;
			std::chrono::duration<double, std::nano> elapsed_us = end - start;
			std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
			std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
		}
		else if (input == "4") {
			std::cout << "Quick Sort" << std::endl;
			auto start = std::chrono::high_resolution_clock::now();
			quickSort(rand_array, 0, ARRAY_SIZE - 1);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed_ms = end - start;
			std::chrono::duration<double, std::nano> elapsed_us = end - start;
			std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
			std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
        }
        else if (input == "5") {
            std::cout << "Heap sort" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
			heapSort(rand_array, ARRAY_SIZE);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed_ms = end - start;
            std::chrono::duration<double, std::nano> elapsed_us = end - start;
            std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
            std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
        }
        else if (input == "6") {
            std::cout << "Counting sort" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
			countsort(rand_array, ARRAY_SIZE);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed_ms = end - start;
            std::chrono::duration<double, std::nano> elapsed_us = end - start;
            std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
            std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
        }
        else if (input == "7") {
            std::cout << "Radix sort" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
			radixsort(rand_array, ARRAY_SIZE);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed_ms = end - start;
            std::chrono::duration<double, std::nano> elapsed_us = end - start;
            std::cout << "Time taken: " << elapsed_ms.count() << " milliseconds" << std::endl;
            std::cout << "Time taken: " << elapsed_us.count() << " nanoseconds" << std::endl;
        }
        else {
            std::cout << "Invalid input! Input an integer between 1 and 7, inclusive." << std::endl;
            return;
        }

        std::cout << "Sorted Array:" << std::endl;
        for (int i = 0; i < ARRAY_SIZE; i++) {
            std::cout << rand_array[i] << " ";
        }
		
    }
}





int main() {

    test_program();
	
	//linkedList list;
	//list.insertNode(321, "John", "Smith");
	//list.insertNode(221, "Jane", "Doe");
	//list.insertNode(31, "Bob", "Smith");
	//list.insertNode(433, "Sally", "Doe");
	//list.insertNode(52, "Joe", "Smith");
	//list.insertNode(6, "Mary", "Doe");
	//list.insertNode(71, "Bill", "Smith");

	//std::cout << "Unsorted List: " << std::endl;
	//list.display();
	//std::cout << "Sorted List: " << std::endl;
	////merge sort list
	//list.insertionSort(&list.head);
	//list.display();




		//const int ARRAY_SIZE = 10;

		//int rand_array[ARRAY_SIZE];

		//for (int i = 0; i < ARRAY_SIZE; i++) {
		//    rand_array[i] = rand() % (2 * ARRAY_SIZE);  //Generate number between 0 and 2 * the size of the array
		//}

		//auto t1 = Clock::now();
		//radixsort(rand_array, ARRAY_SIZE);
		//auto t2 = Clock::now();

		//std::cout << "Sorted Array in Ascending Order:\n";
		//printArray(rand_array, ARRAY_SIZE);


		//std::cout << "Delta t2-t1: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " milliseconds" << std::endl;
		//std::cout << "Delta t2-t1: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanosec" << std::endl;
};