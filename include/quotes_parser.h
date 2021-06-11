#ifndef IEX_PCAP_QUOTES_PARSER_H
#define IEX_PCAP_QUOTES_PARSER_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "iex_decoder.h"

class IEXQuotesParser {
public:
    IEXQuotesParser(std::string pcap_path);
    void extract(std::string symbol, std::string destination_folder);
    void extract(std::string destination_folder, bool split_symbols);
    std::map<std::string, int> count();

private:
    std::string pcap_path;
    std::vector<std::string> symbols;
    void unique_symbols();
};

#endif //IEX_PCAP_QUOTES_PARSER_H
