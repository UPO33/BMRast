#include "Surface.h"
#include <algorithm>
#include <cmath>

struct rgb_t
{
	unsigned char   red;
	unsigned char green;
	unsigned char  blue;
};

const rgb_t jet_colormap[1000] = {
	{ 29,   0, 102}, { 23,   0, 107}, { 17,   0, 112}, { 12,   0, 117}, {  6,   0, 122},
	{  0,   0, 127}, {  0,   0, 128}, {  0,   0, 129}, {  0,   0, 129}, {  0,   0, 130},
	{  0,   0, 131}, {  0,   0, 132}, {  0,   0, 133}, {  0,   0, 133}, {  0,   0, 134},
	{  0,   0, 135}, {  0,   0, 136}, {  0,   0, 137}, {  0,   0, 138}, {  0,   0, 140},
	{  0,   0, 141}, {  0,   0, 142}, {  0,   0, 143}, {  0,   0, 145}, {  0,   0, 146},
	{  0,   0, 147}, {  0,   0, 148}, {  0,   0, 150}, {  0,   0, 151}, {  0,   0, 152},
	{  0,   0, 153}, {  0,   0, 154}, {  0,   0, 156}, {  0,   0, 157}, {  0,   0, 158},
	{  0,   0, 159}, {  0,   0, 160}, {  0,   0, 161}, {  0,   0, 163}, {  0,   0, 164},
	{  0,   0, 165}, {  0,   0, 166}, {  0,   0, 168}, {  0,   0, 169}, {  0,   0, 170},
	{  0,   0, 171}, {  0,   0, 173}, {  0,   0, 174}, {  0,   0, 175}, {  0,   0, 176},
	{  0,   0, 178}, {  0,   0, 179}, {  0,   0, 180}, {  0,   0, 181}, {  0,   0, 183},
	{  0,   0, 184}, {  0,   0, 185}, {  0,   0, 186}, {  0,   0, 188}, {  0,   0, 189},
	{  0,   0, 190}, {  0,   0, 191}, {  0,   0, 193}, {  0,   0, 194}, {  0,   0, 195},
	{  0,   0, 196}, {  0,   0, 197}, {  0,   0, 198}, {  0,   0, 200}, {  0,   0, 201},
	{  0,   0, 202}, {  0,   0, 203}, {  0,   0, 204}, {  0,   0, 206}, {  0,   0, 207},
	{  0,   0, 208}, {  0,   0, 209}, {  0,   0, 211}, {  0,   0, 212}, {  0,   0, 213},
	{  0,   0, 214}, {  0,   0, 216}, {  0,   0, 217}, {  0,   0, 218}, {  0,   0, 219},
	{  0,   0, 221}, {  0,   0, 222}, {  0,   0, 223}, {  0,   0, 225}, {  0,   0, 226},
	{  0,   0, 227}, {  0,   0, 228}, {  0,   0, 230}, {  0,   0, 231}, {  0,   0, 232},
	{  0,   0, 233}, {  0,   0, 234}, {  0,   0, 234}, {  0,   0, 235}, {  0,   0, 236},
	{  0,   0, 237}, {  0,   0, 238}, {  0,   0, 239}, {  0,   0, 239}, {  0,   0, 240},
	{  0,   0, 241}, {  0,   0, 242}, {  0,   0, 243}, {  0,   0, 244}, {  0,   0, 246},
	{  0,   0, 247}, {  0,   0, 248}, {  0,   0, 249}, {  0,   0, 250}, {  0,   0, 251},
	{  0,   0, 253}, {  0,   0, 254}, {  0,   0, 254}, {  0,   0, 254}, {  0,   0, 254},
	{  0,   0, 254}, {  0,   0, 254}, {  0,   0, 255}, {  0,   0, 255}, {  0,   0, 255},
	{  0,   0, 255}, {  0,   0, 255}, {  0,   0, 255}, {  0,   1, 255}, {  0,   1, 255},
	{  0,   2, 255}, {  0,   3, 255}, {  0,   3, 255}, {  0,   4, 255}, {  0,   5, 255},
	{  0,   6, 255}, {  0,   6, 255}, {  0,   7, 255}, {  0,   8, 255}, {  0,   9, 255},
	{  0,  10, 255}, {  0,  11, 255}, {  0,  12, 255}, {  0,  13, 255}, {  0,  14, 255},
	{  0,  15, 255}, {  0,  16, 255}, {  0,  17, 255}, {  0,  18, 255}, {  0,  19, 255},
	{  0,  21, 255}, {  0,  22, 255}, {  0,  23, 255}, {  0,  24, 255}, {  0,  25, 255},
	{  0,  26, 255}, {  0,  27, 255}, {  0,  28, 255}, {  0,  29, 255}, {  0,  30, 255},
	{  0,  31, 255}, {  0,  32, 255}, {  0,  34, 255}, {  0,  35, 255}, {  0,  36, 255},
	{  0,  37, 255}, {  0,  38, 255}, {  0,  39, 255}, {  0,  40, 255}, {  0,  41, 255},
	{  0,  42, 255}, {  0,  43, 255}, {  0,  44, 255}, {  0,  45, 255}, {  0,  46, 255},
	{  0,  48, 255}, {  0,  49, 255}, {  0,  50, 255}, {  0,  51, 255}, {  0,  52, 255},
	{  0,  53, 255}, {  0,  54, 255}, {  0,  55, 255}, {  0,  56, 255}, {  0,  57, 255},
	{  0,  58, 255}, {  0,  58, 255}, {  0,  59, 255}, {  0,  60, 255}, {  0,  60, 255},
	{  0,  61, 255}, {  0,  62, 255}, {  0,  63, 255}, {  0,  63, 255}, {  0,  64, 255},
	{  0,  65, 255}, {  0,  66, 255}, {  0,  67, 255}, {  0,  68, 255}, {  0,  69, 255},
	{  0,  71, 255}, {  0,  72, 255}, {  0,  73, 255}, {  0,  74, 255}, {  0,  75, 255},
	{  0,  76, 255}, {  0,  77, 255}, {  0,  78, 255}, {  0,  79, 255}, {  0,  80, 255},
	{  0,  81, 255}, {  0,  82, 255}, {  0,  84, 255}, {  0,  85, 255}, {  0,  86, 255},
	{  0,  87, 255}, {  0,  88, 255}, {  0,  89, 255}, {  0,  90, 255}, {  0,  91, 255},
	{  0,  92, 255}, {  0,  93, 255}, {  0,  94, 255}, {  0,  95, 255}, {  0,  96, 255},
	{  0,  98, 255}, {  0,  99, 255}, {  0, 100, 255}, {  0, 101, 255}, {  0, 102, 255},
	{  0, 103, 255}, {  0, 104, 255}, {  0, 105, 255}, {  0, 106, 255}, {  0, 107, 255},
	{  0, 108, 255}, {  0, 109, 255}, {  0, 111, 255}, {  0, 112, 255}, {  0, 113, 255},
	{  0, 114, 255}, {  0, 115, 255}, {  0, 116, 255}, {  0, 117, 255}, {  0, 118, 255},
	{  0, 119, 255}, {  0, 120, 255}, {  0, 121, 255}, {  0, 122, 255}, {  0, 123, 255},
	{  0, 125, 255}, {  0, 126, 255}, {  0, 127, 255}, {  0, 128, 255}, {  0, 129, 255},
	{  0, 130, 255}, {  0, 131, 255}, {  0, 132, 255}, {  0, 133, 255}, {  0, 134, 255},
	{  0, 135, 255}, {  0, 136, 255}, {  0, 138, 255}, {  0, 139, 255}, {  0, 140, 255},
	{  0, 141, 255}, {  0, 142, 255}, {  0, 143, 255}, {  0, 144, 255}, {  0, 145, 255},
	{  0, 146, 255}, {  0, 147, 255}, {  0, 148, 255}, {  0, 149, 255}, {  0, 150, 255},
	{  0, 150, 255}, {  0, 151, 255}, {  0, 152, 255}, {  0, 153, 255}, {  0, 153, 255},
	{  0, 154, 255}, {  0, 155, 255}, {  0, 155, 255}, {  0, 156, 255}, {  0, 157, 255},
	{  0, 158, 255}, {  0, 159, 255}, {  0, 161, 255}, {  0, 162, 255}, {  0, 163, 255},
	{  0, 164, 255}, {  0, 165, 255}, {  0, 166, 255}, {  0, 167, 255}, {  0, 168, 255},
	{  0, 169, 255}, {  0, 170, 255}, {  0, 171, 255}, {  0, 172, 255}, {  0, 173, 255},
	{  0, 175, 255}, {  0, 176, 255}, {  0, 177, 255}, {  0, 178, 255}, {  0, 179, 255},
	{  0, 180, 255}, {  0, 181, 255}, {  0, 182, 255}, {  0, 183, 255}, {  0, 184, 255},
	{  0, 185, 255}, {  0, 186, 255}, {  0, 188, 255}, {  0, 189, 255}, {  0, 190, 255},
	{  0, 191, 255}, {  0, 192, 255}, {  0, 193, 255}, {  0, 194, 255}, {  0, 195, 255},
	{  0, 196, 255}, {  0, 197, 255}, {  0, 198, 255}, {  0, 199, 255}, {  0, 200, 255},
	{  0, 202, 255}, {  0, 203, 255}, {  0, 204, 255}, {  0, 205, 255}, {  0, 206, 255},
	{  0, 207, 255}, {  0, 208, 255}, {  0, 209, 255}, {  0, 210, 255}, {  0, 211, 255},
	{  0, 212, 255}, {  0, 213, 255}, {  0, 215, 255}, {  0, 216, 255}, {  0, 217, 255},
	{  0, 218, 254}, {  0, 219, 253}, {  0, 220, 252}, {  0, 221, 252}, {  0, 222, 251},
	{  0, 223, 250}, {  0, 224, 250}, {  0, 225, 249}, {  0, 226, 248}, {  0, 227, 247},
	{  0, 229, 247}, {  1, 230, 246}, {  2, 231, 245}, {  3, 232, 244}, {  3, 233, 243},
	{  4, 234, 242}, {  5, 235, 241}, {  5, 236, 240}, {  6, 237, 239}, {  7, 238, 238},
	{  8, 239, 238}, {  8, 240, 237}, {  9, 241, 236}, { 10, 242, 236}, { 10, 242, 235},
	{ 11, 243, 235}, { 11, 244, 234}, { 12, 245, 234}, { 13, 245, 233}, { 13, 246, 232},
	{ 14, 247, 232}, { 15, 247, 231}, { 15, 248, 231}, { 16, 249, 230}, { 17, 249, 229},
	{ 18, 250, 228}, { 18, 251, 227}, { 19, 251, 226}, { 20, 252, 225}, { 21, 253, 224},
	{ 22, 253, 224}, { 23, 254, 223}, { 23, 254, 222}, { 24, 255, 221}, { 25, 255, 220},
	{ 26, 255, 219}, { 27, 255, 218}, { 28, 255, 218}, { 29, 255, 217}, { 30, 255, 216},
	{ 30, 255, 215}, { 31, 255, 214}, { 32, 255, 214}, { 33, 255, 213}, { 34, 255, 212},
	{ 35, 255, 211}, { 36, 255, 210}, { 37, 255, 209}, { 38, 255, 208}, { 39, 255, 207},
	{ 39, 255, 207}, { 40, 255, 206}, { 41, 255, 205}, { 42, 255, 204}, { 43, 255, 203},
	{ 44, 255, 202}, { 45, 255, 201}, { 46, 255, 200}, { 47, 255, 199}, { 48, 255, 198},
	{ 48, 255, 198}, { 49, 255, 197}, { 50, 255, 196}, { 51, 255, 195}, { 52, 255, 194},
	{ 53, 255, 193}, { 54, 255, 192}, { 55, 255, 191}, { 55, 255, 191}, { 56, 255, 190},
	{ 57, 255, 189}, { 58, 255, 188}, { 59, 255, 187}, { 60, 255, 186}, { 60, 255, 186},
	{ 61, 255, 185}, { 62, 255, 184}, { 63, 255, 183}, { 64, 255, 182}, { 65, 255, 181},
	{ 65, 255, 181}, { 66, 255, 180}, { 67, 255, 179}, { 68, 255, 178}, { 69, 255, 177},
	{ 70, 255, 176}, { 71, 255, 175}, { 72, 255, 174}, { 73, 255, 173}, { 74, 255, 172},
	{ 74, 255, 172}, { 75, 255, 171}, { 76, 255, 170}, { 77, 255, 169}, { 78, 255, 168},
	{ 79, 255, 167}, { 80, 255, 166}, { 81, 255, 165}, { 82, 255, 164}, { 83, 255, 163},
	{ 83, 255, 163}, { 84, 255, 162}, { 84, 255, 162}, { 85, 255, 161}, { 85, 255, 161},
	{ 86, 255, 160}, { 87, 255, 159}, { 87, 255, 159}, { 88, 255, 158}, { 88, 255, 158},
	{ 89, 255, 157}, { 89, 255, 157}, { 90, 255, 156}, { 91, 255, 155}, { 92, 255, 154},
	{ 93, 255, 153}, { 94, 255, 152}, { 95, 255, 151}, { 96, 255, 150}, { 97, 255, 149},
	{ 97, 255, 149}, { 98, 255, 148}, { 99, 255, 147}, {100, 255, 146}, {101, 255, 145},
	{102, 255, 144}, {102, 255, 143}, {103, 255, 142}, {104, 255, 141}, {105, 255, 140},
	{106, 255, 140}, {107, 255, 139}, {107, 255, 138}, {108, 255, 137}, {109, 255, 136},
	{110, 255, 135}, {111, 255, 134}, {112, 255, 134}, {113, 255, 133}, {114, 255, 132},
	{114, 255, 131}, {115, 255, 130}, {116, 255, 130}, {117, 255, 129}, {118, 255, 128},
	{119, 255, 127}, {120, 255, 126}, {121, 255, 125}, {122, 255, 124}, {123, 255, 123},
	{123, 255, 123}, {124, 255, 122}, {125, 255, 121}, {126, 255, 120}, {127, 255, 119},
	{128, 255, 118}, {129, 255, 117}, {130, 255, 116}, {130, 255, 115}, {131, 255, 114},
	{132, 255, 114}, {133, 255, 113}, {134, 255, 112}, {134, 255, 111}, {135, 255, 110},
	{136, 255, 109}, {137, 255, 108}, {138, 255, 107}, {139, 255, 107}, {140, 255, 106},
	{140, 255, 105}, {141, 255, 104}, {142, 255, 103}, {143, 255, 102}, {144, 255, 102},
	{145, 255, 101}, {146, 255, 100}, {147, 255,  99}, {148, 255,  98}, {149, 255,  97},
	{149, 255,  97}, {150, 255,  96}, {151, 255,  95}, {152, 255,  94}, {153, 255,  93},
	{154, 255,  92}, {155, 255,  91}, {156, 255,  90}, {157, 255,  89}, {157, 255,  89},
	{158, 255,  88}, {158, 255,  88}, {159, 255,  87}, {159, 255,  87}, {160, 255,  86},
	{161, 255,  85}, {161, 255,  85}, {162, 255,  84}, {162, 255,  84}, {163, 255,  83},
	{163, 255,  83}, {164, 255,  82}, {165, 255,  81}, {166, 255,  80}, {167, 255,  79},
	{168, 255,  78}, {169, 255,  77}, {170, 255,  76}, {171, 255,  75}, {172, 255,  74},
	{172, 255,  74}, {173, 255,  73}, {174, 255,  72}, {175, 255,  71}, {176, 255,  70},
	{177, 255,  69}, {178, 255,  68}, {179, 255,  67}, {180, 255,  66}, {181, 255,  65},
	{181, 255,  65}, {182, 255,  64}, {183, 255,  63}, {184, 255,  62}, {185, 255,  61},
	{186, 255,  60}, {186, 255,  60}, {187, 255,  59}, {188, 255,  58}, {189, 255,  57},
	{190, 255,  56}, {191, 255,  55}, {191, 255,  55}, {192, 255,  54}, {193, 255,  53},
	{194, 255,  52}, {195, 255,  51}, {196, 255,  50}, {197, 255,  49}, {198, 255,  48},
	{198, 255,  48}, {199, 255,  47}, {200, 255,  46}, {201, 255,  45}, {202, 255,  44},
	{203, 255,  43}, {204, 255,  42}, {205, 255,  41}, {206, 255,  40}, {207, 255,  39},
	{207, 255,  39}, {208, 255,  38}, {209, 255,  37}, {210, 255,  36}, {211, 255,  35},
	{212, 255,  34}, {213, 255,  33}, {214, 255,  32}, {214, 255,  31}, {215, 255,  30},
	{216, 255,  30}, {217, 255,  29}, {218, 255,  28}, {218, 255,  27}, {219, 255,  26},
	{220, 255,  25}, {221, 255,  24}, {222, 255,  23}, {223, 255,  23}, {224, 255,  22},
	{224, 255,  21}, {225, 255,  20}, {226, 255,  19}, {227, 255,  18}, {228, 255,  18},
	{229, 255,  17}, {230, 255,  16}, {231, 255,  15}, {231, 255,  15}, {232, 255,  14},
	{232, 255,  13}, {233, 255,  13}, {234, 255,  12}, {234, 255,  11}, {235, 255,  11},
	{235, 255,  10}, {236, 255,  10}, {236, 255,   9}, {237, 255,   8}, {238, 254,   8},
	{238, 253,   7}, {239, 252,   6}, {240, 251,   5}, {241, 250,   5}, {242, 249,   4},
	{243, 248,   3}, {244, 247,   3}, {245, 246,   2}, {246, 246,   1}, {247, 245,   0},
	{247, 243,   0}, {248, 242,   0}, {249, 242,   0}, {250, 241,   0}, {250, 240,   0},
	{251, 239,   0}, {252, 238,   0}, {252, 237,   0}, {253, 236,   0}, {254, 235,   0},
	{255, 234,   0}, {255, 233,   0}, {255, 232,   0}, {255, 231,   0}, {255, 230,   0},
	{255, 229,   0}, {255, 228,   0}, {255, 227,   0}, {255, 226,   0}, {255, 225,   0},
	{255, 224,   0}, {255, 223,   0}, {255, 222,   0}, {255, 221,   0}, {255, 220,   0},
	{255, 219,   0}, {255, 218,   0}, {255, 217,   0}, {255, 216,   0}, {255, 215,   0},
	{255, 214,   0}, {255, 213,   0}, {255, 212,   0}, {255, 211,   0}, {255, 210,   0},
	{255, 209,   0}, {255, 208,   0}, {255, 207,   0}, {255, 206,   0}, {255, 205,   0},
	{255, 204,   0}, {255, 203,   0}, {255, 202,   0}, {255, 201,   0}, {255, 200,   0},
	{255, 199,   0}, {255, 198,   0}, {255, 197,   0}, {255, 196,   0}, {255, 195,   0},
	{255, 194,   0}, {255, 193,   0}, {255, 192,   0}, {255, 191,   0}, {255, 190,   0},
	{255, 189,   0}, {255, 188,   0}, {255, 187,   0}, {255, 186,   0}, {255, 185,   0},
	{255, 184,   0}, {255, 183,   0}, {255, 182,   0}, {255, 180,   0}, {255, 179,   0},
	{255, 178,   0}, {255, 177,   0}, {255, 176,   0}, {255, 176,   0}, {255, 175,   0},
	{255, 175,   0}, {255, 174,   0}, {255, 173,   0}, {255, 173,   0}, {255, 172,   0},
	{255, 171,   0}, {255, 171,   0}, {255, 170,   0}, {255, 169,   0}, {255, 168,   0},
	{255, 167,   0}, {255, 166,   0}, {255, 165,   0}, {255, 164,   0}, {255, 163,   0},
	{255, 162,   0}, {255, 161,   0}, {255, 160,   0}, {255, 159,   0}, {255, 158,   0},
	{255, 157,   0}, {255, 156,   0}, {255, 155,   0}, {255, 154,   0}, {255, 153,   0},
	{255, 152,   0}, {255, 151,   0}, {255, 150,   0}, {255, 150,   0}, {255, 149,   0},
	{255, 147,   0}, {255, 146,   0}, {255, 146,   0}, {255, 145,   0}, {255, 144,   0},
	{255, 143,   0}, {255, 142,   0}, {255, 141,   0}, {255, 140,   0}, {255, 139,   0},
	{255, 138,   0}, {255, 137,   0}, {255, 136,   0}, {255, 135,   0}, {255, 134,   0},
	{255, 133,   0}, {255, 132,   0}, {255, 131,   0}, {255, 130,   0}, {255, 129,   0},
	{255, 128,   0}, {255, 127,   0}, {255, 126,   0}, {255, 125,   0}, {255, 124,   0},
	{255, 123,   0}, {255, 122,   0}, {255, 121,   0}, {255, 120,   0}, {255, 119,   0},
	{255, 118,   0}, {255, 117,   0}, {255, 116,   0}, {255, 115,   0}, {255, 114,   0},
	{255, 113,   0}, {255, 112,   0}, {255, 111,   0}, {255, 109,   0}, {255, 108,   0},
	{255, 107,   0}, {255, 106,   0}, {255, 105,   0}, {255, 104,   0}, {255, 103,   0},
	{255, 102,   0}, {255, 101,   0}, {255, 100,   0}, {255,  99,   0}, {255,  98,   0},
	{255,  97,   0}, {255,  96,   0}, {255,  95,   0}, {255,  94,   0}, {255,  93,   0},
	{255,  92,   0}, {255,  91,   0}, {255,  91,   0}, {255,  90,   0}, {255,  90,   0},
	{255,  89,   0}, {255,  88,   0}, {255,  88,   0}, {255,  87,   0}, {255,  86,   0},
	{255,  86,   0}, {255,  85,   0}, {255,  84,   0}, {255,  83,   0}, {255,  82,   0},
	{255,  81,   0}, {255,  80,   0}, {255,  79,   0}, {255,  78,   0}, {255,  77,   0},
	{255,  76,   0}, {255,  75,   0}, {255,  74,   0}, {255,  73,   0}, {255,  72,   0},
	{255,  71,   0}, {255,  70,   0}, {255,  69,   0}, {255,  68,   0}, {255,  67,   0},
	{255,  66,   0}, {255,  65,   0}, {255,  64,   0}, {255,  63,   0}, {255,  62,   0},
	{255,  61,   0}, {255,  60,   0}, {255,  59,   0}, {255,  58,   0}, {255,  57,   0},
	{255,  56,   0}, {255,  55,   0}, {255,  54,   0}, {255,  54,   0}, {255,  53,   0},
	{255,  51,   0}, {255,  50,   0}, {255,  49,   0}, {255,  48,   0}, {255,  47,   0},
	{255,  46,   0}, {255,  45,   0}, {255,  44,   0}, {255,  43,   0}, {255,  42,   0},
	{255,  41,   0}, {255,  40,   0}, {255,  39,   0}, {255,  38,   0}, {255,  37,   0},
	{255,  36,   0}, {255,  35,   0}, {255,  34,   0}, {255,  33,   0}, {255,  32,   0},
	{255,  31,   0}, {255,  30,   0}, {255,  29,   0}, {255,  28,   0}, {255,  27,   0},
	{255,  26,   0}, {255,  25,   0}, {255,  24,   0}, {254,  23,   0}, {254,  22,   0},
	{254,  21,   0}, {254,  20,   0}, {254,  19,   0}, {254,  18,   0}, {253,  17,   0},
	{251,  16,   0}, {250,  15,   0}, {249,  14,   0}, {248,  13,   0}, {247,  12,   0},
	{246,  11,   0}, {244,  10,   0}, {243,   9,   0}, {242,   8,   0}, {241,   7,   0},
	{240,   6,   0}, {239,   6,   0}, {239,   5,   0}, {238,   4,   0}, {237,   4,   0},
	{236,   3,   0}, {235,   3,   0}, {234,   2,   0}, {234,   1,   0}, {233,   1,   0},
	{232,   0,   0}, {231,   0,   0}, {230,   0,   0}, {228,   0,   0}, {227,   0,   0},
	{226,   0,   0}, {225,   0,   0}, {223,   0,   0}, {222,   0,   0}, {221,   0,   0},
	{219,   0,   0}, {218,   0,   0}, {217,   0,   0}, {216,   0,   0}, {214,   0,   0},
	{213,   0,   0}, {212,   0,   0}, {211,   0,   0}, {209,   0,   0}, {208,   0,   0},
	{207,   0,   0}, {206,   0,   0}, {204,   0,   0}, {203,   0,   0}, {202,   0,   0},
	{201,   0,   0}, {200,   0,   0}, {198,   0,   0}, {197,   0,   0}, {196,   0,   0},
	{195,   0,   0}, {194,   0,   0}, {193,   0,   0}, {191,   0,   0}, {190,   0,   0},
	{189,   0,   0}, {188,   0,   0}, {186,   0,   0}, {185,   0,   0}, {184,   0,   0},
	{183,   0,   0}, {181,   0,   0}, {180,   0,   0}, {179,   0,   0}, {178,   0,   0},
	{176,   0,   0}, {175,   0,   0}, {174,   0,   0}, {173,   0,   0}, {171,   0,   0},
	{170,   0,   0}, {169,   0,   0}, {168,   0,   0}, {166,   0,   0}, {165,   0,   0},
	{164,   0,   0}, {163,   0,   0}, {161,   0,   0}, {160,   0,   0}, {159,   0,   0},
	{158,   0,   0}, {157,   0,   0}, {156,   0,   0}, {154,   0,   0}, {153,   0,   0},
	{152,   0,   0}, {151,   0,   0}, {150,   0,   0}, {148,   0,   0}, {147,   0,   0},
	{146,   0,   0}, {145,   0,   0}, {143,   0,   0}, {142,   0,   0}, {141,   0,   0},
	{140,   0,   0}, {138,   0,   0}, {137,   0,   0}, {136,   0,   0}, {135,   0,   0},
	{134,   0,   0}, {133,   0,   0}, {133,   0,   0}, {132,   0,   0}, {131,   0,   0},
	{130,   0,   0}, {129,   0,   0}, {129,   0,   0}, {128,   0,   0}, {127,   0,   0},
	{122,   0,   9}, {117,   0,  18}, {112,   0,  27}, {107,   0,  36}, {102,   0,  45}
};



