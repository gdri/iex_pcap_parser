//
// Created by gilles on 30/06/2021.
//

#include "parser.h"
#include "iex_decoder.h"
#include "storage.h"

void ParsePcapFile(std::string pcap_path, IStorage& storage) {
    IEXDecoder decoder;
    if (!decoder.OpenFileForDecoding(pcap_path)) {
        std::cout << "Failed to open file '" << pcap_path << "'." << std::endl;
    }
    std::unique_ptr<IEXMessageBase> msg_ptr;
    auto ret_code = decoder.GetNextMessage(msg_ptr);
    for (; ret_code == ReturnCode::Success; ret_code = decoder.GetNextMessage(msg_ptr))
        storage.Write(*msg_ptr);
}
