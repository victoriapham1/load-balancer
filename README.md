# CS412 Load Balancer

This project simulates a load balancer that processes simulated requests with a given number of servers in a given time (clock cycles).

To view documentation, click [here](https://people.tamu.edu/~vtp283/cs412-proj2/).

## 📃 Execute Code

To compile:

```
make
```

or

```
g++ -o test main.cpp request.cpp webserver.cpp loadbalancer.cpp
```

To run:

```
./test
```

## 🖥️ Simulation

There are two options to run the simulation, (d)efault and (c)ustom. 
- Default will run the simulation with 10 servers in 10,000 clock cycles.
- Custom will allow you to input a given number of servers and clock cycles.
