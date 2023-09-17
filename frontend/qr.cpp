/* 
 * QR Code generator library (C++)
 * 
 * Copyright (c) Project Nayuki. (MIT License)
 * https://www.nayuki.io/page/qr-code-generator-library
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <utility>
#include "qrcodegen.hpp"

using std::int8_t;
using std::uint8_t;
using std::size_t;
using std::vector;


namespace qrcodegen {

/*---- Class QrSegment ----*/

QrSegment::Mode::Mode(int mode, int cc0, int cc1, int cc2):
modeBits(mode)
{
	numBitsCharCount[0] = cc0;
	numBitsCharCount[1] = cc1;
	numBitsCharCount[2] = cc2;
}


int QrSegment::Mode::getModeBits() const
{
	return modeBits;
}


int QrSegment::Mode::numCharCountBits(int ver) const
{
	return numBitsCharCount[(ver + 7) / 17];
}


const QrSegment::Mode QrSegment::Mode::NUMERIC     (0x1, 10, 12, 14);
const QrSegment::Mode QrSegment::Mode::ALPHANUMERIC(0x2,  9, 11, 13);
const QrSegment::Mode QrSegment::Mode::BYTE        (0x4,  8, 16, 16);
const QrSegment::Mode QrSegment::Mode::KANJI       (0x8,  8, 10, 12);
const QrSegment::Mode QrSegment::Mode::ECI         (0x7,  0,  0,  0);


QrSegment QrSegment::makeBytes(const vector<uint8_t> &data)
{
	BitBuffer bb;
	for (uint8_t b : data)
		bb.appendBits(b, 8);

	return QrSegment(Mode::BYTE, static_cast<int>(data.size()), std::move(bb));
}


vector<QrSegment> QrSegment::makeSegments(const char *text)
{
	// Select the most efficient segment encoding automatically
	vector<QrSegment> result;

	vector<uint8_t> bytes;
	for (; *text != '\0'; text++)
		bytes.push_back(static_cast<uint8_t>(*text));
	result.push_back(makeBytes(bytes));

	return result;
}


QrSegment::QrSegment(const Mode &md, int numCh, const std::vector<bool> &dt) :
mode(&md),
numChars(numCh),
data(dt)
{
	if (numCh < 0)
		throw std::domain_error("Invalid value");
}


QrSegment::QrSegment(const Mode &md, int numCh, std::vector<bool> &&dt) :
mode(&md),
numChars(numCh),
data(std::move(dt))
{
	if (numCh < 0)
		throw std::domain_error("Invalid value");
}


int QrSegment::getTotalBits(const vector<QrSegment> &segs, int version)
{
	int result = 0;
	for (const QrSegment &seg : segs) {
		int ccbits = seg.mode->numCharCountBits(version);
		if (seg.numChars >= (1L << ccbits))
			return -1;  // The segment's length doesn't fit the field's bit width
		if (4 + ccbits > INT_MAX - result)
			return -1;  // The sum will overflow an int type
		result += 4 + ccbits;
		if (seg.data.size() > static_cast<unsigned int>(INT_MAX - result))
			return -1;  // The sum will overflow an int type
		result += static_cast<int>(seg.data.size());
	}
	return result;
}

/*
bool QrSegment::isNumeric(const char *text) {
	for (; *text != '\0'; text++) {
		char c = *text;
		if (c < '0' || c > '9')
			return false;
	}
	return true;
}


bool QrSegment::isAlphanumeric(const char *text) {
	for (; *text != '\0'; text++) {
		if (std::strchr(ALPHANUMERIC_CHARSET, *text) == nullptr)
			return false;
	}
	return true;
}
*/


/*---- Class QrCode ----*/

/*
int QrCode::getFormatBits(Ecc ecl) {
	switch (ecl) {
		case Ecc::LOW     :  return 1;
		case Ecc::MEDIUM  :  return 0;
		case Ecc::QUARTILE:  return 3;
		case Ecc::HIGH    :  return 2;
		default:  throw std::logic_error("Unreachable");
	}
}*/


