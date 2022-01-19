#include <poll.h>
#include <sys/socket.h>
#include <vector>
#include <string>


#define MAX_BUFFER_LENGTH 4096

int main(int argc , char *argv[])
{
	(void) argc;
	(void) argv;
	struct sockaddr_in		address;
	socklen_t				addrlen;
	vector<struct pollfd>	pollfds;
	vector<char>			buffer(MAX_BUFFER_LENGTH);
	struct pollfd			serverSocket;
	struct pollfd	        newSocket;
	string					resString;
	int 					opt = 1;
	int                     timeout;
	int                     rc;
	int                     closeConn;

	if ((serverSocket.fd = socket(AF_INET , SOCK_STREAM , 0)) == 0)
		return -1;
	serverSocket.events = POLLIN;
	newSocket.events = POLLIN;

	if (setsockopt(serverSocket.fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
		return -1;
		
	opt = true;

	if (ioctl(serverSocket.fd, FIONBIO, (char *)&opt) < 0)
		return -1;

	pollfds.push_back(serverSocket);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if (bind(serverSocket.fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		return -1;

	if (listen(serverSocket.fd, 32) < 0)
		return -1;

	timeout = (3 * 60 * 1000);

	addrlen = sizeof(address);

	while (true) {
		rc = poll(&pollfds[0], pollfds.size(), timeout);

		if (rc < 1)
			exit(1);

		for (size_t i = 0; i < pollfds.size(); i++) {
			if (pollfds[i].revents == 0)
				continue ;
			if (pollfds[i].fd == serverSocket.fd) {
				while (true) {
					if ((newSocket.fd = accept(serverSocket.fd, NULL, NULL)) < 0) {
						if (errno != EWOULDBLOCK)
							exit(1);
						break ;
					}
					pollfds.push_back(newSocket);
				}
			}
			else {
				closeConn = false;
				while (true) {
					rc = recv(pollfds[i].fd, &buffer[0], buffer.size(), 0);
					if (rc < 0) {
						if (errno != EWOULDBLOCK) {
							closeConn = true;
						}
						break ;
					}
					else if (rc == 0) {
						closeConn = true;
						break ;
					}
					resString.append(buffer.cbegin(), buffer.cend());
					buffer.clear();
					buffer.resize(MAX_BUFFER_LENGTH);
					if (resString.find('\n') != string::npos) {
						rc = send(pollfds[i].fd, resString.c_str(), resString.length(), 0);
						resString.clear();
						if (rc < 0) {
							closeConn = true;
							break ;
						}
					}
				}

				if (closeConn) {
					close(pollfds[i].fd);
					pollfds.erase(pollfds.begin() + i);
					i--;
				}
			}
		}
	}

	for (size_t i = 0; i < pollfds.size(); i++)
		close(pollfds[i].fd);

	return 0;
}