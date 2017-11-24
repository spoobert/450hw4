#include <iostream>
#include <fstream>

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






int main( int argc, const char* argv[] ){

    address_layout addrlayout;
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