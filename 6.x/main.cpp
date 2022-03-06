#include <iostream>


//const char* argv = "Ste7an";
//
//int args = 5 ;
int main(int argc, const char **argv) {

    for (int i = 0;i != argc; i++ ){
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }

    return 0;
}
