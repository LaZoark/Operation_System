# Semaphore Practice
main code here : [semaphoreSimulation.java](https://github.com/LaZoark/Operation_System/blob/main/semaphorePractice/src/semaphoreSimulation.java)  

號誌又稱為旗號，是一個同步物件，用於保持在0至指定最大值之間的一個計數值。當執行緒完成一次對該semaphore物件的等待時，  
該計數值減一；當執行緒完成一次對semaphore物件的釋放時，計數值加一。當計數值為0，則執行緒等待該semaphore物件不再能成功直至該semaphore物件變成signaled狀態。
[維基百科](https://zh.wikipedia.org/zh-tw/%E4%BF%A1%E5%8F%B7%E9%87%8F)  

![resultExplaination](https://user-images.githubusercontent.com/25290627/114026933-6e28e180-98a9-11eb-8241-f62aa0d5602d.png)
