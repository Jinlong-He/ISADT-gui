#include "../include/Cryptor.hpp"
#include <stdlib.h>
#include <iostream>
#include <string>
int main(){
    Cryptor cryptor;
    std::string key = "thisiskey";
    char* out = (char*)malloc(100*sizeof(char));
    std::string origin = "lixie";
    cryptor.aes_encrypt((char*)origin.c_str(), (char*)key.c_str(), out);
    std::cout << out << std::endl;
    char* outout = (char*)malloc(100*sizeof(char));
    cryptor.aes_decrypt(out, (char*)key.c_str(), outout);

    std::cout << outout << std::endl;
    free(out);
    free(outout);
}