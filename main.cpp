#include "hashTable.h"

int main()
{
    HashTable<std::string,int> obj;

    pair<std::string,int> p1("aa",2);
    pair<std::string,int> p2("aa",3);
    pair<std::string,int> p3("aa",4);
    pair<std::string,int> p4("aa",5);
    pair<std::string,int> p5("aa",6);

    obj.add(p1);
    obj.add(p2);
    obj.add(p3);
    obj.add(p4);
    obj.add(p5);

    obj.add("ab",11);
    obj.add("ab",12);
    obj.add("ab",13);

    obj.add("ac",111);
    obj.add("ac",112);
    obj.add("ac",113);

    obj.add("ak",113);
    obj.add("ak",114);
    obj.add("ak",115);

    obj.add("aaa",112);
    obj.add("as",115);


    //obj.print();


    HashTable<std::string,int> obj1;
    obj1 = obj;
    //obj1.print();

    std::cout<<obj.size();
    return 0;
}