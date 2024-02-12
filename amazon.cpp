#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
  string str = "keyowrds blah acoustic USC-CSCI";

  set<string> myset = parseStringToWords(str);

  for (const std::string& word : myset) {
    cout << word << endl;
  }

    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;


    
    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term                       " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if(cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if (cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if (cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            //cmds to do:    
            else if(cmd == "ADD") 
            {
              string userName;
              int hitIndex;

              if(ss >> userName >> hitIndex) {
                userName = convToLower(userName);
                  //what to do if user or product not found?
                  cout << "hitIndex: " << hitIndex << " size " << hits.size() << endl;
                  if(hitIndex < hits.size() && hitIndex >= 0) {
                    Product* currProduct = hits[hitIndex -1];

                    User* currUser = ds.getUser(userName);

                    if(currUser == nullptr) {

                      cout << "Invalid user" << endl;
                    }
                    else {
                      ds.addToCart(currUser, currProduct);
                    }
                  }
                  else {
                    cout << "1 Invalid request" << endl;
                  }
              }
              else{
                    cout << "Invalid request" << endl;
              }
            }
            else if(cmd == "BUYCART") 
            {
              string userName;
              bool validUser = false;
              if(ss >> userName) {

                userName = convToLower(userName);
                User* currUser = ds.getUser(userName);

                  if(currUser != nullptr) {
                    validUser = true;
                  }
                  
                  if(validUser == false) {
                    cout << "Invalid user" << endl;
                  }
                  else {
                  ds.buyCart(currUser);
                  }
              }
              else {
                cout << "Invalid request" << endl;
              }
            }
            else if(cmd == "VIEWCART") 
            {
              string userName;
              if(ss >> userName) {

                bool validUser = false;
                userName = convToLower(userName);
                User* currUser = ds.getUser(userName);

                if(currUser != nullptr){
                  validUser = true;
                }
                
                if(validUser == false) {
                cout << "invalid username" << endl;
                }

                ds.viewCart(currUser);
              }
              else {
                cout << "invalid request" << endl;
              }
            }
	    /* Add support for other commands here */
            else {
                cout << "Unknown command" << endl;
            }
      }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
