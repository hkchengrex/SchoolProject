#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <fcntl.h>
#include "proj1.h"

Server::Server(){
	//Create a piece of private shared memory, with user R/W permission
	int shmid = shmget(IPC_PRIVATE, sizeof(int)*2 + sizeof(bool), IPC_CREAT|0600);
	if (shmid < 0){
		perror("shmget failed.\n");
		exit(EXIT_FAILURE);
	}

	//Let system assign a piece of address for shared memory
	char* shm_pointer = (char *) shmat(shmid, NULL, 0);
	if (shm_pointer == (char *) -1){
		perror("shmat failed.\n");
		exit(EXIT_FAILURE);
	}

	//Break this piece of shared memory into pieces, maintain upon fork()
	buy_count = (int *) shm_pointer;
	curr_price = (int *) (shm_pointer + sizeof(int));
	master_set = (bool *) (shm_pointer + sizeof(int)*2);

	*buy_count = 0;
	*curr_price = 10;
	*master_set = false;
	is_master = false;

	//Establish two semaphores
	sem_key = semget(0, 2, 0600|IPC_PRIVATE|IPC_CREAT);
	if (sem_key == -1){
		perror("semget failed.\n");
		exit(EXIT_FAILURE);
	}
	//Init their values to 1 (usable)
	semctl(sem_key, BUY_COUNT_SEM, SETVAL, 1);
	semctl(sem_key, MASTER_SEM, SETVAL, 1);
}

Server::~Server(){
	//Remove semaphore
	semctl(sem_key, 0, IPC_RMID);
	//Detach shared memory
	shmdt((void *)shm_pointer);
}

int Server::sock(){
	//Open socket
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0){
		perror("Error opening socket.\n");
		exit(EXIT_FAILURE);
	}

	//Bind to the fixed port
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr)); //Init to all zero
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(TCP_PORT_NUMBER); //Convert btye order to network format
	if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("Error binding port.\n");
		exit(EXIT_FAILURE);
	}

	printf("Binding successful.\n");

	return sock_fd;
}

void Server::gen_price(const int sock_fd){
	static time_t last_gen_time = time(NULL);
	static time_t last_send_time = time(NULL);

	time_t curr_time = time(NULL);

	//Semaphore operation to prevent data race on master_set
	struct sembuf my_semop;
	my_semop.sem_num = MASTER_SEM;
	my_semop.sem_op = -1;
	my_semop.sem_flg = SEM_UNDO;

	semop(sem_key, &my_semop, 1); //Allocate resource
	//Only one master is allowed. Master will generate price for all servers.
	if (!(*master_set)){
		*master_set = true;
		is_master = true;
		*curr_price = rand()%100;
	}
	my_semop.sem_op = 1; //Release resource
	semop(sem_key, &my_semop, 1);

	if (difftime(curr_time, last_send_time) >= 1.0){
		last_send_time = curr_time;

		struct msg msg_item;
		msg_item.msg_header = NEW_PRICE_HEAD;
		msg_item.msg_price = *curr_price;
		msg_item.msg_time = curr_time;

		if (is_master){
			//Print to console in server side
			char time_buffer[80];
			struct tm *time_struct;
			time_struct = localtime(&curr_time);
			strftime(time_buffer, 80, "%b %a %d/%m/%Y %H:%M:%S", time_struct);
			printf("Price: $%d  %s\n", *curr_price, time_buffer);
		}

		//Send the current price message packet
		send(sock_fd, reinterpret_cast<const char *>(&msg_item), sizeof(msg), MSG_NOSIGNAL); //Don't die even if client died
	}

	if ((is_master) && (difftime(curr_time, last_gen_time) >= 10.0)){
		last_gen_time = curr_time;
		//Generate new price
		*curr_price = rand()%100;
	}
}

void Server::process_buy_request(const int sock_fd){
	char buffer[sizeof(msg)];
	
	//Make sure the server receive the entire message
	if (recv(sock_fd, buffer, sizeof(msg), MSG_WAITALL) == sizeof(msg)){
		struct msg rece_msg = *((msg*) buffer);
		printf("\nReceived Request to buy at $%d\n", rece_msg.msg_price);

		struct msg msg_item;
		msg_item.msg_price = rece_msg.msg_price;
		msg_item.msg_time = time(NULL);
		msg_item.buy_time = rece_msg.msg_time;

		//Check whether the requested price and the current price are the same
		if (*curr_price == rece_msg.msg_price){
			printf("Buy request accepted.\n");
			msg_item.msg_header = ACCEPT_REQ_HEAD;
		}else{
			printf("Buy request declined.\n");
			msg_item.msg_header = DECLIN_REQ_HEAD;
		}
		//Respond to the request
		write(sock_fd, reinterpret_cast<const char *>(&msg_item), sizeof(msg));
		
		struct sembuf my_semop;
		my_semop.sem_num = BUY_COUNT_SEM;
		my_semop.sem_op = -1;
		my_semop.sem_flg = SEM_UNDO;

		//Use semaphore to prevent data race on buy_count
		semop(sem_key, &my_semop, 1); //Allocate resource
		(*buy_count)++;
		my_semop.sem_op = 1;
		semop(sem_key, &my_semop, 1); //Release resource

		printf("Buy attempts: %d\n", *buy_count);
	}
}
