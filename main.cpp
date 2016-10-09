#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

int main() {
    unsigned int testNumber;
    cout
            << "Please enter number of cases you want to try. \nNumber needs to be between 1 and 10. \nFor each case you will be prompted to enter a pair of numbers, so the program can find all the prime numbers between them."
            << endl;
    cin >> testNumber;
    while (cin.fail() || testNumber == 0 || testNumber > 10) {
        cout << "Try again. Make sure you enter a positive number between 1 and 10." << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> testNumber;
    }

    vector<pair<unsigned int, unsigned int> > allCases;
    pair<int, int> tempPair;

    for (int i = 0; i < testNumber; i++) {
        unsigned int a, b;
        int current = i + 1;
        cout << "Please enter pair " << current << ":" << endl;
        cin >> a >> b;
        while (cin.fail() || a < 1 || b < 1 || a > b || a > 1000000000 || b > 1000000000 || (b - a) > 100000) {
            cout << " You can only enter positive numbers. \nThe first number can be equal or less then the second number. \nThe max number you can enter is 1,000,000,000. The difference between the first and the second number cannot be greater than 100,000." << endl;
            cin.clear();
            cout << "Please enter pair " << current << ":" << endl;
            cin >> a >> b;
        }


        tempPair.first = a;
        tempPair.second = b;
        allCases.push_back(tempPair);
    }

    long size = allCases.size();
    for (int i = 0; i < size; i++) {
        unsigned int a = allCases[i].first;
        unsigned int b = allCases[i].second;
        cout << endl << "Case " << i + 1 << ": prime numbers between " << allCases[i].first << " and " << b << ":" << endl;
        if (a <= 2) {
            a = 3;
            cout << 2 << "\n" << 3 << endl;
        } else if (a % 2 == 0) {
            a += 1;
        }

        for (int j = a; j <= b; j += 2) {
            for (int k = 2; k * k < j; k++) {
                if (j % k == 0) {
                    break;
                } else if (k + 1 > sqrt(j)) {
                    cout << j << endl;
                }
            }
        }
        cout << endl;
    }
    return 0;
}