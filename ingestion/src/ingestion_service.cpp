#include "permit.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <fstream>
#include <filesystem>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using permit::PermitEvent;
using permit::Ack;
using permit::IngestionService;

// Implement the service
class IngestionServiceImpl final : public IngestionService::Service {
public:
    Status SubmitEvent(ServerContext* context, const PermitEvent* request, Ack* response) override {
        std::cout << "Received event from user: " << request->user_id()
                  << ", type: " << request->type() << std::endl;

        response->set_success(true);
        response->set_message("Event received successfully.");

        std::string logPath = "logs/permit_event_" + std::to_string(request->timestamp_ms()) + ".pb";

        std::ofstream out(logPath, std::ios::out | std::ios::binary);
        if (out.is_open()) {
            if (!request->SerializeToOstream(&out)) {
                std::cerr << "Failed to write event to log file." << std::endl;
            }
            out.close();
        } 
        else {
            std::cerr << "Unable to open file for writing: " << logPath << std::endl;
        }
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    IngestionServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}
