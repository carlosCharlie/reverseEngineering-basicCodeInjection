#include <iostream>


int add(int a,int b){
    return a+b;
}
int multiply(int a,int b){
    return a*b;
}


int main ()
{
    char operation;
    int op1,op2;

    std::cin>>op1;
    std::cin>>operation;
    std::cin>>op2;

    //calling functions
    switch(operation){
        case '+':
            std::cout<<add(op1,op2);
        break;
        case '*':
            std::cout<<multiply(op1,op2);
        break;
    }
    return 0;
}
