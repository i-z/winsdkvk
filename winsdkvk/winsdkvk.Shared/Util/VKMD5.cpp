using namespace System;

#include "VKMD5.h"

using namespace Windows::Foundation;
using namespace System::Text;
namespace winsdkvk
{
	namespace WindowsPhone
	{
		namespace SDK
		{
			namespace Util
			{

				Platform::Array<uint8> ^VKMD5::GetHash(Platform::String ^input, Encoding ^encoding)
				{
					if (nullptr == input)
					{
						throw ref new System::ArgumentNullException("input", "Unable to calculate hash over null input data");
					}
					if (nullptr == encoding)
					{
						throw ref new System::ArgumentNullException("encoding", "Unable to calculate hash over a string without a default encoding. Consider using the GetHash(string) overload to use UTF8 Encoding");
					}

					Platform::Array<uint8> ^target = encoding->GetBytes(input);

					return GetHash(target);
				}

				Platform::Array<uint8> ^VKMD5::GetHash(Platform::String ^input)
				{
					return GetHash(input, ref new UTF8Encoding());
				}

				Platform::String ^VKMD5::GetHashString(Platform::Array<uint8> ^input)
				{
					if (nullptr == input)
					{
						throw ref new System::ArgumentNullException("input", "Unable to calculate hash over null input data");
					}

					Platform::String ^retval = BitConverter::ToString(GetHash(input));
					retval = retval->Replace("-", "");

					return retval;
				}

				Platform::String ^VKMD5::GetHashString(Platform::String ^input, Encoding ^encoding)
				{
					if (nullptr == input)
					{
						throw ref new System::ArgumentNullException("input", "Unable to calculate hash over null input data");
					}
					if (nullptr == encoding)
					{
						throw ref new System::ArgumentNullException("encoding", "Unable to calculate hash over a string without a default encoding. Consider using the GetHashString(string) overload to use UTF8 Encoding");
					}

					Platform::Array<uint8> ^target = encoding->GetBytes(input);

					return GetHashString(target);
				}

				Platform::String ^VKMD5::GetHashString(Platform::String ^input)
				{
					return GetHashString(input, ref new UTF8Encoding());
				}

				Platform::Array<uint8> ^VKMD5::GetHash(Platform::Array<uint8> ^input)
				{
					if (nullptr == input)
					{
						throw ref new System::ArgumentNullException("input", "Unable to calculate hash over null input data");
					}

					//Intitial values defined in RFC 1321
					ABCDStruct abcd = ABCDStruct();
					abcd.A = 0x67452301;
					abcd.B = 0xefcdab89;
					abcd.C = 0x98badcfe;
					abcd.D = 0x10325476;

					//We pass in the input array by block, the final block of data must be handled specialy for padding & length embeding
					int32 startIndex = 0;
					while (startIndex <= input->Length - 64)
					{
						VKMD5::GetHashBlock(input, abcd, startIndex);
						startIndex += 64;
					}
					// The final data block. 
					return VKMD5::GetHashFinalBlock(input, startIndex, input->Length - startIndex, abcd, safe_cast<int64>(input->Length) * 8);
				}

				Platform::Array<uint8> ^VKMD5::GetHashFinalBlock(Platform::Array<uint8> ^input, int32 ibStart, int32 cbSize, ABCDStruct ABCD, int64 len)
				{
					Platform::Array<uint8> ^working = ref new Platform::Array<uint8>(64);
					Platform::Array<uint8> ^length = BitConverter::GetBytes(len);

					//Padding is a single bit 1, followed by the number of 0s required to make size congruent to 448 modulo 512. Step 1 of RFC 1321  
					//The CLR ensures that our buffer is 0-assigned, we don't need to explicitly set it. This is why it ends up being quicker to just
					//use a temporary array rather then doing in-place assignment (5% for small inputs)
					Array::Copy(input, ibStart, working, 0, cbSize);
					working[cbSize] = 0x80;

					//We have enough room to store the length in this chunk
					if (cbSize < 56)
					{
						Array::Copy(length, 0, working, 56, 8);
						GetHashBlock(working, ABCD, 0);
					}
					else //We need an aditional chunk to store the length
					{
						GetHashBlock(working, ABCD, 0);
						//Create an entirely new chunk due to the 0-assigned trick mentioned above, to avoid an extra function call clearing the array
						working = ref new Platform::Array<uint8>(64);
						Array::Copy(length, 0, working, 56, 8);
						GetHashBlock(working, ABCD, 0);
					}
					Platform::Array<uint8> ^output = ref new Platform::Array<uint8>(16);
					Array::Copy(BitConverter::GetBytes(ABCD.A), 0, output, 0, 4);
					Array::Copy(BitConverter::GetBytes(ABCD.B), 0, output, 4, 4);
					Array::Copy(BitConverter::GetBytes(ABCD.C), 0, output, 8, 4);
					Array::Copy(BitConverter::GetBytes(ABCD.D), 0, output, 12, 4);
					return output;
				}

