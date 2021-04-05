# Signal Practice (System interrupt)
*The following result is runnung under ubuntu.*
## Run teacher's snippet
![demo1](https://user-images.githubusercontent.com/25290627/113581862-47c13700-965a-11eb-9349-869a7ef059cf.png)
![demo2](https://user-images.githubusercontent.com/25290627/113581865-498afa80-965a-11eb-8a88-4f7438036605.png)

## Without signal handler ?  
1. First snippet will act nornally(default). Which means "`Ctrl+C`" will interrupt the proccess directly.  
2. Second snippet involves division error.  
Any integer devided by zero will lead to "`Floating point exception (core dumped)`" which is *`SIGFPE`*.  
![withoutHandler](https://user-images.githubusercontent.com/25290627/113584224-375e8b80-965d-11eb-94c7-15d508accce2.png)
