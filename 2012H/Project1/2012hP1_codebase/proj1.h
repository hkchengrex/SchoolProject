#ifndef PROJ1_H 
#define PROJ1_H

//Bypass directive
#define ABCD

//Communication protocol
enum header{
	NEW_PRICE_HEAD,
	ACCEPT_REQ_HEAD,
	DECLIN_REQ_HEAD,
	BUY_REQ_HEAD,
};

struct msg{
	header msg_header;
	int msg_price;
	time_t msg_time;
	time_t buy_time;
};

//Server class
class Server{
private:
	//A fixed port is used as no port number is provided in constructor
	static const int TCP_PORT_NUMBER = 5001;

	//Pointer to the start of shared memory
	char* shm_pointer;

	//Three pointer pointing to data using shared memory
	int* buy_count;
	int* curr_price;
	bool* master_set;

	bool is_master;

	//Semaphore information
	int sem_key;
	enum sem_id{
		BUY_COUNT_SEM = 0,
		MASTER_SEM = 1,
	};

public:
	Server();
	~Server();
	/** Open socket and bind the @TCP_PORT_NUMBER port
	* @return Socket Identifier
	*/
	int sock();

	/** A function for sending current price to the client and generate new price.
	* @param sock_fd: Socket identifier for the target client.
	*/
	void gen_price(const int sock_fd);

	/** A function for processing buy request from the client.
	* @param sock_fd: Socket identifier for the target client.
	*/
	void process_buy_request(const int sock_fd);
};

//Client class
class Client{
private:
	int sock_fd;

	//Two pipe identifier for IPC
	int request_price_pipe_fd[2];
	int respond_price_pipe_fd[2];

public:
	/** Constructor for the Client class.
	* @param host_name: Name of the hosting server
	* @param port_num: Port number to be connected
	*/
	Client(const char* host_name, const int port_num = 5001);

	//Receive price from the server
	void get_price();

	//Detect user input and generate buy request
	void gen_buy_request();
};

#endif