void CSurface::FillMandelbortFractal()
{
	double    cr,    ci;
	double nextr, nexti;
	double prevr, previ;

	const unsigned int max_iterations = 100;

	for (unsigned int y = 0; y < mHeight; ++y)
	{
		for (unsigned int x = 0; x < mWidth; ++x)
		{
			cr = 1.5 * (2.0 * x / mWidth - 1.0) - 0.5;
			ci =       (2.0 * y / mHeight - 1.0);

			nextr = nexti = 0;
			prevr = previ = 0;

			for (unsigned int i = 0; i < max_iterations; ++i)
			{
				prevr = nextr;
				previ = nexti;

				nextr =     prevr * prevr - previ * previ + cr;
				nexti = 2 * prevr * previ + ci;

				if (((nextr * nextr) + (nexti * nexti)) > 4)
				{
					using namespace std;

					const double z = sqrt(nextr * nextr + nexti * nexti);

					//https://en.wikipedia.org/wiki/Mandelbrot_set#Continuous_.28smooth.29_coloring
					const unsigned int index = static_cast<unsigned int>
						(1000.0 * log2(1.75 + i - log2(log2(z))) / log2(max_iterations));


					*GetPixel(x, y) = UBGRAColor(jet_colormap[index].red, jet_colormap[index].blue, jet_colormap[index].green, 0);

					break;
				}
			}
		}
	}
}

