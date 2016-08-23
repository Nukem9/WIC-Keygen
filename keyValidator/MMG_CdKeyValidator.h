#pragma once

#pragma pack(push, 1)
class MMG_CdKey
{
public:
	class Validator
	{
	public:
		const char *LocCdKeyAlphabet = "ABCDEFGHIJKLMNOPRSTUVWXY23456789";

		union KeyDefinition
		{
			struct
			{
				unsigned char gap0[8];
				__int64 _bf8;
			} section;

			char data[16];
		};

		KeyDefinition myKey;
		bool myIsChecksumCorrect;

		Validator();
		void SetKey(const char *aKey);
		unsigned int GetSequenceNumber();
	};
};
#pragma pack(pop)