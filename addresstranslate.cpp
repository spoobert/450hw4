#include <iostream>
#include <fstream>
#include <vector>

struct address_layout {
    uint8_t vbits;

    uint8_t pbits;
    uint32_t pgbytes;
};

struct page_table_entry {
    uint32_t frame;
    struct {
        bool valid;
        bool use;
        bool permission;
    } access;
};

struct virtual_address {
    int offset;
    int vpagenumber;
    std::vector<int> vaddress;
    std::vector<int> it;
};




int main( int argc, const char* argv[] ){

    address_layout addrlayout;
    std::vector<std::string> vaddress;
    std::string virtualAddress;
    int i = 0;
    //std::getline( std::cin , vaddress[i] );
    //auto it = vaddress.insert( vaddress.begin(), virtualAddress);

    while(std::getline( std::cin, virtualAddress )){
        vaddress.push_back( virtualAddress);
    };
    for( int i = 0 ; i < vaddress.size() ; i++){
        std::cout << vaddress[i] << std::endl;
    }
    

    if( argc != 2){
        std::cout << "usage: " << argv[0] << " somePageTableFile " << std::endl;  
        std::exit(1);
    }

    std::ifstream addrLayoutFile( argv[1] );
    if( !addrLayoutFile ){
        std::cout << "error opening file " << argv[1] << std::endl;
        std::exit(1);
    }

    addrLayoutFile >> addrlayout.vbits 
                   >> addrlayout.pbits
                   >> addrlayout.pgbytes
                   >> std::ws;
    std::cout << addrlayout.vbits << " " << addrlayout.pbits << " " << addrlayout.pgbytes << std::endl;
    

    return 0;
}