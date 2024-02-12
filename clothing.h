#ifndef CLOTHING_H
#define CLOTHING_H

#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"

class Clothing : public Product 
{
  public:
    Clothing(const std::string category, const std::string name, double price, int qty, 
        const std::string brand, const std::string size);

    ~Clothing();

    std::set<std::string> keywords() const;

    //idk
    //bool isMatch(std::vector<std::string>& searchTerms) const;

    std::string displayString() const;
    std::string showName() const;
    void dump(std::ostream& os) const;

  private:
    std::string brand_;
    std::string size_;
};

#endif