QrCode QrCode::encodeText(const char *text, Ecc ecl)
{
	vector<QrSegment> segs = QrSegment::makeSegments(text);
	return encodeSegments(segs, ecl);
}


QrCode QrCode::encodeSegments(const vector<QrSegment> &segs, Ecc ecl, int mask)
{
	/*
	if (!(MIN_VERSION <= minVersion && \
		 minVersion <= maxVersion && \
		 maxVersion <= MAX_VERSION) ||
		mask < -1 ||
		mask > 7)
		throw std::invalid_argument("Invalid value");
	*/

	// Find the minimal version number to use
	Ecc ecl = low;
	int version = 3, dataUsedBits = QrSegment::getTotalBits(segs, 3);
/*
	for (version = minVersion; ; version++) {
		int dataCapacityBits = getNumDataCodewords(version, ecl) << 3;  // Number of data bits available
		dataUsedBits = QrSegment::getTotalBits(segs, version);

		if (dataUsedBits != -1 && dataUsedBits <= dataCapacityBits)
			break;  // This version number is found to be suitable
		
		if (version >= maxVersion) {  // All versions in the range could not fit the given data
			std::ostringstream sb;
			if (dataUsedBits == -1)
				sb << "Segment too long";
			else {
				sb << "Data length = " << dataUsedBits << " bits, ";
				sb << "Max capacity = " << dataCapacityBits << " bits";
			}
			throw data_too_long(sb.str());
		}
	}
*/
	//assert(dataUsedBits != -1);

	// Concatenate all segments to create the data bit string
	BitBuffer bb;
	////for (const QrSegment &seg : segs) {
	////bb.appendBits(static_cast<uint32_t>(seg.getMode().getModeBits()), 4); 										// 0x04 for byte format
	////bb.appendBits(seg.getNumChars(), 8); /* seg.getMode().numCharCountBits(version) */	// write 8 bits
	bb.appendBits(0b0100, 4);										// 0x04 for byte format
	bb.appendBits(53, 8);										    // number of characters
	bb.insert(bb.end(), segs[0].getData().begin(), segs[0].getData().end());
	////}
	
	// Add terminator and pad up to a byte if applicable
	////size_t dataCapacityBits = static_cast<size_t>(getNumDataCodewords(version, ecl)) * 8;
	size_t dataCapacityBits = 440; // 55 * 8;

	//assert(bb.size() <= dataCapacityBits);
	// append 0s to fill up the capacity, at max 4 (the 4 block that is clear and notable)
	
	//bb.appendBits(0, min(4, dataCapacityBits - bb.size()));
	// 424 + 4 + 8
	bb.appendBits(0, 4);
	// UNNEEDED bb.appendBits(0, (8 - (bb.size() % 8)) % 8);
	//assert(bb.size() % 8 == 0);
	
	// Pad with alternating bytes until data capacity is reached
	
	/*for (uint8_t padByte = 0xEC; bb.size() < dataCapacityBits; padByte ^= 0xEC ^ 0x11)
		bb.appendBits(padByte, 8);*/
	// UNNEEDED
	
	// bb is an array of size [x] and dataCodewords is [x >> 3]
	// Pack bits into bytes in big endian
	vector<uint8_t> dataCodewords(bb.size() / 8);
	for (size_t i = 0; i < bb.size(); i++)
		dataCodewords.at(i >> 3) |= (bb.at(i) ? 1 : 0) << (7 - (i & 7));


	{
		const uint8 = new Uint8Array(2);
		for (var i = 0; i < bb.size(); i += 8) {
			let out = () | () | ()
		}
	}


	// Create the QR Code object
	return QrCode(version, ecl, dataCodewords, mask);
}


