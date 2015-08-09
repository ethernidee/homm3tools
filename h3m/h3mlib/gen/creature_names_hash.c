/*
 * d=3
 * n=174
 * m=141
 * c=1.23
 * maxlen=19
 * minklen=3
 * maxklen=19
 * minchar=32
 * maxchar=122
 * loop=1
 * numiter=1
 * seed=
 */

static int g[] = {
	104, 20, 95, 345, -52, 0, 462, 217, 0, -40,
	0, -110, -463, -618, 137, 70, 114, 1751, 134, -117,
	0, -195, 20, -396, 0, -62, -375, -20, -222, -246,
	1065, 0, 124, 137, -313, -299, -371, 62, -157, 0,
	-141, 0, -22, 12, 102, -177, 30, -92, 65, 364,
	-1061, 0, 65, 0, 261, -1044, -100, -1083, 370, -928,
	0, -12, 19, -67, -101, 1058, 101, -78, -204, 477,
	126, -322, -106, -267, 369, -72, 0, 57, 0, 16,
	-37, 319, 67, -54, 0, 962, 0, -10, 22, 1115,
	342, -1323, -959, -518, 463, 115, 228, -986, -103, 398,
	-30, 0, 0, 0, 88, 415, 214, 0, -154, 446,
	0, 0, -2, 52, 257, 2, 0, 212, 1031, 0,
	-90, 34, -324, -85, 236, 0, 392, 191, 0, -86,
	52, -48, -114, -1038, 0, 157, 320, 0, 246, 160,
	208, -32, -11, -306, -20, 21, 101, 1127, 104, -323,
	0, 0, 129, 165, 213, 93, -67, 16, 57, -103,
	-61, 66, 480, -532, 0, 0, 468, 0, -386, -150,
	44, 1165, 0, 154, 
};

