#include <iomanip>
#include <sstream>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price,
                   int qty, const string brand, const string size) 
        : Product(category, name, price, qty), brand_(brand), size_(size) 
{}

Clothing::~Clothing() 
{}

set<string> Clothing::keywords() const 
{
  //parse the words in the clothing's name and put those words in the associated keywords set
  set<string> keywords_Set = parseStringToWords(name_);
  set<string> brand_keywords_set = parseStringToWords(brand_);
  set<string>::iterator it = brand_keywords_set.begin();

  //add each parsed keyword in the brandname into the assocaited keywords set
  while(it != brand_keywords_set.end()) 
  {
    keywords_Set.insert(*it);
    ++it;
  }
  
  return keywords_Set;
}
string Clothing::showName() const 
{
  ostringstream ss;

  ss << name_;
  return ss.str();
}

string Clothing::displayString() const 
{
  ostringstream ss;

  ss << name_  << "\n" << "Size: " << size_ << " Brand: " 
      << brand_ << "\n";
  
  ss << fixed << setprecision(2) << price_
      << " " << qty_ << " left.";

  return ss.str();
}

void Clothing::dump(ostream& os) const 
{
  os << fixed << setprecision(2);

  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
            << "\n" << size_  << "\n" <<  brand_ << "\n";    
}

