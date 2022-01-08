// Sender class
class Sender {};

// User class
class User : Sender {};

// Throws an exception if not found
User &parse(const std::string &str) {}

// Create command
commandManager.addCommand(
	CommandTemplate.builder()
		.name("OPER")
		.argument("user", Multiple<User>.class)
		.argument("password", String.class)
		.listener(OperCommand /* ? extends CommandListener */)
		.build()
);

// On message recived
try {
	commandManager.dispatch(str);
} catch(const CommandNotFoundException& e) {
	channel.broadcast(str);
}

// Listener
class OperCommand : public CommandListener {

	Response onCommand(Sender &sender, const Command &cmd) {
		User user = dynamic_cast<User>(cmd.get("user"));
		string password = dynamic_cast<string>(cmd.get("password"));
	}
}
