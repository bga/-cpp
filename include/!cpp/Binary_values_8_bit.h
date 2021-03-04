/*
	Copyright 2020 Bga <bga.email@gmail.com>

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#pragma once

enum {
	B0000 = 0x00,
	B0001 = 0x01,
	B0010 = 0x02,
	B0011 = 0x03,
	B0100 = 0x04,
	B0101 = 0x05,
	B0110 = 0x06,
	B0111 = 0x07,
	B1000 = 0x08,
	B1001 = 0x09,
	B1010 = 0x0A,
	B1011 = 0x0B,
	B1100 = 0x0C,
	B1101 = 0x0D,
	B1110 = 0x0E,
	B1111 = 0x0F,

	B00000000 = 0x00,
	B00000001 = 0x01,
	B00000010 = 0x02,
	B00000011 = 0x03,
	B00000100 = 0x04,
	B00000101 = 0x05,
	B00000110 = 0x06,
	B00000111 = 0x07,
	B00001000 = 0x08,
	B00001001 = 0x09,
	B00001010 = 0x0A,
	B00001011 = 0x0B,
	B00001100 = 0x0C,
	B00001101 = 0x0D,
	B00001110 = 0x0E,
	B00001111 = 0x0F,
	B00010000 = 0x10,
	B00010001 = 0x11,
	B00010010 = 0x12,
	B00010011 = 0x13,
	B00010100 = 0x14,
	B00010101 = 0x15,
	B00010110 = 0x16,
	B00010111 = 0x17,
	B00011000 = 0x18,
	B00011001 = 0x19,
	B00011010 = 0x1A,
	B00011011 = 0x1B,
	B00011100 = 0x1C,
	B00011101 = 0x1D,
	B00011110 = 0x1E,
	B00011111 = 0x1F,
	B00100000 = 0x20,
	B00100001 = 0x21,
	B00100010 = 0x22,
	B00100011 = 0x23,
	B00100100 = 0x24,
	B00100101 = 0x25,
	B00100110 = 0x26,
	B00100111 = 0x27,
	B00101000 = 0x28,
	B00101001 = 0x29,
	B00101010 = 0x2A,
	B00101011 = 0x2B,
	B00101100 = 0x2C,
	B00101101 = 0x2D,
	B00101110 = 0x2E,
	B00101111 = 0x2F,
	B00110000 = 0x30,
	B00110001 = 0x31,
	B00110010 = 0x32,
	B00110011 = 0x33,
	B00110100 = 0x34,
	B00110101 = 0x35,
	B00110110 = 0x36,
	B00110111 = 0x37,
	B00111000 = 0x38,
	B00111001 = 0x39,
	B00111010 = 0x3A,
	B00111011 = 0x3B,
	B00111100 = 0x3C,
	B00111101 = 0x3D,
	B00111110 = 0x3E,
	B00111111 = 0x3F,
	B01000000 = 0x40,
	B01000001 = 0x41,
	B01000010 = 0x42,
	B01000011 = 0x43,
	B01000100 = 0x44,
	B01000101 = 0x45,
	B01000110 = 0x46,
	B01000111 = 0x47,
	B01001000 = 0x48,
	B01001001 = 0x49,
	B01001010 = 0x4A,
	B01001011 = 0x4B,
	B01001100 = 0x4C,
	B01001101 = 0x4D,
	B01001110 = 0x4E,
	B01001111 = 0x4F,
	B01010000 = 0x50,
	B01010001 = 0x51,
	B01010010 = 0x52,
	B01010011 = 0x53,
	B01010100 = 0x54,
	B01010101 = 0x55,
	B01010110 = 0x56,
	B01010111 = 0x57,
	B01011000 = 0x58,
	B01011001 = 0x59,
	B01011010 = 0x5A,
	B01011011 = 0x5B,
	B01011100 = 0x5C,
	B01011101 = 0x5D,
	B01011110 = 0x5E,
	B01011111 = 0x5F,
	B01100000 = 0x60,
	B01100001 = 0x61,
	B01100010 = 0x62,
	B01100011 = 0x63,
	B01100100 = 0x64,
	B01100101 = 0x65,
	B01100110 = 0x66,
	B01100111 = 0x67,
	B01101000 = 0x68,
	B01101001 = 0x69,
	B01101010 = 0x6A,
	B01101011 = 0x6B,
	B01101100 = 0x6C,
	B01101101 = 0x6D,
	B01101110 = 0x6E,
	B01101111 = 0x6F,
	B01110000 = 0x70,
	B01110001 = 0x71,
	B01110010 = 0x72,
	B01110011 = 0x73,
	B01110100 = 0x74,
	B01110101 = 0x75,
	B01110110 = 0x76,
	B01110111 = 0x77,
	B01111000 = 0x78,
	B01111001 = 0x79,
	B01111010 = 0x7A,
	B01111011 = 0x7B,
	B01111100 = 0x7C,
	B01111101 = 0x7D,
	B01111110 = 0x7E,
	B01111111 = 0x7F,
	B10000000 = 0x80,
	B10000001 = 0x81,
	B10000010 = 0x82,
	B10000011 = 0x83,
	B10000100 = 0x84,
	B10000101 = 0x85,
	B10000110 = 0x86,
	B10000111 = 0x87,
	B10001000 = 0x88,
	B10001001 = 0x89,
	B10001010 = 0x8A,
	B10001011 = 0x8B,
	B10001100 = 0x8C,
	B10001101 = 0x8D,
	B10001110 = 0x8E,
	B10001111 = 0x8F,
	B10010000 = 0x90,
	B10010001 = 0x91,
	B10010010 = 0x92,
	B10010011 = 0x93,
	B10010100 = 0x94,
	B10010101 = 0x95,
	B10010110 = 0x96,
	B10010111 = 0x97,
	B10011000 = 0x98,
	B10011001 = 0x99,
	B10011010 = 0x9A,
	B10011011 = 0x9B,
	B10011100 = 0x9C,
	B10011101 = 0x9D,
	B10011110 = 0x9E,
	B10011111 = 0x9F,
	B10100000 = 0xA0,
	B10100001 = 0xA1,
	B10100010 = 0xA2,
	B10100011 = 0xA3,
	B10100100 = 0xA4,
	B10100101 = 0xA5,
	B10100110 = 0xA6,
	B10100111 = 0xA7,
	B10101000 = 0xA8,
	B10101001 = 0xA9,
	B10101010 = 0xAA,
	B10101011 = 0xAB,
	B10101100 = 0xAC,
	B10101101 = 0xAD,
	B10101110 = 0xAE,
	B10101111 = 0xAF,
	B10110000 = 0xB0,
	B10110001 = 0xB1,
	B10110010 = 0xB2,
	B10110011 = 0xB3,
	B10110100 = 0xB4,
	B10110101 = 0xB5,
	B10110110 = 0xB6,
	B10110111 = 0xB7,
	B10111000 = 0xB8,
	B10111001 = 0xB9,
	B10111010 = 0xBA,
	B10111011 = 0xBB,
	B10111100 = 0xBC,
	B10111101 = 0xBD,
	B10111110 = 0xBE,
	B10111111 = 0xBF,
	B11000000 = 0xC0,
	B11000001 = 0xC1,
	B11000010 = 0xC2,
	B11000011 = 0xC3,
	B11000100 = 0xC4,
	B11000101 = 0xC5,
	B11000110 = 0xC6,
	B11000111 = 0xC7,
	B11001000 = 0xC8,
	B11001001 = 0xC9,
	B11001010 = 0xCA,
	B11001011 = 0xCB,
	B11001100 = 0xCC,
	B11001101 = 0xCD,
	B11001110 = 0xCE,
	B11001111 = 0xCF,
	B11010000 = 0xD0,
	B11010001 = 0xD1,
	B11010010 = 0xD2,
	B11010011 = 0xD3,
	B11010100 = 0xD4,
	B11010101 = 0xD5,
	B11010110 = 0xD6,
	B11010111 = 0xD7,
	B11011000 = 0xD8,
	B11011001 = 0xD9,
	B11011010 = 0xDA,
	B11011011 = 0xDB,
	B11011100 = 0xDC,
	B11011101 = 0xDD,
	B11011110 = 0xDE,
	B11011111 = 0xDF,
	B11100000 = 0xE0,
	B11100001 = 0xE1,
	B11100010 = 0xE2,
	B11100011 = 0xE3,
	B11100100 = 0xE4,
	B11100101 = 0xE5,
	B11100110 = 0xE6,
	B11100111 = 0xE7,
	B11101000 = 0xE8,
	B11101001 = 0xE9,
	B11101010 = 0xEA,
	B11101011 = 0xEB,
	B11101100 = 0xEC,
	B11101101 = 0xED,
	B11101110 = 0xEE,
	B11101111 = 0xEF,
	B11110000 = 0xF0,
	B11110001 = 0xF1,
	B11110010 = 0xF2,
	B11110011 = 0xF3,
	B11110100 = 0xF4,
	B11110101 = 0xF5,
	B11110110 = 0xF6,
	B11110111 = 0xF7,
	B11111000 = 0xF8,
	B11111001 = 0xF9,
	B11111010 = 0xFA,
	B11111011 = 0xFB,
	B11111100 = 0xFC,
	B11111101 = 0xFD,
	B11111110 = 0xFE,
	B11111111 = 0xFF,

	B0000_0000 = 0x00,
	B0000_0001 = 0x01,
	B0000_0010 = 0x02,
	B0000_0011 = 0x03,
	B0000_0100 = 0x04,
	B0000_0101 = 0x05,
	B0000_0110 = 0x06,
	B0000_0111 = 0x07,
	B0000_1000 = 0x08,
	B0000_1001 = 0x09,
	B0000_1010 = 0x0A,
	B0000_1011 = 0x0B,
	B0000_1100 = 0x0C,
	B0000_1101 = 0x0D,
	B0000_1110 = 0x0E,
	B0000_1111 = 0x0F,
	B0001_0000 = 0x10,
	B0001_0001 = 0x11,
	B0001_0010 = 0x12,
	B0001_0011 = 0x13,
	B0001_0100 = 0x14,
	B0001_0101 = 0x15,
	B0001_0110 = 0x16,
	B0001_0111 = 0x17,
	B0001_1000 = 0x18,
	B0001_1001 = 0x19,
	B0001_1010 = 0x1A,
	B0001_1011 = 0x1B,
	B0001_1100 = 0x1C,
	B0001_1101 = 0x1D,
	B0001_1110 = 0x1E,
	B0001_1111 = 0x1F,
	B0010_0000 = 0x20,
	B0010_0001 = 0x21,
	B0010_0010 = 0x22,
	B0010_0011 = 0x23,
	B0010_0100 = 0x24,
	B0010_0101 = 0x25,
	B0010_0110 = 0x26,
	B0010_0111 = 0x27,
	B0010_1000 = 0x28,
	B0010_1001 = 0x29,
	B0010_1010 = 0x2A,
	B0010_1011 = 0x2B,
	B0010_1100 = 0x2C,
	B0010_1101 = 0x2D,
	B0010_1110 = 0x2E,
	B0010_1111 = 0x2F,
	B0011_0000 = 0x30,
	B0011_0001 = 0x31,
	B0011_0010 = 0x32,
	B0011_0011 = 0x33,
	B0011_0100 = 0x34,
	B0011_0101 = 0x35,
	B0011_0110 = 0x36,
	B0011_0111 = 0x37,
	B0011_1000 = 0x38,
	B0011_1001 = 0x39,
	B0011_1010 = 0x3A,
	B0011_1011 = 0x3B,
	B0011_1100 = 0x3C,
	B0011_1101 = 0x3D,
	B0011_1110 = 0x3E,
	B0011_1111 = 0x3F,
	B0100_0000 = 0x40,
	B0100_0001 = 0x41,
	B0100_0010 = 0x42,
	B0100_0011 = 0x43,
	B0100_0100 = 0x44,
	B0100_0101 = 0x45,
	B0100_0110 = 0x46,
	B0100_0111 = 0x47,
	B0100_1000 = 0x48,
	B0100_1001 = 0x49,
	B0100_1010 = 0x4A,
	B0100_1011 = 0x4B,
	B0100_1100 = 0x4C,
	B0100_1101 = 0x4D,
	B0100_1110 = 0x4E,
	B0100_1111 = 0x4F,
	B0101_0000 = 0x50,
	B0101_0001 = 0x51,
	B0101_0010 = 0x52,
	B0101_0011 = 0x53,
	B0101_0100 = 0x54,
	B0101_0101 = 0x55,
	B0101_0110 = 0x56,
	B0101_0111 = 0x57,
	B0101_1000 = 0x58,
	B0101_1001 = 0x59,
	B0101_1010 = 0x5A,
	B0101_1011 = 0x5B,
	B0101_1100 = 0x5C,
	B0101_1101 = 0x5D,
	B0101_1110 = 0x5E,
	B0101_1111 = 0x5F,
	B0110_0000 = 0x60,
	B0110_0001 = 0x61,
	B0110_0010 = 0x62,
	B0110_0011 = 0x63,
	B0110_0100 = 0x64,
	B0110_0101 = 0x65,
	B0110_0110 = 0x66,
	B0110_0111 = 0x67,
	B0110_1000 = 0x68,
	B0110_1001 = 0x69,
	B0110_1010 = 0x6A,
	B0110_1011 = 0x6B,
	B0110_1100 = 0x6C,
	B0110_1101 = 0x6D,
	B0110_1110 = 0x6E,
	B0110_1111 = 0x6F,
	B0111_0000 = 0x70,
	B0111_0001 = 0x71,
	B0111_0010 = 0x72,
	B0111_0011 = 0x73,
	B0111_0100 = 0x74,
	B0111_0101 = 0x75,
	B0111_0110 = 0x76,
	B0111_0111 = 0x77,
	B0111_1000 = 0x78,
	B0111_1001 = 0x79,
	B0111_1010 = 0x7A,
	B0111_1011 = 0x7B,
	B0111_1100 = 0x7C,
	B0111_1101 = 0x7D,
	B0111_1110 = 0x7E,
	B0111_1111 = 0x7F,
	B1000_0000 = 0x80,
	B1000_0001 = 0x81,
	B1000_0010 = 0x82,
	B1000_0011 = 0x83,
	B1000_0100 = 0x84,
	B1000_0101 = 0x85,
	B1000_0110 = 0x86,
	B1000_0111 = 0x87,
	B1000_1000 = 0x88,
	B1000_1001 = 0x89,
	B1000_1010 = 0x8A,
	B1000_1011 = 0x8B,
	B1000_1100 = 0x8C,
	B1000_1101 = 0x8D,
	B1000_1110 = 0x8E,
	B1000_1111 = 0x8F,
	B1001_0000 = 0x90,
	B1001_0001 = 0x91,
	B1001_0010 = 0x92,
	B1001_0011 = 0x93,
	B1001_0100 = 0x94,
	B1001_0101 = 0x95,
	B1001_0110 = 0x96,
	B1001_0111 = 0x97,
	B1001_1000 = 0x98,
	B1001_1001 = 0x99,
	B1001_1010 = 0x9A,
	B1001_1011 = 0x9B,
	B1001_1100 = 0x9C,
	B1001_1101 = 0x9D,
	B1001_1110 = 0x9E,
	B1001_1111 = 0x9F,
	B1010_0000 = 0xA0,
	B1010_0001 = 0xA1,
	B1010_0010 = 0xA2,
	B1010_0011 = 0xA3,
	B1010_0100 = 0xA4,
	B1010_0101 = 0xA5,
	B1010_0110 = 0xA6,
	B1010_0111 = 0xA7,
	B1010_1000 = 0xA8,
	B1010_1001 = 0xA9,
	B1010_1010 = 0xAA,
	B1010_1011 = 0xAB,
	B1010_1100 = 0xAC,
	B1010_1101 = 0xAD,
	B1010_1110 = 0xAE,
	B1010_1111 = 0xAF,
	B1011_0000 = 0xB0,
	B1011_0001 = 0xB1,
	B1011_0010 = 0xB2,
	B1011_0011 = 0xB3,
	B1011_0100 = 0xB4,
	B1011_0101 = 0xB5,
	B1011_0110 = 0xB6,
	B1011_0111 = 0xB7,
	B1011_1000 = 0xB8,
	B1011_1001 = 0xB9,
	B1011_1010 = 0xBA,
	B1011_1011 = 0xBB,
	B1011_1100 = 0xBC,
	B1011_1101 = 0xBD,
	B1011_1110 = 0xBE,
	B1011_1111 = 0xBF,
	B1100_0000 = 0xC0,
	B1100_0001 = 0xC1,
	B1100_0010 = 0xC2,
	B1100_0011 = 0xC3,
	B1100_0100 = 0xC4,
	B1100_0101 = 0xC5,
	B1100_0110 = 0xC6,
	B1100_0111 = 0xC7,
	B1100_1000 = 0xC8,
	B1100_1001 = 0xC9,
	B1100_1010 = 0xCA,
	B1100_1011 = 0xCB,
	B1100_1100 = 0xCC,
	B1100_1101 = 0xCD,
	B1100_1110 = 0xCE,
	B1100_1111 = 0xCF,
	B1101_0000 = 0xD0,
	B1101_0001 = 0xD1,
	B1101_0010 = 0xD2,
	B1101_0011 = 0xD3,
	B1101_0100 = 0xD4,
	B1101_0101 = 0xD5,
	B1101_0110 = 0xD6,
	B1101_0111 = 0xD7,
	B1101_1000 = 0xD8,
	B1101_1001 = 0xD9,
	B1101_1010 = 0xDA,
	B1101_1011 = 0xDB,
	B1101_1100 = 0xDC,
	B1101_1101 = 0xDD,
	B1101_1110 = 0xDE,
	B1101_1111 = 0xDF,
	B1110_0000 = 0xE0,
	B1110_0001 = 0xE1,
	B1110_0010 = 0xE2,
	B1110_0011 = 0xE3,
	B1110_0100 = 0xE4,
	B1110_0101 = 0xE5,
	B1110_0110 = 0xE6,
	B1110_0111 = 0xE7,
	B1110_1000 = 0xE8,
	B1110_1001 = 0xE9,
	B1110_1010 = 0xEA,
	B1110_1011 = 0xEB,
	B1110_1100 = 0xEC,
	B1110_1101 = 0xED,
	B1110_1110 = 0xEE,
	B1110_1111 = 0xEF,
	B1111_0000 = 0xF0,
	B1111_0001 = 0xF1,
	B1111_0010 = 0xF2,
	B1111_0011 = 0xF3,
	B1111_0100 = 0xF4,
	B1111_0101 = 0xF5,
	B1111_0110 = 0xF6,
	B1111_0111 = 0xF7,
	B1111_1000 = 0xF8,
	B1111_1001 = 0xF9,
	B1111_1010 = 0xFA,
	B1111_1011 = 0xFB,
	B1111_1100 = 0xFC,
	B1111_1101 = 0xFD,
	B1111_1110 = 0xFE,
	B1111_1111 = 0xFF
};
