#include <memory.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

//==========================================================================
// �������� 64-� ������� �����
typedef struct _ulong64
{
	ulong l;
	ulong h;
} ulong64;

//==========================================================================
// ��������� 32-� ������� ����� �� ������ ���� �� ������� (������ BIG ENDIAN)
// BIG ENDIAN - ������ ���� ������ ����� ������� ������ � �����
// ���������:
//   ulong n  - 32-� ������ �����, � ������� ������������ ������
//   uchar* b - ������� ����� ����
//   ulong i  - �������, � ������� ���������� ������ ������ �� �������� ������
#ifndef GET_ULONG_BE
#define GET_ULONG_BE(n,b,i)                     \
{                                               \
    (n) = ( (ulong) (b)[(i)    ] << 24 )        \
        | ( (ulong) (b)[(i) + 1] << 16 )        \
        | ( (ulong) (b)[(i) + 2] <<  8 )        \
        | ( (ulong) (b)[(i) + 3]       );       \
}
#endif

//==========================================================================
// ������ 32-� ������� ����� � ����� ���� � ������ ������� (������ BIG ENDIAN)
// ���������:
//   ulong n  - 32-� ������ �����, �� ������� �������� ������
//   uchar* b - �������� ����� ����
//   ulong i  - �������, � ������� ���������� ������ ������ � �������� �����
#ifndef PUT_ULONG_BE
#define PUT_ULONG_BE(n,b,i)                     \
{                                               \
    (b)[(i)    ] = (uchar) ( (n) >> 24 );       \
    (b)[(i) + 1] = (uchar) ( (n) >> 16 );       \
    (b)[(i) + 2] = (uchar) ( (n) >>  8 );       \
    (b)[(i) + 3] = (uchar) ( (n)       );       \
}
#endif

//==========================================================================
// ������� ������������ 16-�� ��������� ������ ���������� DES
// ���������:
//   - src - 64-� ������ ���� ��������� DES
//   - keys - �������������� 16 64-� ������ ������ ������ ����������
void des_create_keys(ulong64 src, ulong64 keys[16]);
// ������� ���������� DES ������ 64-� ������� �����
// ���������:
//   - src - 64-� ������ ������� ���� ��������� ����� 
//   - keys - 16 64-� ������ ������ ������ ����������
// ���������:
//   - 64-� ������ ������� ���� ������������
ulong64 des_encrypt_block(ulong64 src, ulong64 keys[16]);
// ������� ������������� DES ������ 64-� ������� �����
// ���������:
//   - src - 64-� ������ ������� ���� ������������
//   - keys - 16 64-� ������ ������ ������ ����������
// ���������:
//   - 64-� ������ ������� ���� ��������� ����� 
ulong64 des_decrypt_block(ulong64 src, ulong64 keys[16]);

//==========================================================================
// ��������!!!!
// ���������� ���������� ������ ECB, CBC, CFB � OFB. ��������� ������� 
// ������� ����. 
// ���������:
//   - SRC - ������� ��������� (������������)
//   - SRCLEN - ������ �������� ��������� (������������)
//   - DST - ������������ (���������)
//   - IV - ����������������� ������ ��� ������� (CBC, CFB, OFB)

// ECB
ulong des_encrypt_ecb(uchar *src, ulong srclen, uchar *dst, ulong64 key);
ulong des_decrypt_ecb(uchar *src, ulong srclen, uchar *dst, ulong64 key);

// CBC
ulong des_encrypt_cbc(uchar *src, ulong srclen, uchar *dst, ulong64 key, ulong64 iv);
ulong des_decrypt_cbc(uchar *src, ulong srclen, uchar *dst, ulong64 key, ulong64 iv);

// CFB
ulong des_encrypt_cfb(uchar *src, ulong srclen, uchar *dst, ulong64 key, ulong64 iv);
ulong des_decrypt_cfb(uchar *src, ulong srclen, uchar *dst, ulong64 key, ulong64 iv);

// OFB
ulong des_encrypt_ofb(uchar *src, ulong srclen, uchar *dst, ulong64 key, ulong64 iv);
ulong des_decrypt_ofb(uchar *src, ulong srclen, uchar *dst, ulong64 key, ulong64 iv);