				void VKMD5::GetHashBlock(Platform::Array<uint8> ^input, ABCDStruct %ABCDValue, int32 ibStart)
				{
					Platform::Array<uint32> ^temp = Converter(input, ibStart);
					uint32 a = ABCDValue.A;
					uint32 b = ABCDValue.B;
					uint32 c = ABCDValue.C;
					uint32 d = ABCDValue.D;

					a = r1(a, b, c, d, temp[0], 7, 0xd76aa478);
					d = r1(d, a, b, c, temp[1], 12, 0xe8c7b756);
					c = r1(c, d, a, b, temp[2], 17, 0x242070db);
					b = r1(b, c, d, a, temp[3], 22, 0xc1bdceee);
					a = r1(a, b, c, d, temp[4], 7, 0xf57c0faf);
					d = r1(d, a, b, c, temp[5], 12, 0x4787c62a);
					c = r1(c, d, a, b, temp[6], 17, 0xa8304613);
					b = r1(b, c, d, a, temp[7], 22, 0xfd469501);
					a = r1(a, b, c, d, temp[8], 7, 0x698098d8);
					d = r1(d, a, b, c, temp[9], 12, 0x8b44f7af);
					c = r1(c, d, a, b, temp[10], 17, 0xffff5bb1);
					b = r1(b, c, d, a, temp[11], 22, 0x895cd7be);
					a = r1(a, b, c, d, temp[12], 7, 0x6b901122);
					d = r1(d, a, b, c, temp[13], 12, 0xfd987193);
					c = r1(c, d, a, b, temp[14], 17, 0xa679438e);
					b = r1(b, c, d, a, temp[15], 22, 0x49b40821);

					a = r2(a, b, c, d, temp[1], 5, 0xf61e2562);
					d = r2(d, a, b, c, temp[6], 9, 0xc040b340);
					c = r2(c, d, a, b, temp[11], 14, 0x265e5a51);
					b = r2(b, c, d, a, temp[0], 20, 0xe9b6c7aa);
					a = r2(a, b, c, d, temp[5], 5, 0xd62f105d);
					d = r2(d, a, b, c, temp[10], 9, 0x02441453);
					c = r2(c, d, a, b, temp[15], 14, 0xd8a1e681);
					b = r2(b, c, d, a, temp[4], 20, 0xe7d3fbc8);
					a = r2(a, b, c, d, temp[9], 5, 0x21e1cde6);
					d = r2(d, a, b, c, temp[14], 9, 0xc33707d6);
					c = r2(c, d, a, b, temp[3], 14, 0xf4d50d87);
					b = r2(b, c, d, a, temp[8], 20, 0x455a14ed);
					a = r2(a, b, c, d, temp[13], 5, 0xa9e3e905);
					d = r2(d, a, b, c, temp[2], 9, 0xfcefa3f8);
					c = r2(c, d, a, b, temp[7], 14, 0x676f02d9);
					b = r2(b, c, d, a, temp[12], 20, 0x8d2a4c8a);

					a = r3(a, b, c, d, temp[5], 4, 0xfffa3942);
					d = r3(d, a, b, c, temp[8], 11, 0x8771f681);
					c = r3(c, d, a, b, temp[11], 16, 0x6d9d6122);
					b = r3(b, c, d, a, temp[14], 23, 0xfde5380c);
					a = r3(a, b, c, d, temp[1], 4, 0xa4beea44);
					d = r3(d, a, b, c, temp[4], 11, 0x4bdecfa9);
					c = r3(c, d, a, b, temp[7], 16, 0xf6bb4b60);
					b = r3(b, c, d, a, temp[10], 23, 0xbebfbc70);
					a = r3(a, b, c, d, temp[13], 4, 0x289b7ec6);
					d = r3(d, a, b, c, temp[0], 11, 0xeaa127fa);
					c = r3(c, d, a, b, temp[3], 16, 0xd4ef3085);
					b = r3(b, c, d, a, temp[6], 23, 0x04881d05);
					a = r3(a, b, c, d, temp[9], 4, 0xd9d4d039);
					d = r3(d, a, b, c, temp[12], 11, 0xe6db99e5);
					c = r3(c, d, a, b, temp[15], 16, 0x1fa27cf8);
					b = r3(b, c, d, a, temp[2], 23, 0xc4ac5665);

					a = r4(a, b, c, d, temp[0], 6, 0xf4292244);
					d = r4(d, a, b, c, temp[7], 10, 0x432aff97);
					c = r4(c, d, a, b, temp[14], 15, 0xab9423a7);
					b = r4(b, c, d, a, temp[5], 21, 0xfc93a039);
					a = r4(a, b, c, d, temp[12], 6, 0x655b59c3);
					d = r4(d, a, b, c, temp[3], 10, 0x8f0ccc92);
					c = r4(c, d, a, b, temp[10], 15, 0xffeff47d);
					b = r4(b, c, d, a, temp[1], 21, 0x85845dd1);
					a = r4(a, b, c, d, temp[8], 6, 0x6fa87e4f);
					d = r4(d, a, b, c, temp[15], 10, 0xfe2ce6e0);
					c = r4(c, d, a, b, temp[6], 15, 0xa3014314);
					b = r4(b, c, d, a, temp[13], 21, 0x4e0811a1);
					a = r4(a, b, c, d, temp[4], 6, 0xf7537e82);
					d = r4(d, a, b, c, temp[11], 10, 0xbd3af235);
					c = r4(c, d, a, b, temp[2], 15, 0x2ad7d2bb);
					b = r4(b, c, d, a, temp[9], 21, 0xeb86d391);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: ABCDValue.A = unchecked(a + ABCDValue.A);
					ABCDValue.A = a + ABCDValue.A;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: ABCDValue.B = unchecked(b + ABCDValue.B);
					ABCDValue.B = b + ABCDValue.B;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: ABCDValue.C = unchecked(c + ABCDValue.C);
					ABCDValue.C = c + ABCDValue.C;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: ABCDValue.D = unchecked(d + ABCDValue.D);
					ABCDValue.D = d + ABCDValue.D;
					return;
				}

