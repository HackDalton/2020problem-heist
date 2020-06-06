FROM hackdalton/c-build-base:0.1.0 AS build

WORKDIR /src

COPY . .

RUN chmod +x ./build.sh
RUN ./build.sh

FROM alpine/socat

COPY --from=build /src/heist ./
COPY ./flag.txt ./

CMD socat TCP-LISTEN:8080,reuseaddr,fork EXEC:"./heist"