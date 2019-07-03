//
//  main.cpp
//  Project 1
//
//  Created by Mai Pham on 3/14/18.
//  Copyright © 2018 Mai Pham. All rights reserved.
//

#include "ChainHashing.h"
#include "LinearHashing.h"
#include "DoubleHashing.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int tableSize(int num, double lf);
bool isPrime(int n);

int main()
{
    int size, key, menu;
    string value;
    int lf25, lf50, lf75, lf90;
    
    ifstream myReadList;
    myReadList.open("large100k.txt");
    if(!myReadList.is_open())
        cout << "No text file found. " << endl;
    
	size = 100000;
    // get prime # for table size base on load factor
    lf25 = tableSize(size, 0.25);
    lf50 = tableSize(size, 0.50);
    lf75 = tableSize(size, 0.75);
    lf90 = tableSize(size, 0.90);

    // a (int, string) map with (table size)
    HashMap<int, string> ChainMap1(lf25);
    HashMap<int, string> ChainMap2(lf50);
    HashMap<int, string> ChainMap3(lf75);
    HashMap<int, string> ChainMap4(lf90);
    
    LHashMap<int, string> LinearMap1(lf25);
    LHashMap<int, string> LinearMap2(lf50);
    LHashMap<int, string> LinearMap3(lf75);
    LHashMap<int, string> LinearMap4(lf90);
    
    DHashMap<int, string> DoubleMap1(lf25);
    DHashMap<int, string> DoubleMap2(lf50);
    DHashMap<int, string> DoubleMap3(lf75);
    DHashMap<int, string> DoubleMap4(lf90);
    
    cout << "Please wait...." << endl;
    cout << "Reading data from file..." << endl << endl;
    while (myReadList >> key)
    {
        // read in the key
        // myReadList >> key;
        // convert key to string and reverse it
        value = to_string(key);
        reverse(value.begin(), value.end());
        
        ChainMap1.put(key, value);
        ChainMap2.put(key, value);
        ChainMap3.put(key, value);
        ChainMap4.put(key, value);
        
        LinearMap1.put(key, value);
        LinearMap2.put(key, value);
        LinearMap3.put(key, value);
        LinearMap4.put(key, value);
        
        DoubleMap1.put(key, value);
        DoubleMap2.put(key, value);
        DoubleMap3.put(key, value);
        DoubleMap4.put(key, value);
    }
    /*
    cout << "Menu" << endl;
    cout << "1. Display Hashing" << endl;
    cout << "2. Insert new key/value" << endl;
    cout << "3. Search for key/value" << endl;
    cout << "4. Remove a key/value" << endl;
    cout << "5. Display the list" << endl;
    cout << "6. Quit" << endl;
    cout << "\nPlease choose an option ==> ";
    cin >> menu;
    */
	int x, y, t;
	cout << "Please enter x: ";
    cin >> x;
	cout << "Please enter t: ";
    cin >> t;
	y = t - x;

    HashMap<int, string>::Iterator s1 = ChainMap1.begin();
	HashMap<int, string>::Iterator s2 = ChainMap1.begin();
    s1 = ChainMap1.find(x);
	s2 = ChainMap1.find(t);

    if (s1 == ChainMap1.end()|| s2 == ChainMap1.end())
        cout  << " NO" << endl;
    else
        cout << " Yes" << endl;


    while (menu > 0 && menu < 6){
        switch (menu) {
            case 1:  {
                cout << "            SEPARATE HASHING" << endl;
                cout << "========================================" << endl;
                cout << "Load Factor 0.25 " << endl;
                ChainMap1.printData();
                cout << "Load Factor 0.50 " << endl;
                ChainMap2.printData();
                cout << "Load Factor 0.75 " << endl;
                ChainMap3.printData();
                cout << "Load Factor 0.90 " << endl;
                ChainMap4.printData();
                
                cout << "            LINEAR HASHING" << endl;
                cout << "========================================" << endl;
                cout << "Load Factor 0.25 " << endl;
                LinearMap1.printData();
                cout << "Load Factor 0.50 " << endl;
                LinearMap2.printData();
                cout << "Load Factor 0.75 " << endl;
                LinearMap3.printData();
                cout << "Load Factor 0.90 " << endl;
                LinearMap4.printData();
            
                cout << "            DOUBLING HASHING" << endl;
                cout << "========================================" << endl;
                cout << "Load Factor 0.25 " << endl;
                DoubleMap1.printData();
                cout << "Load Factor 0.50 " << endl;
                DoubleMap2.printData();
                cout << "Load Factor 0.75 " << endl;
                DoubleMap3.printData();
                cout << "Load Factor 0.90 " << endl;
                DoubleMap4.printData();
                break;
            }
            case 2: {
                cout << "Please enter the key: ";
                cin >> key;
                cout << "Please enter the value: ";
                cin >> value;
                ChainMap1.put(key, value);
                ChainMap1.printProbes();
                cout << "Insert completed." << endl;
                break;
            }
            case 3: {
                cout << "Please enter the search key: ";
                cin >> key;
                HashMap<int, string>::Iterator s1 = ChainMap1.begin();
                s1 = ChainMap1.find(key);
                ChainMap1.printProbes();
                if (s1 == ChainMap1.end())
                    cout << key << " is not in the list" << endl;
                else
                    cout << key << " is in the list with value " << (*s1).value() << endl;
                break;
            }
            case 4: {
                cout << "Please enter the key to remove: ";
                cin >> key;
                ChainMap1.erase(key);
                ChainMap1.printProbes();
                cout << "Remove completed." << endl;
                break;
            }
            case 5: {
                cout << "Print all entries (chain map)\n";
                HashMap<int, string>::Iterator c1 = ChainMap1.begin();
                for (c1; !(c1 == ChainMap1.end()); ++c1) {                  // print all entries
                    cout << "(" << (*c1).key() << "," << (*c1).value() << ")\n";
                }
                /*
                cout << "RePrint all entries, linear map\n";
                for (l1 = LinearMap1.begin(); !(l1 == LinearMap1.end()); ++l1) {  // print all entries
                    cout << "(" << (*l1).key() << "," << (*l1).value() << ")\n";
                }*/
                break;
            }
            default:
                break;
        }
        cout << "\nMenu" << endl;
        cout << "1. Display Hashing" << endl;
        cout << "2. Insert new key/value" << endl;
        cout << "3. Search for key/value" << endl;
        cout << "4. Remove a key/value" << endl;
        cout << "5. Display the list" << endl;
        cout << "6. Quit" << endl;
        cout << "\nPlease choose an option ==> ";
        cin >> menu;
    }
	

    cout << "Thank you for using my program." << endl;
    return 0;
}

int tableSize(int num, double lf)   {
    int prime = num/lf+0.5;
    while (isPrime(prime) == false)
        prime++;
    return prime;
}

bool isPrime(int num)   {
    if (num <= 3)
        return num > 1;
    else if (num % 2 == 0 || num % 3 == 0)
        return false;
    else {
        for (int i = 5; i * i <= num; i += 6)
            if (num % i == 0 || num % (i + 2) == 0)
                return false;
        return true;
    }
}

