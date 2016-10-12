#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>
#include <fcntl.h>
#include "proj1.h"


Client::Client(const char* host_name, const int port_num){
	//Open pipe for Inter-process-communication
	if (pipe(request_price_pipe_fd) < 0){
		perror("Open pipe error\n");
		exit(EXIT_FAILURE);
	}

	if (pipe(respond_price_pipe_fd) < 0){
		perror("Open pipe error\n");
		exit(EXIT_FAILURE);
	}

	//Init socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0){
		perror("Error opening socket.\n");
		exit(EXIT_FAILURE);
	}

	struct hostent *server = gethostbyname(host_name);
	if (server == NULL){
		perror("Host not found.\n");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_num);
	memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

	//Connect to target server with specified port and check for error
	if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
		perror("Error connecting to server.\n");
		exit(EXIT_FAILURE);
	}

	printf("Connection successful.\n");
}

void Client::get_price(){
	static int curr_price = 10;

	//Pipe for IPC, one pipe for receiving request from buy_request
	//another pipe for sending the current price to buy_request
	static bool pipe_closed = false;
	if (!pipe_closed){
		pipe_closed = true;
		close(request_price_pipe_fd[1]); //Input side
		close(respond_price_pipe_fd[0]); //Output side

		//Non-blocking IO on pipe so that the process wouldn't stuck
		fcntl(request_price_pipe_fd[0], F_SETFL, O_NONBLOCK);
	}

	char buffer[sizeof(msg)];
	//Make sure the client receive a complete message by peeking at the buffer
	if (recv(sock_fd, buffer, sizeof(msg), MSG_PEEK|MSG_DONTWAIT) == sizeof(msg)){
		//Actually reading and removing data from the buffer
		read(sock_fd, buffer, sizeof(msg));

		struct msg recv_msg = *((msg*) buffer);
		struct tm *msg_tm;
		char msg_tm_buf[80];
		msg_tm = localtime(&recv_msg.msg_time);

		//Determine the type of message received using the message's header
		switch(recv_msg.msg_header){
			case NEW_PRICE_HEAD:
				strftime(msg_tm_buf, 80, "%b %a %d/%m/%Y %H:%M:%S", msg_tm);
				curr_price = recv_msg.msg_price;
				printf("Price: $%d  %s\n", curr_price, msg_tm_buf);
				break;

			case ACCEPT_REQ_HEAD: case DECLIN_REQ_HEAD:
				//Common actions for both accept and decline
				struct tm *buy_tm;
				char buy_tm_buf[80];
				buy_tm = localtime(&recv_msg.buy_time);
				strftime(buy_tm_buf, 80, "%H:%M:%S", buy_tm);
				strftime(msg_tm_buf, 80, "%H:%M:%S", msg_tm);
				printf("The request to buy at $%d issued was ", recv_msg.msg_price);

				if (recv_msg.msg_header == ACCEPT_REQ_HEAD){
					printf("ACCEPTED.\n");
				}else{
					printf("REJECTED.\n");
				}

				printf("Buy Time: %s\nSell Time: %s\n\n", buy_tm_buf, msg_tm_buf);
				break;
		}
	}

	//If another process requested price, send the price
	if (read(request_price_pipe_fd[0], buffer, sizeof(char)+1) > 0){
		write(respond_price_pipe_fd[1], reinterpret_cast<const char *>(&curr_price), sizeof(int));
	}
}

void Client::gen_buy_request(){
	//Pipe for IPC, one pipe for generating request to get_price
	//another pipe for receiving current price from get_price
	static bool pipe_closed = false;
	static int count = 0;
	if (!pipe_closed){
		pipe_closed = true;
		close(request_price_pipe_fd[0]); //Output side
		close(respond_price_pipe_fd[1]); //Input side
	}

	//Wait for user press enter
	while(getchar() != '\n');
	char sock_buffer[sizeof(msg)];
	char pipe_buffer[sizeof(int)];

	//Send a meaningless packet to get_price
	write(request_price_pipe_fd[1], "0", sizeof(char)+1);
	read(respond_price_pipe_fd[0], pipe_buffer, sizeof(int));
	int curr_price = *((int*) pipe_buffer);

	struct msg msg_item = *((msg*) sock_buffer);
	msg_item.msg_header = BUY_REQ_HEAD;
	msg_item.msg_price = curr_price;
	msg_item.msg_time = time(NULL);

	//Convert time to string
	struct tm *time_struct;
	char time_buffer[80];
	time_struct = localtime(&msg_item.msg_time);
	strftime(time_buffer, 80, "%H:%M:%S", time_struct);

	//Issue a buy request to the server
	printf("\nRequest issued: $%d Time: %s\n", curr_price, time_buffer);
	write(sock_fd, reinterpret_cast<const char *>(&msg_item), sizeof(msg));
}

