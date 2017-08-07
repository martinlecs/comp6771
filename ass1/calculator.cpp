#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <cmath>
#include <queue>

void addNumbers(std::stack<std::string>& st);
void subNumbers(std::stack<std::string>& st);
void multNumbers(std::stack<std::string>& st);
void divNumbers(std::stack<std::string>& st);
void sqrtNumber(std::stack<std::string>& st);
void reverseStack(std::stack<std::string>& st);
void printStack(std::stack<std::string>& st);
void printQueue(std::queue<std::string>& qu);
void processString(std::stack<std::string>& st, std::string &s);

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    // string to be read into
    std::string s;

    // create an empty stack
    std::stack<std::string> st;

    //create an empty queue for 'repeat' command
    std::queue<std::string> repqueue;

    //repeat flag
    bool repeat = false;

    //variable to store number of times to repeat
    int repNum;

    // read the file while we have input.
    while (in >> s) {
        if(s != "repeat" && s != "endrepeat") {
            processString(st, s);
        } 
        else if (repeat && s != "endrepeat") {
            //BUG: Not pushing stuff onto the queue
            std::cout << "Pushing crap onto queue\n";
            repqueue.push(s);
        } 
        else if (s == "repeat") {
            std::cout << "Entering repeat" << std::endl;
            repeat = true;

            if(!repNum) std::cout << "repNum not 0\n";
            repNum = std::stoi(st.top());
            st.pop();

        } 
        else if (s == "endrepeat") {
            //BUG: Still not entering statement
            std::cout << "Entering endrepeat" << "\n";

            repeat = false;
            std::string repStr;

            if(!repqueue.empty()) {
                int i = 0;
                while (i < repNum) {

                    std::cout << " in loop\n";
                    repStr = repqueue.front();

                    //Segfault because nothing is being pushed onto
                    //queue

                    processString(st, repStr);
                    repqueue.push(repStr);
                    repqueue.pop();

                    //restart loop
                    if(repqueue.front() == "endrepeat")
                        ++i;
                }
            }
            std::cout << "End endrepeat\n";
            //clear queue
            std::queue<std::string>().swap(repqueue);
        }
    }
    in.close();
    // printStack(st);
    //printQueue(repqueue);
}

void processString(std::stack<std::string>& st, std::string &s) {
    if(isdigit(s[0])) {
        st.push(s);
    }
    else {
        if (s == "add" && st.size() >= 2) {
            addNumbers(st);   
        }
        if (s == "sub" && st.size() >= 2) {
            subNumbers(st);
        }
        if (s == "mult" && st.size() >= 2) {
            multNumbers(st);
        }
        if (s == "div" && st.size() >= 2) {
            divNumbers(st);
        }
        if (s == "sqrt" && st.size() >= 1) {
            sqrtNumber(st);
        }
        if (s == "pop" && !st.empty()) {
            st.pop();
        }
        if (s == "reverse" && st.size() > 1) {
            reverseStack(st);
        }
    }

}

void addNumbers(std::stack<std::string>& st) {
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    if(num1.find ('.') != std::string::npos || 
            num2.find ('.') != std::string::npos )
    {
        double i = std::stod(num1);
        double j = std::stod(num2);
        double sum = i + j;
        std::string res = std::to_string(sum);
        st.push(res);

        std::cout << num1 << " + " << num2 << " = " 
            << sum << std::endl;
    }
    else {
        int i = std::stoi(num1);
        int j = std::stoi(num2);
        int sum = i + j;
        std::string res = std::to_string(sum);
        st.push(res);

        std::cout << num1 << " + " << num2 << " = " 
            << sum << std::endl;
    }
}
void subNumbers(std::stack<std::string>& st) {
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    if(num1.find ('.') != std::string::npos || 
            num2.find ('.') != std::string::npos )
    {
        double i = std::stod(num1);
        double j = std::stod(num2);
        double sum = i - j;
        std::string res = std::to_string(sum);
        st.push(res);

        std::cout << num1 << " - " << num2 << " = " 
            << sum << std::endl;
    }
    else {
        int i = std::stoi(num1);
        int j = std::stoi(num2);
        int sum = i - j;
        std::string res = std::to_string(sum);
        st.push(res);

        std::cout << num1 << " - " << num2 << " = " 
            << sum << std::endl;
    }
}

