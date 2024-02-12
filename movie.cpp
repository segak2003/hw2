#include <iomanip>
#include <sstream>
#include "movie.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, 
           const string genre, const string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) 
{}

Movie::~Movie()
{}

set<string> Movie::keywords() const 
{
  set<string> keywords_Set = parseStringToWords(name_);
  //incase the genre is more than 1 word, which it might not be
  set<string> genre_keywords_set = parseStringToWords(genre_);
  set<string>::iterator it = genre_keywords_set.begin();

  while(it != genre_keywords_set.end() ) 
  {
    keywords_Set.insert(*it);
    ++it;
  }

  return keywords_Set;
}

string Movie::showName() const 
{
  ostringstream ss;

  ss << name_;
  return ss.str();
}

string Movie::displayString() const 
{
  ostringstream ss;

  ss << name_  << "\n" << "Genre: " << genre_ << " Rating: " 
      << rating_ << "\n";
  
  ss << fixed << setprecision(2) << price_ 
      << " " << qty_ << " left.";

  return ss.str();
}

void Movie::dump(ostream& os) const 
{
  os << fixed << setprecision(2);

  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
          << "\n" << genre_ << "\n" << rating_ << endl;                                
}