void CSurface::FillRnadom()
{
	unsigned ii = rand();
	
	if(mPixelFormat == EPF_BGRA_UINT32)
	{
		for(int y = 0; y < mHeight; y++)
		{
			for(int x = 0; x < mWidth; x++)
			{
				srand(ii + x / 8 );
				uint32* pPixel = (uint32*)GetPixel(x, y);
				*pPixel = UMakeBGRAColor(rand() % 255, rand() % 255, rand() % 255, 255);
			}
		}
	}
}

void CSurface::FillGradient()
{
	if(mPixelFormat == EPF_BGRA_UINT32)
	{
		for(int y = 0; y < mHeight; y++)
		{
			for(int x = 0; x < mWidth; x++)
			{
				uint32* pPixel = (uint32*)GetPixel(x, y);
				*pPixel = UMakeBGRAColor(0, y * 255 / mHeight, x * 255 / mWidth, 255);
			}
		}
	}
}

inline uint32 rgb_interp(uint32 src, uint32 dst, uint32 t) 
{
	assert(t <= 255);
	const uint32 s = 255 - t;
#if defined(__LITTLE_ENDIAN__)
	return (
		(((((src >> 0)  & 0xff) * s +
		((dst >> 0)  & 0xff) * t) >> 8)) |
		(((((src >> 8)  & 0xff) * s +
		((dst >> 8)  & 0xff) * t)     )  & ~0xff) |
		(((((src >> 16) & 0xff) * s +
		((dst >> 16) & 0xff) * t) << 8)  & ~0xffff) |
		0xff000000
		);
#else
	return (
		(((((src >> 24) & 0xff) * s +
		((dst >> 24) & 0xff) * t) << 16) & ~0xffffff) |
		(((((src >> 16) & 0xff) * s +
		((dst >> 16) & 0xff) * t) << 8)  & ~0xffff) |
		(((((src >> 8)  & 0xff) * s +
		((dst >> 8)  & 0xff) * t)     )  & ~0xff) |
		0xff
		);
#endif
}
inline uint32 rgba_interp(uint32 src, uint32 dst, uint32 t) 
{
	//assert(t <= 255);
	const uint32 s = 255 - t;
	return (
		(((((src >> 0)  & 0xff) * s +
		((dst >> 0)  & 0xff) * t) >> 8)) |
		(((((src >> 8)  & 0xff) * s +
		((dst >> 8)  & 0xff) * t)     )  & ~0xff) |
		(((((src >> 16) & 0xff) * s +
		((dst >> 16) & 0xff) * t) << 8)  & ~0xffff) |
		(((((src >> 24) & 0xff) * s +
		((dst >> 24) & 0xff) * t) << 16) & ~0xffffff)
		);
}
inline uint32 UBiLerpRGBA(uint32 p00, uint32 p10, uint32 p01, uint32 p11, uint32 x, uint32 y)
{
	 return rgba_interp(rgba_interp(p00, p10, x), rgb_interp(p01, p11, x), y);
}
//using  float
inline uint32 rgba_interpF(uint32 src, uint32 dst, uint32 t) 
{
	assert(t <= 255);

	float ft = t / 255.0f;

	ColorBGRA* ca = (ColorBGRA*)&src;
	ColorBGRA* cb = (ColorBGRA*)&dst;

	int fr = (int)(ULerp(ca->r, cb->r, ft));
	int fg = (int)(ULerp(ca->g, cb->g, ft));
	int fb = (int)(ULerp(ca->b, cb->b, ft));
	int fa = (int)(ULerp(ca->a, cb->a, ft));

	return UMakeBGRAColor(fb, fg, fr, fa);
}
//#define plot_(X,Y,D) *GetPixel(X, Y) = color
#define plot_(X,Y,D)\
if(IsInBound(X, Y)){\
uint32* pPixel = (uint32*)GetPixel(X, Y);\
*pPixel = rgba_interp(*pPixel, color, D * 255);\
}\





