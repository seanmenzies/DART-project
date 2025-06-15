# 🧠 D.A.R.T. – Distributed Analytics & Risk Tracker

A high-performance, distributed system for ingesting and analyzing PERMIT-style user data in real-time, with a C++-first architecture and multi-language integration (Python, SQL, AWS-compatible tooling).

---

## 🎯 Project Goal

Build a modular system that:
- Ingests and processes simulated PERMIT user events
- Distributes data through a real-time pipeline (Kafka or ZeroMQ)
- Stores, aggregates, and analyzes user-level risk and behavior
- Supports batch replays, risk checks, and analytics via a distributed architecture

> Built with **C++20**, **Python**, **SQL**, and **cloud-emulated tooling** (S3, RDS) via Docker.

---

## 🧱 Tech Stack

| Layer        | Tools / Frameworks |
|--------------|--------------------|
| Core Engine  | C++20, Boost.Asio, gRPC or sockets |
| Messaging    | Apache Kafka (or Redpanda), Protobuf |
| Analytics    | Python (Pandas, NumPy, FastAPI) |
| Storage      | PostgreSQL, DuckDB, MinIO (S3-compatible) |
| Orchestration| Docker + Docker Compose |
| Optional UI  | Plotly Dash, Jupyter Notebooks |

---

## 🗂️ PERMIT Event Model

Simulate user activity through the PERMIT acronym:
- **P**osition
- **E**xposure
- **R**isk
- **M**argin
- **I**nteraction
- **T**rade

Events are serialized using Protobuf and streamed through Kafka.

---

## 📆 Milestones & Timeline

### 🔹 Milestone 1: Ingestion Engine (C++)
- Define `permit.proto` schema
- Build `IngestionService` in C++ with gRPC or raw sockets
- Log data to disk in JSON/Protobuf format

### 🔹 Milestone 2: Messaging Layer
- Deploy Kafka or ZeroMQ with Docker
- Integrate C++ producer → Kafka → Python consumer
- Store events in PostgreSQL or DuckDB

### 🔹 Milestone 3: Analytics Engine (Python)
- Build FastAPI service with user endpoints
- Schedule jobs to compute:
  - Daily PnL
  - Exposure summaries
  - Margin risk flags
- Store analytics snapshots in SQL

### 🔹 Milestone 4: Batch Replay / Backtest System
- Write `ReplayRunner` in C++ to simulate past event streams
- Trigger analytics recalculations on replayed data
- Compare real-time vs replay analytics

### 🔹 Milestone 5: Cloud Emulation & CI/CD
- Dockerize all services
- Emulate cloud via:
  - MinIO (S3-compatible)
  - Local PostgreSQL
- GitHub Actions for build/test pipeline

---

## 🚀 Getting Started

```bash
# Clone repo and run core services
git clone https://github.com/yourusername/dart-system.git
cd dart-system
docker-compose up --build
