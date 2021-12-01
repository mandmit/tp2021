FROM gcc:latest as build

ADD . /src

WORKDIR /src

RUN g++ -o main main.cpp

CMD ["./main"]