#include <iostream>

using namespace std;
using std::string;

/*
 * This small program is designed to calculate the smallest palindrome number,
 * which is larger then the given number, entered by user through command line.
 * The next palindrome is calculated based on "string" assumption, rather then number.
 * So, for example the next palindrome for 000 would be 010 and so on.
 *
 * Single digit numbers are treated as palindromes themselves, and thus are incremented by 1.
 */

bool isNumberPalindrome(string);

bool isEvenLength(string);

string handlePalindrome(string);

string handleNonPalindrome(string);

int main() {
    string nextPalindrome;
    int testCases;

    //Input for test cases number
    cout << "Please enter number of test cases >>" << endl;
    cin >> testCases;
    while (cin.fail() || testCases < 1 || testCases > 10) {
        cout << "You can only use numbers from 1 to 10." << endl << "Please enter number of test cases >>";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> testCases;
    }
    string array[testCases];

    for (int i = 0; i < testCases; i++) {

        //For each test case one input is allowed of a number in a form of string with no more than 10000 characters
        cout << "Please enter test case number " << i + 1 << endl;
        cin >> array[i];

        while (array[i].length() > 10000) {
            cout << "The test number length cannot exceed 10,000 digits" << endl << "Please enter test case number "
                 << i + 1 << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cin >> array[i];
        }
    }

    for (int j = 0; j < testCases; j++) {

        //Testing each number to determine whether the input is a palindrome itself. Accordingly, input is handled differently
        nextPalindrome = isNumberPalindrome(array[j]) ? handlePalindrome(array[j]) : handleNonPalindrome(array[j]);
        cout << "The next palindrome for number " << array[j] << " is " << nextPalindrome << endl;

    }

    return 0;
}


bool isEvenLength(string number) {
    return number.length() % 2 == 0;
}


//Helper function to determine if the input is a palindrome itself
//Left part of the string is compared to the reversed version of the right part
//If equaled (string is a combined of 2 mirrored substrings), input determined a palindrome
bool isNumberPalindrome(string number) {
    int length = (int) number.length();
    int left = length / 2 - 1;
    int right = isEvenLength(number) ? length / 2 : length / 2 + 1;
    string endPart = number.substr((unsigned long) right);
    string reversed(endPart.rbegin(), endPart.rend());
    return number.substr(0, (unsigned long) (left + 1)) == reversed;

}

//Handling an input in case it's a palindrome
string handlePalindrome(string input) {
    bool isNines = false;
    unsigned long length = input.length();
    int middle = isEvenLength(input) ? (int) (length / 2) - 1 : (int) length / 2;
    input = input.substr(0, (unsigned long) middle + 1);
    int half = (int) input.length();

    //Evaluating only the first part of the string, as it can be mirrored (depending on even/odd number of characters),
    //the numbers are evaluated from the end to the start of half an input string
    for (int i = half - 1; i >= 0; i--) {
        int current = (input[i]) - 48;

        //In case of evaluated number less then 9, it's incremented by 1 and a corresponding char is replaced accordingly
        if (current + 1 < 10) {
            current += 1;

            input.replace((unsigned long) i, 1, to_string(current));
            break;
        } else {


            //In case the number is 9, we keep adding 1 (turning a number into 0 and carrying 1) from the middle outwards
            //In case we reach the beginning of the string and number is still 9, it's turned into 10
            current = 0;
            input.replace((unsigned long) i, 1, to_string(current));
            if (i == 0) {
                input.insert(0, "1");
                isNines = true;
            }
        }
    }


    //First half of the transformed input is mirrored and concatenated with the reversed version of itself
    string mirror = "";
    int mirrorStart = (int) (length % 2 == 0 ? input.length() - 1 : input.length() - 2);
    if (isNines && length % 2 != 0) {
        input.replace(input.length() - 1, 1, "");
    }
    for (int i = mirrorStart; i >= 0; i--) {
        mirror += input[i];
    }

    input += mirror;

    return input;
}


//Function to handle the non palindrome input number
string handleNonPalindrome(string input) {
    int ltIdx, rtIdx, i, j;
    unsigned long length = input.length();
    bool isEven = isEvenLength(input);
    i = ltIdx = (int) length / 2 - 1;
    j = rtIdx = (int) (isEven ? length / 2 : length / 2 + 1);

    //Evaluating the number from the middle outwards, we compare each corresponding character. If they are equal, we continue.
    //If the number, represented by a char on the left is greater then the one on the right, we simply mirror the left part.
    //If the opposite is true, we increment the number represented by the char on the left, replace the corresponding char with one representing the new number,
    //and then we mirror the left part of the string
    while (i >= 0) {
        if (input[i] == input[j]) {
            i--;
            j++;
            continue;
        } else {
            int lt = (int) input[i] - 48;
            int rt = (int) input[j] - 48;
            if (lt < rt) {
                lt += 1;
                input.replace((unsigned long) i, 1, to_string(lt));
            }
            break;
        }

    }


    string ltPart = input.substr(0, (unsigned long) ltIdx + 1);
    string reversed(ltPart.rbegin(), ltPart.rend());
    input.replace((unsigned long) rtIdx, ltPart.length(), reversed);
    return input;
}
