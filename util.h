#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


//***********************
using namespace std;

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
  cout << "          ENTERING SET-INTERSECTION          " << endl;
  cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
  cout << endl << endl << endl;

  typename std::set<T>::iterator it = s1.begin();
  typename std::set<T>::iterator it2 = s2.begin();

  std::set<T> intersectionSet;
  int i = 0;
  // set intersection = AND search  returns items with ALL words 
  while(it != s1.end() && it2 != s2.end()) 
  {
    if(i == 300) {
      cout<< "PAST" << endl;
      break;
    }
    if(*it < *it2) 
    {
      it++;
    }
  
    if(*it == *it2) 
    {
      //.
      intersectionSet.insert(*it);
      it2++;
    }
    /* this means the current element in s2 is not in s1 so 
     * move onto the next in element in s2 
     */ 
    if(*it > *it2) 
    {
      it2++;
    }
    i++;
  }
  
  return intersectionSet;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
// set union =  OR search  return items with atleast 1 word
  typename std::set<T>::iterator it = s1.begin();
  typename std::set<T>::iterator it2 = s2.begin();
  std::set<T> unionSet;

  while(it != s1.end() || it2 != s2.end())
  {
    if(it != s1.end()){
      unionSet.insert(*it);
      it++;
    }

    if(it2 != s2.end()){
      unionSet.insert(*it2);
      it2++;
    }
  }

  return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
