#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>

double pop_convert_double (std::stack<std::string> &st);
int pop_convert_int (std::stack<std::string> &st);

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
        if(isdigit(s[0])) {
            st.push(s);
        }
        else {
            if(s == "add") {

                if(st.size() >= 2) {
                    std::string num1 = st.top();
                    st.pop();
                    std::string num2 = st.top();
                    st.pop();

                    if(num1.find ('.') != std::string::npos || 
                       num2.find ('.') != std::string::npos )
                    {
                        double i = std::stod(num1);
                        double j = std::stod(num2);

                        std::cout << i + j << std::endl;
                    }
                    else {
                        int i = std::stoi(num1);
                        int j = std::stoi(num2);
                        std::cout<< i + j << std::endl;
                    }
/*
                    int i, j;

                    std::string num1 = st.top();

                    if(s.find('.') != std::string::npos) {
                        static_cast<double>(i);// = pop_convert_double(st);
                    } else {
                        i = pop_convert_int(st);
                    }
                    st.pop();

                    std::string num2 = st.top();

                    if(s.find('.') != std::string::npos) {
                        const_cast<double>(j); 
                        j = pop_convert_double(st);
                    } else {
                        j = pop_convert_int(st);
                    }
                    st.pop();

                    std::cout << i + j << std::endl;
*/
                }
            }
        }
	}
    
    //DEBUGGING
    //Print out contents of stack
    /*
    while(!st.empty()) {
        auto t = st.top();
        std::cout << t << std::endl;
        st.pop();
    }*/

	in.close();
}

double pop_convert_double (std::stack<std::string> &st) {
    double i = std::stod(st.top());
    st.pop();
    return i;
}

int pop_convert_int (std::stack<std::string> &st) {
    int i = std::stoi(st.top());
    st.pop();
    return i;
}
