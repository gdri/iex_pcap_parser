# IEX_pcap_parser
C++ project for decoding and parsing IEX pcap files to csv. This project is mainly for teaching myself some C++. It is greatly inspired from the excellent IEX_pcap project
(https://github.com/rosskidson/IEX_pcap). Thanks to the contributors of IEX_pcap for their great work!

### IEX pcap

The IEX stock exchange provides free orderbook data for all the stocks traded. The network packets containing the
market messages are stored in .pcap files and need to be decoded and parsed. Historical recordings of both top of the
orderbook and deeper levels are accessible on a T+1 basis and can be found here (https://iextrading.com/trading/market-data/).


### Usage

Following is a minimal example to extract the content of a .pcap file to csv.  This is included in the source.

``` c++
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
    return 0;
}

```

### TODO list
- gzip compression/decompression of csv files
- Python bindings
