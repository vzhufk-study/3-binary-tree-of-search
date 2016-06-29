#include <iostream>
#include <additivedictionary.h>
using namespace std;

int main(int argc, char *argv[])
{
    AdditiveDictionary S;
    S.addValueFromFile("50.txt");
    treeElement<ADWord> x = S.findValue(*(new ADWord("the", 1)));
    S.delValue(x.getValue());
    x = S.findValue(*(new ADWord("the", 1)));
    return 0;
}
