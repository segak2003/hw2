#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
////////////bruh
using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

  set<string> keywords;
  stringstream is(rawWords);
  string word;
  string tempWord;

  /* parse each word in the stringstream (rawWords) into individual 
   * words andand put them into the word string 
   */
  while(is >> word)
  {
    tempWord = "";
    for(int i = 0; i < word.length(); i++)  {

      if(!(isalpha(word[i])))
      {
        if(tempWord.size() >= 2) {
          
          keywords.insert(convToLower(tempWord));
        }

        tempWord = "";
      }

      if(isalpha(word[i])) 
      {
        //cout << "ADDING CHAR:  " << word[i] << endl;
        tempWord += word[i];
      }
    }

    if(tempWord.length() >= 2) {
      cout << "ADDING KEYWORD TO SET:  " << tempWord << endl;
      keywords.insert(convToLower(tempWord));
    }
  }

  return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
