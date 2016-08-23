#pragma once

class MMG_Tiger
{
public:
	unsigned __int64 myState[3];
	char myDataLeftovers[64];
	unsigned int myDataLeftoversLength;
	unsigned __int64 myTotalDataLength;

	MMG_CryptoHash GenerateHash(const void *theData, unsigned int theDataLength);
};