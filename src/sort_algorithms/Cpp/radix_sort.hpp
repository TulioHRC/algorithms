#ifndef RADIX_SORT_H
#define RADIX_SORT_H

template <typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T, typename C>
bool getBit(T number, C bitPosition)
{
  if (bitPosition == 8 * (C)sizeof(T)){
    return (number < 0) ? 0 : 1;
  }
  return ((number & (static_cast<T>(1) << bitPosition)) != 0);
}

template <typename T, typename C>
void sortByBit(T* vector, C &left, C &right, C bitPosition)
{
  while(left <= right)
  {
    while(left <= right && getBit(vector[left], bitPosition) == 0) left++;
    while(left <= right && getBit(vector[right], bitPosition) == 1) right--;
    if(left <= right){
      swap(&vector[left], &vector[right]);
      left++;
      right--;
    }
  }
}

template <typename T, typename C>
void radixSortBinary(T* vector, C start, C end, C bit) {
  if (bit < 0 || start >= end) return;
  C left = start;
  C right = end;

  sortByBit(vector, left, right, bit);
  radixSortBinary(vector, start, right, bit - 1);
  radixSortBinary(vector, left, end, bit - 1);
}

template <typename T, typename C>
void radixSort(T* vector, C start, C end) {
  C bit = 8 * (C)sizeof(T);
  radixSortBinary(vector, start, end, bit);
}

#endif