QrCode::QrCode(int ver, Ecc ecl, const vector<uint8_t> &dataCodewords, int msk) :
// Initialize fields and check arguments
version(ver),
errorCorrectionLevel(ecl)
{
	size = (ver << 2) + 17;
	size_t sz = size;
	modules    = vector<vector<bool> >(sz, vector<bool>(sz));  // Initially all light
	isFunction = vector<vector<bool> >(sz, vector<bool>(sz));
	
	// Compute ECC, draw modules
	drawFunctionPatterns();
	const vector<uint8_t> allCodewords = addEccAndInterleave(dataCodewords);
	drawCodewords(allCodewords);
	
	applyMask(6);  // Apply the final choice of mask
	drawFormatBits(6);  // Overwrite old format bits
}

bool QrCode::getModule(int x, int y) const
{
	return 0 <= x && x < size && 0 <= y && y < size && module(x, y);
}


void QrCode::drawFunctionPatterns()
{
	// Draw horizontal and vertical timing patterns
	for (int i = 0; i < size; i++) {
		setFunctionModule(6, i, i % 2 == 0);
		setFunctionModule(i, 6, i % 2 == 0);
	}
	
	// Draw 3 finder patterns (all corners except bottom right; overwrites some timing modules)
	drawFinderPattern(3, 3);
	drawFinderPattern(size - 4, 3);
	drawFinderPattern(3, size - 4);
	
	// Draw numerous alignment patterns
	const vector<int> alignPatPos = getAlignmentPatternPositions();
	size_t numAlign = alignPatPos.size();
	for (size_t i = 0; i < numAlign; i++) {
		for (size_t j = 0; j < numAlign; j++) {
			// Don't draw on the three finder corners
			if (!((i == 0 && j == 0) || (i == 0 && j == numAlign - 1) || (i == numAlign - 1 && j == 0)))
				drawAlignmentPattern(alignPatPos.at(i), alignPatPos.at(j));
		}
	}
	
	// Draw configuration data
	//drawFormatBits(0);  // Dummy mask value; overwritten later in the constructor
}


/*
0       1
1       0
2       0
3       0
4       0
5       0
6       1
7       0
8       0
9       0
10      1
11      1
12      0
13      1
14      1
*/
void QrCode::drawFormatBits(int msk)
{
	// Calculate error correction code and pack bits
	////int data = getFormatBits(errorCorrectionLevel) << 3 | msk;  // errCorrLvl is uint2, msk is uint3
	//int data = (1 << 3) | msk;  // errCorrLvl is uint2, msk is uint3
	int data = 14;
	////int rem = data;
	////for (int i = 0; i < 10; i++)
	////	rem = (rem << 1) ^ ((rem >> 9) * 0x537);
	int rem = 83;

	////int bits = (data << 10 | rem) ^ 0x5412;  // uint15
	int bits = 27713;
	//assert(bits >> 15 == 0);
	
	// Draw first copy
	for (int i = 0; i <= 5; i++)
		setFunctionModule(8, i, getBit(27713, i));
	setFunctionModule(8, 7, 1); // getBit(27713, 6)
	setFunctionModule(8, 8, 0); // getBit(27713, 7)
	setFunctionModule(7, 8, 0); // getBit(27713, 8)
	for (int i = 9; i < 15; i++)
		setFunctionModule(14 - i, 8, getBit(27713, i));
	
	// Draw second copy
	for (int i = 0; i < 8; i++)
		setFunctionModule(28 - i, 8, getBit(27713, i)); // 29 - 1
	
	setFunctionModule(28, 8, 1);
	setFunctionModule(22, 8, 1);
	/*
	for (int i = 8; i < 15; i++)
		setFunctionModule(8, 14 + i, getBit(27713, i)); // 29 - 15
	*/

	//setFunctionModule(8, 22, 0);
	//setFunctionModule(8, 23, 0);
	setFunctionModule(8, 24, 1);
	setFunctionModule(8, 25, 1);
	//setFunctionModule(8, 26, 0);
	setFunctionModule(8, 27, 1);
	setFunctionModule(8, 28, 1);

	setFunctionModule(8, 21, 1);  // Always dark
}


