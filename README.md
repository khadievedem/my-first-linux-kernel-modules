# Simple linux kernel modules
## MODULES LIST
1. simple-module
2. hello_world
3. initdata_test
4.

## Set up before building
Most linux distros distribute linux kernel with their own patches. You'll also need linux-headers, which many distros don't have by default. This may be a barrier to compiling modules from my repo. 
So use kernel from [torvalds/linux](https://github.com/torvalds/linux) :)
### Install linux headers and kernel development pack
#### Archlinux
```
sudo pacman -S linux-headers base-devel
```
#### Ubuntu
```
sudo apt install linux-headers-$(uname -r)
sudo apt install build-essential
```
#### Fedora
```
sudo yum groupinstall "Development Tools"
sudo yum -y install kernel-devel kernel-headers
```
## Build module
###### Build a default module (simple-module)
```sh
make
```
###### Build a "module_name" module
```sh
make MODULE=module_name
```

## Install module
```sh
make MODULE=module_name load
```
or
```sh
cd src
insmod module_name
```

##### Read messages from module
```
dmesg
```

## Remove module
```sh
make MODULE=module_name unload
```
or
```sh
cd src
rmmod module_name
```

## Troubleshooting
```
make[1]: *** /lib/modules/$(uname -r)/build: No such file or directory. Stop.
```
Use [torvalds/linux](https://github.com/torvalds/linux).