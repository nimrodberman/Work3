

#include <stdlib.h>
#include <iostream>
#include <thread>
#include "../include/connectionHandler.h"
#include "../include/UserData.h"
#include "../include/ReadFromKeyboard.h"
#include "../include/ReadFromServer.h"


/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
//help function
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int main () {


    std::string command;
    std::string client_first_input;
    std::mutex mutex;
    std::mutex mutex1;
    std::mutex mutex2;



    do {
        getline(std::cin,client_first_input);
        int spaceApp = client_first_input.find_first_of(' ', 0);
        command = client_first_input.substr(0,spaceApp);
        if (command == "login"){
            UserData* data = new UserData(mutex1);
            std::vector<std::string> line = split(client_first_input, " ");
            std::vector<std::string> HP = split(line[1], ":");
            int port = stoi(HP[1]);
            ConnectionHandler connectionHandler(HP[0], port, mutex);
            ReadFromKeyboard readFromKeyboard= ReadFromKeyboard(data , connectionHandler , client_first_input,mutex2);
            ReadFromServer readFromServer = ReadFromServer (data , connectionHandler,mutex2);

            std::thread th1(&ReadFromKeyboard::run, &readFromKeyboard);
            std::thread th2(&ReadFromServer::run, &readFromServer);
            th2.join();
            th1.join();

            delete(data);
        }
    }
    while( command != "exit" );













    /*



    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

	//From here we will see the rest of the ehco client implementation:
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
		std::string line(buf);
		int len=line.length();
        if (!connectionHandler.sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
		// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

		len=answer.length();
		// A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
		// we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len-1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
    return 0;
     */
}