#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X))+0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))

#define swap_(a, b) std::swap(a, b)



void CSurface::SetPixel(int x, int y, int penSize, ColorT color)
{
	switch (penSize)
	{
	case 1  : SetPixel(x,y, color);
		break;

	case 2  : 
		{
			//P0
			//00

			SetPixel(x    , y    , color);
			SetPixel(x + 1, y    , color);
			SetPixel(x + 1, y + 1, color);
			SetPixel(x    , y + 1, color);

		}
		break;

	case  3 : 
		{
			SetPixel(x    , y - 1, color);
			SetPixel(x - 1, y - 1, color);
			SetPixel(x + 1, y - 1, color);

			SetPixel(x    , y    , color);
			SetPixel(x - 1, y    , color);
			SetPixel(x + 1, y    , color);

			SetPixel(x    , y + 1, color);
			SetPixel(x - 1, y + 1, color);
			SetPixel(x + 1, y + 1, color);

		};
		break;
		break;
	default:
		{
			for(int i = -(penSize / 2); i <= penSize / 2; i++)
			{
				for(int j = -(penSize / 2); j <= penSize / 2; j++)
				{
					SetPixel(x + i, y + j, color);
				}
			}
			return;

		}
	}
}

void CSurface::DrawHorizontalLine(int x0, int x1, int y, int thickness, ColorT color)
{
	if (x0 > x1)
	{
		std::swap(x0, x1);
	}

	for (; x0 <= x1; x0++)
	{
		SetPixel(x0, y, thickness, color);
	}
}

