// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void IntSet::resize(int new_capacity)
{
   //Checks new_capacity for its specific condition.
   //Once found sets capacity to the correct value 
   //depending on its condition.
   if(new_capacity <= 0){
      capacity = DEFAULT_CAPACITY;
   }
   else if(new_capacity <= used){
      capacity = used;
   }
   else{
      capacity = new_capacity;
   }

   //Creates a new array with the specific capacity.
   int* new_array = new int[capacity];

   //Copys data into the new array.
   for(int i = 0; i < used; i++){
     new_array[i] = data[i];
   }

   //Deallocates the data in the old array
   delete [] data;

   //Moves the new array into private member data.
   data = new_array;

}

IntSet::IntSet(int initial_capacity) : capacity(initial_capacity), used(0)
{
   //Checks if capacity is valid.
   //If false capacity is set to DEFAULT_CAPACITY.
   if(initial_capacity <= 0){
      capacity = DEFAULT_CAPACITY;
   } 

   //Sets dynamic array with correct capacity.
   data = new int[capacity];
}

IntSet::IntSet(const IntSet& src) : capacity(src.capacity), used(src.used)
{
   //Creates a new dynamic array.
   data = new int[capacity];

   //Copies data into the new array.
   for(int i = 0; i < capacity; i++){
      data[i] = src.data[i];
   }
}


IntSet::~IntSet()
{
   //Deallocates array.
   delete [] data;
   data = NULL;
}

IntSet& IntSet::operator=(const IntSet& rhs) 
{
   //Checks if the invoking object is NOT equal to rhs.
   if(this != &rhs){

      //Creates a new dynamic array with rhs.capacity.
      int* newData = new int[rhs.capacity];

      //Copies rhs data into the new array.
      for(int i = 0; i < rhs.used; ++i){
         newData[i] = rhs.data[i];
      }

      //Deallocate the data.
      delete [] data;

      //Updates the data/capacity/used.
      data = newData;
      capacity = rhs.capacity;
      used = rhs.used;
      
   }
   return *this;
}

int IntSet::size() const
{
   //Returns the number in used which is the number
   //of elements in the array.
   return used;
}

bool IntSet::isEmpty() const
{
   //If used is 0 then no elemnts are in
   //the array meaning its empty.
   if(used == 0){
      return true;
   }
   return false;
}

bool IntSet::contains(int anInt) const
{
   //Checks if the array is empty or not.
   //If empty returns false.
  if(used > 0){
   for(int i = 0; i < used; i++){
      //Checks if anInt is a value of the array.
      if(data[i] == anInt){
         return true;
      }
   }
  }
  return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   //Checks if invoking IntSet is empty.
    if(isEmpty()) {
        return true;
      }

    else {
         //Checks if otherIntSet is a subset of intSet.
        for(int i = 0; i < used; i++){
            if(!otherIntSet.contains(data[i])){
                return false;
            }
        }
        return true;
    }
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   //Creates a copy of the invoking IntSet.
   IntSet unionSet = (*this);
    
    //Keeps size consistant.
   int otherIntSetSize = otherIntSet.size();

   //Adds data from IntSet however if the data 
   //is also found in otherIntSet it is not added into unionSet.
   for(int i = 0; i < otherIntSetSize; i++){
      if(!unionSet.contains(otherIntSet.data[i])){
         unionSet.add(otherIntSet.data[i]);
      }
   }
   return unionSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   //Creates a copy of the invoking IntSet.
  IntSet intersectSet = (*this);
   
   //Keeps size consistant.
   int otherIntSetSize = otherIntSet.size();

   //Adds elements found in both otherIntSet and
   // IntSet to intersectSet.
   for(int i = 0; i < otherIntSetSize; i++){
      if(!otherIntSet.contains(data[i])){
         intersectSet.remove(data[i]);
      }
   }
  return intersectSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   //Creates a copy of the invoking IntSet.
  IntSet subtractSet = (*this);

   //If subtractSet contains the same element as otherIntSet
   //the the element is removed from the set.
  for(int i = 0; i < otherIntSet.used; i++){
   if(subtractSet.contains(otherIntSet.data[i])){
      subtractSet.remove(otherIntSet.data[i]);
   }
  }
  return subtractSet;
}

void IntSet::reset()
{
   //Sets used to 0 to ignore the current elements in the invoking
   //IntSet and "reset" the invoking IntSet.
   used = 0;
}

bool IntSet::add(int anInt)
{
   //Checks if anInt is already an element in IntSet.
   //If false then anInt is added to IntSet.
   if(contains(anInt) == true){
      return false;
   }

   else{
      //Adjust capactity to add anInt.
      if(used >= capacity){
         resize(int(1.5 * capacity) + 1);
         }

      data[used] = anInt;
      used++;
      return true;
   }
   return false;
}

bool IntSet::remove(int anInt) 
{
   //Checks is anInt is an element of IntSet.
   //If it is in IntSet then the element is found and removed.
  if(contains(anInt)){
   for(int i = 0; i < used; ++i){
      if(data[i] == anInt){
         for(int j = i; j < used - 1; ++j){
            data[j] = data[j+1];
         }
         --used;
         return true;
      }
   }
   }
   return false;
}

bool operator==(const IntSet& is1, const IntSet& is2)
{
   //Checks if both sets are epmty, if true return true.
   if( is1.isEmpty() && is2.isEmpty()){
      return true;
   }

   //Checks if both sets are subsets of each other, 
   //if true they are equal and return true.
   else if(is1.isSubsetOf(is2) && is2.isSubsetOf(is1)){
      return true;
   }

   return false;
}