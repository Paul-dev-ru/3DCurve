#include "QuickSort.h"

// Функция для обмена элементов
template<typename T>
void swap(T& a, T& b) 
{
    T temp = a;
    a = b;
    b = temp;
}

// Функция для разделения массива и выбора опорного элемента
template<typename T>
int partition(std::vector<T>& arr, int low, int high) 
{
    T pivot = arr[high];  // Опорный элемент
    int i = (low - 1);    // Индекс меньшего элемента

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Основная функция быстрой сортировки
template<typename T>
void quickSort(std::vector<T>& arr, int low, int high) 
{
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}