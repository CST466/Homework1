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
void Decrypt(char * plain_text, int key);
void Encrypt(char * plain_text, int key);
int main(int argc, char *argv[])
{
	bool haveOption = false;
	bool haveKey = false;
	bool haveFile = false;
	char * string = "abcdefgxyzdragoncannon\0";
	char tmp[300];
	strcpy(tmp,string);
	cout << "Origonal String: " << tmp;
	Encrypt(tmp,1);
	cout << "\nEncrypted String: " <<tmp;
	Decrypt(tmp,1);
	cout << "\nDecrypted String: " << tmp;
	cout << '\n';

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



void Encrypt(char * plain_text, int key)
{
	int length = strlen(plain_text);
	// Normalize key
	key = key % 26;
	for(int i = 0; i < length; ++i)
	{
		plain_text[i] = (plain_text[i] - 'a' + (signed char)key ) % 26 + 'A';
	}
}

void Decrypt(char * encrypted_text, int key)
{
	int length = strlen(encrypted_text);
	key = key % 26;
	for(int i = 0; i < length; ++i)
	{
		encrypted_text[i] = (encrypted_text[i] - 'A' - key) % 26 + 'a';
		encrypted_text[i] = encrypted_text[i] < 'a' ? encrypted_text[i] + 26 : encrypted_text[i];
	}
}