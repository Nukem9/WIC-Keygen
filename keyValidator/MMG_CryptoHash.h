#pragma once

enum HashAlgorithmIdentifier : uchar
{
	HASH_ALGORITHM_UNKNOWN,
	HASH_ALGORITHM_TIGER,
	NUM_HASH_ALGORITHM,
};

class MMG_CryptoHash
{
public:
	ulong					m_Hash[16];
	ulong					m_HashLength;
	HashAlgorithmIdentifier	m_GeneratedFromHashAlgorithm;

private:

public:
	MMG_CryptoHash();
	MMG_CryptoHash(voidptr_t theHash, uint theByteLength, HashAlgorithmIdentifier theSourceAlgorithm);

	void SetHash(voidptr_t theHash, uint theByteLength, HashAlgorithmIdentifier theSourceAlgorithm);
	unsigned int Get32BitSubset();
};