#include <iostream>
#include <vector>
#include <cmath>
#include <random>

int parent(int i) {
  return i / 2 - (i + 1) % 2;
}
int left(int i, int start) {
  return start + 2 * (i - start) + 1;
}
int right(int i, int start) {
  return start + 2 * (i - start) + 2;
}

void insertionSort(std::vector<int>& vect, int start, int end) {
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

void heapify(std::vector<int>& A, int i, int start, int end) {
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

void buildMaxHeap(std::vector<int>& A, int start, int end) {
  int n = end - start + 1;
  for (int i = n / 2 - 1; i > -1; --i) {
    heapify(A, i + start, start, end);
  }
}

void heapSort(std::vector<int>& A, int start, int end) {
  buildMaxHeap(A, start, end);
  for (int i = end; i > start; --i) {
    std::swap(A[i], A[start]);
    heapify(A, start, start, i - 1);
  }
}

int partition(std::vector<int>& vect, int start, int end) {
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

void quickSort(std::vector<int>& vect, int start, int end) {
  if (start >= end) {
    return;
  }
  int pivot = partition(vect, start, end);
  quickSort(vect, start, pivot - 1);
  quickSort(vect, pivot + 1, end);
}

void introsort(std::vector<int>& vect, int start, int end, int depth) {
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<int> vect(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vect[i];
  }
  introsort(vect, 0, n - 1, 0);
  for (int i = 0; i < n; ++i) {
    std::cout << vect[i] << " ";
  }
  return 0;
}