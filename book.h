#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <set>
#include "product.h"
#include "user.h"
#include "util.h"

class Book : public Product 
{
  public:
  Book(const std::string category, const std::string name, double price, int qty, 
       const std::string author, const std::string ISBN);

  ~Book();

  std::set<std::string> keywords() const;

  //idk
  //bool isMatch(std::vector<std::string>& searchTerms) const;

  std::string displayString() const;
  std::string showName() const;
  void dump(std::ostream& os) const;

  private:
    std::string author_;
    std::string ISBN_;
};

#endif