# CS412 Load Balancer

This project simulates a load balancer that processes simulated requests with a given number of servers in a given time (clock cycles). An optional firewall, or IP range blocker, can be activiated and will provide a simulation of protection against potential DOS attacks.

To view documentation, click [here](https://people.tamu.edu/~vtp283/cs412-proj2/).

## 📃 Execute Code

To compile:

```
make
```

or

```
g++ -o test main.cpp request.cpp webserver.cpp loadbalancer.cpp firewall.cpp
```

To run:

```
./test
```

## 🖥️ Simulation

There are two options to run the simulation, <b>(d)</b>efault and <b>(c)</b>ustom.

-   <b>Default</b> will run the simulation with 10 servers in 10,000 clock cycles.
-   <b>Custom</b> will allow you to input a given number of servers and clock cycles.

## 🛡️ Firewall

To activate the firewall, select <b>(y)</b>es or <b>(n)</b>o.

-   <b>No</b>: This will run the simulation without the firewall activated.
-   <b>Yes</b>: This will activate the firewall. The application will then ask for an input of a valid IP address range.
