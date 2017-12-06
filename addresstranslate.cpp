#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <math.h>

struct address_layout {
    uint16_t vbits;
    uint16_t pbits;
    uint32_t pgbytes;
};

struct page_table_entry {
    uint32_t frame;
    struct {
        bool valid;
        bool use;
        bool permission;
    };
};



int main( int argc, const char* argv[] ){

    address_layout addrlayout;
    //std::vector<unsigned> vaddress;
    std::vector<page_table_entry> pageTable;
    unsigned virtualAddress;
    unsigned vaddressMask;
    //std::getline( std::cin , vaddress[i] );
    //auto it = vaddress.insert( vaddress.begin(), virtualAddress);

    if( argc != 2){
        std::cout << "usage: " << argv[0] << " somepageTableFileFile " << std::endl;  
        std::exit(1);
    }

    std::ifstream pageTableFile( argv[1] );
    if( !pageTableFile ){
        std::cout << "error opening file " << argv[1] << std::endl;
        std::exit(1);
    }

    pageTableFile >> addrlayout.vbits 
                   >> addrlayout.pbits
                   >> addrlayout.pgbytes;

    int offsetBits = log2( addrlayout.pgbytes);
    int tableSize = pow(addrlayout.vbits - offsetBits, 2);
    unsigned mask = unsigned(-1) >> ( 8*sizeof(unsigned) - offsetBits);
    vaddressMask = unsigned(-1) >> ( 8*sizeof(unsigned) - addrlayout.vbits);
    for( int i = 0 ; i < tableSize && pageTableFile ; ++i){
        page_table_entry tmp;
        pageTableFile >> tmp.valid
                      >> tmp.permission
                      >> tmp.frame
                      >> tmp.use;
        pageTable.push_back( tmp);
    };
    pageTable.resize( tableSize, (page_table_entry){0});
    pageTableFile.close();
    std::string tmp;
    unsigned vaddress;
    while( std::cin >> tmp){
        if( tmp[1] == 'x'){
            vaddress = stoi( tmp, NULL , 16);
        }
        else{
            vaddress = stoi(tmp);
        }
        vaddress &= vaddressMask;
        unsigned offset = mask & vaddress;
        unsigned vpn = vaddress >> offsetBits;  
        page_table_entry answer = pageTable[ vpn]; 
        if( !answer.valid ){
            if( !answer.permission){
                std::cout << "SEGFAULT" << std::endl;
            }
            else{
                std::cout << "DISK" << std::endl;
            }
            continue;
        }
        unsigned paddress = ( answer.frame << offsetBits) | offset;
        std::cout << paddress << std::endl;
    }

     


    return 0;
}
