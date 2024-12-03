#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <map>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 8192 // Kích thước bộ đệm

// Struct HTTP request
struct HttpRequest {
    std::string method;               // HTTP Method (GET, POST, PUT, DELETE, ...)
    std::string url;                  // URL (ví dụ: /index.html)
    std::string version;              // Phiên bản HTTP (ví dụ: HTTP/1.1)
    std::map<std::string, std::string> headers; // Các headers trong request (key-value)
    std::string body;                 // Thân request (nếu có, ví dụ với POST)

    // Hàm hiển thị HTTP Request dưới dạng chuỗi
    void display() const {
        std::cout << method << " " << url << " " << version << "\r\n";
        
        // Hiển thị các headers
        for (const auto& header : headers) {
            std::cout << header.first << ": " << header.second << "\r\n";
        }
        
        // Nếu có body, hiển thị
        if (!body.empty()) {
            std::cout << "\r\n" << body;
        }
        
        std::cout << std::endl;
    }
};

// Hàm phân tích HTTP Request từ dữ liệu nhận được từ client
HttpRequest parse_http_request(const std::string& request) {
    HttpRequest http_request;
    size_t method_end = request.find(" ");
    http_request.method = request.substr(0, method_end);

    size_t url_end = request.find(" ", method_end + 1);
    http_request.url = request.substr(method_end + 1, url_end - method_end - 1);

    size_t version_end = request.find("\r\n", url_end + 1);
    http_request.version = request.substr(url_end + 1, version_end - url_end - 1);

    // Phân tích headers
    size_t header_start = version_end + 2;
    size_t header_end;
    while ((header_end = request.find("\r\n", header_start)) != std::string::npos) {
        if (header_end == header_start) break; // Kết thúc headers
        std::string header_line = request.substr(header_start, header_end - header_start);
        
        size_t colon_pos = header_line.find(":");
        if (colon_pos != std::string::npos) {
            std::string header_name = header_line.substr(0, colon_pos);
            std::string header_value = header_line.substr(colon_pos + 2); // Bỏ qua dấu ": "
            http_request.headers[header_name] = header_value;
        }
        header_start = header_end + 2;
    }

    // Body nếu có (dành cho POST, PUT)
    size_t body_start = request.find("\r\n\r\n");
    if (body_start != std::string::npos) {
        http_request.body = request.substr(body_start + 4); // Bỏ qua dấu "\r\n\r\n"
    }

    return http_request;
}

// Hàm xử lý yêu cầu từ client và gửi tới server đích
void handle_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    // Nhận yêu cầu từ client
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        std::cerr << "Failed to receive data from client. Closing connection." << std::endl;
        closesocket(client_socket);
        return;
    }

    // Hiển thị yêu cầu nhận được từ client
    std::cout << "Request from client:\n" << buffer << std::endl;

    // Phân tích HTTP request
    std::string request(buffer);
    HttpRequest http_request = parse_http_request(request);

    // Hiển thị HTTP request đã phân tích
    http_request.display();

    // Tách tên miền và cổng (nếu có)
    std::string host = http_request.headers["Host"];
    std::string server_ip = host;
    int server_port = 80; // Mặc định cổng HTTP

    size_t colon_pos = host.find(":");
    if (colon_pos != std::string::npos) {
        server_ip = host.substr(0, colon_pos);
        server_port = std::stoi(host.substr(colon_pos + 1));
    }

    // Kết nối tới server đích
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Failed to create server socket. Error: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        return;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    
    // Thay đổi inet_pton thành InetPton
    if (InetPton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid server IP address. Closing connection." << std::endl;
        closesocket(server_socket);
        closesocket(client_socket);
        return;
    }

    if (connect(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server. Error: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        closesocket(client_socket);
        return;
    }

    // Gửi yêu cầu HTTP từ client tới server đích
    int bytes_sent = send(server_socket, request.c_str(), request.size(), 0);
    if (bytes_sent == SOCKET_ERROR) {
        std::cerr << "Failed to forward request to server. Error: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        closesocket(client_socket);
        return;
    }

    // Nhận phản hồi từ server và gửi lại cho client
    int bytes_received_from_server;
    while ((bytes_received_from_server = recv(server_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        send(client_socket, buffer, bytes_received_from_server, 0);
    }

    // Đóng kết nối
    closesocket(server_socket);
    closesocket(client_socket);
    std::cout << "Connection closed." << std::endl;
}

int main() {
    // Khởi tạo WinSock
    WSADATA wsaData;
    int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        std::cerr << "WSAStartup failed with error: " << wsResult << std::endl;
        return 1;
    }

    // Tạo socket cho proxy server
    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed. Error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in proxy_addr;
    proxy_addr.sin_family = AF_INET;
    proxy_addr.sin_port = htons(8080); // Proxy chạy trên cổng 8080
    proxy_addr.sin_addr.s_addr = INADDR_ANY;

    // Liên kết socket với địa chỉ
    if (bind(listen_socket, (sockaddr*)&proxy_addr, sizeof(proxy_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    // Lắng nghe kết nối đến
    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    std::cout << "Proxy server is listening on port 8080..." << std::endl;

    // Chấp nhận kết nối từ client
    sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    SOCKET client_socket = accept(listen_socket
