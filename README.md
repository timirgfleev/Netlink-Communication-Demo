# Netlink Communication Project

This project demonstrates simple communication between two applications using the Netlink protocol in C++. The project consists of two applications: a sender (`nl_client`) and a receiver (`nl_server`).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- CMake (version 3.10 or later)
- C++ compiler with C++20 support
- libnl library


### Building

To build the project, use the following commands:

```sh
mkdir build
cd build
cmake ..
make
```

This will generate two executables in the `build` directory: `nl_client` and `nl_server`.

## Usage

To use the applications, first start the server:

```sh
./build/nl_server
```

Then, in a separate terminal, start the client (sudo may be required):

```sh
./build/nl_client
```
or 
```sh
sudo ./build/nl_client
```

The client will send a message to the server, which will then print the received message.

## Code Structure

- `include/`: Contains the header files for the project.
- `recv/`: Contains the source code for the server application.
- `send/`: Contains the source code for the client application.
- `.vscode/`: Contains configuration files for Visual Studio Code.

## Running the Tests

This project includes unit tests to verify the functionality of the `Connection` and `StringMessage` classes. CmakeLists.txt is configured to use them.

To run the tests, you can use:

```sh
ctest
```
in build directory

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

Email - timirgfleev@gmail.com
Project Link: https://github.com/timirgfleev/Netlink-Communication-Demo