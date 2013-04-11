#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


const char * DICTIONARY_FILE_NAME = "dictionary.txt";
const int NUM_OF_KEYS = 26;
using std::string;
using std::cout;
using std::vector;
using std::getline;

// USAGE:  this program breaks a Ceasar Cipher and displays the key used as well 
//			as generates an decrypted output file
// CBreaker <source.txt>
// source.txt
//	file to encrypt/decrypt
void Encrypt(const char * const plain_text, char * cipher_text, int key);
bool LoadFileIntoString( string & str, const string & file_name);
std::ifstream::pos_type filesize(const char* filename);
void Decrypt(const char * const encrypted_text, char * plain_text, int key);
bool LoadDictionary( vector<string> & dictionary);
int main(int argc, char *argv[])
{
	if(argc != 1)
	{
		int correct_key(0);
		string cipher_file_name(argv[1]);
		int cipher_file_size = filesize(cipher_file_name.c_str());
		string cipher_file_text;
		if(LoadFileIntoString(cipher_file_text, cipher_file_name))
		{
			vector<string> dictionary;
			LoadDictionary(dictionary);
			// Create array of 26 wordcounts, one for each key. The key that presents the highest number of word matches is the correct key.
			int word_counts[NUM_OF_KEYS];
			memset(word_counts, 0, sizeof(int) * NUM_OF_KEYS);
			// for each possible key
			for(int key_index = 0; key_index < NUM_OF_KEYS; ++key_index)
			{
				
				char cipher_decrypt[9000];

				Decrypt(cipher_file_text.c_str(), cipher_decrypt, key_index);
				
				string cipher_decrypt_temp(cipher_decrypt);
				for(int word_start = 0; word_start < cipher_file_text.size(); ++word_start)
				{
					for(int word_end = word_start + 3; word_end < cipher_file_text.size() && ((word_end - word_start) < 12); ++word_end)
					{
					
						string possible_word = cipher_decrypt_temp.substr( word_start, word_end - word_start);
						// http://www.cplusplus.com/reference/algorithm/binary_search/
						if (std::binary_search (dictionary.begin(), dictionary.end(), possible_word))
						{
							++word_counts[key_index];
						}
					}
				}
			}
			//find key
			int key(word_counts[0]);
			for(int i(0); i<NUM_OF_KEYS; i++)
			{
				if(word_counts[i] > key)
				{
					key = word_counts[i];
				}
			}
			//display key
			cout << "Key: " << key << "\n";
			//decrypt text
			char * deciphered_text = new char[cipher_file_size];
			Decrypt(cipher_file_text.c_str(), deciphered_text, key);
			//send to output file
			string outputFileName("Decrypted ");
			outputFileName += argv[1];
			std::ofstream Decipherd_file;
			Decipherd_file.open(outputFileName);
			if(Decipherd_file.is_open())
			{
				Decipherd_file.write(deciphered_text,cipher_file_size);
				Decipherd_file.close();
			}
			else
			{
				cout << "File could not be opened!\n";
			}
		}
		else
		{
			cout << argv[1] << " could not be opened!\n";
		}
	}
	else
	{
		cout << "Proper syntax is CBreaker.exe fileToDecrypt.txt\n";
	}
}

void Encrypt(const char * const plain_text, char * cipher_text, int key)
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

void Decrypt(const char * const encrypted_text, char * plain_text, int key)
{
	int length = strlen(encrypted_text);
	key = key % 26;
	for(int i = 0; i < length; ++i)
	{
		plain_text[i] = (toupper(encrypted_text[i]) - 'A' - key) % 26 + 'a';
		plain_text[i] = plain_text[i] < 'a' ? plain_text[i] + 26 : plain_text[i];
	}
	plain_text[length + 1] = '\0';
}


bool LoadDictionary( vector<string> & dictionary)
{
	std::ifstream dictionary_file;
	dictionary_file.open(DICTIONARY_FILE_NAME, std::ios::in);
	string line;
	bool success = false;
	
	if(dictionary_file.is_open())
	{
		success = true;
		while(dictionary_file.good())
		{
			getline(dictionary_file,line);
			// http://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
			//std::transform(line.begin(), line.end(), line.begin(), ::toupper);
			dictionary.push_back(line);
		}
	}
	return success;
}

bool isPlainText(string file_name)
{
	size_t file_size = filesize(file_name.c_str());
	char * file_contents = new char[file_size];
	
	std::ifstream in_file;
	in_file.open( file_name.c_str(), std::ios::binary | std::ios::in);
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
// http://stackoverflow.com/questions/195323/what-is-the-most-elegant-way-to-read-a-text-file-with-c
bool LoadFileIntoString( string & str, const string & file_name)
{
	std::ifstream input_file;
	input_file.open(file_name, std::ios::in);
	bool success = false;
	if(input_file.is_open())
	{
		str = string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
		str.resize(4096);
		input_file.close();
		success = true;
	}
	
		
	return success;
}

