#include "stdafx.h"

extern int g_keyBits[26];

bool TestKey(const char *Key)
{
	MMG_CdKey::Validator validator;
	validator.SetKey(Key);

	if (validator.myIsChecksumCorrect)
	{
		for (int i = 0; i < ARRAYSIZE(g_keyBits); i++)
			printf("%02d ", g_keyBits[i]);

		printf("\n\n");
		printf("Key \"%s\" valid: %d seq: %X\n\n", Key, validator.myIsChecksumCorrect, validator.GetSequenceNumber());

		return true;
	}

	return false;
}

void BruteforceTest()
{
	char key[26];
	strcpy_s(key, "NUKE-NDIE-MDIE-6DIE-HBAF");

	char oldkey[26];
	memset(oldkey, 0, sizeof(oldkey));

	//for (int i = '0'; i <= 'Z'; i++)
	{
		//key[0] = i;
		for (int j = '0'; j <= 'Z'; j++)
		{
			key[5] = j;
			for (int k = '0'; k <= 'Z'; k++)
			{
				key[10] = k;
				for (int l = '0'; l <= 'Z'; l++)
				{
					key[15] = l;
					for (int m = '0'; m <= 'Z'; m++)
					{
						key[20] = m;

						if (memcmp(oldkey, key, 26) == 0)
							continue;

						if (TestKey(key))
							memcpy(oldkey, key, 26);
					}
				}
			}
		}
	}
}

void RandomTest()
{
	char key[26];
	memset(key, 0, sizeof(key));

	srand(GetTickCount());

	while (true)
	{
		for (int i = 0; i < 20; i++)
		{
			key[i] = rand() % ('Z' - '0') + '0';
		}

		TestKey(key);
	}
}

int main(int argc, char* argv[])
{
	RandomTest();
	//BruteforceTest();

	return 1;

	// These keys should always be valid.
	TestKey("6DIE-UDIE-MDIE-6DIE-BDIE");
	TestKey("6DIE-LDIE-6DIE-6DIE-EDIE");
	TestKey("5DIE-NDIE-JDIE-RDIE-YDIE");
	TestKey("3CKW-3G3F-VP5Y-GYDH-36TM");
	TestKey("BMP6-O7PP-N5RE-CV8S-KXIY");
	TestKey("UA7J-ULHG-Y8ES-F4N2-H6GD");
	TestKey("JBR5-V37L-4YAT-RG40-DMXP");
	TestKey("JS6T-VG6W-2YAT-A7P7-C820");
	TestKey("JB4G-I0WN-BG7F-Y39L-GYWK");

	return 0;
}
