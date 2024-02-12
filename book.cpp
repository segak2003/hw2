#include <iomanip>
#include <sstream>
#include "book.h"

using namespace std;

Book::Book(const string category, const string name, double price, int qty, 
           const string ISBN, const string author )
    : Product(category, name, price, qty) 
{
  author_ = author;
  ISBN_ = ISBN;
}

Book::~Book()
{}

set<string> Book::keywords() const 
{
  set<string> keywordSet = parseStringToWords(name_);
  
  set<string> author_keywords_set = parseStringToWords(author_);
  set<string>::iterator it = author_keywords_set.begin();

  while(it != author_keywords_set.end() ) 
  {
    keywordSet.insert(*it);
    ++it;
  }

  keywordSet.insert(ISBN_);
  return keywordSet;
}

string Book::showName() const 
{
  ostringstream ss;

  ss << name_ ;
  return ss.str();
}


string Book::displayString() const 
{
  ostringstream ss;

  ss << name_  << "\n" << "Author: " << author_ << " ISBN: " 
      << ISBN_ << "\n";
  
  ss << fixed << setprecision(2) << price_ 
      << " " << qty_ << " left.";

  return ss.str();
}

void Book::dump(ostream& os) const 
{
  os << fixed << setprecision(2);

  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
            << "\n" << ISBN_ << "\n" << author_ << "\n";                                
}
