#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
void print_list(const list<T> &list)
{
    std::cout << "List: ";
    for (auto iterator = list.cbegin(); iterator != list.cend(); iterator++)
    {
        cout << (*iterator).get() << " ";
    }
    cout << endl << endl;
}

int main()
{
    setbuf(stdout, NULL);
    cout << "Testing default list constructor..." << endl << endl;
    list<int> list1;

    cout << "Testing constructor passing array and it's len..." << endl << endl;
    int arr[] = {1, 2, 3, 4, 5};
    list<int> list2(arr, sizeof(arr) / sizeof(arr[0]));
    print_list(list2);

    cout << "Testing push_back function passing data parameter..." << endl << endl;
    list1.push_back(-5);
    print_list(list1);
    list1.push_back(-6);
    print_list(list1);
    list1.push_back(-7);
    print_list(list1);

    cout << "Testing push_back function passing node ptr..." << endl << endl;
    std::shared_ptr<list_node<int>> node = nullptr;
    node = std::shared_ptr<list_node<int>>(new list_node<int>);
    node->set(-8);
    list1.push_back(node);
    print_list(list1);

    cout << "Testing push_back function passing node ptr..." << endl << endl;
    //list1.push_back(list2);
    //print_list(list1);

    cout << "Testing list constructor passing list..." << endl << endl;
    list<int> list3(list1);
    print_list(list3);
    return 0;
}
