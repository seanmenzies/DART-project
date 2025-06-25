#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "permit.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using permit::IngestionService;
using permit::PermitEvent;
using permit::Ack;
using permit::PositionEvent;
using permit::EventType;

class IngestionTestClient {
public:
    IngestionTestClient(std::shared_ptr<Channel> channel)
        : stub_(IngestionService::NewStub(channel)) {}

    void SendTestEvent() {
        // Construct a test event
        PermitEvent event;
        event.set_user_id("user123");
        event.set_type(EventType::POSITION);
        event.set_timestamp_ms(static_cast<int64_t>(time(nullptr)) * 1000);

        PositionEvent* pos = event.mutable_position();
        pos->set_instrument("AAPL");
        pos->set_quantity(100);
        pos->set_avg_price(145.25);

        Ack response;
        ClientContext context;

        Status status = stub_->SubmitEvent(&context, event, &response);

        if (status.ok()) {
            std::cout << "Success: " << response.success()
                      << " | Message: " << response.message() << std::endl;
        } else {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<IngestionService::Stub> stub_;
};

int main() {
    IngestionTestClient client(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));
    client.SendTestEvent();
    return 0;
}