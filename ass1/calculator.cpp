#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stack>
#include <cmath>
#include <vector>
#include <queue>

void addNumbers(std::stack<std::string>& st);
void subNumbers(std::stack<std::string>& st);
void multNumbers(std::stack<std::string>& st);
void divNumbers(std::stack<std::string>& st);
void sqrtNumber(std::stack<std::string>& st);
void reverseStack(std::stack<std::string>& st);
void printStack(std::stack<std::string>& st);
void processString(std::stack<std::string>& st, std::string &s);
void processRepeats(std::ifstream &in, std::stack<std::string> &st, std::vector<std::string> &history);
std::string modify_string_precision(std::string a_value);

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
        else {
            std::vector<std::string> history;
            processRepeats(in, st, history);
            for (auto element : history)
                processString(st, element);
        }
    }
    in.close();
    printStack(st);
}

void processString(std::stack<std::string>& st, std::string &s) {
    if(isdigit(s[0]) || isdigit(s[1])) {
        if(s.find ('.') != std::string::npos) {
            std::string converted = modify_string_precision(s);
            st.push(converted);
        } else {
            st.push(s);
        }
    }
    else {
        if (s == "add" && st.size() >= 2) {
            addNumbers(st);   
        }
        else if (s == "sub" && st.size() >= 2) {
            subNumbers(st);
        }
        else if (s == "mult" && st.size() >= 2) {
            multNumbers(st);
        }
        else if (s == "div" && st.size() >= 2) {
            divNumbers(st);
        }
        else if (s == "sqrt" && st.size() >= 1) {
            sqrtNumber(st);
        }
        else if (s == "pop" && !st.empty()) {
            st.pop();
        }
        else if (s == "reverse" && !st.empty()) {
            reverseStack(st);
        }
        else {
            std::cerr << "Not enough variables on the stack" 
                << " or invalid input" << std::endl;
        }
    }
}

void processRepeats(std::ifstream &in, std::stack<std::string> &st, std::vector<std::string> &history) {

    int numRepeat = std::stoi(st.top());
    st.pop();

    std::string str;

    while (in >> str) { //continue processing file stream
        if (str == "repeat") {

            //For handling nested repeats. Pops the number of reapeats
            //from the history. And then makes a recursive call to
            //processRepeats
            st.push(history.back());
            history.pop_back();
            processRepeats(in, st, history);        
        } 
        else if (str != "endrepeat") {
            history.push_back(str);
        } 
        else if (str == "endrepeat") {

            if(!history.empty()) {
                int i = 1;

                std::vector<std::string> copy = history;

                while (i < numRepeat) {
                    history.insert(std::end(history), std::begin(copy), std::end(copy));
                    ++i;
                }
            }
            return;
        }   
    }
}

void addNumbers(std::stack<std::string>& st) {
    
    //Pop off the top two variables from the stack
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    //Create a variable to store the result
    std::string result;

    //Check if either of the numbers are doubles
    if(num1.find ('.') != std::string::npos || num2.find ('.') != std::string::npos ) {
        //Add the two numbers together as doubles and push the result onto the stack
        result = std::to_string(std::stod(num1) + std::stod(num2));
        result = modify_string_precision(result); //set precision of result 
    }
    //otherwise the numbers must be ints
    else {
        result = std::to_string(std::stoi(num1) + std::stoi(num2));
    }
    //Push result to stack
    st.push(result);

    //Print out the equation
    std::cout << num1 << " + " << num2 << " = "
        << result << std::endl;
}

void subNumbers(std::stack<std::string>& st) {
    //Pop off the top two variables from the stack
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    //Create a variable to store the result
    std::string result;

    //Check if either of the numbers are doubles
    if(num1.find ('.') != std::string::npos || num2.find ('.') != std::string::npos ) {
        //Subtract the two numbers together as doubles and push the result onto the stack
        result = std::to_string(std::stod(num1) - std::stod(num2));
        result = modify_string_precision(result); //set precision of result 
    }
    //otherwise the numbers must be ints
    else {
        result = std::to_string(std::stoi(num1) - std::stoi(num2));
    }
    //Push result to stack
    st.push(result);

    //Print out the equation
    std::cout << num1 << " - " << num2 << " = " 
        << result << std::endl;
}

void multNumbers(std::stack<std::string>& st) {
     //Pop off the top two variables from the stack
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    //Create a variable to store the result
    std::string result;

    //Check if either of the numbers are doubles
    if(num1.find ('.') != std::string::npos || num2.find ('.') != std::string::npos ) {
        //Multiply the two numbers together as doubles and push the result onto the stack
        result = std::to_string(std::stod(num1) * std::stod(num2));
        result = modify_string_precision(result); //set precision of result 
    }
    //otherwise the numbers must be ints
    else {
        result = std::to_string(std::stoi(num1) * std::stoi(num2));
    }
    //Push result to stack
    st.push(result);

    //Print out the equation
    std::cout << num1 << " * " << num2 << " = " 
        << result << std::endl; 
}

void divNumbers(std::stack<std::string>& st) {
    //Pop off the top two variables from the stack
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    //Create a variable to store the result
    std::string result;

    //Check if either of the numbers are doubles
    if(num1.find ('.') != std::string::npos || num2.find ('.') != std::string::npos ) {

        //Divide the two numbers together as doubles and push the result onto the stack
        result = std::to_string(std::stod(num1) / std::stod(num2));
        result = modify_string_precision(result); //set precision of result  
    }
    //otherwise the numbers must be ints
    else {
        result  = std::to_string(std::stoi(num1) / std::stoi(num2));
    }
    //Push result onto the stack
    st.push(result);
    //Print out the equation
    std::cout << num1 << " / " << num2 << " = " 
        << result << std::endl;
}

void sqrtNumber(std::stack<std::string>& st) {
    //Get top variable off stack
    std::string num = st.top();
    st.pop();

    std::string result;

    //Check that the number is not negative
    if(!(std::stoi(num) < 0)) {

        if(num.find('.') != std::string::npos) {
            result = std::to_string(sqrt(std::stod(num)));
            result = modify_string_precision(result);
        } else {
            result = std::to_string(static_cast<int>(sqrt(std::stoi(num)))); //Need to static cast because sqrt returns a double value
        }
        //Push result onto stack
        st.push(result);
        std::cout << "sqrt " << num << " = " << result << std::endl;

    } else {
        std::cerr << "Cannot perform sqrt on invalid number. Number must be >= 0" << std::endl;
    }
}


void reverseStack(std::stack<std::string>& st) {
    int n = std::stoi(st.top());
    st.pop();

    //Create a temporary queue to store values we want to reverse
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

std::string modify_string_precision(std::string a_value) {
    double temp = std::stod(a_value);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(3) << temp;
    std::string rand = stream.str();
    return stream.str();
}

