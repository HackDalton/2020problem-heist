FROM hackdalton/c-build-base:0.1.0 AS build

WORKDIR /src

COPY . .

RUN chmod +x ./build.sh
RUN ./build.sh

FROM hackdalton/alpine-airport:1.0.0

COPY --from=build /src/heist ./
COPY ./flag.txt ./

CMD airport "./heist"