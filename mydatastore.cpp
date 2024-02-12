#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>
#include "db_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;


MyDataStore::MyDataStore() 
{}

MyDataStore::~MyDataStore()
{
  for(int i = 0; i < userStorage_.size(); i++) 
  {
    delete userStorage_[i];
  }

  for(int i = 0; i < productStorage_.size(); i++) 
  {
    delete productStorage_[i];
  }
}

void MyDataStore::addProduct(Product* p) 
{
  //std::cout << "ADDING PRODUCT TO STORAGE: " << p -> showName() << endl;
  productStorage_.push_back(p);
  set<string> keywords = p -> keywords();

  //std::cout << p -> showName() << "'s keywords: " << endl;
  for (const string& keyword : keywords) {
    //std::cout << keyword << ", ";
  }
  //std::cout << endl;

  set<string>::iterator it = keywords.begin();
  while(it != keywords.end())  
  {
    string keyword = *it;
    keywordToProductsMap[keyword].insert(p);
    it++;
  }
}

void MyDataStore::addUser(User* u)
{
  userStorage_.push_back(u);
}

/**
    * Performs a search of products whose keywords match the given "terms"
    *  type 0 = AND search (intersection of results for each term) while
    *  type 1 = OR search (union of results for each term)
    */
vector<Product*> MyDataStore::search(vector<string>& terms, int type) 
{
  //std::cout << "=============================================" << endl;
  //std::cout << "          ENTERING SEARCH FUCNTION" << endl;
  //std::cout << "=============================================" << endl;
  //std::cout << endl << endl;

  

  set<Product*> results;  

  for(size_t i = 0; i < terms.size(); ++i) 
  {
    //std::cout << "Terms[" << i <<"]:  " << terms[i] << endl;
  }

  //std::cout << "PRINTING MAP CONTENTS" << endl << endl;

  for(const auto& pair : keywordToProductsMap) {
    const string& keyword = pair.first;
    const set<Product*>& products = pair.second;

    //std::cout << "Keyword: " << keyword << " -> Products: ";
    for (Product* product : products) {
        // Assuming Product class has a method to get some identifiable info
        //std::cout << product -> showName() << ", ";
    }
    //std::cout << endl;
  }

  //std::cout << endl;
  for(size_t i = 0; i < terms.size(); ++i) 
  {
    //std::cout << "LOOKING FOR:   " << terms[i] << endl;
    map<string, set<Product*>>::iterator mapIt = keywordToProductsMap.find(terms[i]);

    if (mapIt == keywordToProductsMap.end()) 
    {
      //std::cout << "AT END OF MAP, IDX:  " << i << endl;

    }
    if (mapIt != keywordToProductsMap.end()) 
    {
      //std::cout << "PRODCT(S) FOUND!!!!" << mapIt -> second.size() << endl;
      if((results.empty() == 1) && (type == 0)) 
      {
        results = mapIt -> second;
      }
      else {
        if (type == 0) {  // AND search
          results = setIntersection(results, mapIt->second);
        } 
        else if (type == 1) {  // OR search
          results = setUnion(results, mapIt->second);
        }
      }
    }
    else if (type == 0) {  // If any term in AND search is not found
      //std::cout << "Total products found:  " << results.size() << endl;
      results.clear();
      //std::cout << "BREAKING" << endl;
      break;
    }
  }
  
  vector<Product*> found_products;
  set<Product*>::iterator resIT = results.begin();
  while(resIT != results.end()) 
  {
    found_products.push_back(*resIT);
    resIT++;
    //std::cout << "ADDING ITEM" << endl; 
  }

  //std::cout << "REUTNING"<< endl;
  return found_products;
}

void MyDataStore::addToCart(User* u, Product* p) 
{
  map<User*, vector<Product*>>::iterator it = cartMap_.find(u);
  
  if(it != cartMap_.end()) 
  {
    it -> second.push_back(p);
  }
  else
  {
    //first in last out ***fix**** 
    cartMap_[u] = vector<Product*>{p};
  }
}

void MyDataStore::buyCart(User* u)
{
  map<User*, vector<Product*>>::iterator it = cartMap_.find(u);
  
  if(it != cartMap_.end()) 
  {
    vector<Product*> currCart = it -> second;

    int i = (it -> second.size()) - 1 ;
    while(i > -1) {
      if(u -> getBalance() >= currCart[i] -> getPrice()) {
      //u -> deductAmount(it->second->getprice());
      //it->second->pop_front();
        u -> deductAmount(currCart[i] -> getPrice());
        currCart[i] -> subtractQty(1);
        currCart.erase(currCart.begin() + i);
        i--;
      }
      else {
        i--;
      }
    }
  }
  //while user funds are >= the price of the current item in the product vector
  


  /*if(it != cartMap_.end()) 
  {
    vector<Product*> currCart = it -> second;

    int i = it -> second.size() - 1 ;
    while(it != cartMap_.end()) {
      if(u -> getBalance() >= currCart[i] -> getPrice()) {
      //u -> deductAmount(it->second->getprice());
      //it->second->pop_front();
        u -> deductAmount(currCart[i] -> getPrice());
        currCart[i] -> subtractQty(1);
        currCart.erase(currCart.begin() + i);
      }
      else {
        i--;
      }
    }
  }*/
}

void MyDataStore::viewCart(User* u) 
{
  string currProd;
  map<User*,vector<Product*>>::iterator it = cartMap_.find(u);
  
  if(it != cartMap_.end()) { 
    for(int i = 0; i < it -> second.size(); i++) 
    {
      currProd = cartMap_[u][i] -> getName();
      cout << "Item #" << (i+1)  << ": " << currProd << endl;
    }
  }
}



void MyDataStore::dump(ostream& ofile) 
{
  ofile << "<products>" << "\n";

  for(int i = 0; i< productStorage_.size(); i++) 
  {
    productStorage_[i] -> dump(ofile);
  }

  ofile << "</products>" << "\n";

  ofile << "<users>" << "\n";

  for(int i = 0; i< userStorage_.size(); i++) 
  {
    userStorage_[i] -> dump(ofile);
  }
  ofile << "</users>" << "\n";

  /*
  vector<Product*>::iterator itProd = productStorage_.begin();

  while(itProd != productStorage_.end()) {
    (*itProd) -> dump(ofile);
    itProd++;
  }

  

  ofile << "<users>" << endl;
  vector<User*>::iterator itUser = userStorage_.begin();
  while(itUser != userStorage_.end()) {
    (*itUser) -> dump(ofile);
    itUser++;
  }

  ofile << "<users>" << endl; */
}



User* MyDataStore::getUser(string userName)
{
  for(int i = 0; i < userStorage_.size(); i++) {
    if(userStorage_[i] -> getName() == userName) {
      return userStorage_[i];
    }
  }
  return nullptr;
}