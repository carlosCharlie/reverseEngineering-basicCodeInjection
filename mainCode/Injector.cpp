#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <mutex>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
std::mutex mtx;

int main() {

    pid_t pid = vfork();

    switch (pid)
    {
    case -1:
        std::cout<<"error";
        break;

    case 0: //child
        std::cout<<getpid();
        std::cout<<"runing target"<<std::endl;
        execv("./src/target",nullptr);

        break;

    default:

        //getting target address
        std::string address;
        std::ifstream file;
        long addressPointer;
        std::string data = "";

        do{
        	sleep(1);
        	file.open("/proc/"+std::to_string(pid)+"/maps");
        	getline(file,address);
        }while(address=="");
        getline(file,address);
        int spaceIndex = 0;
        while (address[spaceIndex]!='-'){spaceIndex++;};
        address = address.substr(0,spaceIndex);
        addressPointer = stol(address, 0, 16)+570;//address to call to multiply function
        file.close();

        //replace multiply op with add
        char add = 0x4a;
        int fileDes =open(("/proc/"+std::to_string(pid)+"/mem").c_str(),O_RDWR);
        lseek(fileDes,addressPointer+1,SEEK_SET);
        write(fileDes,&add,sizeof(char));
        close(fileDes);

        int status;
        wait(&status);
        break;
    }
    
    return 0;
}
