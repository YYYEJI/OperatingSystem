/* 
100

- 병렬화 가능: 80% -> 1-s 
- 벙렬화 불가능: 20% -> s


4 core 컴퓨터에서의 실행 시간은?
    core 수: n

time: 80/4 + 20
소요시간: (1-s)/n + s
속도: 1/((1-s)/n+s)



---------professor---------
single core에서 100시간 소요되는 작업
- 병렬화 가능: 80% -> 1-s
- 병렬화 불가능: 20% -> s

4 core 컴퓨터에서의 실행 시간은?
   core 수: n

80 / 4 + 20


소요시간: (1-s) / n + s
속도: 1 / ((1-s) / n + s)



*/