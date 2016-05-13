// lab4.cpp: определяет точку входа для консольного приложения.
//
#define MSG_LEN 24

#include "stdafx.h"
#include "lcg.h"
#include "des.h"
#include <time.h>

// IV & Key generation
ulong64 GenerateULONG(Lcg *lcg)
{
	ulong64 result = { lcg->Generate(), lcg->Generate() };
	return result;
}

int main()
{
	uchar source[MSG_LEN] = "Hello, world of crypto!";	// Source message
	uchar encrypted[MSG_LEN], decrypted[MSG_LEN];		// Buffers
	ulong result;										// How many bytes processed

	try
	{
		Lcg *lcg = new Lcg(13819061, 4294967295, 3464571621, time(0));	// LCG initialization

		ulong64 key = GenerateULONG(lcg);								// Key generation
		ulong64 iv = GenerateULONG(lcg);								// IV generation

		printf("Source message: \"%s\"\n\n", source);

		// OFB mode
		result = des_encrypt_ofb(source, MSG_LEN, encrypted, key, iv);
		printf_s(" Encrypted OFB: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_ofb(encrypted, MSG_LEN, decrypted, key, iv);
		printf(" Decrypted OFB: \"%s\"\n\n", decrypted);

		// CFB mode
		result = des_encrypt_cfb(source, MSG_LEN, encrypted, key, iv);
		printf_s(" Encrypted CFB: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_cfb(encrypted, MSG_LEN, decrypted, key, iv);
		printf(" Decrypted CFB: \"%s\"\n\n", decrypted);

		// CBC mode
		result = des_encrypt_cbc(source, MSG_LEN, encrypted, key, iv);
		printf_s(" Encrypted CBC: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_cbc(encrypted, MSG_LEN, decrypted, key, iv);
		printf(" Decrypted CBC: \"%s\"\n\n", decrypted);

		// ECB mode
		result = des_encrypt_ecb(source, MSG_LEN, encrypted, key);
		printf_s(" Encrypted ECB: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_ecb(encrypted, MSG_LEN, decrypted, key);
		printf(" Decrypted ECB: \"%s\"\n\n", decrypted);
	}
	catch (char *e)
	{
		printf("Error: %s\n", e);
	}

    return 0;
}