static int T0[] = {
	12, 138, 149, 21, 25, 34, 37, 130, 141, 141,
	111, 125, 164, 103, 170, 20, 149, 156, 173, 40,
	67, 158, 32, 135, 80, 116, 136, 1, 147, 105,
	134, 159, 62, 101, 172, 87, 127, 35, 36, 87,
	168, 147, 38, 159, 68, 26, 171, 44, 1, 162,
	84, 68, 146, 108, 21, 53, 50, 157, 54, 24,
	80, 6, 1, 142, 100, 0, 48, 53, 27, 76,
	140, 22, 41, 171, 173, 110, 15, 162, 154, 8,
	151, 56, 68, 115, 165, 89, 160, 41, 64, 33,
	57, 35, 136, 165, 45, 13, 18, 146, 7, 86,
	104, 110, 48, 82, 158, 12, 18, 108, 31, 165,
	54, 91, 60, 65, 62, 106, 160, 117, 93, 134,
	146, 126, 161, 108, 117, 25, 114, 127, 163, 113,
	31, 93, 50, 79, 1, 26, 83, 11, 126, 107,
	2, 6, 16, 54, 64, 70, 161, 50, 13, 72,
	2, 160, 24, 164, 86, 133, 15, 26, 79, 4,
	140, 110, 89, 8, 8, 90, 26, 83, 93, 153,
	16, 96, 151, 32, 142, 41, 95, 129, 92, 108,
	19, 94, 66, 109, 74, 8, 156, 117, 20, 85,
	45, 50, 41, 41, 110, 39, 117, 136, 4, 22,
	166, 112, 92, 45, 138, 118, 151, 47, 9, 145,
	65, 36, 47, 123, 145, 122, 131, 119, 57, 151,
	31, 102, 27, 64, 135, 129, 96, 79, 92, 100,
	101, 84, 30, 11, 121, 169, 129, 90, 34, 139,
	61, 91, 167, 109, 40, 130, 49, 163, 75, 106,
	132, 98, 26, 151, 155, 153, 107, 77, 58, 17,
	169, 151, 93, 25, 155, 32, 12, 110, 122, 47,
	67, 10, 130, 28, 168, 0, 165, 105, 95, 171,
	51, 37, 8, 21, 76, 53, 31, 157, 173, 17,
	21, 12, 86, 151, 150, 24, 78, 120, 160, 9,
	18, 60, 83, 138, 89, 69, 131, 80, 0, 52,
	70, 43, 81, 78, 64, 149, 123, 95, 124, 114,
	113, 138, 127, 17, 115, 103, 41, 20, 50, 19,
	21, 60, 79, 104, 16, 168, 165, 147, 75, 158,
	17, 145, 27, 98, 41, 92, 65, 165, 5, 16,
	105, 118, 154, 58, 135, 87, 154, 168, 99, 22,
	13, 121, 74, 93, 94, 32, 32, 81, 153, 13,
	50, 14, 143, 34, 56, 74, 40, 6, 5, 70,
	5, 12, 96, 128, 119, 75, 115, 157, 12, 55,
	67, 156, 113, 167, 37, 25, 26, 69, 106, 171,
	83, 149, 11, 44, 9, 59, 119, 49, 58, 116,
	112, 63, 121, 34, 9, 58, 101, 124, 33, 105,
	5, 92, 79, 118, 86, 116, 135, 112, 4, 68,
	109, 87, 35, 112, 123, 44, 163, 60, 85, 47,
	3, 23, 102, 124, 49, 111, 0, 143, 53, 34,
	74, 59, 126, 146, 169, 7, 164, 103, 98, 0,
	96, 30, 78, 5, 41, 47, 98, 165, 38, 95,
	69, 65, 29, 128, 134, 61, 21, 137, 62, 29,
	89, 55, 149, 11, 86, 110, 11, 76, 31, 101,
	68, 127, 123, 147, 124, 156, 12, 48, 148, 50,
	135, 43, 108, 165, 172, 68, 52, 19, 23, 106,
	41, 113, 153, 16, 116, 65, 118, 119, 133, 150,
	47, 28, 95, 170, 167, 46, 153, 5, 86, 127,
	48, 40, 170, 156, 31, 160, 50, 75, 6, 66,
	173, 47, 5, 153, 55, 113, 98, 118, 66, 118,
	153, 135, 136, 154, 21, 110, 59, 56, 34, 40,
	38, 106, 156, 109, 104, 137, 98, 80, 118, 23,
	154, 157, 164, 150, 168, 162, 169, 84, 106, 61,
	28, 77, 14, 164, 58, 36, 93, 109, 84, 119,
	141, 123, 51, 123, 58, 155, 86, 148, 53, 22,
	171, 25, 6, 162, 1, 166, 150, 170, 68, 82,
	49, 96, 159, 56, 79, 35, 84, 164, 136, 168,
	109, 103, 109, 160, 52, 159, 133, 138, 134, 4,
	161, 131, 30, 159, 119, 31, 143, 118, 135, 88,
	13, 53, 156, 82, 10, 54, 19, 22, 138, 31,
	98, 90, 39, 113, 96, 79, 122, 154, 24, 125,
	116, 57, 57, 111, 1, 74, 70, 132, 18, 23,
	39, 24, 76, 13, 106, 86, 67, 117, 109, 23,
	141, 25, 114, 6, 139, 28, 86, 87, 8, 102,
	30, 116, 151, 87, 53, 152, 154, 115, 103, 172,
	138, 142, 14, 32, 155, 113, 119, 41, 48, 46,
	64, 15, 63, 170, 22, 20, 24, 100, 100, 32,
	28, 130, 149, 172, 36, 20, 150, 16, 54, 131,
	119, 92, 67, 3, 130, 17, 32, 166, 74, 68,
	7, 170, 102, 152, 3, 27, 118, 30, 80, 165,
	76, 121, 73, 44, 79, 140, 114, 34, 38, 168,
	158, 149, 78, 51, 144, 34, 61, 3, 19, 127,
	63, 26, 124, 166, 170, 119, 11, 114, 149, 84,
	105, 43, 31, 170, 88, 103, 136, 20, 137, 166,
	14, 121, 134, 92, 165, 104, 126, 44, 107, 145,
	171, 171, 163, 121, 155, 159, 58, 158, 91, 25,
	68, 15, 69, 92, 11, 149, 21, 140, 169, 124,
	60, 1, 108, 111, 81, 15, 73, 166, 106, 54,
	49, 130, 43, 90, 100, 151, 54, 143, 162, 126,
	28, 13, 37, 152, 79, 55, 11, 172, 35, 46,
	114, 95, 39, 41, 25, 120, 56, 98, 105, 162,
	153, 154, 118, 14, 62, 44, 165, 116, 5, 146,
	61, 25, 159, 98, 4, 56, 145, 7, 46, 7,
	45, 161, 94, 84, 28, 119, 23, 84, 44, 128,
	72, 15, 100, 8, 29, 162, 53, 12, 105, 50,
	158, 158, 76, 135, 74, 72, 18, 45, 79, 56,
	49, 60, 77, 58, 120, 118, 58, 108, 94, 100,
	4, 6, 36, 6, 135, 85, 57, 75, 41, 77,
	152, 108, 28, 48, 158, 69, 123, 14, 25, 87,
	112, 74, 148, 15, 132, 86, 126, 8, 13, 46,
	109, 17, 52, 145, 15, 5, 48, 65, 72, 81,
	134, 50, 16, 154, 98, 0, 49, 39, 6, 66,
	127, 118, 141, 93, 134, 91, 5, 86, 100, 10,
	124, 27, 28, 168, 172, 35, 165, 38, 100, 64,
	120, 60, 114, 128, 41, 31, 128, 82, 62, 134,
	149, 112, 120, 9, 126, 84, 138, 162, 138, 115,
	12, 96, 82, 30, 11, 81, 136, 167, 107, 122,
	6, 49, 88, 63, 128, 12, 137, 81, 40, 117,
	140, 56, 55, 87, 58, 0, 163, 14, 162, 127,
	129, 167, 41, 37, 15, 52, 110, 151, 46, 43,
	99, 44, 84, 6, 99, 38, 18, 62, 119, 50,
	171, 78, 107, 52, 165, 165, 44, 146, 5, 25,
	91, 126, 18, 133, 155, 33, 11, 83, 11, 49,
	118, 102, 93, 28, 108, 18, 67, 119, 72, 4,
	169, 69, 87, 119, 105, 135, 121, 84, 32, 78,
	169, 7, 135, 170, 172, 131, 163, 130, 36, 130,
	132, 89, 138, 2, 63, 152, 116, 97, 103, 76,
	157, 78, 13, 62, 15, 110, 23, 128, 20, 47,
	32, 16, 55, 159, 4, 45, 109, 159, 1, 145,
	115, 125, 60, 79, 119, 116, 49, 61, 39, 152,
	137, 14, 48, 142, 76, 56, 70, 91, 2, 82,
	139, 35, 90, 12, 12, 94, 57, 121, 79, 50,
	92, 12, 1, 145, 83, 120, 79, 125, 173, 110,
	95, 128, 125, 101, 9, 140, 13, 149, 46, 69,
	63, 101, 16, 160, 24, 81, 62, 159, 122, 73,
	9, 40, 30, 110, 27, 86, 29, 61, 135, 173,
	16, 140, 90, 128, 59, 100, 94, 64, 67, 140,
	133, 130, 59, 141, 108, 76, 49, 163, 61, 163,
	62, 63, 30, 92, 173, 49, 4, 28, 103, 132,
	20, 119, 90, 102, 73, 149, 28, 160, 39, 88,
	118, 164, 36, 4, 132, 145, 80, 173, 134, 133,
	154, 14, 22, 10, 99, 21, 52, 95, 42, 155,
	53, 54, 100, 143, 10, 167, 49, 133, 61, 80,
	44, 130, 106, 12, 48, 2, 113, 125, 65, 93,
	52, 157, 95, 52, 78, 169, 60, 144, 147, 22,
	118, 64, 146, 34, 93, 148, 20, 143, 108, 81,
	41, 144, 37, 139, 148, 77, 134, 87, 29, 25,
	6, 73, 0, 94, 118, 79, 89, 170, 41, 55,
	18, 152, 119, 156, 12, 38, 130, 24, 173, 56,
	106, 32, 26, 135, 164, 1, 31, 124, 80, 60,
	141, 79, 125, 141, 173, 69, 38, 88, 65, 72,
	143, 75, 50, 80, 57, 21, 102, 149, 17, 125,
	139, 118, 74, 155, 72, 95, 93, 21, 127, 122,
	81, 91, 16, 164, 133, 109, 15, 124, 128, 145,
	89, 34, 108, 169, 21, 65, 9, 115, 33, 18,
	67, 172, 136, 133, 145, 26, 54, 65, 40, 173,
	5, 113, 90, 13, 103, 41, 122, 110, 166, 69,
	81, 81, 95, 8, 68, 117, 65, 69, 50, 98,
	87, 117, 89, 41, 77, 60, 60, 123, 117, 100,
	123, 122, 39, 31, 136, 142, 73, 76, 78, 57,
	145, 151, 138, 67, 159, 24, 31, 91, 164, 143,
	90, 100, 162, 164, 158, 73, 90, 3, 43, 63,
	119, 103, 84, 65, 173, 3, 4, 139, 93, 111,
	133, 94, 73, 116, 113, 159, 39, 137, 76, 30,
	98, 158, 130, 86, 149, 106, 152, 65, 101, 21,
	129, 38, 125, 39, 104, 116, 34, 100, 81, 127,
	37, 32, 48, 110, 141, 153, 87, 6, 108, 164,
	28, 33, 140, 158, 111, 115, 82, 81, 173, 2,
	95, 128, 40, 46, 159, 136, 154, 12, 62, 53,
	139, 99, 86, 5, 28, 45, 151, 20, 18, 161,
	76, 118, 88, 137, 152, 163, 5, 46, 147, 84,
	32, 36, 106, 93, 111, 121, 47, 133, 18, 147,
	133, 58, 50, 131, 21, 114, 41, 96, 134, 59,
	75, 29, 169, 164, 166, 148, 145, 163, 12, 110,
	73, 44, 138, 172, 138, 75, 119, 3, 34, 130,
	142, 168, 14, 18, 117, 27, 125, 158, 124, 77,
	35, 25, 106, 23, 7, 99, 163, 144, 80, 1,
	80, 146, 46, 44, 144, 2, 112, 81, 171, 146,
	37, 140, 132, 52, 150, 76, 79, 101, 165, 155,
	127, 98, 95, 18, 53, 118, 144, 15, 2, 33,
	165, 107, 150, 145, 14, 57, 34, 7, 80, 89,
	125, 124, 81, 173, 96, 113, 72, 172, 140, 63,
	145, 86, 162, 58, 104, 33, 168, 67, 41, 170,
	92, 32, 96, 69, 169, 110, 118, 29, 118, 16,
	110, 69, 140, 18, 68, 54, 123, 132, 44, 89,
	22, 7, 167, 2, 57, 98, 27, 52, 157, 68,
	40, 75, 100, 136, 144, 95, 73, 80, 116, 9,
	96, 53, 70, 54, 63, 130, 101, 12, 89, 
};

