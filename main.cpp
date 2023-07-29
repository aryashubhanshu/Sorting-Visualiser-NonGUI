#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void visualize(const vector<int> &data, int currentIndex, int currentEndIndex) {
  for (int i = 0; i < data.size(); i++) {
    if (i >= currentIndex && i <= currentEndIndex) {
      cout << "\033[1;31m";  // Red color 
    } else {
      cout << "\033[1;32m";  // Green color 
    }
    for (int j = 0; j < data[i]; j++) {
      cout << "=";
    }
    cout << "\033[0m" << endl;  // Reset color
    this_thread::sleep_for(chrono::milliseconds(50));
  }
  cout << endl;
}

void bubbleSort(vector<int> &data) {
  for (int i = 0; i < data.size() - 1; i++) {
    for (int j = 0; j < data.size() - i - 1; j++) {
      if (data[j] > data[j + 1]) {
        swap(data[j], data[j + 1]);
        visualize(data, j, j + 1);
      }
    }
  }
}

void selectionSort(vector<int> &data) {
  for (int i = 0; i < data.size() - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < data.size(); j++) {
      if (data[j] < data[minIndex]) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      swap(data[i], data[minIndex]);
      visualize(data, i, minIndex);
    }
  }
}

void insertionSort(vector<int> &data) {
  for (int i = 1; i < data.size(); i++) {
    int j = i;
    while (j > 0 && data[j - 1] > data[j]) {
      swap(data[j - 1], data[j]);
      j--;
      visualize(data, j, i);
    }
  }
}

void quickSort(vector<int> &data, int start, int end) {
  if (start >= end) {
    return;
  }
  int pivot = data[end];
  int partitionIndex = start;
  for (int i = start; i < end; i++) {
    if (data[i] < pivot) {
      swap(data[i], data[partitionIndex]);
      partitionIndex++;
    }
  }
  swap(data[partitionIndex], data[end]);
  visualize(data, start, end);
  quickSort(data, start, partitionIndex - 1);
  quickSort(data, partitionIndex + 1, end);
}

void merge(vector<int> &data, int start, int mid, int end) {
  int n1 = mid - start + 1;
  int n2 = end - mid;
  vector<int> left(n1);
  vector<int> right(n2);
  for (int i = 0; i < n1; i++) {
    left[i] = data[start + i];
  }
  for (int i = 0; i < n2; i++) {
    right[i] = data[mid + i + 1];
  }
  int i = 0, j = 0, k = start;
  while (i < n1 && j < n2) {
    if (left[i] <= right[j]) {
      data[k] = left[i];
      i++;
    } else {
      data[k] = right[j];
      j++;
    }
    k++;
    visualize(data, start, end);
  }
  while (i < n1) {
    data[k] = left[i];
    i++;
    k++;
    visualize(data, start, end);
  }
  while (j < n2) {
    data[k] = right[j];
    j++;
    k++;
    visualize(data, start, end);
  }
}

void mergeSort(vector<int> &data, int start, int end) {
  if (start < end) {
    int mid = start + (end - start) / 2;
    mergeSort(data, start, mid);
    mergeSort(data, mid + 1, end);
    merge(data, start, mid, end);
  }
}

void heapify(vector<int> &data, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && data[left] > data[largest]) {
    largest = left;
  }
  if (right < n && data[right] > data[largest]) {
    largest = right;
  }
  if (largest != i) {
    swap(data[i], data[largest]);
    visualize(data, i, largest);
    heapify(data, n, largest);
  }
}

void heapSort(vector<int> &data) {
  int n = data.size();
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(data, n, i);
  }
  for (int i = n - 1; i >= 0; i--) {
    swap(data[0], data[i]);
    visualize(data, 0, i);
    heapify(data, i, 0);
  }
}

int main() {
  vector<int> data = { 9, 6, 4, 15, 3, 7 };
  string sortingAlgorithm;
  cout << "Enter the algorithm you want to use:" << endl;
  cout << "1. Quick Sort" << endl;
  cout << "2. Merge Sort" << endl;
  cout << "3. Heap Sort" << endl;
  cout << "4. Bubble Sort" << endl;
  cout << "5. Insertion Sort" << endl;
  cout << "6. Selection Sort" << endl;
  cin >> sortingAlgorithm;
  if (sortingAlgorithm == "1") {
    quickSort(data, 0, data.size() - 1);
  } else if (sortingAlgorithm == "2") {
    mergeSort(data, 0, data.size() - 1);
  } else if (sortingAlgorithm == "3") {
    heapSort(data);
  } else if (sortingAlgorithm == "4") {
    bubbleSort(data);
  } else if (sortingAlgorithm == "5") {
    insertionSort(data);
  } else if (sortingAlgorithm == "6") {
    selectionSort(data);
  } else {
    cout << "Invalid Input" << endl;
  }
  return 0;
}
