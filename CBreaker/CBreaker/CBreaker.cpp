#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>


const char * DICTIONARY_FILE_NAME = "dictionary.txt";

using std::string;
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
	char tmpStr[3000];
	bool haveOption = false;
	bool haveKey = false;
	bool haveFile = false;
	bool encrypt = false;
	int key(0);
	if(argc != 4)
	{
		if(toupper(argv[1][1]) == 'H')
		{
			cout << 
				"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<CCipher.exe>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" <<
				"This program encrypts/decripts text given a text file containing pure text\n" <<
				"Text must be lowercase with no spaces to encrypt\n" <<
				"and all uppercase with no spaces to decrypt\n" <<
				"A new text file is generated for each encrypt/decrypt\n\n" <<
				"It's essentally usless...\n" <<
				"Unless you are trying to hide something from your Mom\n\n" <<
				"Options: \n" <<
				"-d decrypt\n" <<
				"-e encrypt\n\n" <<
				"Key: number used to encrypt/decrypt\n\n" <<
				"Source: Text file to be decrypted/encrypted\n";
		}
		cout << "usage: " << argv[0] << "<option> <key> <source.txt>\n";
	}
	else if (argc = 3)
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
		haveKey = true;
		while(key % 26 == 0)
		{
			cout << "!WARNING! Key is Zero! Enter new key: ";
			std::cin >> key;
			haveKey = true;
		}
		// check source
		std::ifstream TextFile(argv[3]);
		if(TextFile.is_open())
		{
			TextFile >> tmpStr;
			haveFile = true;
		}
		else
		{
			cout << "\"" << argv[3] << "\" cannot be opened!\n";
		}
		if(haveFile && haveKey && haveOption)
		{
			std::string outFileName;
			// if decrypt
			if(!encrypt)
			{
				// write to a file
				Decrypt(tmpStr,key);// decrypt
				outFileName += "Decrypted ";
				outFileName += argv[3];
				std::ofstream decryptedFile(outFileName.c_str());
				if(decryptedFile.is_open())
				{
					decryptedFile << tmpStr;
					decryptedFile.close();
				}
				else
				{
					cout << "Output file cannot be opened!\n";
				}

			}
			//else if encrypt
			else
			{
				Encrypt(tmpStr,key);
				outFileName += "Encrypted ";
				outFileName += argv[3];
				std::ofstream encryptedFile(outFileName.c_str());
				if(encryptedFile.is_open())
				{
					encryptedFile << tmpStr;
					encryptedFile.close();
				}
				else
				{
					cout << "Output file cannot be opened!/n";
				}
				// write out to file
			}
		}
	}
	else
	{
		cout << "usage: " << argv[0] << "<option> <key> <source.txt>\n";
	}
}



void Encrypt(const char const * plain_text, char * cipher_text, int key)
{
	int length = strlen(plain_text);
	// Normalize key
	key = key % 26;
	for(int i = 0; i < length; ++i)
	{
		cipher_text[i] = (plain_text[i] - 'a' + (signed char)key ) % 26 + 'A';
	}
	
	cipher_text[length + 1] = '\0';
}

void Decrypt(const char const * encrypted_text, char * plain_text, int key)
{
	int length = strlen(encrypted_text);
	key = key % 26;
	for(int i = 0; i < length; ++i)
	{
		plain_text[i] = (encrypted_text[i] - 'A' - key) % 26 + 'a';
		plain_text[i] = plain_text[i] < 'a' ? plain_text[i] + 26 : plain_text[i];
	}
	plain_text[length + 1] = '\0';
}


bool LoadDictionary( vector<string> & dictionary)
{
	std::ifstream dictionary_file;
	dictionary_file.open(DICTIONARY_FILE_NAME, ios::in);
	string line;
	bool success = false;
	
	if(dictionary_file.isopen())
	{
		success = truel
		while(dictionary_file.good())
		{
			getline (myfile,line);
			dictionary.push_back(line);
		}
	}
	return success;
}

bool isPlainText(string file_name)
{
	size_t file_size = filesize(file_name.cstr());
	char * file_contents = new char[file_size];
	
	ifstream in_file;
	in_file.open( file_name.cstr(), ios::binary | ios::in);
	in_file.read(file_contents, file_size);
	in_file.close();
	
	bool is_plain_text = true;
	
	for(int i = 0; i < file_size && is_plain_text; ++i)
	{
		// Conditions for file data not being ascii text
		// from http://stackoverflow.com/questions/277521/how-to-identify-the-file-content-as-ascii-or-binary
		if( (file_contents[i] < 9) || (file_contents[i] > 13 && file_contents[i] < 32) || (file_contents[i] > 126))
		{
			is_plain_text = false;	
		}
	}
	
	return is_plain_text;
}

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    return in.tellg(); 
}

