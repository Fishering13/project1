FROM ubuntu:24.04 AS builder
RUN apt-get update && apt-get install -y --no-install-recommends cmake g++ \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY include include
COPY src src
COPY CMakeLists.txt Doxyfile ./
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF \
    && cmake --build build --parallel

FROM ubuntu:24.04
RUN apt-get update && apt-get install -y --no-install-recommends libstdc++6 \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY --from=builder /app/build/matrix_calculator ./matrix_calculator
ENTRYPOINT ["./matrix_calculator"]
