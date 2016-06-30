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
   treeElement<ADWord> *in = BinTree::findValue(*(new ADWord(value, amount)));
   if (in){
       in->getValuePointer()->setAmount(in->getValue().getAmount() + amount);
   }else{
        BinTree::addValue(V);
   }
   return true;
}

bool  AdditiveDictionary::addValueFromFile(std::string file_name){
    std::ifstream file;
    file.open(file_name);

    std::string word;
    while (file>>word) {
        addValue(word, 1);
    }
    return true;
}
