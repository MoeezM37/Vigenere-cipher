// Project (Vigenere Cipher) by Moeez Muhammad

/*

Program to encrypt or decrypt text using user-inputted key

Steps to run program:

	1. User enters whether to encrypt or decrypt text using E/e for encryption or D/d for decryption
	2. User enters text to encrypt or decrypt (only English alphabet letters will be encrypted/decrypted)
	3. User enters key used to encrypt or decrypt with (user entry is repeated until key consists only of English alphabet letters)
	4. Encrypted/Decrypted text is outputted to console

*/

/*

Values to test for:

	For text:
		1. Only English alphabet letters and whitespace (e.g. blank spaces between words)
		2. Letters, numbers and whitespace
		3. Letters, numbers, whitespace and symbols (e.g. !,@,#,etc)

	For key:
		1. Only letters and whitespace
		2. Letters, whitespace and numbers
		3. Letters, whitespace, numbers and symbols

	For mode:
		1. E/e for encryption
		2. D/d for decryption
		3. Other letters, numbers, whitespace and symbols

*/

#include <iostream>
#include <string>
using namespace std;

// Function that applies encryption algorithm

string encrypt(string in, string repeatedKey)
{
	string out = "";

	for (int ii = 0; ii < in.length(); ii++)
	{
		out += char((((int(in[ii]) - 65) + (int(repeatedKey[ii]) - 65)) % 26) + 65);
	}

	return out;
}

// Function that applies decryption algorithm
// If index of letter outside of range (1 - 26) then if statement ensures letter from alphabet is selected

string decrypt(string in, string repeatedKey)
{
	string out = "";
	int outChar;

	for (int ii = 0; ii < in.length(); ii++)
	{
		outChar = int(in[ii] - 65) - int(repeatedKey[ii] - 65);
		if (outChar < 0)
		{
			out += char(((outChar + 26) % 26) + 65);
		}
		else
		{
			out += char((outChar % 26) + 65);
		}
	}

	return out;
}

int main()
{
	// Declaring all necessary variables

	string mode, textIn, key, textPlain = "", keyLetters = "", keyRep = "", textCipher = "", textOut = "";
	bool keyNotAllChars = false, modeE;
	int textInLen, keyLen, textPlainLen, keyRepLen, keyLettersLen, textCipherLen;

	// Ask user whether to encrypt or decrypt
	// Loop repeats until valid mode selected

	while (true)
	{
		cout << "Enter E to encrypt or D to decrypt: ";
		cin >> mode;
		if (mode == "E" || mode == "e")
		{
			cout << endl << "Encryption mode selected" << endl;
			modeE = true;
			break;
		}
		else if (mode == "D" || mode == "d")
		{
			cout << endl << "Decryption mode selected" << endl;
			modeE = false;
			break;
		}
		else
		{
			cout << endl << "Invalid entry. Please try again." << endl;
		}
	}

	// If encrypt mode selected

	if (modeE)
	{

		// Ask user for text to encrypt

		cout << endl << "Enter text to encrypt (press Enter to finish) (Warning: only letters from the English alphabet will be encrypted!) : ";
		getline(cin >> ws, textIn);
		textInLen = textIn.length();

		// Ask user for keyword to encrypt with
		// Loop repeats until key has only English alphabet letters and/or whitespace

		do
		{
			cout << endl << "Enter key to encrypt with (press Enter to finish): ";
			getline(cin >> ws, key);
			keyLen = key.length();
			for (int ii = 0; ii < keyLen; ii++)
			{
				keyNotAllChars = false;
				if (isblank(key[ii]))
				{
					continue;
				}
				else if (isalpha(key[ii]) == false)
				{
					keyNotAllChars = true;
					cout << endl << "Your key should only contain letters from the English alphabet. Please try again." << endl;
					break;
				}
			}
		} while (keyNotAllChars);
		
		// Extracting only English alphabet letters from key and converting to uppercase

		for (int ii = 0; ii < keyLen; ii++)
		{
			if (isalpha(key[ii]))
			{
				keyLetters += toupper(key[ii]);
			}
		}
		keyLettersLen = keyLetters.length();

		// Extracting only English alphabet letters from text and converting to uppercase

		for (int ii = 0; ii < textInLen; ii++)
		{
			if (isalpha(textIn[ii]))
			{
				textPlain += toupper(textIn[ii]);
			}
		}
		textPlainLen = textPlain.length();

		// Repeating key until it matches text length

		for (int ii = 0; ii < textPlainLen; ii++)
		{
			keyRepLen = keyRep.length();
			if (keyRepLen == textPlainLen)
			{
				break;
			}
			else
			{
				keyRep += keyLetters[ii % keyLettersLen];
			}
		}

		// Applying encryption algorithm function

		textCipher = encrypt(textPlain, keyRep);

		textCipherLen = textCipher.length();

		// Splitting encrypted text into 5 letter blocks

		for (int ii = 0; ii < textCipherLen; ii += 5)
		{
			textOut += textCipher.substr(ii, 5) + " ";
		}

		// Outputting encrypted text to console

		cout << endl << "The encrypted ciphertext is: " << textOut << endl;
	}
	
	// If decrypt mode selected

	else
	{
		
		// Ask user for text to decrypt
		
		cout << endl << "Enter text to decrypt (press Enter to finish) (Warning: Only letters from the English alphabet will be decrypted!) : ";
		getline(cin >> ws, textIn);
		textInLen = textIn.length();

		// Ask user for keyword to decrypt with
		// Loop repeats until key has only English alphabet letters and/or whitespace

		do
		{
			cout << endl << "Enter keyword to decrypt with (press Enter to finish): ";
			getline(cin >> ws, key);
			keyLen = key.length();
			for (int ii = 0; ii < keyLen; ii++)
			{
				keyNotAllChars = false;
				if (isblank(key[ii]))
				{
					continue;
				}
				else if (isalpha(key[ii]) == false)
				{
					keyNotAllChars = true;
					cout << endl << "Your keyword should only contain letters. Please try again." << endl;
					break;
				}
			}
		} while (keyNotAllChars);

		// Extracting only English alphabet letters from key and converting to uppercase

		for (int ii = 0; ii < keyLen; ii++)
		{
			if (isalpha(key[ii]))
			{
				keyLetters += toupper(key[ii]);
			}
		}
		keyLettersLen = keyLetters.length();

		// Extracting only English alphabet letters from encrypted text and converting to uppercase

		for (int ii = 0; ii < textInLen; ii++)
		{
			if (isalpha(textIn[ii]))
			{
				textCipher += toupper(textIn[ii]);
			}
		}
		textCipherLen = textCipher.length();

		// Repeating key until it matches text length

		for (int ii = 0; ii < textCipherLen; ii++)
		{
			keyRepLen = keyRep.length();
			if (keyRepLen == textCipherLen)
			{
				break;
			}
			else
			{
				keyRep += keyLetters[ii % keyLettersLen];
			}
		}

		// Applying decryption algorithm

		textPlain = decrypt(textCipher, keyRep);

		// Outputting decrypted text to console

		cout << endl << "The encrypted ciphertext is: " << textPlain << endl;
	}
}