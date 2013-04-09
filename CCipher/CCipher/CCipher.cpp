#include <fstream>
#include <iostream>
using std::cout;
// USAGE:  this program encrypts or decrypts a text file given a key and source file
// CCipher <option> <key> <source.txt>
// option
//	-d decrypt
//	-e encrypt
//	-h help
// Key
//	number to shift
// source.txt
//	file to encrypt/decrypt
int main(int argc, char *argv[])
{
	bool haveOption = false;
	bool haveKey = false;
	bool haveFile = false;

	if(argc != 4 )
		cout << "usage: " << argv[0] << "<option> <key> <source.txt>\n";
	else
	{
		cout << "you entered: ";
		for( int i(0); i<argc; i++)
		{
			cout << argv[i];
		}
		cout << '\n';
	}
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