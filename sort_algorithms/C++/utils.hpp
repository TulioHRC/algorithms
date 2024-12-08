#ifndef UTILS_H
#define UTILS_H

template <typename ElementType>
void swap(ElementType *a, ElementType *b){
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

#endif