all:
	g++ src/save.cpp -o build/save
	g++ src/restore.cpp -o build/restore 

install :
	bash install.sh

uninstall :
	bash uninstall.sh
