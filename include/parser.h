
#ifndef IEX_PCAP_PARSER_H
#define IEX_PCAP_PARSER_H

#include <string>
#include "storage.h"
#include "iex_decoder.h"

//TODO: return info about parsing rather than void
void ParsePcapFile(std::string pcap_path, IStorage& storage) ;

#endif //IEX_PCAP_PARSER_H