static int T1[] = {
	5, 9, 29, 117, 39, 118, 110, 143, 62, 147,
	133, 151, 162, 172, 141, 57, 135, 75, 93, 53,
	171, 139, 104, 133, 126, 145, 95, 14, 165, 124,
	144, 170, 133, 166, 105, 165, 110, 33, 134, 165,
	7, 85, 142, 169, 76, 109, 53, 37, 3, 146,
	90, 166, 103, 12, 117, 48, 158, 31, 54, 149,
	155, 24, 137, 106, 16, 61, 97, 119, 94, 50,
	110, 93, 135, 70, 89, 37, 171, 134, 66, 0,
	98, 149, 159, 27, 161, 102, 67, 137, 125, 121,
	104, 133, 157, 0, 53, 61, 24, 19, 169, 19,
	76, 171, 97, 100, 41, 76, 113, 21, 108, 88,
	25, 43, 150, 96, 82, 126, 102, 159, 95, 83,
	9, 102, 42, 167, 94, 88, 46, 118, 107, 42,
	129, 10, 31, 44, 102, 72, 112, 33, 85, 38,
	121, 102, 73, 98, 25, 155, 50, 119, 133, 137,
	28, 142, 65, 63, 127, 151, 151, 0, 87, 76,
	34, 42, 86, 57, 78, 6, 129, 16, 39, 32,
	54, 161, 134, 128, 77, 151, 109, 119, 97, 60,
	82, 117, 121, 61, 64, 70, 142, 128, 160, 144,
	123, 133, 57, 128, 42, 85, 25, 16, 111, 44,
	23, 128, 32, 24, 38, 170, 107, 9, 33, 86,
	71, 142, 70, 18, 29, 134, 88, 171, 81, 67,
	133, 22, 18, 9, 150, 60, 86, 167, 76, 23,
	38, 92, 143, 62, 108, 7, 50, 42, 16, 75,
	128, 79, 43, 17, 90, 72, 143, 4, 61, 50,
	63, 13, 72, 82, 22, 40, 142, 100, 34, 37,
	115, 64, 129, 85, 126, 63, 92, 2, 105, 101,
	70, 52, 6, 146, 80, 15, 126, 134, 112, 71,
	63, 69, 115, 35, 148, 85, 60, 20, 55, 18,
	155, 105, 173, 148, 66, 72, 83, 27, 28, 41,
	26, 157, 129, 13, 129, 35, 20, 81, 161, 133,
	144, 50, 20, 86, 77, 168, 163, 137, 6, 36,
	147, 153, 142, 146, 127, 26, 36, 29, 53, 65,
	70, 79, 40, 17, 84, 169, 53, 105, 68, 40,
	56, 30, 83, 68, 108, 160, 54, 97, 116, 60,
	126, 81, 31, 86, 54, 159, 112, 82, 6, 166,
	139, 68, 63, 5, 73, 84, 14, 89, 110, 39,
	36, 170, 85, 1, 99, 138, 17, 96, 58, 41,
	16, 87, 107, 57, 136, 91, 153, 135, 105, 52,
	51, 173, 173, 7, 43, 64, 92, 57, 145, 28,
	88, 0, 16, 165, 1, 116, 129, 19, 30, 13,
	52, 38, 92, 160, 95, 54, 77, 67, 16, 0,
	111, 59, 166, 102, 66, 35, 166, 158, 84, 130,
	4, 172, 130, 13, 163, 123, 121, 110, 142, 151,
	115, 13, 15, 33, 173, 102, 87, 76, 169, 95,
	69, 98, 154, 61, 26, 3, 139, 6, 22, 6,
	104, 72, 114, 148, 38, 139, 129, 0, 131, 147,
	150, 125, 49, 86, 0, 104, 128, 146, 133, 25,
	162, 24, 124, 33, 104, 94, 29, 69, 100, 51,
	68, 22, 116, 8, 170, 154, 147, 117, 154, 104,
	91, 123, 47, 140, 27, 47, 62, 147, 11, 21,
	172, 173, 38, 123, 25, 142, 43, 54, 30, 135,
	97, 98, 157, 31, 98, 146, 11, 71, 89, 158,
	168, 6, 107, 33, 139, 126, 73, 27, 99, 84,
	41, 97, 76, 71, 46, 101, 35, 84, 130, 72,
	138, 141, 92, 109, 173, 35, 40, 105, 22, 72,
	30, 92, 34, 127, 34, 169, 107, 75, 14, 37,
	82, 64, 92, 150, 57, 16, 1, 84, 100, 131,
	156, 56, 90, 67, 157, 89, 94, 23, 20, 108,
	95, 43, 26, 130, 170, 52, 125, 96, 127, 132,
	125, 27, 22, 44, 3, 71, 60, 171, 155, 152,
	128, 130, 34, 45, 23, 10, 126, 117, 33, 139,
	43, 121, 8, 69, 69, 170, 113, 12, 92, 66,
	144, 44, 86, 158, 88, 81, 55, 6, 17, 1,
	14, 153, 119, 148, 30, 49, 44, 92, 166, 72,
	65, 27, 43, 107, 15, 103, 134, 39, 48, 95,
	61, 51, 87, 147, 98, 42, 151, 135, 40, 168,
	136, 54, 139, 73, 20, 162, 114, 65, 80, 106,
	129, 146, 125, 172, 71, 141, 93, 24, 172, 142,
	119, 51, 11, 32, 25, 109, 66, 2, 62, 106,
	170, 24, 152, 135, 89, 165, 123, 29, 56, 22,
	136, 11, 160, 79, 2, 57, 46, 95, 81, 37,
	55, 18, 88, 66, 43, 105, 168, 109, 90, 151,
	91, 150, 158, 139, 86, 106, 5, 34, 142, 102,
	30, 164, 114, 6, 21, 38, 149, 135, 102, 48,
	15, 64, 56, 60, 9, 171, 101, 146, 131, 9,
	115, 40, 160, 100, 6, 72, 24, 3, 98, 167,
	106, 120, 149, 46, 126, 162, 76, 101, 115, 4,
	141, 130, 69, 23, 9, 78, 12, 110, 42, 136,
	120, 149, 2, 98, 75, 0, 162, 92, 4, 87,
	85, 102, 33, 52, 148, 152, 40, 50, 79, 156,
	47, 39, 112, 116, 62, 113, 12, 67, 50, 2,
	35, 144, 163, 165, 98, 13, 39, 6, 68, 86,
	4, 66, 6, 160, 117, 159, 141, 136, 59, 111,
	141, 152, 69, 128, 16, 172, 87, 16, 7, 131,
	18, 42, 101, 173, 25, 25, 4, 57, 31, 65,
	143, 27, 123, 149, 6, 66, 127, 139, 20, 4,
	76, 162, 156, 138, 116, 173, 136, 21, 7, 136,
	152, 17, 170, 80, 8, 14, 97, 4, 71, 121,
	69, 40, 140, 11, 7, 146, 69, 126, 112, 90,
	130, 6, 78, 113, 144, 12, 104, 99, 26, 103,
	78, 126, 155, 56, 44, 72, 163, 56, 44, 167,
	133, 97, 149, 14, 111, 146, 4, 107, 137, 130,
	79, 130, 134, 124, 149, 82, 151, 11, 21, 27,
	24, 100, 146, 172, 156, 16, 70, 145, 72, 106,
	130, 24, 29, 98, 38, 140, 70, 34, 74, 25,
	165, 153, 155, 117, 103, 130, 17, 73, 134, 38,
	92, 150, 130, 64, 148, 104, 80, 36, 68, 145,
	142, 24, 169, 172, 114, 25, 130, 10, 60, 30,
	36, 43, 2, 17, 152, 97, 140, 169, 162, 92,
	33, 57, 116, 130, 127, 151, 51, 114, 88, 16,
	145, 62, 36, 54, 9, 19, 18, 100, 26, 93,
	124, 41, 1, 95, 7, 173, 40, 67, 128, 38,
	84, 28, 88, 19, 158, 41, 170, 27, 156, 76,
	43, 119, 138, 80, 173, 140, 99, 17, 66, 125,
	102, 8, 159, 96, 103, 166, 95, 135, 51, 50,
	0, 128, 70, 80, 147, 46, 121, 135, 73, 95,
	30, 108, 40, 160, 14, 40, 126, 106, 49, 10,
	49, 152, 18, 26, 74, 113, 11, 161, 75, 54,
	29, 67, 149, 120, 83, 107, 61, 168, 106, 88,
	90, 20, 67, 78, 75, 22, 166, 109, 118, 143,
	126, 172, 15, 150, 50, 161, 36, 90, 69, 94,
	121, 164, 64, 96, 110, 139, 21, 164, 125, 120,
	78, 41, 132, 145, 120, 33, 160, 112, 135, 96,
	73, 79, 94, 88, 47, 145, 68, 75, 53, 129,
	170, 1, 119, 52, 89, 56, 17, 103, 46, 142,
	49, 116, 9, 173, 79, 129, 25, 65, 60, 160,
	161, 133, 57, 74, 40, 104, 45, 100, 172, 90,
	55, 168, 91, 31, 34, 158, 99, 144, 21, 153,
	69, 128, 72, 76, 30, 74, 127, 15, 68, 118,
	160, 50, 162, 118, 120, 74, 53, 138, 28, 77,
	109, 144, 121, 111, 167, 147, 87, 93, 118, 108,
	64, 5, 54, 136, 81, 85, 37, 26, 92, 97,
	144, 70, 148, 124, 14, 86, 25, 60, 50, 53,
	137, 152, 24, 76, 81, 9, 50, 169, 102, 160,
	95, 167, 165, 150, 121, 64, 53, 150, 90, 137,
	74, 52, 33, 40, 2, 47, 126, 19, 99, 168,
	73, 55, 146, 89, 28, 32, 141, 58, 18, 52,
	80, 98, 135, 114, 62, 125, 16, 158, 41, 81,
	5, 57, 15, 98, 138, 89, 83, 85, 11, 139,
	115, 78, 110, 56, 160, 139, 81, 120, 15, 99,
	172, 88, 15, 133, 28, 70, 76, 36, 46, 109,
	109, 51, 158, 124, 141, 122, 32, 51, 26, 43,
	16, 141, 113, 118, 16, 92, 75, 97, 38, 83,
	22, 28, 171, 29, 153, 17, 99, 56, 53, 145,
	165, 162, 14, 150, 105, 156, 98, 137, 33, 116,
	172, 41, 76, 103, 159, 143, 154, 107, 37, 56,
	58, 111, 38, 89, 19, 173, 92, 14, 101, 22,
	17, 98, 113, 167, 39, 86, 10, 56, 87, 7,
	70, 136, 110, 99, 43, 71, 68, 15, 5, 98,
	63, 63, 35, 101, 152, 54, 93, 63, 60, 20,
	85, 69, 111, 16, 63, 150, 95, 65, 25, 8,
	72, 95, 144, 1, 12, 5, 72, 73, 12, 69,
	171, 76, 132, 32, 169, 103, 78, 88, 166, 130,
	101, 69, 25, 38, 85, 80, 6, 172, 137, 31,
	6, 28, 119, 142, 29, 131, 150, 125, 99, 56,
	47, 41, 39, 24, 156, 51, 64, 76, 43, 164,
	147, 135, 100, 80, 50, 153, 50, 82, 129, 120,
	123, 147, 39, 117, 153, 156, 39, 121, 107, 139,
	169, 147, 6, 34, 163, 163, 77, 53, 65, 112,
	36, 30, 73, 136, 111, 116, 115, 153, 24, 63,
	99, 140, 28, 131, 75, 173, 113, 115, 121, 47,
	80, 116, 12, 86, 143, 1, 67, 38, 46, 124,
	143, 82, 155, 34, 36, 84, 150, 144, 63, 167,
	33, 154, 125, 61, 111, 26, 60, 91, 7, 24,
	15, 149, 159, 122, 158, 139, 70, 68, 157, 52,
	5, 119, 76, 144, 75, 27, 98, 98, 58, 60,
	38, 169, 45, 169, 14, 114, 160, 61, 31, 160,
	77, 38, 135, 62, 160, 111, 20, 48, 171, 169,
	101, 2, 106, 169, 139, 7, 22, 55, 105, 80,
	115, 135, 76, 161, 123, 82, 93, 101, 143, 116,
	87, 47, 146, 41, 101, 124, 144, 113, 173, 142,
	108, 92, 136, 40, 87, 93, 40, 101, 148, 137,
	8, 90, 99, 76, 77, 48, 150, 162, 52, 19,
	23, 35, 36, 85, 120, 57, 151, 132, 156, 113,
	110, 27, 160, 105, 14, 28, 44, 29, 80, 33,
	6, 142, 121, 123, 55, 125, 71, 14, 132, 123,
	33, 148, 150, 62, 59, 96, 111, 28, 47, 94,
	141, 157, 113, 128, 80, 120, 156, 125, 141, 54,
	158, 147, 14, 98, 88, 70, 49, 159, 84, 0,
	101, 117, 148, 77, 171, 33, 166, 109, 62, 39,
	21, 29, 22, 126, 157, 102, 72, 132, 45, 40,
	12, 30, 5, 27, 120, 94, 97, 169, 71, 
};

