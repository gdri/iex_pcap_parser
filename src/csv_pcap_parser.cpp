#include <string>
#include "parser.h"
#include "storage.h"

int main(int argc, char *argv[]) {
    // first arg: pcap file
    std::string pcap_path {argv[1]};
    // second arg: target path for output csv
    std::string destination_folder {argv[2]};

    // writing to csv format
    IStorage* storage = new CsvStorage(destination_folder);

    // parse file
    ParsePcapFile(pcap_path, *storage);
    delete storage;
    return 0;
}
