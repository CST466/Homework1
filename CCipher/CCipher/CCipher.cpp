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



void Encrypt(unsigned char * plain_text, int key)
{
	int length = strlen(plain_text);
	const unsigned char ASCII_END = 0x7A;
	// Normalize key
	key = key % 26;
	for(int i = 0; i < length; ++i)
	{
		plain_text[i] = (plain_text[i] + (unsigned char)key ) % ASCII_END;
	}
}

void Decrypt(unsigned char * plain_text, int key)
{
	int length = strlen(plain_text);
	const unsigned char ASCII_END = 0x7A;
	key = key % 26;
	
	for(int i = 0; i < length; ++i)
	{
		plain_text[i] = (plain_text[i] + -key) % ASCII_END;
	}
}