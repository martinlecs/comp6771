#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <cmath>
#include <queue>

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

    //create an empty queue for 'repeat' command
    std::queue<string> repqueue;

    //repeat flag
    bool repeat = false;

    //variable to store number of times to repeat
    int repNum;

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
                        double sum = i + j;
                        std::string res = std::to_string(sum);
                        st.push(res);

                        std::cout << i << " + " << j << " = " 
                            << sum << std::endl;
                    }
                    else {
                        int i = std::stoi(num1);
                        int j = std::stoi(num2);
                        int sum = i + j;
                        std::string res = std::to_string(sum);
                        st.push(res);

                        std::cout << i << " + " << j << " = " 
                            << sum << std::endl;
                    }
                }
            }

            if (s == "sub") {
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
                        double sub = i - j;
                        std::string res = std::to_string(sub);
                        st.push(res);

                        std::cout << i << " - " << j << " = " 
                            << sub << std::endl;
                    }
                    else {
                        int i = std::stoi(num1);
                        int j = std::stoi(num2);
                        int sub = i - j;
                        std::string res = std::to_string(sub);
                        st.push(res);

                        std::cout << i << " - " << j << " = " 
                            << sub << std::endl;
                    }
                }
            }


            if (s == "mult") {
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
                        double mul = i * j;
                        std::string res = std::to_string(mul);
                        st.push(res);

                        std::cout << i << " * " << j << " = " 
                            << mul << std::endl;
                    }
                    else {
                        int i = std::stoi(num1);
                        int j = std::stoi(num2);
                        int mul = i * j;
                        std::string res = std::to_string(mul);
                        st.push(res);

                        std::cout << i << " * " << j << " = " 
                            << mul << std::endl;
                    }
                }
            }

            if (s == "div") {
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
                        double div = i / j;
                        std::string res = std::to_string(div);
                        st.push(res);

                        std::cout << i << " / " << j << " = " 
                            << div << std::endl;
                    }
                    else {
                        int i = std::stoi(num1);
                        int j = std::stoi(num2);
                        int div = i / j;
                        std::string res = std::to_string(div);
                        st.push(res);

                        std::cout << i << " / " << j << " = " 
                            << div << std::endl;
                    }
                }           
            }

            if (s == "sqrt") {
                //Note must convert to double for sqrt
                if(st.size() >= 1) {
                    std::string num = st.top();
                    st.pop();

                    double i = std::stod(num);
                    double res = sqrt(i);
                    st.push(std::to_string(res));

                    std::cout << "sqrt " << i << " = " << res << std::endl;
                }


            }

            if (s == "pop") {
                if(!st.empty())
                    st.pop();
            }

            if (s == "reverse") {
                int n = std::stoi(st.top());
                st.pop();

                std::queue<string> qu;

                for(int i = 0; i < n; ++i) {
                    qu.push(st.top());
                    st.pop();
                }
                while(!qu.empty()) {
                    st.push(qu.front());
                    qu.pop();
                }
            }

            if (s == "repeat") {
                //set a flag
                repeat = true;
                //set repeat number
                repNum = std::to_string(st.top());
                st.pop();
            }

            if (s == "endrepeat") {
                //need to put all the above basic math things into their
                //own functions
                
                for(int i = 0; i < repNum; ++i) {
                    if(repqueue.front() == "add" ) {}
                    if(repqueue.front() == "sub" ) {}
                    if(repqueue.front() == "mult" ) {}
                    if(repqueue.front() == "div" ) {}
                    if(repqueue.front() == "sqrt" ) {}
                    if(repqueue.front() == "pop" ) {}
                    if(repqueue.front() == "" ) {}
                    if(repqueue.front() == "add" ) {}


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
       }
       */
    in.close();
}