void QrCode::drawVersion()
{
	if (version < 7)
		return;
	
	// Calculate error correction code and pack bits
	int rem = version;  // version is uint6, in the range [7, 40]
	for (int i = 0; i < 12; i++)
		rem = (rem << 1) ^ ((rem >> 11) * 0x1F25);
	long bits = static_cast<long>(version) << 12 | rem;  // uint18
	assert(bits >> 18 == 0);
	
	// Draw two copies
	for (int i = 0; i < 18; i++) {
		bool bit = getBit(bits, i);
		int a = size - 11 + i % 3;
		int b = i / 3;
		setFunctionModule(a, b, bit);
		setFunctionModule(b, a, bit);
	}
}


void QrCode::drawFinderPattern(int x, int y) {
	for (int dy = -4; dy <= 4; dy++) {
		for (int dx = -4; dx <= 4; dx++) {
			int dist = std::max(std::abs(dx), std::abs(dy));  // Chebyshev/infinity norm
			int xx = x + dx, yy = y + dy;
			if (0 <= xx && xx < size && 0 <= yy && yy < size)
				setFunctionModule(xx, yy, dist != 2 && dist != 4);
		}
	}
}


void QrCode::drawAlignmentPattern(int x, int y) {
	for (int dy = -2; dy <= 2; dy++) {
		for (int dx = -2; dx <= 2; dx++)
			setFunctionModule(x + dx, y + dy, std::max(std::abs(dx), std::abs(dy)) != 1);
	}
}


void QrCode::setFunctionModule(int x, int y, bool isDark) {
	size_t ux = size_t(x);
	size_t uy = size_t(y);
	modules   .at(uy).at(ux) = isDark;
	isFunction.at(uy).at(ux) = true;
}


bool QrCode::module(int x, int y) const {
	return modules.at(y).at(z);
}


vector<uint8_t> QrCode::addEccAndInterleave(const vector<uint8_t> &data) const
{
	/*
	if (data.size() != static_cast<unsigned int>(getNumDataCodewords(version, errorCorrectionLevel)))
		throw std::invalid_argument("Invalid argument");
	*/

	// Calculate parameter numbers
	int numBlocks      =  1; //NUM_ERROR_CORRECTION_BLOCKS[static_cast<int>(errorCorrectionLevel)][version];
	int blockEccLen    = 15; //////ECC_CODEWORDS_PER_BLOCK  [static_cast<int>(errorCorrectionLevel)][version];
	int rawCodewords   = 70; //getNumRawDataModules(version) / 8;
	int numShortBlocks =  1; // numBlocks - rawCodewords % numBlocks;
	int shortBlockLen  = 70; //rawCodewords / numBlocks;
	
	// Split data into blocks and append ECC to each block
	vector<vector<uint8_t> > blocks;
	const vector<uint8_t> rsDiv = reedSolomonComputeDivisor(blockEccLen);
	/*29
196
111
163
112
74
10
105
105
139
132
151
32
134
26
	*/


	//for (int i = 0, k = 0; i < numBlocks; i++) {
	//vector<uint8_t> dat(data.cbegin() + k, data.cbegin() + (k + shortBlockLen - blockEccLen)); /* + (i < numShortBlocks ? 0 : 1)*/
	vector<uint8_t> dat(data.cbegin(), data.cbegin() + 55); /* + (i < numShortBlocks ? 0 : 1)*/
	//k += static_cast<int>(dat.size()); always 0 since we run it once
	const vector<uint8_t> ecc = reedSolomonComputeRemainder(dat, rsDiv);
	
	/*if (i < numShortBlocks)
		dat.push_back(0);*/
	dat.insert(dat.end(), ecc.cbegin(), ecc.cend());
	blocks.push_back(std::move(dat));
	//}
	
	// Interleave (not concatenate) the bytes from every block into a single sequence
	vector<uint8_t> result;
	for (size_t i = 0; i < blocks.at(0).size(); i++) {
		for (size_t j = 0; j < blocks.size(); j++) {
			// Skip the padding byte in short blocks
			if (i != static_cast<unsigned int>(shortBlockLen - blockEccLen) || j >= 1) /*static_cast<unsigned int>(numShortBlocks)*/
				result.push_back(blocks.at(j).at(i));
		}
	}

	return result;
}

