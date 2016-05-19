// lab4.cpp: определяет точку входа для консольного приложения.
//
#define MSG_LEN 256

#include "stdafx.h"
#include "lcg.h"
#include "des.h"
#include <time.h>
#include <string>

// IV & Key generation
ulong64 GenerateULONG(Lcg *lcg)
{
	ulong64 result = { lcg->Generate(), lcg->Generate() };
	return result;
}

uchar InvertBit(uchar byte, int pos)
{
	return byte ^ (1 << pos);
}

ulong AppendRandom(Lcg *lcg, uchar *src, ulong len)
{
	size_t endLen = len % 8;

	if (endLen > 0)
	{
		ulong i = len;

		for (; i < (len + (8 - endLen)); i++)
			src[i] = lcg->Generate() % 256;

		return i;
	}
		
	return len;
}

int main()
{
	uchar source[MSG_LEN];								// Source message
	uchar encrypted[MSG_LEN], decrypted[MSG_LEN];		// Buffers
	ulong result;										// How many bytes/bits processed
	
	printf("Enter string:\n");
	scanf("%[^\n]", source);
	
	size_t len = strnlen((const char *)source, MSG_LEN) + 1;			// Length of string + zero-char

	try
	{
		Lcg *lcg = new Lcg(13819061, 4294967295, 3464571621, time(0));	// LCG initialization

		ulong64 key = GenerateULONG(lcg);								// Key generation
		ulong64 iv = GenerateULONG(lcg);								// IV generation

		printf("Source message: \"%s\"\n\n", source);
/*
		// OFB mode
		result = des_encrypt_ofb(source, len, encrypted, key, iv);
		printf_s(" Encrypted OFB: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_ofb(encrypted, result, decrypted, key, iv);
		printf(" Decrypted OFB: \"%s\"\n", decrypted);

		encrypted[0] = InvertBit(encrypted[0], 2);
		printf_s(" Corrupted OFB: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_ofb(encrypted, result, decrypted, key, iv);
		printf(" Decrypted OFB: \"%s\"\n\n", decrypted);
*/
		// CFB mode
		result = des_encrypt_cfb(source, len * 8, encrypted, key, iv, 44);
		printf_s(" Encrypted CFB: \"%.*s\"\n", result / 8, encrypted);

		result = des_decrypt_cfb(encrypted, result, decrypted, key, iv, 44);
		printf(" Decrypted CFB: \"%s\"\n", decrypted);

		encrypted[0] = InvertBit(encrypted[0], 2);
		printf_s(" Corrupted CFB: \"%.*s\"\n", result / 8, encrypted);

		result = des_decrypt_cfb(encrypted, result, decrypted, key, iv, 44);
		printf(" Decrypted CFB: \"%s\"\n\n", decrypted);

		len = AppendRandom(lcg, source, len);
		// CBC mode
		result = des_encrypt_cbc(source, len, encrypted, key, iv);
		printf_s(" Encrypted CBC: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_cbc(encrypted, result, decrypted, key, iv);
		printf(" Decrypted CBC: \"%s\"\n", decrypted);

		encrypted[0] = InvertBit(encrypted[0], 2);
		printf_s(" Corrupted CBC: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_cbc(encrypted, result, decrypted, key, iv);
		printf(" Decrypted CBC: \"%s\"\n\n", decrypted);

		// ECB mode
		result = des_encrypt_ecb(source, len, encrypted, key);
		printf_s(" Encrypted ECB: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_ecb(encrypted, result, decrypted, key);
		printf(" Decrypted ECB: \"%s\"\n", decrypted);

		encrypted[0] = InvertBit(encrypted[0], 2);
		printf_s(" Corrupted ECB: \"%.*s\"\n", result, encrypted);

		result = des_decrypt_ecb(encrypted, result, decrypted, key);
		printf(" Decrypted ECB: \"%s\"\n\n", decrypted);
	}
	catch (char *e)
	{
		printf("Error: %s\n", e);
	}

    return 0;
}

