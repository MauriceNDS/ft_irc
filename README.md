# ft_irc
The ft_irc project is an exercise in creating an Internet Relay Chat (IRC) server in C++. The server should be able to handle multiple clients simultaneously and should not hang. It should be implemented using non-blocking file descriptors and a single poll() (or equivalent) for handling all input/output operations.

## Requirements
To complete the ft_irc project, you must meet the following requirements:

* Implement the IRC server in C++ 98.
* Do not use forking.
* Accept incoming IRC connections on the specified port.
* Require a connection password for clients.
* Implement the following commands: /nick, /join, /part, /users, /names, /msg, /send_file, /accept_file, /quit.
