#ifndef IEX_PCAP_STORAGE_H
#define IEX_PCAP_STORAGE_H

#include <string>
#include <fstream>
#include <typeindex>
#include <typeinfo>
#include <map>
#include "iex_messages.h"

/// \class IStorage
/// \brief Base class for message storage.
class IStorage {
public:
    virtual ~IStorage() {};
    /// \brief Write message into storage.
    ///
    /// \param msg Pointer to the current decoded message.
    virtual void Write(const IEXMessageBase& msg) = 0;
};

/// \class CsvStorage
/// \brief Message storage in Csv format.
class CsvStorage : public IStorage {
public:
    /// \param _destination path to csv.
    CsvStorage(std::string _destination) : destination(_destination) {}
    ~CsvStorage() {
        for (auto& elem: out_map)
        {
            elem.second->close();
            delete elem.second;
            elem.second = 0;
        }
    }
    void Write(const IEXMessageBase& msg) override;
private:
    /// \brief Destination path for csv files to be written.
    std::string destination;

    // TODO: use std::unique_ptr<ofstream> instead
    /// \brief map of out streams, indexed by message type.
    std::map<std::string, std::ofstream *> out_map;
};

#endif //IEX_PCAP_STORAGE_H
