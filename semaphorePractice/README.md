# Semaphore Practice
main code here : [semaphoreSimulation.java](https://github.com/LaZoark/Operation_System/blob/main/semaphorePractice/src/semaphoreSimulation.java)  
code in C++ here : [semaphore.cpp](https://github.com/LaZoark/Operation_System/blob/main/semaphorePractice/semaphore.cpp)  
**you might need to add `-pthead` after `g++` command to compile the `.cpp` which included `<thread>`.**  
for instance,  
```
g++ -pthread -out foo.exe foo.cpp
```

號誌又稱為旗號，是一個同步物件，用於保持在0至指定最大值之間的一個計數值。當執行緒完成一次對該semaphore物件的等待時，  
該計數值減一；當執行緒完成一次對semaphore物件的釋放時，計數值加一。當計數值為0，則執行緒等待該semaphore物件不再能成功直至該semaphore物件變成signaled狀態。  
### <hr>
    Semaphore具備兩種操作動作，稱為V（signal()）與P（wait()）（即部分參考書常稱的「PV操作」）。V操作會增加信號標S的數值，P操作會減少它。

### 運作方式：
初始化，給與它一個非負數的整數值。  
執行P（wait()），信號標S的值將被減少。企圖進入臨界區段的行程，需要先執行P（wait()）。當信號標S減為負值時，行程會被擋住，不能繼續；當信號標S不為負值時，行程可以獲准進入臨界區段。  
執行V（signal()），信號標S的值會被增加。結束離開臨界區段的行程，將會執行V（signal()）。當信號標S不為負值時，先前被擋住的其他行程，將可獲准進入**臨界區段**。

[維基百科](https://zh.wikipedia.org/zh-tw/%E4%BF%A1%E5%8F%B7%E9%87%8F)  

![resultExplaination](https://user-images.githubusercontent.com/25290627/114026933-6e28e180-98a9-11eb-8241-f62aa0d5602d.png)
![codeExplaination](https://user-images.githubusercontent.com/25290627/114275028-8dfc0900-9a53-11eb-8786-e2cef7eedf71.png)  
#### in C++
![CPP](https://user-images.githubusercontent.com/25290627/114275032-8f2d3600-9a53-11eb-88e7-60182ed8e2ee.png)  

#### CodeBlocks made me go back to work!  
![goToWorkNow](https://user-images.githubusercontent.com/25290627/114275035-8fc5cc80-9a53-11eb-8dc5-be3ff83c313d.png)

  
**html testing**  
<img src="https://user-images.githubusercontent.com/25290627/114275035-8fc5cc80-9a53-11eb-8dc5-be3ff83c313d.png" data-canonical-src="https://user-images.githubusercontent.com/25290627/114275035-8fc5cc80-9a53-11eb-8dc5-be3ff83c313d.png" width="640" height="400" />
