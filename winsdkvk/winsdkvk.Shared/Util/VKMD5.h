#pragma once
// ****************************************************************************
// <copyright file="MD5.cs" company="Microsoft Corporation">
// Copyright © Microsoft Corporation
// </copyright>
// ****************************************************************************
// Copyright (c) Microsoft Corporation.  All rights reserved.
// ****************************************************************************

namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{

			//C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
			#pragma warning( disable: 1591 )

				// **************************************************************
				// * Raw implementation of the MD5 hash algorithm
				// * from RFC 1321.
				// *
				// * Written By: Reid Borsuk and Jenny Zheng
				// * Copyright (c) Microsoft Corporation.  All rights reserved.
				// **************************************************************

				// Simple struct for the (a,b,c,d) which is used to compute the mesage digest.    
				private value class ABCDStruct
				{
				public:
					uint32 A = 0;
					uint32 B = 0;
					uint32 C = 0;
					uint32 D = 0;
				};

				public ref class VKMD5 sealed abstract
				{
					//Prevent CSC from adding a default public constructor

				public:
					static Platform::Array<uint8> ^GetHash(Platform::String ^input, Encoding ^encoding);

					static Platform::Array<uint8> ^GetHash(Platform::String ^input);

					static Platform::String ^GetHashString(Platform::Array<uint8> ^input);

					static Platform::String ^GetHashString(Platform::String ^input, Encoding ^encoding);

					static Platform::String ^GetHashString(Platform::String ^input);

					static Platform::Array<uint8> ^GetHash(Platform::Array<uint8> ^input);

				internal:
					static Platform::Array<uint8> ^GetHashFinalBlock(Platform::Array<uint8> ^input, int32 ibStart, int32 cbSize, ABCDStruct ABCD, int64 len);

					// Performs a single block transform of MD5 for a given set of ABCD inputs
					/* If implementing your own hashing framework, be sure to set the initial ABCD correctly according to RFC 1321:
					//    A = 0x67452301;
					//    B = 0xefcdab89;
					//    C = 0x98badcfe;
					//    D = 0x10325476;
					*/
					static void GetHashBlock(Platform::Array<uint8> ^input, ABCDStruct %ABCDValue, int32 ibStart);

					//Manually unrolling these equations nets us a 20% performance improvement
				private:
					static uint32 r1(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t);

					static uint32 r2(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t);

					static uint32 r3(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t);

					static uint32 r4(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t);

					// Implementation of left rotate
					// s is an int instead of a uint becuase the CLR requires the argument passed to >>/<< is of 
					// type int. Doing the demoting inside this function would add overhead.
					static uint32 LSR(uint32 i, int32 s);

					//Convert input array into array of UInts
					static Platform::Array<uint32> ^Converter(Platform::Array<uint8> ^input, int32 ibStart);
				};
			}
		}
	}
}

//C# TO C++ CONVERTER TODO TASK: C++ #pragma warning numbers are different from C# #pragma warning numbers:
#pragma warning( default: 1591 )
