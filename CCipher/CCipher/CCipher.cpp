#include <fstream>
#include <iostream>
// USAGE
// CCipher [[option][key]] {source.txt}
// option
//	-d decrypt
//	-e encrypt
// Key
//	number to shift
// source.txt
//	file to encrypt/decrypt
int main(int argc, char *argv[])
{
	if(argc != 4)
		cout << "usage: " << argv[0] << "
}
