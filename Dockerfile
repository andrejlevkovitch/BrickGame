FROM andrejlevkovitch/ubuntu_qt_boost:second

ADD . /app

RUN mkdir /app/build

WORKDIR /app/build

RUN cmake -DBUILD_SHARED_LIBS=1 -DCMAKE_BUILD_TYPE=Release ..
RUN cmake --build .
RUN make test

RUN make clean
RUN rm * ../bin ../lib -rf

RUN cmake -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=1 -DCMAKE_BUILD_TYPE=Release ..
RUN cmake --build .
RUN make test

RUN make clean
RUN rm * ../bin ../lib -rf

RUN cmake -DCMAKE_CXX_COMPILER=clang++ -DBUILD_SHARED_LIBS=0 -DCMAKE_BUILD_TYPE=Release ..
RUN cmake --build .
RUN make test
