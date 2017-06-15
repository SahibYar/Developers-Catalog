#include <iostream>
#include <string>
using namespace std;

// Getting the 4bytes Block from the given string.
unsigned int get_32bit_Block(string stream, int block_no)
{
	return	 stream[(block_no * 4) + 0] +
			(stream[(block_no * 4) + 1] << 8) +
			(stream[(block_no * 4) + 2] << 16) +
			(stream[(block_no * 4) + 3] << 24);
}

// Finalization mix - force all bits of a hash block to avalanche
unsigned int finalize_hash_value(unsigned int h)
{
	h ^= h >> 16;
	h *= 0x85ebca6b;	// 2,246,822,507
	h ^= h >> 13;
	h *= 0xc2b2ae35;	// 3,266,489,909
	h ^= h >> 16;

	return h;
}


//MurmurHash3_x86_32bit
unsigned int MurmurHash3(string data, unsigned int seed)
{
	unsigned int h1 = seed;

	//for x86 32bit variant of Murmur3 hash function, 2 constants are required.
	const unsigned int c1 = 0xcc9e2d51;		// 3,432,918,353
	const unsigned int c2 = 0x1b873593;		// 461,845,907

	const int r1 = 15;
	const int r2 = 13;

	const int m = 5;
	const int n = 0xe6546b64;	//3,864,292,196

	const int remaining_Bytes = data.length() & 3; // data.length() % 4
	const int total_32bit_blocks = (data.length() - remaining_Bytes) / 4;	//total 32bit blocks

	
	for (int block_no = 0; block_no < total_32bit_blocks; block_no++)
	{
		unsigned int k1 = get_32bit_Block(data, block_no);
		k1 *= c1;
		k1 = _rotl(k1, r1);	//ROTL32
		k1 *= c2;

		h1 ^= k1;
		h1 = _rotl(h1, r2);
		h1 = h1 * m + n;
	}

	unsigned int k1 = 0;

	switch (remaining_Bytes)
	{
	case 3: k1 ^= data[(total_32bit_blocks * 4) + 2] << 16;
	case 2: k1 ^= data[(total_32bit_blocks * 4) + 1] << 8;
	case 1: k1 ^= data[(total_32bit_blocks * 4) + 0];

		k1 *= c1; 
		k1 = _rotl(k1, r1); 
		k1 *= c2;
		h1 ^= k1;
	};

	h1 ^= data.length();
	h1 = finalize_hash_value(h1);

	return h1;
}

int main()
{
	string data = "Sahib Yas";
	unsigned int seed = 123;

	cout << "MurmurHash3(\"Sahib Yar\", 123) = " << MurmurHash3(data, seed) << endl;
	system("pause");
}

/*************************************************

Output:

MurmurHash3("Sahib Yar", 123) = 2957982819
*************************************************/