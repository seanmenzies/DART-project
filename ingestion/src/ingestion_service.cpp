#include "permit.grpc.pb.h"
#include "ProtobufFileWriter.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <fstream>
#include <filesystem>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;

using permit::PermitEvent;
using permit::Ack;
using permit::IngestionService;

// Implement the service
class IngestionServiceImpl final : public IngestionService::Service {
private:
    std::unique_ptr<ProtobufFileWriter> Writer;

public:
    IngestionServiceImpl() 
        : Writer(std::make_unique<ProtobufFileWriter>()) {

    }

    Status SubmitEvent(ServerContext* context, const PermitEvent* request, Ack* response) override {
        std::cout << "Received event from user: " << request->user_id()
                  << ", type: " << request->type() << std::endl;

        bool ok = Writer->WriteEventToFile(*request);

        response->set_success(ok);
        response->set_message(ok ? "Logged successfully" : "Logging failed");
        
        return ok ? Status::OK : Status(StatusCode::INTERNAL, "Failed to write to file");
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
