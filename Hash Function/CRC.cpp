#include<iostream>
#include <bitset>         // std::bitset
#include<string>
using namespace std;

const int N = 4;			// size of CRC Generator
const int L = 16;			// size of input stream
const string CRCG = "1011";	// CRC Generator

/// number of bits after leading 1
///	Like for 001101, bits after leading 1 are 3 which are 101
int bitAfterLeading_1(bitset<L + (N - 1)> in)
{
	for (size_t i = in.size() - 1; i > 0; --i)
		if (in.test(i)) return i;
	return 0;
}

bitset<N - 1> CRC(bitset<L + (N - 1)> input, bitset<N> crc)
{
	int i = bitAfterLeading_1(input);
	while (i >= N - 1)
	{
		bitset<L + (N - 1)> xor_temp;
		xor_temp |= bitset<xor_temp.size()>(crc.to_string());
		xor_temp <<= (i - crc.size()) + 1;
		input ^= xor_temp;				// input = input XOR CRCG from 1st leading set bit.
		i = bitAfterLeading_1(input);
	}

	input <<= (input.size() - (N - 1));					// shifting the last N-1 to left
	return bitset<N - 1>(input.to_string());			// returning only left most N-1 bit
}

int main()
{
	bitset<L> input;
	input = 127;
	string crcg = "1001";
	bitset<L + (N - 1)> sending_stream(input.to_string());
	sending_stream <<= N - 1;

	cout << "Orignal Data: " << input << endl;
	cout << "Sending Data: " << sending_stream << endl;
	cout << "CRC Generator: " << crcg << endl;
	cout << "CRC: " << CRC(sending_stream, bitset<N>(crcg)) << endl;
	system("PAUSE");
}
/************OUTPUT*******************************
Orignal Data : 0000000001111111
Sending Data : 0000000001111111000
CRC Generator : 1001
CRC : 001
*************************************************/
