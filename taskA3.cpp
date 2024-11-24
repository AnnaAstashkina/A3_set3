#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>

class ArrayGenerator {
 public:
  static std::vector<int> generateRandomArray() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<> distr(0, 6000);
    std::vector<int> arr(10000);
    for (int i = 0; i < 10000; ++i) {
      arr[i] = distr(generator);
    }
    return arr;
  }

  static std::vector<int> generateReverseSortedArray() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<> distr(0, 6000);
    std::vector<int> arr(10000);
    for (int i = 0; i < 10000; ++i) {
      arr[i] = distr(generator);
    }
    std::sort(arr.begin(), arr.end());
    std::reverse(arr.begin(), arr.end());
    return arr;
  }

  static std::vector<int> generateNearlySortedArray() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<> distr(0, 6000);
    std::vector<int> arr(10000);
    for (int i = 0; i < 10000; ++i) {
      arr[i] = distr(generator);
    }
    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < 15; ++i) {
      std::uniform_int_distribution<> distrs(0, 500);
      int idx1 = distrs(generator);
      int idx2 = distrs(generator);
      std::swap(arr[idx1], arr[idx2]);
    }
    for (int i = 500; i <= 9900; i += 100) {
      std::uniform_int_distribution<> distrs(i, i + 100);
      for (int j = 0; j < 3; ++j) {
        int idx1 = distrs(generator);
        int idx2 = distrs(generator);
        std::swap(arr[idx1], arr[idx2]);
      }
    }
    return arr;
  }
};

class SortTester {
 private:
  static int left(int i, int start) {
    return start + 2 * (i - start) + 1;
  }
  static int right(int i, int start) {
    return start + 2 * (i - start) + 2;
  }

  static void insertionSort(std::vector<int>& vect, int start, int end) {
    for (int i = start + 1; i <= end; ++i) {
      int key = vect[i];
      int j = i - 1;
      while (j >= start && vect[j] > key) {
        vect[j + 1] = vect[j];
        j--;
      }
      vect[j + 1] = key;
    }
  }

  static void heapify(std::vector<int>& A, int i, int start, int end) {
    int j = i;
    int lef = left(i, start);
    int righ = right(i, start);
    if (lef <= end && A[lef] > A[j]) {
      j = lef;
    }
    if (righ <= end && A[righ] > A[j]) {
      j = righ;
    }
    if (j != i) {
      std::swap(A[j], A[i]);
      heapify(A, j, start, end);
    }
  }

  static void buildMaxHeap(std::vector<int>& A, int start, int end) {
    int n = end - start + 1;
    for (int i = n / 2 - 1; i > -1; --i) {
      heapify(A, i + start, start, end);
    }
  }

  static void heapSort(std::vector<int>& A, int start, int end) {
    buildMaxHeap(A, start, end);
    for (int i = end; i > start; --i) {
      std::swap(A[i], A[start]);
      heapify(A, start, start, i - 1);
    }
  }

  static int partition(std::vector<int>& vect, int start, int end) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<> distr(start, end);
    int ind = distr(generator);
    std::swap(vect[ind], vect[end]);
    int pivot = vect[end];
    int i = start - 1;
    for (int j = start; j < end; ++j) {
      if (vect[j] <= pivot) {
        ++i;
        std::swap(vect[i], vect[j]);
      }
    }
    std::swap(vect[i + 1], vect[end]);
    return i + 1;
  }

  static void quickSort(std::vector<int>& vect, int start, int end) {
    if (start >= end) {
      return;
    }
    int pivot = partition(vect, start, end);
    quickSort(vect, start, pivot - 1);
    quickSort(vect, pivot + 1, end);
  }

  static void introsort(std::vector<int>& vect, int start, int end, int depth) {
    if (start >= end) {
      return;
    }
    if (end - start + 1 <= 15) {
      insertionSort(vect, start, end);
      return;
    }
    if (depth >= 2 * std::log2(vect.size())) {
      heapSort(vect, start, end);
      return;
    }
    int pivot = partition(vect, start, end);
    introsort(vect, start, pivot - 1, depth + 1);
    introsort(vect, pivot + 1, end, depth + 1);
  }

 public:
  static long long testQuickSort(std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }

  static long long testIntroSort(std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    introsort(arr, 0, arr.size() - 1, 0);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }
};

template <typename T>
void printVector(const std::vector<T>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << ", ";
  }
  std::cout << std::endl << std::endl;
}

int main() {
  std::vector<int> randomArrParent = ArrayGenerator::generateRandomArray();
  std::vector<int> reverseArrParent = ArrayGenerator::generateReverseSortedArray();
  std::vector<int> nearlySortedArrParent = ArrayGenerator::generateNearlySortedArray();
  double timeQuickArr;
  double timeIntrosortArr;
  double timeQuickReverse;
  double timeIntrosortReverse;
  double timeQuickNear;
  double timeIntrosortNear;
  std::vector<double> vecTimeQuickArr;
  std::vector<double> vecTimeIntrosortArr;
  std::vector<double> vecTimeQuickReverse;
  std::vector<double> vecTimeIntrosortReverse;
  std::vector<double> vecTimeQuickNear;
  std::vector<double> vecTimeIntrosortNear;
  std::vector<int> is;
  for (int i = 500; i <= 10000; i += 100) {
    is.push_back(i);
    for (int j = 0; j < 5; ++j) {
      std::vector<int> randomArr = std::vector<int>(randomArrParent.begin(), randomArrParent.begin() + i);
      timeQuickArr += SortTester::testQuickSort(randomArr);
      randomArr = std::vector<int>(randomArrParent.begin(), randomArrParent.begin() + i);
      timeIntrosortArr += SortTester::testIntroSort(randomArr);

      std::vector<int> reverseArr = std::vector<int>(reverseArrParent.begin(), reverseArrParent.begin() + i);
      timeQuickReverse += SortTester::testQuickSort(reverseArr);
      reverseArr = std::vector<int>(reverseArrParent.begin(), reverseArrParent.begin() + i);
      timeIntrosortReverse += SortTester::testIntroSort(reverseArr);

      std::vector<int> nearlySortedArr =
          std::vector<int>(nearlySortedArrParent.begin(), nearlySortedArrParent.begin() + i);
      timeQuickNear += SortTester::testQuickSort(nearlySortedArr);
      nearlySortedArr = std::vector<int>(nearlySortedArrParent.begin(), nearlySortedArrParent.begin() + i);
      timeIntrosortNear += SortTester::testIntroSort(nearlySortedArr);
    }
    timeQuickArr /= 5.;
    timeIntrosortArr/=5.;
    timeQuickReverse /= 5.;
    timeIntrosortReverse /= 5.;
    timeQuickNear /= 5.;
    timeIntrosortNear /= 5.;

    vecTimeQuickArr.push_back(timeQuickArr);
    vecTimeIntrosortArr.push_back(timeIntrosortArr);
    vecTimeQuickReverse.push_back(timeQuickReverse);
    vecTimeIntrosortReverse.push_back(timeIntrosortReverse);
    vecTimeQuickNear.push_back(timeQuickNear);
    vecTimeIntrosortNear.push_back(timeIntrosortNear);
  }
  printVector(is);
  printVector(vecTimeQuickArr);
  printVector(vecTimeIntrosortArr);
  printVector(vecTimeQuickReverse);
  printVector(vecTimeIntrosortReverse);
  printVector(vecTimeQuickNear);
  printVector(vecTimeIntrosortNear);
}