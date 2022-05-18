#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

class Request
{
	public:
		std::vector<std::string>	args;
		std::string					command;
		bool						invalidMessage;

	public:
		Request(): args(), command(), invalidMessage(false) {};
		~Request() {};
		Request( const Request &x ) { *this = x; };
		Request & operator = ( const Request &rhs )
		{
			if (this == &rhs)
				return (*this);
			this->args = rhs.args;
			this->command = rhs.command;
			this->invalidMessage = rhs.invalidMessage;
			return (*this);
		};
};

Request		_splitRequest(std::string req)
{
	Request	request;
	size_t	i = 0;
	size_t	j = 0;

	if (req[i] == ' ' || !req[i]) {
		request.invalidMessage = true;
		return (request);
	}
	j = i;
	while (req[i])
	{
		if (req[i] == ' ')
		{
			if (req[i + 1] == ' ') {
				request.invalidMessage = true;
				return (request);
			}
			request.args.push_back(req.substr(j, i - j)); // 0, 5 - 0, 
			while (req[i] == ' ')
				i++;
			j = i;// 5, 
		}
		if (req[i] == ':')
		{
			if (req[i - 1] != ' ') {
				request.invalidMessage = true;
				return (request);
			}
			request.args.push_back(req.substr(i + 1, req.length() - i));// 6 + 1, 18 - 6
			request.command = request.args[0];
			request.args.erase(request.args.begin());
			return (request);
		}
		i++;
	}

	if (i && req[j])
		request.args.push_back(req.substr(j, i - j));
	request.command = request.args[0];
	request.args.erase(request.args.begin());
	return (request);
};

int main(int ac, char **av)
{
	Request request;
	std::string line;
	while (1)
	{
		getline(std::cin, line);
		request = _splitRequest(line);
		// print args of request
		std::cout << "ARGS:";
		for (size_t i = 0; i < request.args.size(); i++)
			std::cout << "|" << request.args[i] << "|";
		std::cout << std::endl << "command: " << request.command << std::endl << "invalidMessage: " << request.invalidMessage << std::endl << std::endl;
		request.args.clear();
		request.command = "";
		request.invalidMessage = false;
	}
}