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
	char * string = "abcdefgxyzdragoncannon\0";
	char tmp[300];
	strcpy(tmp,string);
	cout << "Origonal String: " << tmp;
	Encrypt(tmp,1);
	cout << "\nEncrypted String: " <<tmp;
	Decrypt(tmp,1);
	cout << "\nDecrypted String: " << tmp;
	cout << '\n';

	bool haveOption = false;
	bool haveKey = false;
	bool haveFile = false;
	bool encrypt = false;
	int key(0);
	if(argc != 4)
	{
		cout << "usage: " << argv[0] << "<option> <key> <source.txt>\n";
		if(toupper(argv[1][1]) == 'H')
		{
			cout << 
				"CCipher.exe\n" <<
				"This program encrypts/decripts text given a text file containing pure text\n" <<
				"Text must be lowercase with no spaces to encrypt and all uppercase with no spaces to decrypt\n" <<
				"A new text file is generated for each encrypt/decrypt/n" <<
				"It's essentally usless...\n"
				"Options: \n" <<
				"-d decrypt\n" <<
				"-e encrypt\n\n" <<
				"Key: number used to encrypt/decrypt\n\n" <<
				"Source: Text file to be decrypted/encrypted\n";
		}
	}
	else if (argc = 4)
	{
		// check options
		if(toupper(argv[1][1]) == 'D')
		{
			haveOption = true;
			encrypt = false;
		}
		else if(toupper(argv[1][1]) == 'E')
		{
			haveOption = true;
			encrypt = true;
		}
		else 
		{
			cout << "Invalid option!\nOptions are -d(decrypt), -e(encrypt), and -h(help)\n";
		}
		// get key and make sure it is not shifted zero times
		key = atoi(argv[2]);
		while(key % 26 == 0)
		{
			cout << "!WARNING! Key is Zero! Enter new key: ";
			std::cin >> key;
		}
		// check source

		// if decrypt
			// convert key to number and store
			// open text file
			// store in temp string
			// decrypt
			// write to a file
		//else if encrypt
			// convert key to a number and store
			// open text file
			// store in temp string
			// write out to file
		//else you are wrong
		cout << "you entered: ";
		for( int i(0); i<argc; i++)
		{
			cout << argv[i];
		}
		cout << '\n';
	}
	else
	{
		cout << "usage: " << argv[0] << "<option> <key> <source.txt>\n";
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