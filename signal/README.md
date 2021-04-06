# Signal Practice (System interrupt)
*The following result is runnung under ubuntu.*
## Running teacher's snippet.
![demo1](https://user-images.githubusercontent.com/25290627/113581862-47c13700-965a-11eb-9349-869a7ef059cf.png)
![demo2](https://user-images.githubusercontent.com/25290627/113581865-498afa80-965a-11eb-8a88-4f7438036605.png)

## Without signal handler ?  
1. First snippet will act nornally(default). Which means "`Ctrl+C`" will interrupt the proccess directly.  
2. Second snippet involves division error.  
Any integer devided by zero will lead to "`Floating point exception (core dumped)`" which is *`SIGFPE`*.  
![withoutHandler](https://user-images.githubusercontent.com/25290627/113584224-375e8b80-965d-11eb-94c7-15d508accce2.png)

## Besides SIGINT & SIGFPE, there are various kind of signal handler.
Let's take `SIGPIPE` for example.  
- [sigpipe_socket_Server.c](https://github.com/LaZoark/Operation_System/blob/main/signal/sigpipe_socket_Server.c) is a server that allow client to connect and then terminate.  
- [sigpipe_socket_Client.c](https://github.com/LaZoark/Operation_System/blob/main/signal/sigpipe_socket_Client.c) force a SIGPIPE error by connecting to an echo server and sending data while the server just terminates the connection.  
***Signal occured  
![SIGPIPE_alreadyInUse](https://user-images.githubusercontent.com/25290627/113590628-785a9e00-9665-11eb-9ca3-534b96cf68e8.png)  
***Work properly  
![SIGPIPE_workProperly](https://user-images.githubusercontent.com/25290627/113590635-7a246180-9665-11eb-9921-29843a682a4e.png)  


reference:  
[Demonstration to generate SIGPIPE Error with Socket](http://enggedu.com/demonstration_to_generate_SIGPIPE_error_with_socket/index.php)  
[Using signals and sigpipe](https://stackoverflow.com/questions/7774569/using-signals-and-sigpipe)
