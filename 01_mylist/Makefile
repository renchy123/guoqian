KERN_DIR = /home/renchy/virtual-os/win7_share_folder/linux-2.6.22.6
#KERN_DIR =/usr/src/linux-headers-5.8.0-43-generic 

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= mylist.o