				uint32 VKMD5::r1(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t)
				{
					//                  (b + LSR((a + F(b, c, d) + x + t), s))
					//F(x, y, z)        ((x & y) | ((x ^ 0xFFFFFFFF) & z))
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: return unchecked(b + LSR((a + ((b & c) | ((b^0xFFFFFFFF) & d)) + x + t), s));
					return b + LSR((a + ((b & c) | ((b ^ 0xFFFFFFFF) & d)) + x + t), s);
				}

				uint32 VKMD5::r2(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t)
				{
					//                  (b + LSR((a + G(b, c, d) + x + t), s))
					//G(x, y, z)        ((x & z) | (y & (z ^ 0xFFFFFFFF)))
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: return unchecked(b + LSR((a + ((b & d) | (c & (d^0xFFFFFFFF))) + x + t), s));
					return b + LSR((a + ((b & d) | (c & (d ^ 0xFFFFFFFF))) + x + t), s);
				}

				uint32 VKMD5::r3(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t)
				{
					//                  (b + LSR((a + H(b, c, d) + k + i), s))
					//H(x, y, z)        (x ^ y ^ z)
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: return unchecked(b + LSR((a + (b^c^d) + x + t), s));
					return b + LSR((a + (b ^ c ^ d) + x + t), s);
				}

				uint32 VKMD5::r4(uint32 a, uint32 b, uint32 c, uint32 d, uint32 x, int32 s, uint32 t)
				{
					//                  (b + LSR((a + I(b, c, d) + k + i), s))
					//I(x, y, z)        (y ^ (x | (z ^ 0xFFFFFFFF)))
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'unchecked' in this context:
//ORIGINAL LINE: return unchecked(b + LSR((a + (c^(b | (d^0xFFFFFFFF))) + x + t), s));
					return b + LSR((a + (c ^ (b | (d ^ 0xFFFFFFFF))) + x + t), s);
				}

				uint32 VKMD5::LSR(uint32 i, int32 s)
				{
					return ((i << s) | (i >> (32 - s)));
				}

				Platform::Array<uint32> ^VKMD5::Converter(Platform::Array<uint8> ^input, int32 ibStart)
				{
					if (nullptr == input)
					{
						throw ref new System::ArgumentNullException("input", "Unable convert null array to array of uInts");
					}

					Platform::Array<uint32> ^result = ref new Platform::Array<uint32>(16);

					for (int32 i = 0; i < 16; i++)
					{
						result[i] = safe_cast<uint32>(input[ibStart + i * 4]);
						result[i] += safe_cast<uint32>(input[ibStart + i * 4 + 1]) << 8;
						result[i] += safe_cast<uint32>(input[ibStart + i * 4 + 2]) << 16;
						result[i] += safe_cast<uint32>(input[ibStart + i * 4 + 3]) << 24;
					}

					return result;
				}
			}
		}
	}
}
