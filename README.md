# IEX_pcap_parser
C++ project for decoding and parsing IEX pcap files to csv. This project is mainly for teaching myself some C++. It is greatly inspired from the excellent IEX_pcap project
(https://github.com/rosskidson/IEX_pcap). Thanks to the contributors of IEX_pcap for their great work!

### IEX pcap

The IEX stock exchange provides free orderbook data for all the stocks traded. The network packets containing the
market messages are stored in .pcap files and need to be decoded and parsed. Historical recordings of both top of the
orderbook and deeper levels are accessible on a T+1 basis and can be found here (https://iextrading.com/trading/market-data/).


### Usage

Following is a minimal example to extract all the quotes for all symbols of a given pcap file and output to csv.  This is included in the source.

``` c++
#include <fstream>
#include "quotes_parser.h"

int main(int argc, char *argv[]) {

    if (argc > 4)
        return 1;

    if (argc < 3)
        return 1;

    // first arg: pcap file
    IEXQuotesParser parser{argv[1]};
    // second arg: output csv file
    std::string output_file = argv[2];
    if (argc == 3) {
        // Here parse all symbols and split across csv files
        parser.extract(output_file, false);
        return 0;
    } else if (argc == 4) {
        // Here parse a single symbol
        // third arg: symbol name
        std::string symbol = argv[3];
        parser.extract(symbol, output_file);
        return 0;
    }
}
```

### TODO list
- gzip compression/decompression of csv files
- Python bindings
- abstract parser class to handle multiple categories of messages (not only quotes)