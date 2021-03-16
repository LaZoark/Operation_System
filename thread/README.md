# Thread

**在終端機底下用```gcc <檔名.c> -lpthread``` 來編譯一個可執行的檔案(會自動生成a.out)**  
**接著用```./a.out <參數>``` 來執行這個程式**  
*註:請先指定好檔案路徑(e.g. ```cd Documents/OS_study/thread```)

### hw1 
[teacher's code(lab3.c)](https://github.com/LaZoark/Operation_System/blob/main/thread/lab3.c)  
### hw2
[thread.c](https://github.com/LaZoark/Operation_System/blob/main/thread/thread.c) 


### Bonus [Shared Memory V.S. Threading]
- ↓Shared memory : It spends only `0.023` second(s).  
![sharedMemory_timespan](https://user-images.githubusercontent.com/25290627/111311611-622a7500-8699-11eb-8ab5-ba1598b02afd.png)  
- ↓Threading     : It spends about `0.070` second(s).  
![thread_timespan](https://user-images.githubusercontent.com/25290627/111311615-63f43880-8699-11eb-8fcc-31641c32263f.png)  
*In this case, apparently, threading is definitely not a good choice.*
