#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
void print_list(const list<T> &list)
{
    if (list.is_empty())
    {
        cout << "List is empty.";
    }
    else
    {
        cout << "List: ";
        for (auto iterator = list.cbegin(); iterator != list.cend(); iterator++)
        {
            cout << (*iterator).get() << " ";
        }
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
    list1.push_back(5);
    print_list(list1);
    list1.push_back(6);
    print_list(list1);
    list1.push_back(7);
    print_list(list1);
    list1.push_back(8);
    print_list(list1);
    list1.push_back(9);
    print_list(list1);
    list1.push_back(10);
    print_list(list1);

    cout << "Testing push_front func..." << endl << endl;
    list1.push_front(4);
    print_list(list1);
    list1.push_front(3);
    print_list(list1);

    cout << "Testing pop function..." << endl << endl;
    list1.pop();
    print_list(list1);

    cout << "Testing pop function..." << endl << endl;
    list1.pop();
    print_list(list1);

    cout << "Testing remove function..." << endl << endl;
    list1.remove(list1.begin() + 2);
    print_list(list1);
    list1.remove(list1.begin());
    print_list(list1);

    cout << "Testing insert function..." << endl << endl;
    list1.insert(list1.begin() + 1, -10);
    print_list(list1);

    cout << "Testing reverse function..." << endl << endl;
    list1.reverse();
    print_list(list1);

    cout << "Testing push_back function passing list..." << endl << endl;
    list1.push_back(list2);
    print_list(list1);

    cout << "Testing = operator..." << endl << endl;
    cout << "List1 == List2: ";
    (list1 == list2) ? cout << "true" << endl << endl : cout << "false" << endl << endl;

    cout << "Testing != operator..." << endl << endl;
    cout << "List1 != List2: ";
    (list1 != list2) ? cout << "true" << endl << endl : cout << "false" << endl << endl;

    cout << "Testing clear func..." << endl << endl;
    list1.clear();
    print_list(list1);

    return 0;
}
