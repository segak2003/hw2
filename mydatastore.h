#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"


class MyDataStore : public DataStore {
public:

    MyDataStore();

    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    void addToCart(User* u, Product* p);
    
    void buyCart(User* u);

    void viewCart(User* u);

    User* getUser(std::string userName);
    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

  private:
    std::vector<Product*> productStorage_;
    std::vector<User*> userStorage_;
    std::map<User*, std::vector<Product*>> cartMap_;
    std::map<std::string, std::set<Product*>> keywordToProductsMap;
};

#endif