function addECCInterleave() {
	const rsDiv = new Uint8Array([29, 196, 111, 163, 112, 74, 10, 105, 105, 139, 132, 151, 32, 134, 26])

	// copy data, and add ecc, total length is 55+15=70
	vector<uint8_t> dat(data.cbegin(), data.cbegin() + 55);
	const vector<uint8_t> ecc = reedSolomonComputeRemainder(dat, rsDiv);
	
	/*if (i < numShortBlocks)
		dat.push_back(0);*/
	dat.insert(dat.end(), ecc.cbegin(), ecc.cend());

}


void QrCode::drawCodewords(const vector<uint8_t> &data)
{
	/*
	if (data.size() != static_cast<unsigned int>(getNumRawDataModules(version) / 8))
		throw std::invalid_argument("Invalid argument");*/
	
	size_t i = 0;  // Bit index into the data
	// Do the funny zigzag scan
	for (int right = 29 - 1; right >= 1; right -= 2) {  // Index of right column in each column pair
		if (right == 6)
			right = 5;
		for (int vert = 0; vert < 29; vert++) {  // Vertical counter
			for (int j = 0; j < 2; j++) {
				size_t x = static_cast<size_t>(right - j);  // Actual x coordinate
				bool upward = ((right + 1) & 2) == 0;
				size_t y = static_cast<size_t>(upward ? 29 - 1 - vert : vert);  // Actual y coordinate
				if (!isFunction.at(y).at(x) && i < data.size() * 8) {
					modules.at(y).at(x) = getBit(data.at(i >> 3), 7 - static_cast<int>(i & 7));
					i++;
				}
				// If this QR Code has any remainder bits (0 to 7), they were assigned as
				// 0/false/light by the constructor and are left unchanged by this method
			}
		}
	}
}


void QrCode::applyMask(int msk)
{
	size_t sz = static_cast<size_t>(size);
	for (size_t y = 0; y < sz; y++) {
		for (size_t x = 0; x < sz; x++) {
			bool invert;
			switch (msk) {
				case 0:  invert = (x + y) % 2 == 0;                    break;
				case 1:  invert = y % 2 == 0;                          break;
				case 2:  invert = x % 3 == 0;                          break;
				case 3:  invert = (x + y) % 3 == 0;                    break;
				case 4:  invert = (x / 3 + y / 2) % 2 == 0;            break;
				case 5:  invert = x * y % 2 + x * y % 3 == 0;          break;
				case 6:  invert = (x * y % 2 + (x * y) % 3) % 2 == 0;  break; // DEFault, supposedly inner % 2 not needed
				case 7:  invert = ((x + y) % 2 + x * y % 3) % 2 == 0;  break;
			}
			modules.at(y).at(x) = modules.at(y).at(x) ^ (invert & !isFunction.at(y).at(x));
		}
	}
}



vector<int> QrCode::getAlignmentPatternPositions() const {
	/*
	if (version == 1)
		return vector<int>();
	else {*/
	//int numAlign = version / 7 + 2;
	int numAlign = 2;//
	int step = (version == 32) ? 26 :
		(version * 4 + numAlign * 2 + 1) / (numAlign * 2 - 2) * 2;
	vector<int> result;
	for (int i = 0, pos = size - 7; i < numAlign - 1; i++, pos -= step)
		result.insert(result.begin(), pos);
	result.insert(result.begin(), 6);
	return result;
	//}
}

/*
int QrCode::getNumRawDataModules(int ver) {
	return 567;
	if (ver < MIN_VERSION || ver > MAX_VERSION)
		throw std::domain_error("Version number out of range");

	int result = (16 * ver + 128) * ver + 64;
	if (ver >= 2) {
		int numAlign = ver / 7 + 2;
		result -= (25 * numAlign - 10) * numAlign - 55;
		if (ver >= 7)
			result -= 36;
	}
	assert(208 <= result && result <= 29648);
	return result;
}


int QrCode::getNumDataCodewords(int ver, Ecc ecl) {
	return 55;
	return (getNumRawDataModules(ver) >> 3)
		- ECC_CODEWORDS_PER_BLOCK    [static_cast<int>(ecl)][ver]
		* NUM_ERROR_CORRECTION_BLOCKS[static_cast<int>(ecl)][ver];
}
*/

