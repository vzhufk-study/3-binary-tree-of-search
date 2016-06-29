#ifndef ADDITIVEDICTIONARY_H
#define ADDITIVEDICTIONARY_H

#include <bintree.h>

#include <string>
#include <adword.h>


class AdditiveDictionary: public BinTree<ADWord>
{
public:
    AdditiveDictionary();
    bool addValue(std::string, unsigned);
    bool addValueFromFile(std::string);
    bool compare(std::string, std::string);
    bool equal(std::string, std::string);
};

#endif // ADDITIVEDICTIONARY_H
