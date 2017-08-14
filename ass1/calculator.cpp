#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stack>
#include <cmath>
#include <vector>
#include <queue>

void processString(std::stack<std::string> &st, std::string &s);
void performArithmetic(std::stack<std::string> &st, char operation);
void printResults(std::string &num1, std::string &num2, std::string &result, 
        char operation);
void sqrtNumber(std::stack<std::string> &st);
void reverseStack(std::stack<std::string> &st);
std::string modify_string_precision(std::string a_value);
std::vector<std::string> processRepeats(std::ifstream &in, 
        std::stack<std::string> &st);

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
            //Create a vector that stores repeated instructions
            std::vector<std::string> repeatedCommands = processRepeats(in, st);
            for (auto element : repeatedCommands)
                processString(st, element);
        }
    }
    in.close();
}

void processString(std::stack<std::string> &st, std::string &s) {
    //Check if string is a digit
    if(isdigit(s[0]) || isdigit(s[1])) {
        //Check if string is a double
        if(s.find ('.') != std::string::npos) {
            std::string converted = modify_string_precision(s);
            st.push(converted);
        } else {
            st.push(s);
        }
    }
    else {
        if(s == "sqrt") {
            sqrtNumber(st);
        }
        else if(s == "pop") {
            st.pop();
        }
        else if(s == "reverse") {
            reverseStack(st);
        }
        else if(s == "add") {
            performArithmetic(st, '+');
        }
        else if( s == "sub") {
            performArithmetic(st, '-');
        }
        else if(s == "mult") {
            performArithmetic(st, '*');
        }
        else if(s == "div") {
            performArithmetic(st, '/');
        } else {
            std::cerr << "Not enough variables on the stack" 
                << " or invalid input" << std::endl;
        }
    }
}

void performArithmetic(std::stack<std::string> &st, char operation) {
    //Pop off the top two variables from the stack
    std::string num1 = st.top();
    st.pop();
    std::string num2 = st.top();
    st.pop();

    //Create a variable to store the result
    std::string result;

    //Check if either of the numbers are doubles
    if(num1.find('.') != std::string::npos || 
            num2.find('.') != std::string::npos ) {

        if(operation == '+') {
            //Add double numbers
            result = std::to_string(std::stod(num1) + std::stod(num2));
        }
        else if (operation == '-') {
            //sub double numbers
            result = std::to_string(std::stod(num1) - std::stod(num2));
        }
        else if (operation == '*') {
            //Multiply double numbers
            result = std::to_string(std::stod(num1) * std::stod(num2));
        }
        else if (operation == '/') {
            //Divide double numbers
            result = std::to_string(std::stod(num1) / std::stod(num2));
        }

       // result = modify_string_precision(result); //set precision of result 
    }

    //otherwise the numbers must be ints
    else {
        if(operation == '+') {
            //Add int numbers
            result = std::to_string(std::stoi(num1) + std::stoi(num2));
        }
        else if (operation == '-') {
            //Sub int numbers
            result = std::to_string(std::stoi(num1) - std::stoi(num2));
        }
        else if (operation == '*') {
            //Multiply int numbers
            result = std::to_string(std::stoi(num1) * std::stoi(num2));
        }
        else if (operation == '/') {
            //Divide int numbers
            result = std::to_string(std::stoi(num1) / std::stoi(num2));
        }
    }
    printResults(num1, num2, result, operation); 
    st.push(result);
}

void printResults(std::string &num1, std::string &num2, std::string &result, 
        char operation) {
    //Results are printed accurately but other stuff isn't anymore

    if (result.find('.') != std::string::npos) {
        //Convert to double
        double res = std::stod(result);

        std::cout << num1 << " " << operation << " " << num2
        << " = " << res << std::endl;

    } else {

        std::cout << num1 << " " << operation << " " << num2
        << " = " << result << std::endl;
    }
}

void sqrtNumber(std::stack<std::string> &st) {
    //get top variable off stack
    std::string num = st.top();
    st.pop();

    std::string result;

    //check that the number is not negative
    if(!(std::stoi(num) < 0)) {
        if(num.find('.') != std::string::npos) {
            result = std::to_string(sqrt(std::stod(num)));
            result = modify_string_precision(result);
        } else {
            //need to static cast because sqrt returns a double value
            result = std::to_string(static_cast<int>(sqrt(std::stoi(num))));        }
            //push result onto stack
            st.push(result);
            std::cout << "sqrt " << num << " = " << result << std::endl;
    } else {
        std::cerr << "cannot perform sqrt on invalid number. number must be >= 0" << std::endl;
    }
}

void reverseStack(std::stack<std::string> &st) {
    int n = std::stoi(st.top());
    st.pop();

    //create a temporary queue to store values we want to reverse
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

std::vector<std::string> processRepeats(std::ifstream &in, std::stack<std::string> &st) {

    //gets number of repeats from the stack
    int numRepeat = std::stoi(st.top());
    st.pop();

    //create vectors to store result of current function call and future
    //recursive calls
    std::vector<std::string> history;
    std::vector<std::string> prevRepeats;

    std::string str;

    while (in >> str) { //continue processing file stream
        if (str == "repeat") {

            //for handling nested repeats. pops the number of reapeats
            //from the history. and then makes a recursive call to processrepeats

            st.push(history.back());
            history.pop_back();
            prevRepeats = processRepeats(in, st);        
        } 
        else if (str != "endrepeat") {
            history.push_back(str);
        } 
        else if (str == "endrepeat") {

            //Append current call's history to previous recursive call's history.
            history.insert(std::end(history), std::begin(prevRepeats), std::end(prevRepeats));

            //Create a copy of the history vector
            std::vector<std::string> copy = history;

            int i = 1; //Set to 1 rather than 0 to get correct number of repeats

            while (i < numRepeat) {
                history.insert(std::end(history), std::begin(copy), std::end(copy));
                ++i;
            }
            break;
        }   
    }
    return history;
}

std::string modify_string_precision(std::string a_value) {
    double temp = std::stod(a_value);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(3) << temp;
    std::string rand = stream.str();
    return stream.str();
}
