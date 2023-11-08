#include <iostream>
#include "Array.h"
int main()
{
    Array<int> list;
    list.setSize(5,5);
    cout << list.getSize() << endl;
    list.add(5);
    list.add(4);
    list.add(3);
    list.add(2);
    list.add(2);
    list.add(2);
    list.add(2);
    list.print();
    list.printR();
    cout << list.getUpperBound() << endl;
    cout << list.getSize() << endl;
    list.freeExtra();
    list.print();
    cout << list.getUpperBound() << endl;
    cout << list.getSize() << endl;
    //list.removeAll();
    //list.print();
    //cout << list.getUpperBound() << endl;
    //cout << list.getSize() << endl;
    list[3] = 5;
    list.print();
    cout << list[3] << "\t";
    cout << list[1] << endl;


    Array<int> list2;
    list2.add(9);
    list2.add(8);
    list2.add(7);
    list2.print();
    cout << list.getUpperBound() << endl;
    cout << list.getSize() << endl;
    list += list2;
    list.print();
    cout << list.getData(5) << endl;
    list.insertAt(4, 13);
    list.print();
    list.removeAt(4);
    list.print();
    //list.printR();
    
}

