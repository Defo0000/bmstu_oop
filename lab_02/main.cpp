#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
void print_list(const list<T> &list)
{
    for (auto iterator = list.cbegin(); iterator != list.cend(); iterator++)
    {
        cout << (*iterator).get() << " ";
    }
    cout << endl;
}

int main()
{
    cout << "Testing default list constructor..." << endl << endl;
    list<int> list1;

    cout << "Testing push_back function passing arr ptr and len..." << endl << endl;
    int arr[] = {1, 2, 3, 4, 5};
    list<int> list2(arr, sizeof(arr) / sizeof(arr[0]));
    print_list(list2);

    cout << "Testing push_back function using data parameter..." << endl << endl;
    list1.push_back(-5);
    list1.push_back(-6);
    list1.push_back(-7);
    //print_list(list1);

    cout << "Testing default list constructor.." << endl << endl;
    //list<int> list2(list1);
    return 0;
}
