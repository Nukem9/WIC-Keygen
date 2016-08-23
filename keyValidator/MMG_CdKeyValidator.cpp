#include "stdafx.h"

int g_keyBits[26];

MMG_CdKey::Validator::Validator()
{
	memset(&this->myKey, 0, sizeof(this->myKey));
	this->myIsChecksumCorrect = false;
}

void MMG_CdKey::Validator::SetKey(const char *aKey)
{
	if (!aKey)
		return;

	char key[26];
	int keyIndex = 0;
	int theValue = 0;

	for (int i = 0; i < ARRAYSIZE(key); i++)
	{
		if (aKey[i] == 0)
			break;

		if (aKey[i] != '-')
		{
			key[keyIndex] = aKey[i];

			if (islower(aKey[i]))
				key[keyIndex] -= ' ';

			if (key[keyIndex] == '1')
				key[keyIndex] = 'I';
			else if (key[keyIndex] == '0')
				key[keyIndex] = 'O';

			int v7 = 0;
			while (LocCdKeyAlphabet[v7] != key[keyIndex])
			{
				++v7;

				if (v7 >= 33)
					return;
			}
			++keyIndex;
			theValue = v7;

			assert(keyIndex < ARRAYSIZE(key));
		}
	}

	memset(this->myKey.data, 0, sizeof(this->myKey.data));

	int i = 0;
	key[keyIndex] = 0;

	MMG_BitWriter<unsigned char> v24((unsigned char *)&this->myKey.data, 128);
	
	if (keyIndex)
	{
		do
		{
			assert(key[i] != 0);

			int v10 = 0;
			while (LocCdKeyAlphabet[v10] != key[i])
			{
				++v10;
				if (v10 >= 33)
					goto LABEL_30;
			}
			theValue = v10;
		LABEL_30:
			g_keyBits[i] = theValue;
			v24.WriteBits(theValue, 5);
			++i;
		} while (i < keyIndex);
	}

	*(DWORD *)&key[0] = *(DWORD *)&this->myKey.data[0];
	*(DWORD *)&key[4] = *(DWORD *)&this->myKey.data[4];
	*(DWORD *)&key[8] = *(DWORD *)&this->myKey.data[8];
	*(DWORD *)&key[12] = *(DWORD *)&this->myKey.data[12];

	unsigned char xorValue = ((this->myKey.section._bf8 >> 32) << 4) | ((this->myKey.section._bf8 >> 32) & 0xF);

	for (int xorIndex = 2; xorIndex < 11; xorIndex++)
		key[xorIndex] ^= xorValue;

	*(DWORD *)&this->myKey.data[0] = *(DWORD *)&key[0];
	*(DWORD *)&this->myKey.data[4] = *(DWORD *)&key[4];
	*(DWORD *)&this->myKey.data[8] = *(DWORD *)&key[8];
	*(DWORD *)&this->myKey.data[12] = *(DWORD *)&key[12];

	unsigned int v17 = *(DWORD *)&this->myKey.data[0];
	unsigned int v18 = *(DWORD *)&this->myKey.data[4] >> 3;

	*(DWORD *)&this->myKey.data[4] = *(DWORD *)(&this->myKey.data[4]) & 0xFFFFF227 | 0x1220;
	*(DWORD *)&this->myKey.data[0] = v17;

	int v19 = v18 & 0x3FF;

	MMG_Tiger mmgTiger;
	auto cryptoHash = mmgTiger.GenerateHash(this->myKey.data, sizeof(this->myKey.data));

	unsigned int v21 = *(DWORD *)(&this->myKey.data[4]) & 0xFFFFE007 | 8 * (cryptoHash.Get32BitSubset() & 0x3FF);
	*(DWORD *)&this->myKey.data[0] = *(DWORD *)&this->myKey.data[0];
	*(DWORD *)&this->myKey.data[4] = v21;

	if (((*(unsigned __int64 *)&this->myKey.data[0] >> 35) & 0x3FFi64) == v19)
		this->myIsChecksumCorrect = 1;
}

unsigned int MMG_CdKey::Validator::GetSequenceNumber()
{
	if (this->myIsChecksumCorrect)
		return  (*(unsigned __int64 *)&this->myKey.data[0] >> 10) & 0x1FFFFFF;

	return -1;
}