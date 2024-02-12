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
  productStorage_.push_back(p);
  set<string> keywords = p -> keywords();

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
 set<Product*> results;  


  for(size_t i = 0; i < terms.size(); ++i) 
  {
   
    map<string, set<Product*>>::iterator mapIt = keywordToProductsMap.find(terms[i]);

    if (mapIt == keywordToProductsMap.end()) 
    {
     
    }
    if (mapIt != keywordToProductsMap.end()) 
    {
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
      results.clear();

      break;
    }
  }
  
  vector<Product*> found_products;
  set<Product*>::iterator resIT = results.begin();
  while(resIT != results.end()) 
  {
    found_products.push_back(*resIT);
    resIT++;
    
  }


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
    
    cartMap_[u] = vector<Product*>{p};
  }
}

void MyDataStore::buyCart(User* u)
{
  map<User*, vector<Product*>>::iterator it = cartMap_.find(u);
  
  if(it != cartMap_.end()) {

  int i = (it -> second.size()) - 1;

    while(i > -1) 
    {
      Product* currProd = it -> second[i];

      if((currProd -> getQty() > 0) && (u -> getBalance() >= currProd -> getPrice())) 
      {
        u -> deductAmount(currProd -> getPrice());
        currProd -> subtractQty(1);
        it -> second.erase(it -> second.begin()+ i);
      }
      --i;
    }
  }
}

void MyDataStore::viewCart(User* u) 
{
  map<User*,vector<Product*>>::iterator it = cartMap_.find(u);
  
  if(it != cartMap_.end()) { 
    for(int i = 0; i < it -> second.size(); i++) 
    {
      cout << "Item " << (i+1)  << "\n" << cartMap_[u][i] -> displayString() << endl;
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