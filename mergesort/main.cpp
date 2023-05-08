#include <vector>
#include <future>
#include <iostream>
template<typename T>
void merge(std::vector<T>& arr, size_t start, size_t mid, size_t end) {
    std::vector<T> temp(end - start + 1);
    size_t i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= end) {
        temp[k++] = arr[j++];
    }

    for (i = start; i <= end; i++) {
        arr[i] = temp[i - start];
    }
}

template<typename T>
void mergeSort(std::vector<T>& arr, const size_t start = 0, const size_t end = arr.size()) {
    if (start >= end) {
        return;
    }

    const size_t mid = (start + end) / 2;

    std::future<void> left = std::async(std::launch::async, mergeSort<T>, std::ref(arr), start, mid);
    std::future<void> right = std::async(std::launch::async, mergeSort<T>, std::ref(arr), mid + 1, end);

    left.wait();
    right.wait();

    merge<T>(arr, start, mid, end);
}

int main() {
    std::vector<int> arr{ 5, 2, 7, 1, 8, 3, 6, 4, 9 };

    mergeSort<int>(arr, 0, arr.size() - 1);

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
}