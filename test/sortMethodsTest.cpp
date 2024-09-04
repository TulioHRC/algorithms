#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sort/sortAlgorithms.hpp"
#include "sort/sortAlgorithmsMenu.hpp"

template <typename T>
bool verifySort(T* vector, ll size){
    for(ll i = 1; i < size; i++){
        if(vector[i-1] > vector[i]) return false;
    }
    return true;
}

template <typename T>
T* getVectorClone(T* vector, ll size){
    T* newVector = new T[size];

    for(int i = 0; i < size; i++){
        newVector[i] = vector[i];
    }

    return newVector;
}

// Variáveis globais
int* emptyVector;
ll emptyVectorSize;

int* oneElementVector;
ll oneElementVectorSize;

int* alreadySortedVector;
ll alreadySortedVectorSize;

int* reversedSortedVector;
ll reversedSortedVectorSize;

int* duplicatedVector;
ll duplicatedVectorSize;

short int* shortIntRandomVector;
ll randomVectorSizes;
int seed;

void setup() {
    emptyVector = new int[0];
    emptyVectorSize = 0;

    oneElementVector = new int[1]{1};
    oneElementVectorSize = 1;

    alreadySortedVector = new int[5]{1, 2, 3, 4, 5};
    alreadySortedVectorSize = 5;

    reversedSortedVector = new int[5]{5, 4, 3, 2, 1};
    reversedSortedVectorSize = 5;

    duplicatedVector = new int[5]{5, -1, 5, 2, 1};
    duplicatedVectorSize = 5;

    std::srand(static_cast<unsigned>(std::time(0))); 

    seed = std::rand();
    randomVectorSizes = 10000;
    shortIntRandomVector = new short int[randomVectorSizes];
    initVector(shortIntRandomVector, randomVectorSizes, 0, seed);
}

int* emptyVectorClone;
int* oneElementVectorClone;
int* alreadySortedVectorClone;
int* reversedSortedVectorClone;
int* duplicatedVectorClone;
short int* shortIntRandomVectorClone;

void cloneTestCases(){
    emptyVectorClone = getVectorClone(emptyVector, emptyVectorSize);
    oneElementVectorClone = getVectorClone(oneElementVectorClone, oneElementVectorSize);
    alreadySortedVectorClone = getVectorClone(alreadySortedVector, alreadySortedVectorSize);
    reversedSortedVectorClone = getVectorClone(reversedSortedVector, reversedSortedVectorSize);
    duplicatedVectorClone = getVectorClone(duplicatedVector, duplicatedVectorSize);
    shortIntRandomVectorClone = getVectorClone(shortIntRandomVector, randomVectorSizes);
}

TEST_CASE("BubbleSort test case", "[bubbleSort]") {
    cloneTestCases();
    bubbleSort(emptyVectorClone, 0, emptyVectorSize);
    REQUIRE(verifySort(emptyVectorClone, emptyVectorSize));
}

TEST_CASE("InsertionSort test case", "[insertionSort]") {
    cloneTestCases();
    insertionSort(emptyVectorClone, 0, emptyVectorSize);
    REQUIRE(verifySort(emptyVectorClone, emptyVectorSize));
}

TEST_CASE("Cleanup", "[cleanup]") {
    delete[] emptyVector;
    delete[] oneElementVector;
    delete[] alreadySortedVector;
    delete[] reversedSortedVector;
    delete[] duplicatedVector;
    delete[] shortIntRandomVector;

    delete[] emptyVectorClone;
    delete[] oneElementVectorClone;
    delete[] alreadySortedVectorClone;
    delete[] reversedSortedVectorClone;
    delete[] duplicatedVectorClone;
    delete[] shortIntRandomVectorClone;
}
