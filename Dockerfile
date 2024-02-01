FROM gcc:latest

ARG PORT=5050
ENV ENV_VAR=$PORT

WORKDIR /usr/src/app

COPY . .

RUN apt-get update && \
    apt-get install -y \
        cmake \
        make \
        gcc \
        g++ \
        libc++-dev \
    && rm -rf /var/lib/apt/lists/*

EXPOSE $PORT

CMD make clean && make tcp_server && ./tcp_server_run $PORT

