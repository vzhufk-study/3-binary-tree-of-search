#include "additivedictionary.h"

#include <fstream>

AdditiveDictionary::AdditiveDictionary()
{

}


bool AdditiveDictionary::compare(std::string A, std::string B){
    return A.length() > B.length();
}

bool comp(ADWord A,ADWord B){
    return A.getAmount() > B.getAmount();
}

bool AdditiveDictionary::equal(std::string A, std::string B){
    return (A.compare(B) == 0);
}


bool  AdditiveDictionary::addValue(std::string value, unsigned amount){
   ADWord V(value, amount);
   BinTree::addValue(V);
   return true;
}

bool  AdditiveDictionary::addValueFromFile(std::string file_name){
    std::ifstream file;
    file.open(file_name);

    std::string word;
    while (file>>word) {
        unsigned amount;
        file>>amount;
        addValue(word, amount);
    }
    return true;
}
