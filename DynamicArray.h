//Programmer: Ethan Chiang
//Programmer ID: 1538719

#ifndef DynamicArray_h
#define DynamicArray_h

#include <algorithm>
using namespace std;

template <typename T>
class DynamicArray
{
  T* classinfo;

  T dummy;
  int CAP;

  public: 
  DynamicArray(int=2); // constructor // default = 2
  DynamicArray(const DynamicArray<T>&); // copy constructor
  ~DynamicArray() {delete [ ] classinfo;} // destructor
  DynamicArray<T>& operator=(const DynamicArray<T>&); // assignment operator
  int capacity() const {return CAP;}
  void capacity(int); // increase CAP
  T operator[ ] (int) const; // getter
  T& operator[ ] (int); // setter
};

template <typename T>
DynamicArray<T>::DynamicArray(int CAP) // consturctor
{
  this->CAP = CAP;
  classinfo = new T[CAP];

  for(int i = 0; i < CAP; i++)
    classinfo[i] = T();
}

template <typename T>
T DynamicArray<T>::operator[ ] (int index) const // getter
{
  if(index < 0 || index >= CAP) return T();
  return classinfo[index];
}

template <typename T>
T& DynamicArray<T>::operator[ ] (int index) // setter
{
  if(index < 0) return dummy;
  if(index >= CAP) capacity(2 * index);
  return classinfo[index];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original)
{
  CAP = original.CAP; // still just a copy 
  classinfo = new T[CAP]; // not a copy -- new object gets its own array
  for (int i = 0; i < CAP; i++) // copy the contents of the array from the original...
    classinfo[i] = original.classinfo[i]; // ...to the copy
  dummy = original.dummy; // not really necessary because who cares what dummy contains?
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& original)
{
  if (this != &original) // of it's not a self copy...
  {
    // do what the destructor does
    delete [ ] classinfo;

    // do what the copy constructor does
    CAP = original.CAP; // still just a copy 
    classinfo = new T[CAP]; // not a copy -- new object gets its own array
    for (int i = 0; i < CAP; i++) // copy the contents of the array from the original...
      classinfo[i] = original.classinfo[i]; // ...to the copy
    dummy = original.dummy; // not really necessary because who cares what dummy contains?
  }
  return *this; // return a self reference
}

template <typename T>
void DynamicArray<T>::capacity(int CAP)
{
  T* temp = new T[CAP];
  int limit = min(CAP, this->CAP); 

  for (int i = 0; i < limit; i++)
    temp[i] = classinfo[i];

  for (int i = limit; i < CAP; i++)
    temp[i] = T();

  delete [ ] classinfo; 
  classinfo = temp;
  this->CAP = CAP;
}

#endif