static int T2[] = {
	75, 70, 58, 153, 144, 3, 90, 167, 118, 1,
	48, 152, 156, 165, 59, 16, 172, 39, 69, 70,
	124, 24, 66, 66, 145, 66, 62, 133, 128, 78,
	73, 21, 140, 131, 0, 103, 126, 91, 96, 70,
	84, 144, 48, 58, 135, 99, 75, 126, 131, 136,
	14, 81, 160, 80, 139, 123, 138, 27, 83, 92,
	98, 156, 113, 56, 105, 106, 159, 57, 15, 82,
	119, 91, 44, 160, 149, 172, 85, 42, 124, 42,
	4, 130, 115, 156, 36, 80, 98, 1, 100, 7,
	85, 63, 131, 16, 31, 161, 39, 164, 25, 80,
	97, 4, 167, 161, 173, 109, 149, 141, 86, 138,
	78, 116, 106, 131, 98, 102, 33, 55, 150, 14,
	118, 129, 77, 67, 138, 100, 54, 3, 90, 79,
	83, 5, 76, 76, 159, 67, 4, 126, 27, 90,
	90, 105, 32, 23, 54, 123, 117, 87, 4, 85,
	101, 114, 41, 170, 7, 5, 96, 61, 0, 4,
	132, 83, 9, 34, 151, 160, 102, 155, 112, 121,
	71, 21, 52, 96, 44, 98, 45, 153, 11, 41,
	65, 104, 48, 12, 95, 119, 50, 44, 48, 12,
	49, 1, 8, 64, 143, 58, 89, 40, 44, 68,
	96, 115, 55, 112, 116, 58, 2, 148, 19, 111,
	19, 42, 62, 59, 55, 157, 4, 97, 20, 44,
	109, 69, 46, 117, 125, 15, 167, 32, 56, 37,
	101, 144, 152, 148, 75, 86, 32, 69, 53, 43,
	6, 72, 78, 61, 131, 125, 36, 127, 48, 56,
	172, 149, 118, 44, 84, 61, 59, 77, 86, 107,
	115, 13, 70, 85, 153, 145, 172, 12, 40, 51,
	47, 38, 115, 79, 70, 153, 84, 26, 70, 131,
	120, 164, 107, 39, 16, 59, 141, 77, 71, 168,
	159, 36, 95, 110, 64, 137, 6, 86, 105, 76,
	78, 68, 33, 49, 147, 103, 28, 58, 121, 91,
	15, 67, 81, 123, 99, 89, 0, 58, 167, 63,
	44, 144, 91, 139, 72, 156, 94, 70, 68, 17,
	147, 139, 85, 6, 6, 58, 109, 35, 108, 49,
	118, 116, 108, 17, 57, 33, 99, 57, 83, 84,
	113, 127, 54, 30, 84, 119, 12, 170, 15, 73,
	13, 162, 30, 98, 114, 137, 46, 27, 36, 33,
	97, 66, 123, 112, 36, 1, 170, 18, 139, 19,
	80, 170, 120, 171, 133, 36, 147, 135, 129, 54,
	57, 18, 41, 30, 139, 147, 160, 11, 1, 22,
	44, 90, 80, 159, 20, 108, 160, 8, 119, 118,
	27, 17, 114, 148, 14, 65, 2, 153, 18, 123,
	33, 75, 141, 66, 98, 106, 39, 76, 117, 32,
	98, 153, 123, 170, 130, 135, 104, 108, 144, 49,
	44, 171, 58, 158, 137, 72, 41, 139, 43, 60,
	88, 68, 127, 55, 134, 131, 4, 48, 70, 112,
	157, 29, 149, 9, 118, 156, 115, 120, 31, 110,
	10, 49, 11, 166, 125, 94, 33, 127, 140, 44,
	161, 17, 102, 34, 126, 141, 157, 122, 7, 53,
	60, 164, 75, 27, 173, 19, 9, 114, 139, 32,
	42, 150, 81, 54, 134, 33, 140, 160, 152, 107,
	30, 131, 116, 124, 157, 60, 84, 140, 9, 91,
	20, 61, 82, 87, 81, 81, 106, 82, 14, 71,
	115, 48, 39, 14, 102, 166, 39, 61, 152, 10,
	168, 0, 141, 110, 124, 117, 30, 9, 139, 142,
	120, 81, 42, 50, 64, 1, 170, 157, 55, 5,
	169, 95, 22, 126, 170, 101, 64, 100, 69, 10,
	90, 63, 72, 115, 167, 23, 168, 15, 24, 126,
	158, 145, 25, 26, 13, 90, 27, 9, 65, 74,
	15, 60, 170, 29, 12, 158, 130, 68, 76, 17,
	79, 166, 81, 143, 99, 74, 166, 94, 81, 9,
	38, 65, 154, 63, 83, 159, 145, 103, 168, 37,
	3, 1, 89, 165, 23, 94, 150, 153, 162, 52,
	171, 67, 37, 70, 36, 136, 136, 149, 57, 42,
	83, 35, 129, 68, 145, 51, 145, 54, 146, 52,
	11, 75, 144, 135, 100, 18, 131, 167, 168, 158,
	117, 131, 135, 110, 8, 125, 80, 98, 100, 129,
	133, 9, 164, 80, 69, 127, 131, 41, 0, 95,
	93, 11, 171, 63, 138, 89, 73, 96, 83, 67,
	72, 26, 25, 33, 128, 25, 158, 34, 115, 84,
	163, 66, 85, 146, 146, 154, 99, 96, 13, 99,
	17, 98, 102, 14, 153, 59, 104, 52, 147, 5,
	112, 45, 31, 129, 78, 159, 154, 54, 137, 33,
	160, 61, 91, 16, 50, 96, 12, 168, 98, 31,
	69, 11, 34, 61, 86, 127, 51, 155, 116, 58,
	124, 113, 31, 18, 78, 160, 28, 131, 158, 166,
	156, 144, 53, 65, 153, 104, 154, 157, 90, 78,
	6, 159, 81, 40, 47, 167, 167, 90, 140, 102,
	149, 90, 41, 6, 108, 111, 158, 129, 60, 134,
	121, 34, 97, 166, 92, 76, 88, 72, 51, 5,
	150, 57, 164, 57, 98, 29, 42, 83, 120, 8,
	11, 87, 91, 44, 93, 17, 148, 70, 146, 41,
	103, 20, 37, 25, 173, 125, 68, 137, 21, 131,
	24, 91, 126, 169, 131, 93, 109, 35, 48, 1,
	154, 132, 150, 90, 105, 153, 164, 7, 71, 100,
	40, 167, 112, 69, 10, 111, 20, 79, 75, 41,
	28, 99, 133, 154, 86, 82, 73, 21, 109, 113,
	14, 90, 71, 165, 172, 168, 144, 162, 167, 34,
	80, 26, 19, 18, 95, 29, 122, 116, 100, 23,
	157, 128, 114, 108, 100, 18, 16, 165, 39, 126,
	104, 46, 34, 167, 29, 24, 153, 173, 12, 147,
	157, 26, 33, 53, 113, 53, 11, 129, 53, 79,
	54, 6, 6, 58, 82, 171, 171, 34, 5, 36,
	118, 32, 150, 121, 84, 108, 123, 84, 132, 21,
	57, 107, 47, 90, 153, 152, 144, 156, 107, 15,
	61, 153, 21, 67, 37, 96, 57, 26, 122, 62,
	62, 66, 86, 38, 6, 170, 138, 121, 80, 97,
	142, 137, 22, 15, 54, 1, 159, 16, 157, 92,
	31, 37, 72, 45, 104, 101, 133, 153, 128, 81,
	34, 16, 139, 120, 47, 145, 117, 11, 84, 23,
	100, 67, 25, 158, 171, 77, 149, 65, 29, 90,
	84, 62, 20, 159, 96, 130, 117, 68, 18, 114,
	90, 133, 26, 26, 28, 158, 156, 12, 16, 155,
	131, 105, 40, 148, 81, 29, 43, 56, 94, 72,
	139, 4, 134, 159, 155, 49, 107, 91, 117, 125,
	31, 33, 85, 49, 51, 113, 25, 34, 117, 41,
	7, 66, 139, 48, 32, 38, 77, 75, 87, 164,
	140, 52, 160, 100, 29, 142, 141, 136, 59, 85,
	80, 82, 110, 165, 132, 162, 96, 149, 14, 31,
	9, 21, 101, 26, 156, 101, 91, 170, 78, 13,
	19, 42, 21, 119, 156, 130, 128, 131, 64, 89,
	32, 50, 90, 31, 113, 78, 166, 110, 52, 65,
	109, 90, 95, 37, 108, 70, 138, 25, 66, 34,
	30, 85, 76, 51, 22, 58, 8, 142, 8, 64,
	49, 40, 106, 140, 63, 45, 44, 56, 148, 88,
	121, 83, 5, 35, 120, 105, 105, 84, 131, 163,
	110, 153, 66, 13, 23, 80, 63, 23, 48, 63,
	87, 90, 96, 19, 56, 159, 57, 100, 33, 31,
	15, 147, 114, 125, 30, 118, 126, 128, 61, 68,
	157, 65, 50, 136, 22, 72, 34, 54, 147, 49,
	69, 131, 0, 131, 58, 97, 143, 67, 95, 114,
	48, 25, 156, 54, 143, 13, 172, 95, 133, 52,
	155, 116, 117, 31, 70, 131, 103, 96, 12, 69,
	145, 81, 26, 138, 30, 84, 61, 173, 143, 149,
	106, 18, 0, 88, 64, 143, 93, 62, 56, 53,
	114, 38, 161, 50, 69, 50, 7, 165, 146, 11,
	60, 110, 92, 86, 74, 114, 162, 127, 106, 132,
	102, 38, 142, 95, 90, 6, 121, 133, 122, 54,
	167, 161, 142, 71, 144, 36, 89, 64, 125, 139,
	8, 115, 123, 55, 81, 41, 29, 103, 120, 13,
	122, 31, 73, 92, 13, 156, 98, 126, 115, 46,
	6, 108, 34, 149, 6, 170, 3, 87, 61, 128,
	52, 61, 61, 167, 116, 143, 35, 137, 72, 147,
	142, 12, 171, 42, 104, 10, 24, 28, 128, 131,
	67, 134, 57, 93, 101, 55, 89, 104, 142, 142,
	50, 13, 29, 112, 6, 145, 73, 33, 100, 137,
	7, 69, 150, 4, 111, 67, 133, 114, 109, 44,
	36, 26, 78, 33, 132, 8, 137, 96, 150, 108,
	63, 135, 57, 51, 19, 126, 151, 114, 158, 78,
	68, 78, 111, 22, 105, 21, 82, 64, 135, 17,
	100, 172, 35, 4, 23, 167, 12, 152, 89, 162,
	86, 144, 115, 136, 13, 135, 80, 165, 67, 64,
	69, 135, 142, 173, 157, 65, 20, 57, 121, 156,
	66, 47, 146, 102, 51, 161, 87, 63, 139, 3,
	44, 43, 139, 151, 171, 153, 112, 70, 136, 5,
	134, 31, 140, 95, 30, 116, 60, 150, 67, 127,
	43, 163, 11, 94, 50, 84, 6, 80, 51, 55,
	103, 170, 2, 117, 37, 137, 9, 77, 163, 157,
	101, 67, 128, 47, 34, 44, 162, 86, 12, 47,
	39, 47, 37, 42, 134, 79, 119, 140, 151, 170,
	21, 81, 158, 15, 16, 14, 152, 25, 91, 133,
	0, 10, 19, 129, 57, 45, 165, 37, 132, 169,
	84, 163, 42, 121, 32, 2, 19, 143, 135, 170,
	139, 156, 69, 116, 164, 85, 130, 134, 103, 39,
	94, 95, 49, 105, 50, 98, 150, 78, 57, 121,
	100, 128, 15, 117, 66, 147, 49, 154, 83, 130,
	17, 42, 7, 48, 128, 133, 117, 109, 87, 10,
	134, 37, 31, 159, 141, 45, 9, 71, 115, 66,
	10, 41, 12, 25, 150, 71, 172, 26, 51, 73,
	148, 60, 116, 147, 100, 62, 106, 43, 171, 12,
	53, 124, 41, 77, 109, 8, 122, 119, 71, 55,
	3, 81, 96, 16, 98, 73, 79, 88, 91, 130,
	162, 65, 8, 96, 39, 109, 158, 137, 152, 155,
	141, 32, 105, 0, 109, 33, 8, 49, 67, 37,
	87, 83, 142, 141, 71, 168, 58, 154, 107, 47,
	105, 79, 108, 165, 162, 85, 162, 55, 159, 150,
	32, 138, 127, 116, 26, 149, 13, 15, 48, 80,
	44, 135, 155, 4, 102, 52, 172, 152, 32, 105,
	25, 129, 3, 125, 120, 157, 36, 100, 30, 21,
	76, 63, 152, 30, 5, 4, 171, 10, 11, 45,
	83, 47, 172, 64, 52, 93, 109, 42, 71, 133,
	140, 97, 89, 143, 40, 27, 126, 77, 120, 157,
	98, 22, 38, 68, 44, 35, 73, 34, 45, 
};

#define uchar unsigned char

int
creature_names_hash(const uchar *key)
{
	int i;
	unsigned f0, f1, f2;
	const uchar *kp = key;

	for (i=-32, f0=f1=f2=0; *kp; ++kp) {
		if (*kp < 32 || *kp > 122)
			return -1;
		if (kp-key > 18)
			return -1;
		f0 += T0[i + *kp];
		f1 += T1[i + *kp];
		f2 += T2[i + *kp];
		i += 91;
	}

	if (kp-key < 3)
		return -1;

	f0 %= 174;
	f1 %= 174;
	f2 %= 174;

	if (f1 == f0 && ++f1 >= 174)
		f1 = 0;
	if (f2 == f0 && ++f2 >= 174)
		f2 = 0;
	if (f1 == f2) {
		if (++f2 >= 174)
			f2 = 0;
		if (f2 == f0 && ++f2 >= 174)
			f2 = 0;
	}

	return g[f0] + g[f1] + g[f2];
}