void CSurface::DrawVerticalLine(int y0, int y1, int x, int thickness, ColorT color)
{
	if(y0 > y1)
	{
		std::swap(y0, y1);
	}

	for(; y0 <= y1; y0++)
	{
		SetPixel(x, y0, thickness, color);
	}
}

void CSurface::DrawLineAA(int x1, int y1, int x2, int y2, ColorT color)
{
	float dx = (float)x2 - (float)x1;
	float dy = (float)y2 - (float)y1;

	if ( fabs(dx) > fabs(dy) ) {
		if ( x2 < x1 ) {
			swap_(x1, x2);
			swap_(y1, y2);
		}
		float gradient = dy / dx;
		float xend = round_(x1);
		float yend = y1 + gradient*(xend - x1);
		float xgap = rfpart_(x1 + 0.5);
		int xpxl1 = xend;
		int ypxl1 = ipart_(yend);
		plot_(xpxl1, ypxl1, rfpart_(yend)*xgap);
		plot_(xpxl1, ypxl1+1, fpart_(yend)*xgap);
		float intery = yend + gradient;

		xend = round_(x2);
		yend = y2 + gradient*(xend - x2);
		xgap = fpart_(x2+0.5);
		int xpxl2 = xend;
		int ypxl2 = ipart_(yend);
		plot_(xpxl2, ypxl2, rfpart_(yend) * xgap);
		plot_(xpxl2, ypxl2 + 1, fpart_(yend) * xgap);

		int x;
		for(x=xpxl1+1; x <= (xpxl2-1); x++) {
			plot_(x, ipart_(intery), rfpart_(intery));
			plot_(x, ipart_(intery) + 1, fpart_(intery));
			intery += gradient;
		}
	} else {
		if ( y2 < y1 ) {
			swap_(x1, x2);
			swap_(y1, y2);
		}
		float gradient = dx / dy;
		float yend = round_(y1);
		float xend = x1 + gradient*(yend - y1);
		float ygap = rfpart_(y1 + 0.5);
		int ypxl1 = yend;
		int xpxl1 = ipart_(xend);
		plot_(xpxl1, ypxl1, rfpart_(xend)*ygap);
		plot_(xpxl1, ypxl1+1, fpart_(xend)*ygap);
		float interx = xend + gradient;

		yend = round_(y2);
		xend = x2 + gradient*(yend - y2);
		ygap = fpart_(y2+0.5);
		int ypxl2 = yend;
		int xpxl2 = ipart_(xend);
		plot_(xpxl2, ypxl2, rfpart_(xend) * ygap);
		plot_(xpxl2, ypxl2 + 1, fpart_(xend) * ygap);

		int y;
		for(y=ypxl1+1; y <= (ypxl2-1); y++) {
			plot_(ipart_(interx), y, rfpart_(interx));
			plot_(ipart_(interx) + 1, y, fpart_(interx));
			interx += gradient;
		}
	}
}



void CSurface::DrawLineAA(Int2 a, Int2 b, ColorT color, int thickness)
{
	DrawLineAA(a, b, color);

	//DrawLineAA(a - n, b - n, color);
	//DrawLineAA(a, b, color);
	//DrawLineAA(a + n, b + n, color);
}

#undef swap_
#undef plot_
#undef ipart_
#undef fpart_
#undef round_
#undef rfpart_

// void CSurface::DrawLine(int x0, int y0, int x1, int y1, ColorT color)
// {
// 	x0 = UClamp(x0, 0, mWidth - 1);
// 	y0 = UClamp(y0, 0, mHeight - 1);
// 	
// 	x1 = UClamp(x1, 0, mWidth -1);
// 	y1 = UClamp(y1, 0, mHeight - 1);
// 
// 	if(x0 == x1 && y0 == y1) return;
// 
// 	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
// 	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
// 	int err = (dx > dy ? dx : -dy) / 2, e2;
// 
// 	for (;;)
// 	{
// 		*GetPixel(x0, y0) = color;
// 
// 		if (x0 == x1 && y0 == y1)
// 			break;
// 
// 		e2 = err;
// 		if (e2 > -dx)
// 		{
// 			err -= dy; x0 += sx;
// 		}
// 		if (e2 < dy)
// 		{
// 			err += dx; y0 += sy;
// 		}
// 	}
// }
// 

void CSurface::DrawLine(int x1, int y1, int x2, int y2, unsigned thickness, ColorT color)
{
	int steep = 0;
	int sx    = ((x2 - x1) > 0) ? 1 : -1;
	int sy    = ((y2 - y1) > 0) ? 1 : -1;
	int dx    = abs(x2 - x1);
	int dy    = abs(y2 - y1);

	if (dy > dx)
	{
		std::swap(x1,y1);
		std::swap(dx,dy);
		std::swap(sx,sy);

		steep = 1;
	}

	int e = 2 * dy - dx;

	for (int i = 0; i < dx; ++i)
	{
		if (steep)
			SetPixel(y1, x1, thickness, color);
		else
			SetPixel(x1, y1, thickness, color);

		while (e >= 0)
		{
			y1 += sy;
			e -= (dx << 1);
		}

		x1 += sx;
		e  += (dy << 1);
	}

	SetPixel(x2,y2, thickness, color);
}


void CSurface::DrawGradientLine(Int2 a, Int2 b, unsigned thickness, ColorT color)
{
	
}

void CSurface::BlendRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color)
{
	x = std::min(x, mWidth);
	y = std::min(y, mHeight);

	w = std::min(x + w, mWidth);
	h = std::min(y + h, mHeight);

	
	if(mPixelFormat == EPF_BGRA_UINT32)
	{
		for (unsigned yy = y; yy < h; yy++)
		{
			for (unsigned xx = x; xx < w; xx++)
			{
				uint32* pixel = (uint32*)GetPixel(xx, yy);
				uint32 a = (color & 0xFF000000) >> 24;
				*pixel = rgba_interp(*pixel, color, a);	

			}
		}
	}
	else
	{
		UCHECK(false);
	}
}

void CSurface::FillTriangle(Int2 t0, Int2 t1, Int2 t2, ColorT color)
{
	if (t0.y>t1.y) std::swap(t0, t1);
	if (t0.y>t2.y) std::swap(t0, t2);
	if (t1.y>t2.y) std::swap(t1, t2);

	int total_height = t2.y - t0.y;

	Int2 T1_T0 = (t1 - t0);
	Int2 T2_T0 = (t2 - t0);
	Int2 T2_T1 = (t2 - t1);

	for (int y = t0.y; y <= t1.y; y++) 
	{
		int segment_height = t1.y - t0.y + 1;
		float alpha = (float)(y - t0.y) / total_height;
		float beta = (float)(y - t0.y) / segment_height;
		Int2 A = t0 + T2_T0 *alpha;
		Int2 B = t0 + T1_T0 *beta;
		if (A.x>B.x)
			std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) 
		{
			ColorT col = color;
// 			if(j == A.x || j == B.x)
// 			{
// 				ColorT pPixel = *GetPixel(j, y);
// 				col = rgba_interp(pPixel, color, 128);
// 				//col = UMakeBGRAColor(0,0,255, 0);
// 			}
			
			SetPixel(j, y,  col);
			//*((unsigned int*)&image[y*Stride + (j * BitDepth)]) = color.value;
		}
	}
	for (int y = t1.y; y <= t2.y; y++) 
	{
		int segment_height = t2.y - t1.y + 1;
		float alpha = (float)(y - t0.y) / total_height;
		float beta = (float)(y - t1.y) / segment_height;
		Int2 A = t0 + T2_T0 *alpha;
		Int2 B = t1 + T2_T1 *beta;
		if (A.x>B.x)
			std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) 
		{
			ColorT col = color;
// 			if(j == A.x || j == B.x)
// 			{
// 				ColorT pPixel = *GetPixel(j, y);
// 				col = rgba_interp(pPixel, color, 128);
// 			}

			SetPixel(j, y, col);
			//*((unsigned int*)&image[y*Stride + (j * BitDepth)]) = color.value;
		}
	}
}



