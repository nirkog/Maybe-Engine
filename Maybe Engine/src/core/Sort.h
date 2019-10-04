#pragma once

#include <iostream>

namespace mb {

	template<typename T>
	class Comparators
	{
	public:
		static bool Default(const T& a, const T& b)
		{
			return a < b;
		}

		static bool DefaultReverse(const T& a, const T& b)
		{
			return a > b;
		}
	};

	template<typename T>
	class SortAlgorithms
	{
	private:
		static void Swap(T* a, T* b)
		{
			T tmpA = *a;
			*a = *b;
			*b = tmpA;
		}

		static int Partition(T* arr, int low, int high, bool(*comparator)(const T&, const T&))
		{
			T pivot = arr[high]; 
			int i = (low - 1); 

			for (int j = low; j <= high - 1; j++)
			{
				if (comparator(arr[j], pivot))
				{ 
					i++;
					Swap(&arr[i], &arr[j]);
				}
			}
			Swap(&arr[i + 1], &arr[high]);
			return (i + 1);
		}
	public:
		//Comparator should return true if a < b
		static void SelectionSort(T* arr, unsigned int count, bool (*comparator)(const T&, const T&))
		{
			unsigned int minIndex = 0;
			unsigned int i, j;

			for (i = 0; i < count; i++)
			{
				minIndex = i;
				for (j = i; j < count; j++)
					if (comparator(arr[j], arr[minIndex])) minIndex = j;

				Swap(&arr[i], &arr[minIndex]);
			}
		}

		static void BubbleSort(T* arr, unsigned int count, bool(*comparator)(const T&, const T&))
		{
			unsigned int i, swaps;

			do
			{
				swaps = 0;

				for (i = 0; i < count - 1; i++)
				{
					if (comparator(arr[i + 1], arr[i]))
					{
						Swap(&arr[i + 1], &arr[i]);
						swaps++;
					}
				}
			} while (swaps != 0);
		}
	
		static void InsertionSort(T* arr, unsigned int count, bool(*comparator)(const T&, const T&))
		{
			unsigned int i, j;
			T key;

			for (i = 1; i < count; i++)
			{
				key = arr[i];
				j = i - 1;

				while (j >= 0 && comparator(key, arr[j]))
				{
					arr[j + 1] = arr[j];
					j--;
				}

				arr[j + 1] = key;
			}
		}

		static void QuickSort(T* arr, int low, int high, bool(*comparator)(const T&, const T&))
		{
			if (low < high)
			{
				int pi = Partition(arr, low, high, comparator);

				QuickSort(arr, low, pi - 1, comparator);
				QuickSort(arr, pi + 1, high, comparator);
			}
		}

		static void QuickSort(T* arr, unsigned int count, bool(*comparator)(const T&, const T&))
		{
			QuickSort(arr, 0, count - 1, comparator);
		}
	};

}