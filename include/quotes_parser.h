#ifndef IEX_PCAP_QUOTES_PARSER_H
#define IEX_PCAP_QUOTES_PARSER_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "iex_decoder.h"

/// \class IexQuotesParser
/// \brief A class for parsing and storing to csv an IEX file stream.
class IEXQuotesParser {
public:
    IEXQuotesParser(std::string pcap_path);

    /// \brief Parse QuotesUpdates messages for a given symbol and write in a csv file.
    ///
    /// \param symbol Security identifier
    /// \param destination_folder A string for the output csv destination folder.
    void ExtractToCsv(std::string symbol, std::string destination_folder);

    /// \brief Parse QuotesUpdates messages for all symbols and write in a csv file.
    ///
    /// \param destination_folder A string for the output csv destination folder.
    /// \param split_symbols A boolean if true split parsed quotes into multiple csv files (one per symbol).
    /// Otherwise just write in one large csv file.
    void ExtractToCsv(std::string destination_folder, bool split_symbols);

    /// \brief Count QuoteUpdateMessages for each symbol.
    /// /// \return A std::map with symbol and key and message count as value.
    std::map<std::string, int> CountMessagesPerSymbol();

private:
    /// \brief A string with absolute path to the pcap file to be parsed.
    std::string pcap_path;

    /// \brief Parse QuotesUpdates messages for all symbols and write in a csv file.
    std::vector<std::string> symbols;

    /// \brief Number of unique symbols in pcap files.
    void UniqueSymbols();
};

#endif //IEX_PCAP_QUOTES_PARSER_H