void CSurface::FillTriangleF(Float2 t0, Float2 t1, Float2 t2, ColorT color)
{
	if (t0.y>t1.y) std::swap(t0, t1);
	if (t0.y>t2.y) std::swap(t0, t2);
	if (t1.y>t2.y) std::swap(t1, t2);

	int total_height = t2.y - t0.y;

	Float2 T1_T0 = (t1 - t0);
	Float2 T2_T0 = (t2 - t0);
	Float2 T2_T1 = (t2 - t1);

	for (int y = t0.y; y <= t1.y; y++) 
	{
		int segment_height = t1.y - t0.y;
		float alpha = (float)(y - t0.y) / total_height;
		float beta = (float)(y - t0.y) / segment_height;
		Float2 A = t0 + T2_T0 *alpha;
		Float2 B = t0 + T1_T0 *beta;
		if (A.x>B.x)
			std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) 
		{
			ColorT col = color;
// 			if(j == A.x || j == B.x)
// 			{
// 				ColorT pPixel = *GetPixel(j, y);
// 				col = rgba_interp(pPixel, color, 128);
// 				//col = UMakeBGRAColor(0,0,255, 0);
// 			}
			
			SetPixel(j, y,  col);
			//*((unsigned int*)&image[y*Stride + (j * BitDepth)]) = color.value;
		}
	}
	for (int y = t1.y; y <= t2.y; y++) 
	{
		int segment_height = t2.y - t1.y;
		float alpha = (float)(y - t0.y) / total_height;
		float beta = (float)(y - t1.y) / segment_height;
		Float2 A = t0 + T2_T0 *alpha;
		Float2 B = t1 + T2_T1 *beta;
		if (A.x>B.x)
			std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) 
		{
			ColorT col = color;
// 			if(j == A.x || j == B.x)
// 			{
// 				ColorT pPixel = *GetPixel(j, y);
// 				col = rgba_interp(pPixel, color, 128);
// 			}

			SetPixel(j, y, col);
			//*((unsigned int*)&image[y*Stride + (j * BitDepth)]) = color.value;
		}
	}
}





void CSurface::FillTriangleAA(Int2 a, Int2 b, Int2 c, ColorT color)
{
	FillTriangleF(a, b, c, color);
	//color = UMakeBGRAColor(255, 0,0,0);
	PerformLineAA(a, b, color);
	PerformLineAA(b, c, color);
	PerformLineAA(c, a, color);
}



void CSurface::FillTriangle2(Int2 a, Int2 b, Int2 c, ColorT color)
{
	// create edges for the triangle
	Edge edges[3] = {
		Edge((int)a.x, (int)a.y,(int)b.x, (int)b.y),
		Edge((int)b.x, (int)b.y,(int)c.x, (int)c.y),
		Edge((int)c.x, (int)c.y,(int)a.x, (int)a.y)
	};

	int maxLength = 0;
	int longEdge = 0;

	// find edge with the greatest length in the y axis
	for(int i = 0; i < 3; i++) {
		int length = edges[i].Y2 - edges[i].Y1;
		if(length > maxLength) {
			maxLength = length;
			longEdge = i;
		}
	}

	int shortEdge1 = (longEdge + 1) % 3;
	int shortEdge2 = (longEdge + 2) % 3;

	// draw spans between edges; the long edge can be drawn
	// with the shorter edges to draw the full triangle
	DrawSpansBetweenEdges(edges[longEdge], edges[shortEdge1], color);
	DrawSpansBetweenEdges(edges[longEdge], edges[shortEdge2], color);
};


void CSurface::FillQuad(Int2 a, Int2 b, Int2 c, Int2 d, ColorT color)
{
	FillTriangleF(a, b, c, color);
	FillTriangleF(c, d, a, color);
}
void CSurface::FillQuadAA(Int2 a, Int2 b, Int2 c, Int2 d, ColorT color)
{
	FillTriangleF(a, b, c, color);
	FillTriangleF(c, d, a, color);
	
	PerformLineAA(a, b, color);
	PerformLineAA(b, c, color);
	PerformLineAA(c, d, color);
	PerformLineAA(d, a, color);
}

