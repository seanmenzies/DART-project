FROM grpc/cxx:latest

WORKDIR /app
COPY . .

RUN mkdir -p ingestion/build && cd ingestion/build && \
    cmake .. && make -j$(nproc)

CMD ["./ingestion/build/ingestion_service"]