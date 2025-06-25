#include "ProtobufFileWriter.h"
#include <fstream>
#include <filesystem>

ProtobufFileWriter::ProtobufFileWriter()
{
    std::filesystem::create_directories(baseDirectory);
}

bool ProtobufFileWriter::WriteEventToFile(const permit::PermitEvent& event) {
    std::string path = baseDirectory + "/permit_events" + std::to_string(event.timestamp_ms()) + "pb";
    std::filesystem::create_directories(baseDirectory);
    std::ofstream output(path, std::ios::binary | std::ios::app);
    return event.SerializeToOstream(&output);
}