//////////////////////////////////////////////////////////////////////////
void CSurface::FillRect(unsigned x, unsigned y, unsigned w, unsigned h, ColorT color)
{
	x = std::min(x, mWidth);
	y = std::min(y, mHeight);

	w = std::min(x + w, mWidth);
	h = std::min(y + h, mHeight);

	for (unsigned yy = y; yy < h; yy++)
	{
		for (unsigned xx = x; xx < w; xx++)
		{
			*GetPixel(xx, yy) = color;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CSurface::DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc)
{
	if (pSrc == NULL || dstX >= mWidth || dstY >= mHeight) return;

	unsigned r =  dstX + pSrc->Width();
	unsigned b = dstY + pSrc->Height();

	r = std::min(r, mWidth);
	b = std::min(b, mHeight);

	for (unsigned y = dstY; y < b; y++)
	{
		for (unsigned x = dstX; x < r; x++)
		{
			*GetPixel(x, y) = *(pSrc->GetPixel(x - dstX, y - dstY));
		}
	}

}

void CSurface::DrawSurface(unsigned dstX, unsigned dstY, const CSurface* pSrc, unsigned srcX, unsigned srcY, unsigned w, unsigned h)
{

	
}

void CSurface::DrawSurfaceRotated(Int2 dstOffset, const CSurface* pSrc, int angleInDegrees, Int2 origin)
{
	float angleRadian = angleInDegrees * DEG2RAD;

	float sinValue = sin(angleRadian);
	float cosValue = cos(angleRadian);


	Int2 leftTop = URotatePoint(0,0, sinValue, cosValue, origin.x, origin.y);
	Int2 rightTop = URotatePoint(pSrc->mWidth, 0, sinValue,cosValue, origin.x, origin.y);
	Int2 rightBottom = URotatePoint(pSrc->mWidth, pSrc->mHeight, sinValue, cosValue, origin.x, origin.y);
	Int2 leftBottom = URotatePoint(0, pSrc->mHeight, sinValue, cosValue,  origin.x, origin.y);

	Int2 minPoint = Int2::Min(leftTop, Int2::Min(rightTop, Int2::Min(rightBottom, leftBottom)));
	Int2 maxPoint = Int2::Max(leftTop, Int2::Max(rightTop, Int2::Max(rightBottom, leftBottom)));

	Int2 newSize = maxPoint - minPoint;

	sinValue = sin(-angleRadian);
	cosValue = cos(-angleRadian);


	int sinI = (int)(sinValue * 2048);
	int cosI = (int)(cosValue * 2048);

	{
		{
			for(unsigned x = 0; x < newSize.x; x++)
			{
				for(unsigned y = 0; y < newSize.y;  y++)
				{
					Int2 p = Int2(x, y) + dstOffset;
					if(p > Int2(0,0) && p < Int2(mWidth, mHeight))
					{
						ColorT* dstPixel = (ColorT*)GetPixel(p);
						Int2 rotatedPoint = URotatePoint(x + minPoint.x, y + minPoint.y, sinValue, cosValue, origin.x, origin.y);

						if(rotatedPoint >= Int2(0,0) && rotatedPoint < Int2(pSrc->Width(), pSrc->Height()))
						{
							ColorT* srcPixel = (ColorT*)pSrc->GetPixel(rotatedPoint.x, rotatedPoint.y);
							*dstPixel = *srcPixel;
						}
					}

				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CSurface::DrawSurfaceRotatedCenter(Int2 dstOffest, const CSurface* pSrc, int rotationDegree)
{
	float angleRadian = rotationDegree * DEG2RAD;

	float sinValue = sin(angleRadian);
	float cosValue = cos(angleRadian);


	Int2 leftTop = URotatePoint(0,0, sinValue, cosValue);
	Int2 rightTop = URotatePoint(pSrc->mWidth, 0, sinValue,cosValue);
	Int2 rightBottom = URotatePoint(pSrc->mWidth, pSrc->mHeight, sinValue, cosValue);
	Int2 leftBottom = URotatePoint(0, pSrc->mHeight, sinValue, cosValue);

	Int2 minPoint = Int2::Min(leftTop, Int2::Min(rightTop, Int2::Min(rightBottom, leftBottom)));
	Int2 maxPoint = Int2::Max(leftTop, Int2::Max(rightTop, Int2::Max(rightBottom, leftBottom)));

	Int2 newSize = maxPoint - minPoint;
	Int2 halfSize = newSize / Int2(2, 2);

	sinValue = sin(-angleRadian);
	cosValue = cos(-angleRadian);


	int sinI = (int)(sinValue * 2048);
	int cosI = (int)(cosValue * 2048);

	for(unsigned x = 0; x < newSize.x; x++)
	{
		for(unsigned y = 0; y < newSize.y;  y++)
		{
			Int2 p = Int2(x, y) + dstOffest - halfSize;
			if(p > Int2(0,0) && p < Int2(mWidth, mHeight))
			{
				ColorT* dstPixel = (ColorT*)GetPixel(p);
				Int2 rotatedPoint = URotatePoint(x + minPoint.x, y + minPoint.y, sinValue, cosValue);

				if(rotatedPoint >= Int2(0,0) && rotatedPoint < Int2(pSrc->Width(), pSrc->Height()))
				{
					ColorT* srcPixel = (ColorT*)pSrc->GetPixel(rotatedPoint.x, rotatedPoint.y);
					*dstPixel = *srcPixel;
				}
			}

		}
	}
}

//////////////////////////////////////////////////////////////////////////
//#incomplete
void CSurface::DrawSurfaceRotatedCenterAA(Int2 dstOffset, const CSurface* pSrc, int rotationDegree)
{
	float angleRadian = rotationDegree * DEG2RAD;

	float sinValue = sin(angleRadian);
	float cosValue = cos(angleRadian);

	//points in dst surface
	Int2 leftTop = URotatePoint(0,0, sinValue, cosValue);
	Int2 rightTop = URotatePoint(pSrc->mWidth, 0, sinValue,cosValue);
	Int2 rightBottom = URotatePoint(pSrc->mWidth, pSrc->mHeight, sinValue, cosValue);
	Int2 leftBottom = URotatePoint(0, pSrc->mHeight, sinValue, cosValue);

	Int2 minPoint = Int2::Min(leftTop, Int2::Min(rightTop, Int2::Min(rightBottom, leftBottom)));
	Int2 maxPoint = Int2::Max(leftTop, Int2::Max(rightTop, Int2::Max(rightBottom, leftBottom)));

	Int2 newSize = maxPoint - minPoint;
	Int2 halfSize = newSize / Int2(2, 2);

	sinValue = sin(-angleRadian);
	cosValue = cos(-angleRadian);


	int sinI = (int)(sinValue * 2048);
	int cosI = (int)(cosValue * 2048);

	Int2 srcSize(pSrc->Width(), pSrc->Height());

	for(unsigned x = 0; x < newSize.x; x++)
	{
		for(unsigned y = 0; y < newSize.y;  y++)
		{
			Int2 p = Int2(x, y) + dstOffset - halfSize;
			if(p > Int2(0,0) && p < Int2(mWidth, mHeight))
			{
				ColorT* dstPixel = (ColorT*)GetPixel(p);
				Int2 rotatedPoint = URotatePoint(x + minPoint.x, y + minPoint.y, sinValue, cosValue);

				if(rotatedPoint >= Int2(0,0) && rotatedPoint < srcSize)
				{
					ColorT* srcPixel = (ColorT*)pSrc->GetPixel(rotatedPoint.x, rotatedPoint.y);
					*dstPixel = *srcPixel;

					if(rotatedPoint.x == 0 || rotatedPoint.x == srcSize.x-1)
					{
						//PerformAAPiexl(p.x, p.y);
					}
					if(rotatedPoint.y == 0 || rotatedPoint.y == srcSize.y - 1)
					{
						//PerformAAPiexl(p.x, p.y);
					}
				}
			}

		}
	}

	ColorT c = UMakeBGRAColor(0, 0, 255, 0);

	//DrawLine(leftTop, rightTop, c);
	//DrawLine(rightTop, rightBottom, c);
	//DrawLine(rightBottom, leftBottom, c);
	//DrawLine(leftBottom, leftTop, c);

}

void CSurface::DrawCircle(int x, int y, int radius, ColorT color)
{
}

#if 1
#define plot_(X,Y,D)\
	if(IsInBound(X, Y)){\
	ColorT cc = BilinearSample(X, Y);\
	SetPixel(X, Y, cc);}






#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X))+0.5))
#define fpart_(X) (((double)(X))-(double)ipart_(X))
#define rfpart_(X) (1.0-fpart_(X))

#define swap_(a, b) std::swap(a, b)

void CSurface::PerformAAPiexl(int x, int y)
{
	Int2 xy = Int2(x, y);
	Int2 max = Int2(mWidth - 1, mHeight - 1);

	bool bNeedsClamp = !(xy > Int2(0,0) && xy < max);

	static const Int2 offsets[] = 
	{
		Int2(0    , 0 - 1),
		//Int2(0 - 1, 0 - 1),
		Int2(0 + 1, 0 - 1),

		Int2(0    , 0    ),
		Int2(0 - 1, 0    ),
		Int2(0 + 1, 0    ),

		Int2(0    , 0 + 1),
		Int2(0 - 1, 0 + 1),
		//Int2(0 + 1, 0 + 1)
	};

	static const int N = _countof(offsets);


	

	int r = 0, g = 0, b = 0, a = 0;

	for(unsigned i = 0; i < N; i++)
	{
		Int2 p = offsets[i] + xy;
		if(bNeedsClamp)
		{
			p = Int2::Clamp(p, Int2(0, 0), max);
		}


		ColorT pixel = *GetPixel(p);

		unsigned eb, eg, er, ea;
		UExtractBGRAColor(pixel, eb, eg, er, ea);

		r += er;
		g += eg;
		b += eb;
		a += ea;
	}

	r = (int)(r / N);
	g = (int)(g / N);
	b = (int)(b / N);

	r &= 0xFF;
	g &= 0xFF;
	b &= 0xFF;
	
	SetPixel(x, y, UMakeBGRAColor(b, g, r, a));
}

void CSurface::PerformAAPiexl4(int x, int y)
{
	if(0)
	{
		PerformAAPiexl(x    , y    );
		PerformAAPiexl(x + 1, y    );
		PerformAAPiexl(x + 1, y + 1);
		PerformAAPiexl(x    , y + 1);
	}
	else 
	{
		PerformAAPiexl(x    , y - 1);
		PerformAAPiexl(x - 1, y - 1);
		PerformAAPiexl(x + 1, y - 1);

		PerformAAPiexl(x    , y    );
		PerformAAPiexl(x - 1, y    );
		PerformAAPiexl(x + 1, y    );

		PerformAAPiexl(x    , y + 1);
		PerformAAPiexl(x - 1, y + 1);
		PerformAAPiexl(x + 1, y + 1);
	}
	



}

//////////////////////////////////////////////////////////////////////////
void CSurface::PerformLineAA(int x1, int y1, int x2, int y2, ColorT color)
{

#if 1
	int steep = 0;
	int sx    = ((x2 - x1) > 0) ? 1 : -1;
	int sy    = ((y2 - y1) > 0) ? 1 : -1;
	int dx    = abs(x2 - x1);
	int dy    = abs(y2 - y1);

	if (dy > dx)
	{
		std::swap(x1,y1);
		std::swap(dx,dy);
		std::swap(sx,sy);

		steep = 1;
	}

	int e = 2 * dy - dx;

	for (int i = 0; i < dx; ++i)
	{
		if (steep)
			PerformAAPiexl4(y1, x1);
		else
			PerformAAPiexl4(x1, y1);

		while (e >= 0)
		{
			y1 += sy;
			e -= (dx << 1);
		}

		x1 += sx;
		e  += (dy << 1);
	}

	//PerformAAPiexl(x2,y2);

#else
	float dx = (float)x2 - (float)x1;
	float dy = (float)y2 - (float)y1;

	if ( fabs(dx) > fabs(dy) ) {
		if ( x2 < x1 ) {
			swap_(x1, x2);
			swap_(y1, y2);
		}
		float gradient = dy / dx;
		float xend = round_(x1);
		float yend = y1 + gradient*(xend - x1);
		float xgap = rfpart_(x1 + 0.5);
		int xpxl1 = xend;
		int ypxl1 = ipart_(yend);
		plot_(xpxl1, ypxl1, rfpart_(yend)*xgap);
		plot_(xpxl1, ypxl1+1, fpart_(yend)*xgap);
		float intery = yend + gradient;

		xend = round_(x2);
		yend = y2 + gradient*(xend - x2);
		xgap = fpart_(x2+0.5);
		int xpxl2 = xend;
		int ypxl2 = ipart_(yend);
		plot_(xpxl2, ypxl2, rfpart_(yend) * xgap);
		plot_(xpxl2, ypxl2 + 1, fpart_(yend) * xgap);

		int x;
		for(x=xpxl1+1; x <= (xpxl2-1); x++) {
			plot_(x, ipart_(intery), rfpart_(intery));
			plot_(x, ipart_(intery) + 1, fpart_(intery));
			intery += gradient;
		}
	} else {
		if ( y2 < y1 ) {
			swap_(x1, x2);
			swap_(y1, y2);
		}
		float gradient = dx / dy;
		float yend = round_(y1);
		float xend = x1 + gradient*(yend - y1);
		float ygap = rfpart_(y1 + 0.5);
		int ypxl1 = yend;
		int xpxl1 = ipart_(xend);
		plot_(xpxl1, ypxl1, rfpart_(xend)*ygap);
		plot_(xpxl1, ypxl1+1, fpart_(xend)*ygap);
		float interx = xend + gradient;

		yend = round_(y2);
		xend = x2 + gradient*(yend - y2);
		ygap = fpart_(y2+0.5);
		int ypxl2 = yend;
		int xpxl2 = ipart_(xend);
		plot_(xpxl2, ypxl2, rfpart_(xend) * ygap);
		plot_(xpxl2, ypxl2 + 1, fpart_(xend) * ygap);

		int y;
		for(y=ypxl1+1; y <= (ypxl2-1); y++) {
			plot_(ipart_(interx), y, rfpart_(interx));
			plot_(ipart_(interx) + 1, y, fpart_(interx));
			interx += gradient;
		}
	}
#endif

#undef swap_
#undef plot_
#undef ipart_
#undef fpart_
#undef round_
#undef rfpart_
#endif
}

//////////////////////////////////////////////////////////////////////////
void CSurface::FillRibbon(Int2 a, Int2 b, int thickness, ColorT color)
{
	Float2 lineN = Float2(UGetLineNormal(a, b));
	lineN.Normalize();
	Int2 offset = (Int2)(lineN * thickness);

	//Edge e0(a + offset, a - offset);
	//Edge e1(b + offset, b - offset);
	Edge e0(a + offset, b + offset);
	Edge e1(a - offset, b - offset);
	DrawSpansBetweenEdges(e0, e1, color);

}

//////////////////////////////////////////////////////////////////////////
void CSurface::DrawRibbon(Int2 a, Int2 b, int thickness, ColorT color)
{
	Float2 lineN = Float2(UGetLineNormal(a, b));
	lineN.Normalize();
	Int2 offset = (Float2)(lineN * thickness);

	DrawLine(a + offset, a - offset, 1, color);
	DrawLine(b + offset, b - offset, 1, color);

	DrawLine(a + offset, b + offset, 1, color);
	DrawLine(a - offset, b - offset, 1, color);
}

CSurface::ColorT CSurface::BilinearSample(Int2 xy) const
  {
	Int2 tl = xy - Int2(-1, -1);
	Int2 tr = xy - Int2(1, -1);
	Int2 br = xy - Int2(1, 1);
	Int2 bl = xy - Int2(-1, 1);

	Int2 max = Int2(mWidth - 1, mHeight - 1);

	tl = Int2::Clamp(tl, Int2(0,0), max);
	tr = Int2::Clamp(tr, Int2(0,0), max);
	bl = Int2::Clamp(bl, Int2(0,0), max);
	br = Int2::Clamp(br, Int2(0,0), max);


	return rgba_interp(
		rgba_interp(*GetPixel(tl), *GetPixel(br), 128), 
		rgba_interp(*GetPixel(tr), *GetPixel(bl), 128), 128);

}



CSurface::ColorT CSurface::Sample2X(float x, float y)
{
	float intx = 0;
	float inty = 0;

	float fracX = modf(x, &intx);
	float fracY = modf(y, &inty);

	//fracX = fracX * 2 - 1;
	//fracY = fracY * 2 - 1;

	int tx = ((int)(fracX * 255)) & 255;
	int ty = ((int)(fracY * 255)) & 255;

	Int2 xy(x, y);

	Int2 tl = xy - Int2(-1, -1);
	Int2 tr = xy - Int2(1, -1);
	Int2 br = xy - Int2(1, 1);
	Int2 bl = xy - Int2(-1, 1);

	Int2 max = Int2(mWidth - 1, mHeight - 1);

	tl = Int2::Clamp(tl, Int2(0,0), max);
	tr = Int2::Clamp(tr, Int2(0,0), max);
	bl = Int2::Clamp(bl, Int2(0,0), max);
	br = Int2::Clamp(br, Int2(0,0), max);

	return UBiLerpRGBA(*GetPixel(tl), *GetPixel(tr), *GetPixel(bl), *GetPixel(br), tx, 128);
}

void CSurface::TriDrawHorizontalLine(int x0, int x1, int y, int thickness, ColorT color)
{
	
	if (x0 > x1)
	{
		std::swap(x0, x1);
	}

	int firstx = x0;

	for (; x0 <= x1; x0++)
	{
		if(x0 == firstx || x0 == x1)
			color = UMakeBGRAColor(0,0,255, 0);
		else
			color = UMakeBGRAColor(255, 255, 255, 255);


		SetPixel(x0, y, thickness, color);
	}
}

void CSurface::DrawSpansBetweenEdges(Edge e1, Edge e2, ColorT color)
{
	// calculate difference between the y coordinates
	// of the first edge and return if 0
	float e1ydiff = (float)(e1.Y2 - e1.Y1);
	if(e1ydiff == 0.0f)
		return;

	// calculate difference between the y coordinates
	// of the second edge and return if 0
	float e2ydiff = (float)(e2.Y2 - e2.Y1);
	if(e2ydiff == 0.0f)
		return;

	// calculate differences between the x coordinates
	// and colors of the points of the edges
	float e1xdiff = (float)(e1.X2 - e1.X1);
	float e2xdiff = (float)(e2.X2 - e2.X1);
	//Color e1colordiff = (e1.Color2 - e1.Color1);
	//Color e2colordiff = (e2.Color2 - e2.Color1);

	// calculate factors to use for interpolation
	// with the edges and the step values to increase
	// them by after drawing each span
	float factor1 = (float)(e2.Y1 - e1.Y1) / e1ydiff;
	float factorStep1 = 1.0f / e1ydiff;
	float factor2 = 0.0f;
	float factorStep2 = 1.0f / e2ydiff;

	// loop through the lines between the edges and draw spans
	for(int y = e2.Y1; y < e2.Y2; y++) 
	{
		/*// create and draw span
		Span span(e1.Color1 + (e1colordiff * factor1),
			e1.X1 + (int)(e1xdiff * factor1),
			e2.Color1 + (e2colordiff * factor2),
			e2.X1 + (int)(e2xdiff * factor2));
		DrawSpan(span, y);
		*/

		bool isFirstOrLastY = (y == e2.Y1 || y == e2.Y2 - 1);

		float xx0 = e1.X1 + (e1xdiff * factor1);	//the first x
		float xx1 = e2.X1 + (e2xdiff * factor2);	//the last x

		int x0 = xx0;
		int x1 = xx1;

		if (x0 > x1)
		{
			std::swap(x0, x1);
		}

		int firstx = x0;

		for (; x0 <= x1; x0++)
		{
			bool isFirstOrLastX = x0 == firstx || x0 == x1;

			if(x0 == firstx )
			{
				float intPart = 0;
				float fracPart = modf(xx0, &intPart);
				
				//2x ms
				ColorT c = Sample2X(xx0, y);
				//fracPart *= 255;

				//SetPixel(x0, y, 1, color);

				SetPixel(x0, y, 1, c);
			}
			else
			{
				color = UMakeBGRAColor(255, 255, 255, 255);
				SetPixel(x0, y, 1, color);
			}


			
		}

		// increase factors
		factor1 += factorStep1;
		factor2 += factorStep2;
	}
}
