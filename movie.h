#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <set>
#include "product.h"
#include "user.h"
#include "util.h"

class Movie : public Product 
{
  public:
    Movie(const std::string category, const std::string name, double price, int qty, 
        const std::string genre, const std::string rating);

    ~Movie();

    std::set<std::string> keywords() const;

    //idk
    //bool isMatch(std::vector<std::string>& searchTerms) const;

    std::string displayString() const;
    std::string showName() const;
    void dump(std::ostream& os) const;

  private:
    std::string genre_;
    std::string rating_;
};

#endif