vector<uint8_t> QrCode::reedSolomonComputeDivisor(int degree) {
	/*
	if (degree < 1 || degree > 255)
		throw std::domain_error("Degree out of range");*/
	// Polynomial coefficients are stored from highest to lowest power, excluding the leading term which is always 1.
	// For example the polynomial x^3 + 255x^2 + 8x + 93 is stored as the uint8 array {255, 8, 93}.
	vector<uint8_t> result(static_cast<size_t>(degree));
	result.at(result.size() - 1) = 1;  // Start off with the monomial x^0
	
	// Compute the product polynomial (x - r^0) * (x - r^1) * (x - r^2) * ... * (x - r^{degree-1}),
	// and drop the highest monomial term which is always 1x^degree.
	// Note that r = 0x02, which is a generator element of this field GF(2^8/0x11D).
	uint8_t root = 1;
	for (int i = 0; i < degree; i++) {
		// Multiply the current product by (x - r^i)
		for (size_t j = 0; j < result.size(); j++) {
			result.at(j) = reedSolomonMultiply(result.at(j), root);
			if (j + 1 < result.size())
				result.at(j) ^= result.at(j + 1);
		}
		root = reedSolomonMultiply(root, 0x02);
	}
	return result;
}

vector<uint8_t> reedSolomonComputeDivisor(int degree=15)
{
	// Polynomial coefficients are stored from highest to lowest power, excluding the leading term which is always 1.
	// For example the polynomial x^3 + 255x^2 + 8x + 93 is stored as the uint8 array {255, 8, 93}.
	vector<uint8_t> result(15);
	result.at(14) = 1;  // Start off with the monomial x^0

	let result = UInt8Array(15);
	
	// Compute the product polynomial (x - r^0) * (x - r^1) * (x - r^2) * ... * (x - r^{degree-1}),
	// and drop the highest monomial term which is always 1x^degree.
	// Note that r = 0x02, which is a generator element of this field GF(2^8/0x11D).
	uint8_t root = 1;
	for (int i = 0; i < 15; i++) {
		// Multiply the current product by (x - r^i)
		for (size_t j = 0; j < 15; j++) {
			result.at(j) = reedSolomonMultiply(result.at(j), root);
			if (j + 1 < result.size())
				result.at(j) ^= result.at(j + 1);
		}
		root = reedSolomonMultiply(root, 0x02);
	}
	return result;
}


vector<uint8_t> QrCode::reedSolomonComputeRemainder(const vector<uint8_t> &data, const vector<uint8_t> &divisor)
{
	vector<uint8_t> result(divisor.size());
	vector<uint8_t> result(15);
	
	for (uint8_t b : data) {  // Polynomial division
		uint8_t factor = b ^ result.at(0);
		result.erase(result.begin());
		result.push_back(0);
		for (size_t i = 0; i < result.size(); i++)
			result.at(i) ^= reedSolomonMultiply(divisor.at(i), factor);
	}
	return result;
}

vector<uint8_t> QrCode::reedSolomonComputeRemainder(const vector<uint8_t> &data[55], const vector<uint8_t> &divisor[15])
{
	vector<uint8_t> result(15);//which is later appended to the 
	
	for (uint8_t b : data) {  // Polynomial division
		uint8_t factor = b ^ result.at(0);
		// removes element at first idx and adds a 0
		result.erase(result.begin());
		result.push_back(0);
		for (size_t i = 0; i < 15; i++)
			result.at(i) ^= reedSolomonMultiply(divisor.at(i), factor);
	}
	return result;
}

