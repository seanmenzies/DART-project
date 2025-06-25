#pragma once

#include <string>
#include "permit.pb.h"

class ProtobufFileWriter {
public:
    ProtobufFileWriter();

    bool WriteEventToFile(const permit::PermitEvent& event);
private:
    std::string baseDirectory = "../logs/";
};