/*
 * Phoenix2D (RoboCup Soccer Simulation 2D League)
 * Copyright (c) 2013 Ivan Gonzalez
 *
 * This file is part of Phoenix2D.
 *
 * Phoenix2D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phoenix2D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Phoenix2D.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Connect.h"
#include "Config.h"
namespace Phoenix
{
struct Socket {
	int socketfd;
	struct sockaddr_in server;
};

Socket sock;

void connectToServer(const char *host, int port) {
	int sockfd;
	struct sockaddr_in server_addr;
	struct hostent *host_0;
	struct in_addr *addr_ptr;
	if (inet_addr(host) == INADDR_NONE) {
		host_0 = (struct hostent *)gethostbyname(host);
		if (host_0 == 0) {
			std::cerr << "Connect::connectToServer(const char *, int) -> can not get host" << std::endl; //Error: can not get host
			return;
		} else {
			addr_ptr = (struct in_addr *)(*host_0->h_addr_list);
			host = inet_ntoa(*addr_ptr);
		}
	}
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		std::cerr << "Connect::connectToServer(const char *, int) -> can not open socket" << std::endl; //Error: can not open socket
		return;
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(0);
	sock.server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Connect:connectToServer(const char *, int) -> can not bind host" << std::endl; //Error: can not bind host
		return;
	}
	sock.socketfd = sockfd;
	bzero(&sock.server, sizeof(sock.server));
	sock.server.sin_family = AF_INET;
	sock.server.sin_port = htons(port);
	sock.server.sin_addr.s_addr = inet_addr(host);
}

Connect::Connect(const char *host, int port) {
	connectToServer(host, port);
}

Connect::~Connect() {
	if (Config::VERBOSE) std::cout << "Connect out" << std::endl;
}

void Connect::disconnect() {
	shutdown(sock.socketfd, SHUT_RDWR);
	close(sock.socketfd);
}

bool Connect::sendMessage(std::string msg) {
	int size = msg.size() + 1;
	if (sendto(sock.socketfd, msg.c_str(), size, 0, (struct sockaddr *)&sock.server, sizeof(sock.server)) < 0) {
		std::cerr << "Connect::sendMessage(string) -> error sending message" << std::endl;
		return false;
	}
	return true;
}

std::string Connect::receiveMessage() {
	char msg[4096];
	socklen_t servlen;
	struct sockaddr_in serv_addr;
	servlen = sizeof(serv_addr);
	if (recvfrom(sock.socketfd, msg, 4096, 0, (struct sockaddr *)&serv_addr, &servlen) < 0) {
		std::cerr << "Connect::receiveMessage() -> error reading message" << std::endl;
		return "(error socket_failed)";
	} else {
		if (sock.server.sin_port != serv_addr.sin_port) {
			sock.server.sin_port = serv_addr.sin_port;
		}
		return std::string(msg);
	}
}
}