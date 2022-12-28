
#include <iostream>
#include "rbtree.h"
#include "menu.h"


using namespace std;


int main() {
    RBTree demo;
    int info, input;
    menu();
    cin >> info;
    while (info != 6) {
        switch (info) {
        case 1: cout << endl<<"Element to be inserted -- ";
            cin >> input; demo.InsertNode(input);
            break;

        case 2: cout << endl<<"Element to be searched -- ";
            cin >> input;
            if (demo.TreeSearch(input)) { cout << "Element found."<<endl; }
            else { cout << "Element not found."<<endl; }
            break;

        case 3: cout << "Pre-Order Tree Walk ";            
            demo.PrePrint();
            cout << endl;
            break;

        case 4: cout << "Post-Order Tree Walk ";            
            demo.PostPrint();
            cout << endl;
            break;

        case 5: cout << endl<<"Element to be deleted? -- ";
            cin >> input;
            demo.Remove(input);
            break;

        default: cout << "Wrong Choice."<<endl;
        }
        cout << endl<<"Anything Else? -- ";
        cin >> info;
    }
    cout << endl<<"Terminating.... ";
    return 0;
}