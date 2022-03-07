#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <poll.h>
#include <sstream>
#include <netdb.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <unistd.h>

#define MAX_BUFFER_LENGTH 512

using std::string;

string getDateTime(const char *format) {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), format, timeinfo);
	return buffer;
}

void run(int sockfd, const string& password) {
	string init;
	init += "PASS " + password + "\n";
	init += "NICK timebot\n";
	init += "USER timebot 0 * :timebot\n";
	init += "JOIN #time\n";
	send(sockfd, init.c_str(), init.length(), 0);
	
	int len;
	char buffer[MAX_BUFFER_LENGTH];
	string content;
	string line;

	bool use24format = false;

	while ((len = recv(sockfd, buffer, MAX_BUFFER_LENGTH - 1, 0)) > 0) {
		buffer[len] = 0;
		content += buffer;
		if (content.find('\n') != string::npos) {
			content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());

			std::istringstream ss(content.c_str());
			while (std::getline(ss, line, '\n')) {
				if (ss.eof() && !line.empty())
					content = line;
				else
					content.clear();
				string command = "PRIVMSG #time ";
				if (line.find(command) != string::npos) {
					line.erase(0, line.find(command) + command.length());
					string message = command + ":";
					if (line.find("24") != string::npos) {
						use24format = true;
						message += "Successfully set hours format on 24.";
					} else if (line.find("12") != string::npos) {
						use24format = false;
						message += "Successfully set hours format on 12.";
					} else if (line.find("datetime") != string::npos) {
						if (use24format)
							message += getDateTime("Today is %A, %B %d, %Y and it is %H:%M");
						else
							message += getDateTime("Today is %A, %B %d, %Y and it is %I:%M %p");
					} else if (line.find("date") != string::npos) {
						message += getDateTime("Today is %A, %B %d, %Y");
					} else if (line.find("time") != string::npos) {
						if (use24format)
							message += getDateTime("It is %H:%M");
						else
							message += getDateTime("It is %I:%M %p");
					} else {
						message += "Send `datetime', `date' or `time' on this channel. ";
						message += "Use `24` or `12` to change the format for hours.";
					}
					message += "\n";
					send(sockfd, message.c_str(), message.length(), 0);
				}
			}
		}
	}
}

int main(int argc, const char **argv) {
	if (argc < 3 || argc > 4) {
		std::cerr << "Only two or three arguments allowed." << std::endl;
		return 1;
	}
	std::cout << "Setting up the client..." << std::endl;

	int sockfd, port;
	struct sockaddr_in serv_addr;
    struct hostent *server;

	port = argc == 4 ? std::atoi(argv[2]) : 6667;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cerr << std::strerror(errno) << std::endl;
		return errno;
	}
    server = gethostbyname(argv[1]);
	if (server == NULL) {
		std::cerr << std::strerror(errno) << std::endl;
		return errno;
	}

    std::memcpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) { 
		std::cerr << std::strerror(errno) << std::endl;
		return errno;
	}

	run(sockfd, argv[argc - 1]);
	close(sockfd);
	shutdown(sockfd, SHUT_RDWR);
	return 0;
}
