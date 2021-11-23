#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "ItemCollection.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int barcode) {
    return (barcode / 1000000) % 10;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int barcode) {
    return (barcode / 100000) % 10;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int barcode) {
    return (barcode / 10000) % 10;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int barcode) {
    return (barcode / 1000) % 10;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int barcode) {
    return (barcode / 100) % 10;
}

// function to return the hash value based on the sixth digit
unsigned int hashfct6(unsigned int barcode) {
    return (barcode/10) % 10;
}

// function to return the hash value based on the seventh digit
unsigned int hashfct7(unsigned int barcode) {
    return barcode % 10;
}


// Constructor for struct Item
Item::Item(string itemColor, string itemShape, string itemBrand,
		 unsigned int barcode):itemColor_(itemColor),itemShape_(itemShape), itemBrand_(itemBrand),
				       barcode_(barcode)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void ItemCollection::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemColor;
    string itemShape;
    string itemBrand;
    unsigned int barcode;
    while (myfile >> itemColor >> itemShape >> itemBrand >> barcode) {
			if (itemColor.size() > 0)
      	addItem(itemColor, itemShape, itemBrand, barcode);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void ItemCollection::addItem(string itemColor, string itemShape, string itemBrand, unsigned int barcode) {
    
    Item temp = (itemColor, itemShape, itemBrand);

    hT1.emplace(barcode, temp);
    hT2.emplace(barcode, temp);
    hT3.emplace(barcode, temp);
    hT4.emplace(barcode, temp);
    hT5.emplace(barcode, temp);
    hT6.emplace(barcode, temp);
    hT7.emplace(barcode, temp);   

}

bool ItemCollection::removeItem(unsigned int barcode) {

    if (hT1.find(barcode) != hT1.end())
    {
        hT1.erase(barcode);
        hT2.erase(barcode);
        hT3.erase(barcode);
        hT4.erase(barcode);
        hT5.erase(barcode);
        hT6.erase(barcode);
        hT7.erase(barcode);
        return true;
    }
    return false;
}

unsigned int ItemCollection::bestHashing() {

    unsigned int min_loc = 100000, max_loc = 0;
    unsigned int balance[7] = { 0,0,0,0,0,0,0 };
    unsigned int min[7] = { 10000,10000,10000,10000,10000,10000,10000 };
    unsigned int max[7] = { 0,0,0,0,0,0,0 };
    for (int i = 0; i < 10; i++)
    {
        if (hT1.bucket_size(i) < min[0]) { min[0] = hT1.bucket_size(i); }
        if (hT1.bucket_size(i) > max[0]) { max[0] = hT1.bucket_size(i); }
        balance[0] = max[0] - min[0];

        if (hT2.bucket_size(i) < min[1]) { min[1] = hT2.bucket_size(i); }
        if (hT2.bucket_size(i) > max[1]) { max[1] = hT2.bucket_size(i); }
        balance[1] = max[1] - min[1];

        if (hT3.bucket_size(i) < min[2]) { min[2] = hT3.bucket_size(i); }
        if (hT3.bucket_size(i) > max[2]) { max[2] = hT3.bucket_size(i); }
        balance[2] = max[2] - min[2];

        if (hT4.bucket_size(i) < min[3]) { min[3] = hT4.bucket_size(i); }
        if (hT4.bucket_size(i) > max[3]) { max[3] = hT4.bucket_size(i); }
        balance[3] = max[3] - min[3];

        if (hT5.bucket_size(i) < min[4]) { min[4] = hT5.bucket_size(i); }
        if (hT5.bucket_size(i) > max[4]) { max[4] = hT5.bucket_size(i); }
        balance[4] = max[4] - min[4];

        if (hT6.bucket_size(i) < min[5]) { min[5] = hT6.bucket_size(i); }
        if (hT6.bucket_size(i) > max[5]) { max[5] = hT6.bucket_size(i); }
        balance[5] = max[5] - min[5];

        if (hT7.bucket_size(i) < min[6]) { min[6] = hT7.bucket_size(i); }
        if (hT7.bucket_size(i) > max[6]) { max[6] = hT7.bucket_size(i); }
        balance[6] = max[6] - min[6];
    }
    
    int lowest=10000;
    unsigned int lowestIt;
    for (int j = 0; j < 7; j++)
    {
        std::cout << "Balance: " << balance[j] << std::endl;
        if (balance[j] < lowest)
        {
            lowestIt = j + 1;
            lowest = balance[j];
        }
    }

    return lowestIt;
}

// ALREADY COMPLETED
size_t ItemCollection::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) || (hT1.size() != hT7.size()))
  	throw std::length_error("Hash table sizes are not the same");
    
	return hT1.size();
}
