# Network-driver
This is a dummy network driver for understanding 
this creates dummy interface after inserting the module.

1)create "Makefile" and add this to it

obj-m := Net_new0.o

2)Run in command line :
make -C /lib/modules/$(uname -r)/build M=$PWD modules

3)insmod Net_new0.ko


4)ifconfig
![image](https://user-images.githubusercontent.com/31912867/219359222-455b1dd0-d959-4780-bdaa-4ed6fcbcf7ee.png)


5)assign ip address
ifconfig dummy0 192.162.10.0
![image](https://user-images.githubusercontent.com/31912867/219359539-4eea6faa-6b9b-4a08-afe2-953a7e6c0c56.png)

6)ping this ip

7)check logs using dmesg 
