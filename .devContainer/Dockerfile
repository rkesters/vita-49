
FROM mamba/cppvcpkg:latest

RUN cd /opt \
    && git clone https://github.com/adeharo9/cpp-dotenv.git -n \
    && cd /opt/cpp-dotenv \
    && git checkout v1.0.0-alpha \
    && cd /opt/cpp-dotenv && cmake CMakeLists.txt && make

COPY FindPQXX.cmake /usr/local/share/cmake-3.18/Modules/
COPY FindPOSTGRES.cmake /usr/local/share/cmake-3.18/Modules/


RUN mkdir -p /root/.vscode-server/extensions \
    /root/.vscode-server-insiders/extensions \
    && chown -R root \ 
    /root/.vscode-server/extensions \
    /root/.vscode-server-insiders/extensions  

RUN vcpkg install caf glog boost-asio boost-chrono boost-filesystem nlohmann-json date && vcpkg integrate install
RUN vcpkg install croncpp gtest cpprestsdk