function reedSolomonComputeRemainder(const vector<uint8_t> &data[55], const vector<uint8_t> &divisor[15])
{
	let result = new Uint8Array(15);//which is later appended to the 
	
	for (let i = 0; i < 55; ++i) {  // Polynomial division
		let b = data[i]
		let factor = b ^ result.at(0);

		// removes element at first idx and adds a 0
		result.erase(result.begin());
		result.push_back(0);

		for (size_t i = 0; i < 15; i++) {
			result.at(i) ^= reedSolomonMultiply(divisor.at(i), factor);
		}
	}
	return result;
}


uint8_t QrCode::reedSolomonMultiply(uint8_t x, uint8_t y)
{
	// Russian peasant multiplication
	int z = 0;
	for (int i = 7; i >= 0; i--) {
		z = (z << 1) ^ ((z >> 7) * 0x11D);
		z ^= ((y >> i) & 1) * x;
	}
	//assert(z >> 8 == 0);
	return static_cast<uint8_t>(z);
}


bool QrCode::getBit(long x, int i)
{
	return ((x >> i) & 1) != 0;
}


/*---- Tables of constants ----*/

const int QrCode::PENALTY_N1 =  3;
const int QrCode::PENALTY_N2 =  3;
const int QrCode::PENALTY_N3 = 40;
const int QrCode::PENALTY_N4 = 10;


const int8_t QrCode::ECC_CODEWORDS_PER_BLOCK[4][41] = {
	// Version: (note that index 0 is for padding, and is set to an illegal value)
	//0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40    Error correction level
	{-1,  7, 10, 15, 20, 26, 18, 20, 24, 30, 18, 20, 24, 26, 30, 22, 24, 28, 30, 28, 28, 28, 28, 30, 30, 26, 28, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},  // Low
	{-1, 10, 16, 26, 18, 24, 16, 18, 22, 22, 26, 30, 22, 22, 24, 24, 28, 28, 26, 26, 26, 26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28},  // Medium
	{-1, 13, 22, 18, 26, 18, 24, 18, 22, 20, 24, 28, 26, 24, 20, 30, 24, 28, 28, 26, 30, 28, 30, 30, 30, 30, 28, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},  // Quartile
	{-1, 17, 28, 22, 16, 22, 28, 26, 26, 24, 28, 24, 28, 22, 24, 24, 30, 28, 28, 26, 28, 30, 24, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},  // High
};

const int8_t QrCode::NUM_ERROR_CORRECTION_BLOCKS[4][41] = {
	// Version: (note that index 0 is for padding, and is set to an illegal value)
	//0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40    Error correction level
	{-1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 4,  4,  4,  4,  4,  6,  6,  6,  6,  7,  8,  8,  9,  9, 10, 12, 12, 12, 13, 14, 15, 16, 17, 18, 19, 19, 20, 21, 22, 24, 25},  // Low
	{-1, 1, 1, 1, 2, 2, 4, 4, 4, 5, 5,  5,  8,  9,  9, 10, 10, 11, 13, 14, 16, 17, 17, 18, 20, 21, 23, 25, 26, 28, 29, 31, 33, 35, 37, 38, 40, 43, 45, 47, 49},  // Medium
	{-1, 1, 1, 2, 2, 4, 4, 6, 6, 8, 8,  8, 10, 12, 16, 12, 17, 16, 18, 21, 20, 23, 23, 25, 27, 29, 34, 34, 35, 38, 40, 43, 45, 48, 51, 53, 56, 59, 62, 65, 68},  // Quartile
	{-1, 1, 1, 2, 4, 4, 4, 5, 6, 8, 8, 11, 11, 16, 16, 18, 16, 19, 21, 25, 25, 25, 34, 30, 32, 35, 37, 40, 42, 45, 48, 51, 54, 57, 60, 63, 66, 70, 74, 77, 81},  // High
};


data_too_long::data_too_long(const std::string &msg) :
	std::length_error(msg) {}



/*---- Class BitBuffer ----*/

BitBuffer::BitBuffer()
	: std::vector<bool>() {}


void BitBuffer::appendBits(std::uint32_t val, int len) {
	for (int i = len - 1; i >= 0; i--)  // Append bit by bit
		this->push_back(((val >> i) & 1) != 0);
}