void multNumbers(std::stack<std::string>& st) {
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    if(num1.find ('.') != std::string::npos || 
            num2.find ('.') != std::string::npos )
    {
        double i = std::stod(num1);
        double j = std::stod(num2);
        double mul = i * j;
        std::string res = std::to_string(mul);
        st.push(res);

        std::cout << num1 << " * " << num2 << " = " 
            << mul << std::endl;
    }
    else {
        int i = std::stoi(num1);
        int j = std::stoi(num2);
        int mul = i * j;
        std::string res = std::to_string(mul);
        st.push(res);

        std::cout << num1 << " * " << num2 << " = " 
            << mul << std::endl;
    }
}
void divNumbers(std::stack<std::string>& st) {
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    if(num1.find ('.') != std::string::npos || 
            num2.find ('.') != std::string::npos )
    {
        double i = std::stod(num1);
        double j = std::stod(num2);
        double div = i / j;
        std::string res = std::to_string(div);
        st.push(res);

        std::cout << num1 << " / " << num2 << " = " 
            << div << std::endl;
    }
    else {
        int i = std::stoi(num1);
        int j = std::stoi(num2);
        int div = i / j;
        std::string res = std::to_string(div);
        st.push(res);

        std::cout << num1 << " / " << num2 << " = " 
            << div << std::endl;
    }
}
void sqrtNumber(std::stack<std::string>& st) {
    std::string num = st.top();
    st.pop();

    double i = std::stod(num);
    double res = sqrt(i);
    st.push(std::to_string(res));

    std::cout << "sqrt " << num 
        << " = " << res << std::endl;
}
void reverseStack(std::stack<std::string>& st) {
    int n = std::stoi(st.top());
    st.pop();

    std::queue<std::string> qu;

    for(int i = 0; i < n; ++i) {
        qu.push(st.top());
        st.pop();
    }

    while(!qu.empty()) {
        st.push(qu.front());
        qu.pop();
    }
}

void printStack(std::stack<std::string>& st) {
    std::cout << "Attempting to print out stack\n";
    while(!st.empty()) {
        std::string s = st.top();
        std::cout << s << std::endl;
        st.pop();
    }
}

void printQueue(std::queue<std::string>& qu) {
    while(!qu.empty()) {
        std::string s = qu.front();
        std::cout << s << " ";
        qu.pop();
    }
}
/*
   if (repeat && s != "endrepeat") {
   std::cout << "Pushing crap onto queue\n";
   repqueue.push(s);
//BUG: Not going into this statement
}          
if (s == "repeat") {
//BUG: Not entering this statement
std::cout << "Entering repeat" << std::endl;
repeat = true;
std::cout << "need help\n";
repNum = 0; 

std::cout << st.top() << "\n";

//repNum = std::stoi(st.top());
std::cout << "cant print repNum\n";
// Segfault here
// st.pop();

}
if (s == "endrepeat") {
//BUG: Still not entering statement
std::cout << "endrepeat" << "\n";

repeat = false;
std::string repStr;

int i = 0;
while (i < repNum) {

std::cout << i << "\n";
//Assuming there are enough values on
//the stack to play with ie.
//Assume no segfault will happen due to an empty
//stack
repStr = repqueue.front();

//Segfault because nothing is being pushed onto
//queue

processString(st, repStr);
repqueue.push(repStr);
repqueue.pop();

//restart loop
if(repqueue.front() == "endrepeat")
++i;
}
//clear queue
std::queue<std::string>().swap(repqueue);
}*/

