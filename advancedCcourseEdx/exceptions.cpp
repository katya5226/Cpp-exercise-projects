#include <iostream>

using namespace std;

/*int main() {

    try {
        throw 20;
    }
    catch (int exc) { cout << "int exception." << endl; }
    catch (double exc) { cout << "double exception." << endl; }
    catch (...) { cout << "All other exception types." << endl; }

    try {
        throw 20.0;
    }
    catch (int exc) { cout << "int exception." << endl; }
    catch (double exc) { cout << "double exception." << endl; }
    catch (...) { cout << "All other exception types." << endl; }

    try {
        throw true;
    }
    catch (int exc) { cout << "int exception." << endl; }
    catch (double exc) { cout << "double exception." << endl; }
    catch (...) { cout << "All other exception types." << endl; }

    //You can also nest try - blocks and forward exceptions to the parent try - block using the throw keyword like so.

    try {
        try {
            //Do something here that causes an exception
            throw 10;
        }
        catch (int numb) {
            cout << "Caught int exception." << endl;
            throw;
        }
    }
    catch (...) {
        cout << "An error occurred." << endl;
    }

}*/