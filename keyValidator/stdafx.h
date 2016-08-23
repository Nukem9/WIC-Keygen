#pragma once

#include <Windows.h>
#include <assert.h>
#include <stdio.h>

typedef unsigned long long int	word64;
typedef unsigned long			word32;
typedef unsigned char			byte;

typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned __int32	uint32;
typedef unsigned __int64	uint64;
typedef unsigned long		ulong;
typedef void				*voidptr_t;

#include "MMG_BitStream.h"
#include "MMG_CryptoHash.h"
#include "MMG_Tiger.h"
#include "MMG_CdKeyValidator.h"