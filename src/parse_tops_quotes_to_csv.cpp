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
