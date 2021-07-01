#include <fstream>
#include "storage.h"
#include "iex_messages.h"

void CsvStorage::Write(const IEXMessageBase &msg) {
    std::string msg_type_str = MessageTypeToString(msg.GetMessageType());

    if (out_map.find(msg_type_str) == out_map.end())
    {
        // first time this message type has been seen
        // open out stream and write header
        out_map[msg_type_str] = new std::ofstream(destination + "/" + msg_type_str + ".csv");
        std::ofstream * out = out_map[msg_type_str];
        for (auto& field : msg.Header())
            *out << field << ",";
        *out << std::endl;
    }
    std::ofstream * out = out_map[msg_type_str];
    // now write messages values
    for (auto& value : msg.ToList())
        *out << value << ",";
    *out << std::endl;
}
