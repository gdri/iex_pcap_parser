#include "quotes_parser.h"
#include <fstream>
#include "iex_decoder.h"
#include <map>
#include <vector>
#include <algorithm>



IEXQuotesParser::IEXQuotesParser(std::string pcap_path) : pcap_path(pcap_path) {
    UniqueSymbols();
}

void IEXQuotesParser::UniqueSymbols() {
    std::set<std::string> symbols_set;

    IEXDecoder decoder;
    if (!decoder.OpenFileForDecoding(pcap_path)) {
        std::cout << "Failed to open file '" << pcap_path << "'." << std::endl;
    }

    std::unique_ptr<IEXMessageBase> msg_ptr;
    auto ret_code = decoder.GetNextMessage(msg_ptr);

    for (; ret_code == ReturnCode::Success; ret_code = decoder.GetNextMessage(msg_ptr)) {
        if (msg_ptr->GetMessageType() == MessageType::QuoteUpdate) {

            // Cast it to the derived type.
            auto quote_msg = dynamic_cast<QuoteUpdateMessage*>(msg_ptr.get());
            symbols_set.insert(quote_msg->symbol);
        }
    }
    std::vector<std::string> symbols_vect(symbols_set.begin(), symbols_set.end());
    symbols = symbols_vect;
}

void IEXQuotesParser::ExtractToCsv(std::string symbol, std::string destination_folder) {
    // csv filename is same as pcap
    std::string pcap_filename = pcap_path.substr(pcap_path.rfind("/") + 1);
    std::string output_csv_filename = symbol + "_" + pcap_filename.substr(0, pcap_filename.find(".")) + ".csv";

    std::ofstream out_stream;
    std::string full_path = destination_folder + "/" + output_csv_filename;
    out_stream.open(full_path);

    bool is_symbol_in = (std::find(symbols.begin(), symbols.end(), symbol) != symbols.end());

    if (is_symbol_in)
    {
        IEXDecoder decoder;
        if (!decoder.OpenFileForDecoding(pcap_path)) {
            std::cout << "Failed to open file '" << pcap_path << "'." << std::endl;
        }

        out_stream << "timestamp,bid_size,bid_price,ask_size,ask_price" << std::endl;
        std::unique_ptr<IEXMessageBase> msg_ptr;

        auto ret_code = decoder.GetNextMessage(msg_ptr);
        for (; ret_code == ReturnCode::Success; ret_code = decoder.GetNextMessage(msg_ptr)) {
            if (msg_ptr->GetMessageType() == MessageType::QuoteUpdate) {
                auto quote_msg = dynamic_cast<QuoteUpdateMessage*>(msg_ptr.get());
                if (quote_msg && quote_msg->symbol == symbol) {
                    out_stream << quote_msg->timestamp << ","
                    << quote_msg->bid_size << ","
                    << quote_msg->bid_price << ","
                    << quote_msg->ask_size << ","
                    << quote_msg->ask_price << std::endl;
                }
            }
        }
        out_stream.close();
    }
}

void IEXQuotesParser::ExtractToCsv(std::string destination_folder, bool split_symbols) {
    IEXDecoder decoder;
    if (!decoder.OpenFileForDecoding(pcap_path)) {
        std::cout << "Failed to open file '" << pcap_path << "'." << std::endl;
    }

    // csv filename is same as pcap
    std::string pcap_filename = pcap_path.substr(pcap_path.rfind("/") + 1);
    std::string output_csv_filename = pcap_filename.substr(0, pcap_filename.find(".")) + ".csv";

    std::unique_ptr<IEXMessageBase> msg_ptr;
    auto ret_code = decoder.GetNextMessage(msg_ptr);
    if (split_symbols)
    {
        // creating a map of streams indexed by symbols
        std::map<std::string, std::ofstream*> output_map;
        for (auto& symbol: symbols)
        {
            std::string filename = symbol + "_" + output_csv_filename;
            output_map[symbol] = new std::ofstream(destination_folder + "/" + filename);
        }

        // iterate through packets and write into mapped stream
        for (; ret_code == ReturnCode::Success; ret_code = decoder.GetNextMessage(msg_ptr)) {
            if (msg_ptr->GetMessageType() == MessageType::QuoteUpdate) {
                auto quote_msg = dynamic_cast<QuoteUpdateMessage *>(msg_ptr.get());
                std::string symbol = quote_msg->symbol;
                *output_map[symbol] << quote_msg->timestamp << ","
                                    << quote_msg->symbol << ","
                                    << quote_msg->bid_size << ","
                                    << quote_msg->bid_price << ","
                                    << quote_msg->ask_size << ","
                                    << quote_msg->ask_price << std::endl;
            }
        }
        // close all streams
        for (auto& elem: output_map)
        {
            delete elem.second;
            elem.second = 0;
        }
    }
    else
    {
        std::ofstream out_stream;
        std::string full_path = destination_folder + "/" + output_csv_filename;
        out_stream.open(full_path);
        out_stream << "timestamp,symbol,bid_size,bid_price,ask_size,ask_price" << std::endl;

        for (; ret_code == ReturnCode::Success; ret_code = decoder.GetNextMessage(msg_ptr)) {
            if (msg_ptr->GetMessageType() == MessageType::QuoteUpdate) {
                auto quote_msg = dynamic_cast<QuoteUpdateMessage*>(msg_ptr.get());
                out_stream << quote_msg->timestamp << ","
                           << quote_msg->symbol << ","
                           << quote_msg->bid_size << ","
                           << quote_msg->bid_price << ","
                           << quote_msg->ask_size << ","
                           << quote_msg->ask_price << std::endl;
            }
        }
        out_stream.close();
    }
}

std::map<std::string, int> IEXQuotesParser::CountMessagesPerSymbol() {
    std::map<std::string, int> symbol_counts;

    for (auto& symbol: symbols)
        symbol_counts[symbol] = 0;

    IEXDecoder decoder;
    if (!decoder.OpenFileForDecoding(pcap_path)) {
        std::cout << "Failed to open file '" << pcap_path << "'." << std::endl;
    }

    std::unique_ptr<IEXMessageBase> msg_ptr;
    auto ret_code = decoder.GetNextMessage(msg_ptr);
    for (; ret_code == ReturnCode::Success; ret_code = decoder.GetNextMessage(msg_ptr)) {
        if (msg_ptr->GetMessageType() == MessageType::QuoteUpdate) {
            auto quote_msg = dynamic_cast<QuoteUpdateMessage*>(msg_ptr.get());
            symbol_counts[quote_msg->symbol]++;
        }
    }
    return symbol_counts;
}