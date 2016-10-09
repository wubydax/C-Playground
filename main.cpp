#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool isOperator(char);

int getOperatorPriority(char);

bool isHigherOrSamePriorityInStack(stack<char>, char);

void handleStackOutput(stack<char>*, string*);


int main() {
    unsigned int testCases;
    vector<string> infixVector;
    stack<char> operatorStack;

    stack<char>* stackPtr = &operatorStack;


    cout << "Enter number of test cases from 1 to 10" << endl << ">>";
    cin >> testCases;

    //adding expressions from input to string vector, while iterating over number of test cases

    for (int i = 0; i < testCases; i++) {
        cout << "Enter expression number " << i + 1 << endl << ">>";
        string infix;
        cin >> infix;
        infixVector.push_back(infix);
    }

    long vectorSize = infixVector.size();

    //Iterating over string vector to convert each expression to postfix
    for (int i = 0; i < vectorSize; i++) {
        string currentExpression = infixVector[i];
        long expressionSize = currentExpression.length();
        string postfix = "";
        string* postfixPtr = &postfix;



        //Iterating over chars in expression string to build the postfix using stack algorithm
        for (int j = 0; j < expressionSize; j++) {
            char currentChar = currentExpression[j];

            //Start examining the chars to see if they are operators, operands or parentheses
            //Calling boolean function to check if the char is operator
            if (isOperator(currentChar)) {

                //If stack is empty, any operator goes in
                if (operatorStack.empty()) {
                    operatorStack.push(currentChar);
                } else {

                    //If the stack is not empty, we examine the top element
                    //If the top element is greater or same priority, we pop stack and add them to output until reaching operator with lower priority
                    while (isHigherOrSamePriorityInStack(operatorStack, currentChar)) {
                        handleStackOutput(stackPtr, postfixPtr);
                    }
                    operatorStack.push(currentChar);
                }
            } else if (currentChar == '(') {

                //If the char is opening parentheses, we push it into the stack in any case
                operatorStack.push(currentChar);
            } else if (currentChar == ')') {

                //If the char is closing parentheses, we pop all until we reach the opening parentheses
                //Then we add them to output
                while (operatorStack.top() != '(') {
                    handleStackOutput(stackPtr, postfixPtr);
                }

                //Popping next operator in stack, as it is an opening parentheses
                operatorStack.pop();
            } else {
                postfix += currentChar;
            }

        }

        //Popping the rest of the operators and adding to output at the end of operation if anything left in stack
        while (!operatorStack.empty()) {
            handleStackOutput(stackPtr, postfixPtr);
        }

        cout << postfix << endl;
    }

    return 0;
}

//Function to determine whether the char is an operator
bool isOperator(char x) {
    return x == '+' || x == '-' || x == '*' || x == '/' || x == '^';
}

//Function to determine the priority of an operator char
int getOperatorPriority(char x) {
    switch (x) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

//Function to compare the top operator in stack and the next operator in line of input
bool isHigherOrSamePriorityInStack(stack<char> s, char x) {
    return !s.empty() && getOperatorPriority(s.top()) >= getOperatorPriority(x);
}

//Function to handle the popping from stack and adding to output. Since done in many places, exported to separate function
//Also my first time working with pointers... yayyyy pointers!!!
void handleStackOutput(stack<char>* stackPtr, string* postfixPtr) {
    *postfixPtr += stackPtr->top();
    stackPtr->pop();
}