#include <string>
#include <fstream>
#include "quotes_parser.h"
#include <map>

int main(int argc, char *argv[]) {

    // First argument: pcap file to parse
    // Second argument: output csv file for symbol count

    if (argc != 3)
    {
        return 1;
    }

    IEXQuotesParser parser {argv[1]};
    std::map<std::string, int> count = parser.count();

    std::ofstream out_stream;
    try {
        out_stream.open(argv[2]);
    } catch (...) {
        std::cout << "Exception thrown opening output file." << std::endl;
    }

    out_stream << "Symbol, count" << std::endl;
    for (auto const& elem : count)
        out_stream<< elem.first << "," << elem.second << std::endl;

    return 0;
}
