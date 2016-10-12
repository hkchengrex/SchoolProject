CHENG, Ho Kei 12219689 - PA1 Trade

*Brief:*
The server will bind to the 5001 port, so usage of the client will be client_main <hostname> 5001. No extension has been made in this project.

*Client Object:*
Before forking into two processes, the client object will create 2 pipes for Inter-Process-Communication. 

After fork(), one of the processes will run get_price(), which will listen to socket for the updated price.

Another process will run gen_buy_process, which listen to user's input. Upon pressing enter, the gen_buy_request will ask get_price for the most updated price via the two pipes, one for requesting and another for responding. After it gets the price, it will generate a buy request to the server via socket.

*Server Object:*
As no parameter is passed in the constuctor, the server will bind to the hardcoded 5001 port. The server would use a shared memory way to perform inter-process-communication. For each connected cilent, there will be 2 server processes running. 

The process_buy_request process will listen to the client's request, check whether the client's proposed price is the same as the lastest price, and generate the result to the client. 

The gen_price processes will would 1 master - The master is the first created gen_price process. Only the master gen_price can generate new price and print to the console. All gen_price process can send the current price to the client via sockets.

Inside the server, the current price, buy count and the master flag are shared between processes. Two semaphores are implemented to prevent data races.
