#include "iex_decoder.h"
#include <string>
#include <iostream>
#include <fstream>

/// counts messages from pcap files per message type
void count_messages(std::string input_file, std::string output_file) {
    IEXDecoder decoder;
    if (!decoder.OpenFileForDecoding(input_file)) {
        std::cout << "Failed to open file '" << input_file << "'." << std::endl;
    }

    // Get the first message from the pcap file.
    std::unique_ptr<IEXMessageBase> msg_ptr;
    auto ret_code = decoder.GetNextMessage(msg_ptr);
    int no_data_msg_count = 0;
    int stream_head_msg_count = 0;
    int system_event_msg_count = 0;
    int security_directory_msg_count = 0;
    int trading_status_msg_count = 0;
    int operation_halt_status_msg_count = 0;
    int short_sale_price_test_status_msg_count = 0;
    int official_price_msg_count = 0;
    int trade_break_msg_count = 0;
    int auction_information_msg_count = 0;
    int price_level_update_buy_msg_count = 0;
    int price_level_update_sell_msg_count = 0;
    int quotes_msg_count = 0;
    int trades_msg_count = 0;
    int total_msg_count = 0;
    for (; ret_code == ReturnCode::Success; ret_code = decoder.GetNextMessage(msg_ptr)) {
        total_msg_count++;
        if (msg_ptr->GetMessageType() == MessageType::NoData) {
            no_data_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::StreamHeader) {
            stream_head_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::SystemEvent) {
            system_event_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::SecurityDirectory) {
            security_directory_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::TradingStatus) {
            trading_status_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::OperationalHaltStatus) {
            operation_halt_status_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::ShortSalePriceTestStatus) {
            short_sale_price_test_status_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::QuoteUpdate) {
                quotes_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::TradeReport)
        {
            trades_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::OfficialPrice)
        {
            official_price_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::TradeBreak)
        {
            trade_break_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::AuctionInformation)
        {
            auction_information_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::PriceLevelUpdateBuy)
        {
            price_level_update_buy_msg_count++;
        }
        else if (msg_ptr->GetMessageType() == MessageType::PriceLevelUpdateSell)
        {
            price_level_update_sell_msg_count++;
        }

    }
    std::cout << "No Data " << no_data_msg_count << std::endl;
    std::cout << "Stream Header " << stream_head_msg_count << std::endl;
    std::cout << "System Event " << system_event_msg_count << std::endl;
    std::cout << "Trading Status " << trading_status_msg_count << std::endl;
    std::cout << "Operational Halt Status " << operation_halt_status_msg_count << std::endl;
    std::cout << "Short Sale Price Test Status " << short_sale_price_test_status_msg_count << std::endl;
    std::cout << "Quote Update " << quotes_msg_count << std::endl;
    std::cout << "Trade Report " << trades_msg_count << std::endl;
    std::cout << "Official Price " << official_price_msg_count << std::endl;
    std::cout << "Trade Break " << trade_break_msg_count << std::endl;
    std::cout << "Auction Information " << auction_information_msg_count << std::endl;
    std::cout << "Price Level Update Buy " << price_level_update_buy_msg_count << std::endl;
    std::cout << "Price Level Update Sell " << price_level_update_sell_msg_count << std::endl;
    std::cout << "Total " << total_msg_count << std::endl;

}

//int main(int argc, char* argv[])
//{
//    // Get the input pcap file as an argument.
//    if (argc < 2) {
//        std::cout << "Usage: iex_pcap_decoder <input_pcap>" << std::endl;
//        return 1;
//    }
//
//    std::string pcap_path(argv[1]);
////    count_messages(pcap_path);
//    std::set<std::string> symbols;
//    symbols = available_symbols(pcap_path);
//
//    std::ofstream out_stream;
//    std::string output_file(argv[2]);
//    try {
//        out_stream.open(output_file);
//    } catch (...) {
//        std::cout << "Exception thrown opening output file." << std::endl;
//    }
//    return 0;
//}

int main(int argc, char* argv[])
{
    return 0;
}
