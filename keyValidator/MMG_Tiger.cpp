#include "stdafx.h"
#include "tiger.h"

MMG_CryptoHash MMG_Tiger::GenerateHash(const void *theData, unsigned int theDataLength)
{
	__int64 result[3];
	tiger((word64 *)theData, theDataLength, (word64 *)result);

	return MMG_CryptoHash(result, sizeof(result), HASH_ALGORITHM_TIGER);
}