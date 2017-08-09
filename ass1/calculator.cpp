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
void processRepeats(std::ifstream &in, std::stack<std::string> &st);

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

    // read the file while we have input.
    while (in >> s) {
        if(s != "repeat") 
            processString(st, s);
        else
        processRepeats(in, st);
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
        else {
            std::cout << "Not enough variables on the stack" << std::endl;
        }
    }
}

void processRepeats(std::ifstream &in, std::stack<std::string> &st) {

   //Create a new queue
    std::queue<std::string> repQueue;
    
    //Get number of repetitions
    int numRepeat = std::stoi(st.top());
    st.pop();
    std::cout << "numReps:"<< numRepeat << std::endl;

    std::string str;

    while (in >> str) { //continue processing file stream
        if (str == "repeat") {
            //Need to handle unexpected output
            st.push(repQueue.back());
            repQueue.pop();
            processRepeats(in, st);        
        } 
        else if (str != "endrepeat") {
            repQueue.push(str);
            std::cout << str << std::endl;
        } 
        else if (str == "endrepeat") {
            int i = 0;
            while (i < numRepeat) {
                std::string s = repQueue.front();
                std::cout << "string=" << s << std::endl;
                repQueue.push(s);
                repQueue.pop();
                processString(st, s);
                ++i;
            }
            printQueue(repQueue);
            return;
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

    std::cout << "sqrt " << i 
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
