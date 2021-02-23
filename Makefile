include ../../Makefile.cfg



all:
	
	mkdir -p cd_root
	$(CC) $(CCFLAGS)-O2 -DEXAMPLES_VMODE=VMODE_NTSC main.c pakkun.c ksys573_pad.c -o PSX.elf
	elf2exe PSX.elf cd_root/PSX.exe -mark_jpn
	systemcnf PSX.exe > cd_root/system.cnf
	mkisofs -o PSX.hsf -V GAMEISO -sysid PLAYSTATION cd_root
	mkpsxiso PSX.hsf PSX.bin /share/licenses/infojap.dat
	rm -f PSX.hsf