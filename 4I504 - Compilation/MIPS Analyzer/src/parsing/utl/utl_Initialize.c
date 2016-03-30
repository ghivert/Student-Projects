
/* ###--------------------------------------------------------------### */
/* file		: utl_Initialize.c					*/
/* date		: May 05 2006						*/
/* version	: v200							*/
/* author	: Pirouz BAZARGAN SABET					*/
/* description	: utility function					*/
/* ###--------------------------------------------------------------### */

#include <stdio.h>
#include UTL_H

/* ###--------------------------------------------------------------### */
/* function	: utl_Initialize					*/
/* description	: initializations					*/
/* called func.	: none							*/
/* ###--------------------------------------------------------------### */

void utl_Initialize ()

  {
  if ((UTL_STATUS & UTL_STS__INITIALIZED) == 0)
    {
	/* ###------------------------------------------------------### */
	/*   delimiters							*/
	/* ###------------------------------------------------------### */

    UTL_DLM_LEFT  [UTL_DLM__PARENTHESIS] = '(';
    UTL_DLM_LEFT  [UTL_DLM__BRACE      ] = '{';
    UTL_DLM_LEFT  [UTL_DLM__BRACKET    ] = '[';
    UTL_DLM_LEFT  [UTL_DLM__COMPARESIGN] = '<';
    UTL_DLM_LEFT  [UTL_DLM__OTHERS     ] = ' ';

    UTL_DLM_RIGHT [UTL_DLM__PARENTHESIS] = ')';
    UTL_DLM_RIGHT [UTL_DLM__BRACE      ] = '}';
    UTL_DLM_RIGHT [UTL_DLM__BRACKET    ] = ']';
    UTL_DLM_RIGHT [UTL_DLM__COMPARESIGN] = '>';
    UTL_DLM_RIGHT [UTL_DLM__OTHERS     ] = ' ';

	/* ###------------------------------------------------------### */
	/*   character's type						*/
	/* ###------------------------------------------------------### */

    UTL_CHR_TYPE  [  0] = 0             ;
    UTL_CHR_TYPE  [  1] = 0             ;
    UTL_CHR_TYPE  [  2] = 0             ;
    UTL_CHR_TYPE  [  3] = 0             ;
    UTL_CHR_TYPE  [  4] = 0             ;
    UTL_CHR_TYPE  [  5] = 0             ;
    UTL_CHR_TYPE  [  6] = 0             ;
    UTL_CHR_TYPE  [  7] = 0             ;
    UTL_CHR_TYPE  [  8] = 0             ;
    UTL_CHR_TYPE  [  9] = UTL_CHR__SPC  | UTL_CHR__BLK;

    UTL_CHR_TYPE  [ 10] = UTL_CHR__SPC  ;
    UTL_CHR_TYPE  [ 11] = UTL_CHR__SPC  ;
    UTL_CHR_TYPE  [ 12] = UTL_CHR__SPC  ;
    UTL_CHR_TYPE  [ 13] = UTL_CHR__SPC  ;
    UTL_CHR_TYPE  [ 14] = 0             ;
    UTL_CHR_TYPE  [ 15] = 0             ;
    UTL_CHR_TYPE  [ 16] = 0             ;
    UTL_CHR_TYPE  [ 17] = 0             ;
    UTL_CHR_TYPE  [ 18] = 0             ;
    UTL_CHR_TYPE  [ 19] = 0             ;

    UTL_CHR_TYPE  [ 20] = 0             ;
    UTL_CHR_TYPE  [ 21] = 0             ;
    UTL_CHR_TYPE  [ 22] = 0             ;
    UTL_CHR_TYPE  [ 23] = 0             ;
    UTL_CHR_TYPE  [ 24] = 0             ;
    UTL_CHR_TYPE  [ 25] = 0             ;
    UTL_CHR_TYPE  [ 26] = 0             ;
    UTL_CHR_TYPE  [ 27] = 0             ;
    UTL_CHR_TYPE  [ 28] = 0             ;
    UTL_CHR_TYPE  [ 29] = 0             ;

    UTL_CHR_TYPE  [ 30] = 0             ;
    UTL_CHR_TYPE  [ 31] = 0             ;
    UTL_CHR_TYPE  [ 32] = UTL_CHR__SPC  | UTL_CHR__BLK;
    UTL_CHR_TYPE  [ 33] = 0             ;
    UTL_CHR_TYPE  [ 34] = 0             ;
    UTL_CHR_TYPE  [ 35] = 0             ;
    UTL_CHR_TYPE  [ 36] = 0             ;
    UTL_CHR_TYPE  [ 37] = 0             ;
    UTL_CHR_TYPE  [ 38] = 0             ;
    UTL_CHR_TYPE  [ 39] = 0             ;

    UTL_CHR_TYPE  [ 40] = 0             ;
    UTL_CHR_TYPE  [ 41] = 0             ;
    UTL_CHR_TYPE  [ 42] = 0             ;
    UTL_CHR_TYPE  [ 43] = 0             ;
    UTL_CHR_TYPE  [ 44] = 0             ;
    UTL_CHR_TYPE  [ 45] = 0             ;
    UTL_CHR_TYPE  [ 46] = 0             ;
    UTL_CHR_TYPE  [ 47] = 0             ;
    UTL_CHR_TYPE  [ 48] = UTL_CHR__BODX ;			/* '0'	*/
    UTL_CHR_TYPE  [ 49] = UTL_CHR__BODX ;			/* '1'	*/
    UTL_CHR_TYPE  [ 50] = UTL_CHR__ODX  ;			/* '2'	*/
    UTL_CHR_TYPE  [ 51] = UTL_CHR__ODX  ;			/* '3'	*/
    UTL_CHR_TYPE  [ 52] = UTL_CHR__ODX  ;			/* '4'	*/
    UTL_CHR_TYPE  [ 53] = UTL_CHR__ODX  ;			/* '5'	*/
    UTL_CHR_TYPE  [ 54] = UTL_CHR__ODX  ;			/* '6'	*/
    UTL_CHR_TYPE  [ 55] = UTL_CHR__ODX  ;			/* '7'	*/
    UTL_CHR_TYPE  [ 56] = UTL_CHR__DX   ;			/* '8'	*/
    UTL_CHR_TYPE  [ 57] = UTL_CHR__DX   ;			/* '9'	*/
    UTL_CHR_TYPE  [ 58] = 0             ;
    UTL_CHR_TYPE  [ 59] = 0             ;

    UTL_CHR_TYPE  [ 60] = 0             ;
    UTL_CHR_TYPE  [ 61] = 0             ;
    UTL_CHR_TYPE  [ 62] = 0             ;
    UTL_CHR_TYPE  [ 63] = 0             ;
    UTL_CHR_TYPE  [ 64] = 0             ;
    UTL_CHR_TYPE  [ 65] = UTL_CHR__UPP  | UTL_CHR__XDG ;	/* 'A'	*/
    UTL_CHR_TYPE  [ 66] = UTL_CHR__UPP  | UTL_CHR__XDG ;	/* 'B'	*/
    UTL_CHR_TYPE  [ 67] = UTL_CHR__UPP  | UTL_CHR__XDG ;	/* 'C'	*/
    UTL_CHR_TYPE  [ 68] = UTL_CHR__UPP  | UTL_CHR__XDG ;	/* 'D'	*/
    UTL_CHR_TYPE  [ 69] = UTL_CHR__UPP  | UTL_CHR__XDG ;	/* 'E'	*/

    UTL_CHR_TYPE  [ 70] = UTL_CHR__UPP  | UTL_CHR__XDG  ;	/* 'F'	*/
    UTL_CHR_TYPE  [ 71] = UTL_CHR__UPP  ;			/* 'G'	*/
    UTL_CHR_TYPE  [ 72] = UTL_CHR__UPP  ;			/* 'H'	*/
    UTL_CHR_TYPE  [ 73] = UTL_CHR__UPP  ;			/* 'I'	*/
    UTL_CHR_TYPE  [ 74] = UTL_CHR__UPP  ;			/* 'J'	*/
    UTL_CHR_TYPE  [ 75] = UTL_CHR__UPP  ;			/* 'K'	*/
    UTL_CHR_TYPE  [ 76] = UTL_CHR__UPP  ;			/* 'L'	*/
    UTL_CHR_TYPE  [ 77] = UTL_CHR__UPP  ;			/* 'M'	*/
    UTL_CHR_TYPE  [ 78] = UTL_CHR__UPP  ;			/* 'N'	*/
    UTL_CHR_TYPE  [ 79] = UTL_CHR__UPP  ;			/* 'O'	*/

    UTL_CHR_TYPE  [ 80] = UTL_CHR__UPP  ;			/* 'P'	*/
    UTL_CHR_TYPE  [ 81] = UTL_CHR__UPP  ;			/* 'Q'	*/
    UTL_CHR_TYPE  [ 82] = UTL_CHR__UPP  ;			/* 'R'	*/
    UTL_CHR_TYPE  [ 83] = UTL_CHR__UPP  ;			/* 'S'	*/
    UTL_CHR_TYPE  [ 84] = UTL_CHR__UPP  ;			/* 'T'	*/
    UTL_CHR_TYPE  [ 85] = UTL_CHR__UPP  ;			/* 'U'	*/
    UTL_CHR_TYPE  [ 86] = UTL_CHR__UPP  ;			/* 'V'	*/
    UTL_CHR_TYPE  [ 87] = UTL_CHR__UPP  ;			/* 'W'	*/
    UTL_CHR_TYPE  [ 88] = UTL_CHR__UPP  ;			/* 'X'	*/
    UTL_CHR_TYPE  [ 89] = UTL_CHR__UPP  ;			/* 'Y'	*/

    UTL_CHR_TYPE  [ 90] = UTL_CHR__UPP  ;			/* 'Z'	*/
    UTL_CHR_TYPE  [ 91] = 0             ;
    UTL_CHR_TYPE  [ 92] = 0             ;
    UTL_CHR_TYPE  [ 93] = 0             ;
    UTL_CHR_TYPE  [ 94] = 0             ;
    UTL_CHR_TYPE  [ 95] = 0             ;
    UTL_CHR_TYPE  [ 96] = 0             ;
    UTL_CHR_TYPE  [ 97] = UTL_CHR__LOW  | UTL_CHR__XDG;		/* 'a'	*/
    UTL_CHR_TYPE  [ 98] = UTL_CHR__LOW  | UTL_CHR__XDG;		/* 'b'	*/
    UTL_CHR_TYPE  [ 99] = UTL_CHR__LOW  | UTL_CHR__XDG;		/* 'c'	*/

    UTL_CHR_TYPE  [100] = UTL_CHR__LOW  | UTL_CHR__XDG;		/* 'd'	*/
    UTL_CHR_TYPE  [101] = UTL_CHR__LOW  | UTL_CHR__XDG;		/* 'e'	*/
    UTL_CHR_TYPE  [102] = UTL_CHR__LOW  | UTL_CHR__XDG;		/* 'f'	*/
    UTL_CHR_TYPE  [103] = UTL_CHR__LOW  ;			/* 'g'	*/
    UTL_CHR_TYPE  [104] = UTL_CHR__LOW  ;			/* 'h'	*/
    UTL_CHR_TYPE  [105] = UTL_CHR__LOW  ;			/* 'i'	*/
    UTL_CHR_TYPE  [106] = UTL_CHR__LOW  ;			/* 'j'	*/
    UTL_CHR_TYPE  [107] = UTL_CHR__LOW  ;			/* 'k'	*/
    UTL_CHR_TYPE  [108] = UTL_CHR__LOW  ;			/* 'l'	*/
    UTL_CHR_TYPE  [109] = UTL_CHR__LOW  ;			/* 'm'	*/

    UTL_CHR_TYPE  [110] = UTL_CHR__LOW  ;			/* 'n'	*/
    UTL_CHR_TYPE  [111] = UTL_CHR__LOW  ;			/* 'o'	*/
    UTL_CHR_TYPE  [112] = UTL_CHR__LOW  ;			/* 'p'	*/
    UTL_CHR_TYPE  [113] = UTL_CHR__LOW  ;			/* 'q'	*/
    UTL_CHR_TYPE  [114] = UTL_CHR__LOW  ;			/* 'r'	*/
    UTL_CHR_TYPE  [115] = UTL_CHR__LOW  ;			/* 's'	*/
    UTL_CHR_TYPE  [116] = UTL_CHR__LOW  ;			/* 't'	*/
    UTL_CHR_TYPE  [117] = UTL_CHR__LOW  ;			/* 'u'	*/
    UTL_CHR_TYPE  [118] = UTL_CHR__LOW  ;			/* 'v'	*/
    UTL_CHR_TYPE  [119] = UTL_CHR__LOW  ;			/* 'w'	*/

    UTL_CHR_TYPE  [120] = UTL_CHR__LOW  ;			/* 'x'	*/
    UTL_CHR_TYPE  [121] = UTL_CHR__LOW  ;			/* 'y'	*/
    UTL_CHR_TYPE  [122] = UTL_CHR__LOW  ;			/* 'z'	*/
    UTL_CHR_TYPE  [123] = 0             ;
    UTL_CHR_TYPE  [124] = 0             ;
    UTL_CHR_TYPE  [125] = 0             ;
    UTL_CHR_TYPE  [126] = 0             ;
    UTL_CHR_TYPE  [127] = 0             ;
    UTL_CHR_TYPE  [128] = 0             ;
    UTL_CHR_TYPE  [129] = 0             ;

    UTL_CHR_TYPE  [130] = 0             ;
    UTL_CHR_TYPE  [131] = 0             ;
    UTL_CHR_TYPE  [132] = 0             ;
    UTL_CHR_TYPE  [133] = 0             ;
    UTL_CHR_TYPE  [134] = 0             ;
    UTL_CHR_TYPE  [135] = 0             ;
    UTL_CHR_TYPE  [136] = 0             ;
    UTL_CHR_TYPE  [137] = 0             ;
    UTL_CHR_TYPE  [138] = 0             ;
    UTL_CHR_TYPE  [139] = 0             ;

    UTL_CHR_TYPE  [140] = 0             ;
    UTL_CHR_TYPE  [141] = 0             ;
    UTL_CHR_TYPE  [142] = 0             ;
    UTL_CHR_TYPE  [143] = 0             ;
    UTL_CHR_TYPE  [144] = 0             ;
    UTL_CHR_TYPE  [145] = 0             ;
    UTL_CHR_TYPE  [146] = 0             ;
    UTL_CHR_TYPE  [147] = 0             ;
    UTL_CHR_TYPE  [148] = 0             ;
    UTL_CHR_TYPE  [149] = 0             ;

    UTL_CHR_TYPE  [150] = 0             ;
    UTL_CHR_TYPE  [151] = 0             ;
    UTL_CHR_TYPE  [152] = 0             ;
    UTL_CHR_TYPE  [153] = 0             ;
    UTL_CHR_TYPE  [154] = 0             ;
    UTL_CHR_TYPE  [155] = 0             ;
    UTL_CHR_TYPE  [156] = 0             ;
    UTL_CHR_TYPE  [157] = 0             ;
    UTL_CHR_TYPE  [158] = 0             ;
    UTL_CHR_TYPE  [159] = 0             ;

    UTL_CHR_TYPE  [160] = 0             ;
    UTL_CHR_TYPE  [161] = 0             ;
    UTL_CHR_TYPE  [162] = 0             ;
    UTL_CHR_TYPE  [163] = 0             ;
    UTL_CHR_TYPE  [164] = 0             ;
    UTL_CHR_TYPE  [165] = 0             ;
    UTL_CHR_TYPE  [166] = 0             ;
    UTL_CHR_TYPE  [167] = 0             ;
    UTL_CHR_TYPE  [168] = 0             ;
    UTL_CHR_TYPE  [169] = 0             ;

    UTL_CHR_TYPE  [170] = 0             ;
    UTL_CHR_TYPE  [171] = 0             ;
    UTL_CHR_TYPE  [172] = 0             ;
    UTL_CHR_TYPE  [173] = 0             ;
    UTL_CHR_TYPE  [174] = 0             ;
    UTL_CHR_TYPE  [175] = 0             ;
    UTL_CHR_TYPE  [176] = 0             ;
    UTL_CHR_TYPE  [177] = 0             ;
    UTL_CHR_TYPE  [178] = 0             ;
    UTL_CHR_TYPE  [179] = 0             ;

    UTL_CHR_TYPE  [180] = 0             ;
    UTL_CHR_TYPE  [181] = 0             ;
    UTL_CHR_TYPE  [182] = 0             ;
    UTL_CHR_TYPE  [183] = 0             ;
    UTL_CHR_TYPE  [184] = 0             ;
    UTL_CHR_TYPE  [185] = 0             ;
    UTL_CHR_TYPE  [186] = 0             ;
    UTL_CHR_TYPE  [187] = 0             ;
    UTL_CHR_TYPE  [188] = 0             ;
    UTL_CHR_TYPE  [189] = 0             ;

    UTL_CHR_TYPE  [190] = 0             ;
    UTL_CHR_TYPE  [191] = 0             ;
    UTL_CHR_TYPE  [192] = 0             ;
    UTL_CHR_TYPE  [193] = 0             ;
    UTL_CHR_TYPE  [194] = 0             ;
    UTL_CHR_TYPE  [195] = 0             ;
    UTL_CHR_TYPE  [196] = 0             ;
    UTL_CHR_TYPE  [197] = 0             ;
    UTL_CHR_TYPE  [198] = 0             ;
    UTL_CHR_TYPE  [199] = 0             ;

    UTL_CHR_TYPE  [200] = 0             ;
    UTL_CHR_TYPE  [201] = 0             ;
    UTL_CHR_TYPE  [202] = 0             ;
    UTL_CHR_TYPE  [203] = 0             ;
    UTL_CHR_TYPE  [204] = 0             ;
    UTL_CHR_TYPE  [205] = 0             ;
    UTL_CHR_TYPE  [206] = 0             ;
    UTL_CHR_TYPE  [207] = 0             ;
    UTL_CHR_TYPE  [208] = 0             ;
    UTL_CHR_TYPE  [209] = 0             ;

    UTL_CHR_TYPE  [210] = 0             ;
    UTL_CHR_TYPE  [211] = 0             ;
    UTL_CHR_TYPE  [212] = 0             ;
    UTL_CHR_TYPE  [213] = 0             ;
    UTL_CHR_TYPE  [214] = 0             ;
    UTL_CHR_TYPE  [215] = 0             ;
    UTL_CHR_TYPE  [216] = 0             ;
    UTL_CHR_TYPE  [217] = 0             ;
    UTL_CHR_TYPE  [218] = 0             ;
    UTL_CHR_TYPE  [219] = 0             ;

    UTL_CHR_TYPE  [220] = 0             ;
    UTL_CHR_TYPE  [221] = 0             ;
    UTL_CHR_TYPE  [222] = 0             ;
    UTL_CHR_TYPE  [223] = 0             ;
    UTL_CHR_TYPE  [224] = 0             ;
    UTL_CHR_TYPE  [225] = 0             ;
    UTL_CHR_TYPE  [226] = 0             ;
    UTL_CHR_TYPE  [227] = 0             ;
    UTL_CHR_TYPE  [228] = 0             ;
    UTL_CHR_TYPE  [229] = 0             ;

    UTL_CHR_TYPE  [230] = 0             ;
    UTL_CHR_TYPE  [231] = 0             ;
    UTL_CHR_TYPE  [232] = 0             ;
    UTL_CHR_TYPE  [233] = 0             ;
    UTL_CHR_TYPE  [234] = 0             ;
    UTL_CHR_TYPE  [235] = 0             ;
    UTL_CHR_TYPE  [236] = 0             ;
    UTL_CHR_TYPE  [237] = 0             ;
    UTL_CHR_TYPE  [238] = 0             ;
    UTL_CHR_TYPE  [239] = 0             ;

    UTL_CHR_TYPE  [240] = 0             ;
    UTL_CHR_TYPE  [241] = 0             ;
    UTL_CHR_TYPE  [242] = 0             ;
    UTL_CHR_TYPE  [243] = 0             ;
    UTL_CHR_TYPE  [244] = 0             ;
    UTL_CHR_TYPE  [245] = 0             ;
    UTL_CHR_TYPE  [246] = 0             ;
    UTL_CHR_TYPE  [247] = 0             ;
    UTL_CHR_TYPE  [248] = 0             ;
    UTL_CHR_TYPE  [249] = 0             ;

    UTL_CHR_TYPE  [250] = 0             ;
    UTL_CHR_TYPE  [251] = 0             ;
    UTL_CHR_TYPE  [252] = 0             ;
    UTL_CHR_TYPE  [253] = 0             ;
    UTL_CHR_TYPE  [254] = 0             ;
    UTL_CHR_TYPE  [255] = 0             ;

	/* ###------------------------------------------------------### */
	/*   character's converted to a value				*/
	/* ###------------------------------------------------------### */

    UTL_CHR_VALUE [  0] =  0            ;
    UTL_CHR_VALUE [  1] =  0            ;
    UTL_CHR_VALUE [  2] =  0            ;
    UTL_CHR_VALUE [  3] =  0            ;
    UTL_CHR_VALUE [  4] =  0            ;
    UTL_CHR_VALUE [  5] =  0            ;
    UTL_CHR_VALUE [  6] =  0            ;
    UTL_CHR_VALUE [  7] =  0            ;
    UTL_CHR_VALUE [  8] =  0            ;
    UTL_CHR_VALUE [  9] =  0            ;

    UTL_CHR_VALUE [ 10] =  0            ;
    UTL_CHR_VALUE [ 11] =  0            ;
    UTL_CHR_VALUE [ 12] =  0            ;
    UTL_CHR_VALUE [ 13] =  0            ;
    UTL_CHR_VALUE [ 14] =  0            ;
    UTL_CHR_VALUE [ 15] =  0            ;
    UTL_CHR_VALUE [ 16] =  0            ;
    UTL_CHR_VALUE [ 17] =  0            ;
    UTL_CHR_VALUE [ 18] =  0            ;
    UTL_CHR_VALUE [ 19] =  0            ;

    UTL_CHR_VALUE [ 20] =  0            ;
    UTL_CHR_VALUE [ 21] =  0            ;
    UTL_CHR_VALUE [ 22] =  0            ;
    UTL_CHR_VALUE [ 23] =  0            ;
    UTL_CHR_VALUE [ 24] =  0            ;
    UTL_CHR_VALUE [ 25] =  0            ;
    UTL_CHR_VALUE [ 26] =  0            ;
    UTL_CHR_VALUE [ 27] =  0            ;
    UTL_CHR_VALUE [ 28] =  0            ;
    UTL_CHR_VALUE [ 29] =  0            ;

    UTL_CHR_VALUE [ 30] =  0            ;
    UTL_CHR_VALUE [ 31] =  0            ;
    UTL_CHR_VALUE [ 32] =  0            ;
    UTL_CHR_VALUE [ 33] =  0            ;
    UTL_CHR_VALUE [ 34] =  0            ;
    UTL_CHR_VALUE [ 35] =  0            ;
    UTL_CHR_VALUE [ 36] =  0            ;
    UTL_CHR_VALUE [ 37] =  0            ;
    UTL_CHR_VALUE [ 38] =  0            ;
    UTL_CHR_VALUE [ 39] =  0            ;

    UTL_CHR_VALUE [ 40] =  0            ;
    UTL_CHR_VALUE [ 41] =  0            ;
    UTL_CHR_VALUE [ 42] =  0            ;
    UTL_CHR_VALUE [ 43] =  0            ;
    UTL_CHR_VALUE [ 44] =  0            ;
    UTL_CHR_VALUE [ 45] =  0            ;
    UTL_CHR_VALUE [ 46] =  0            ;
    UTL_CHR_VALUE [ 47] =  0            ;
    UTL_CHR_VALUE [ 48] =  0            ;			/* '0'	*/
    UTL_CHR_VALUE [ 49] =  1            ;			/* '1'	*/
    UTL_CHR_VALUE [ 50] =  2            ;			/* '2'	*/
    UTL_CHR_VALUE [ 51] =  3            ;			/* '3'	*/
    UTL_CHR_VALUE [ 52] =  4            ;			/* '4'	*/
    UTL_CHR_VALUE [ 53] =  5            ;			/* '5'	*/
    UTL_CHR_VALUE [ 54] =  6            ;			/* '6'	*/
    UTL_CHR_VALUE [ 55] =  7            ;			/* '7'	*/
    UTL_CHR_VALUE [ 56] =  8            ;			/* '8'	*/
    UTL_CHR_VALUE [ 57] =  9            ;			/* '9'	*/
    UTL_CHR_VALUE [ 58] =  0            ;
    UTL_CHR_VALUE [ 59] =  0            ;

    UTL_CHR_VALUE [ 60] =  0            ;
    UTL_CHR_VALUE [ 61] =  0            ;
    UTL_CHR_VALUE [ 62] =  0            ;
    UTL_CHR_VALUE [ 63] =  0            ;
    UTL_CHR_VALUE [ 64] =  0            ;
    UTL_CHR_VALUE [ 65] = 10            ;			/* 'A'	*/
    UTL_CHR_VALUE [ 66] = 11            ;			/* 'B'	*/
    UTL_CHR_VALUE [ 67] = 12            ;			/* 'C'	*/
    UTL_CHR_VALUE [ 68] = 13            ;			/* 'D'	*/
    UTL_CHR_VALUE [ 69] = 14            ;			/* 'E'	*/

    UTL_CHR_VALUE [ 70] = 15            ;			/* 'F'	*/
    UTL_CHR_VALUE [ 71] =  0            ;
    UTL_CHR_VALUE [ 72] =  0            ;
    UTL_CHR_VALUE [ 73] =  0            ;
    UTL_CHR_VALUE [ 74] =  0            ;
    UTL_CHR_VALUE [ 75] =  0            ;
    UTL_CHR_VALUE [ 76] =  0            ;
    UTL_CHR_VALUE [ 77] =  0            ;
    UTL_CHR_VALUE [ 78] =  0            ;
    UTL_CHR_VALUE [ 79] =  0            ;

    UTL_CHR_VALUE [ 80] =  0            ;
    UTL_CHR_VALUE [ 81] =  0            ;
    UTL_CHR_VALUE [ 82] =  0            ;
    UTL_CHR_VALUE [ 83] =  0            ;
    UTL_CHR_VALUE [ 84] =  0            ;
    UTL_CHR_VALUE [ 85] =  0            ;
    UTL_CHR_VALUE [ 86] =  0            ;
    UTL_CHR_VALUE [ 87] =  0            ;
    UTL_CHR_VALUE [ 88] =  0            ;
    UTL_CHR_VALUE [ 89] =  0            ;

    UTL_CHR_VALUE [ 90] =  0            ;
    UTL_CHR_VALUE [ 91] =  0            ;
    UTL_CHR_VALUE [ 92] =  0            ;
    UTL_CHR_VALUE [ 93] =  0            ;
    UTL_CHR_VALUE [ 94] =  0            ;
    UTL_CHR_VALUE [ 95] =  0            ;
    UTL_CHR_VALUE [ 96] =  0            ;
    UTL_CHR_VALUE [ 97] = 10            ;			/* 'a'	*/
    UTL_CHR_VALUE [ 98] = 11            ;			/* 'b'	*/
    UTL_CHR_VALUE [ 99] = 12            ;			/* 'c'	*/

    UTL_CHR_VALUE [100] = 13            ;			/* 'd'	*/
    UTL_CHR_VALUE [101] = 14            ;			/* 'e'	*/
    UTL_CHR_VALUE [102] = 15            ;			/* 'f'	*/
    UTL_CHR_VALUE [103] =  0            ;
    UTL_CHR_VALUE [104] =  0            ;
    UTL_CHR_VALUE [105] =  0            ;
    UTL_CHR_VALUE [106] =  0            ;
    UTL_CHR_VALUE [107] =  0            ;
    UTL_CHR_VALUE [108] =  0            ;
    UTL_CHR_VALUE [109] =  0            ;

    UTL_CHR_VALUE [110] =  0            ;
    UTL_CHR_VALUE [111] =  0            ;
    UTL_CHR_VALUE [112] =  0            ;
    UTL_CHR_VALUE [113] =  0            ;
    UTL_CHR_VALUE [114] =  0            ;
    UTL_CHR_VALUE [115] =  0            ;
    UTL_CHR_VALUE [116] =  0            ;
    UTL_CHR_VALUE [117] =  0            ;
    UTL_CHR_VALUE [118] =  0            ;
    UTL_CHR_VALUE [119] =  0            ;

    UTL_CHR_VALUE [120] =  0            ;
    UTL_CHR_VALUE [121] =  0            ;
    UTL_CHR_VALUE [122] =  0            ;
    UTL_CHR_VALUE [123] =  0            ;
    UTL_CHR_VALUE [124] =  0            ;
    UTL_CHR_VALUE [125] =  0            ;
    UTL_CHR_VALUE [126] =  0            ;
    UTL_CHR_VALUE [127] =  0            ;
    UTL_CHR_VALUE [128] =  0            ;
    UTL_CHR_VALUE [129] =  0            ;

    UTL_CHR_VALUE [130] =  0            ;
    UTL_CHR_VALUE [131] =  0            ;
    UTL_CHR_VALUE [132] =  0            ;
    UTL_CHR_VALUE [133] =  0            ;
    UTL_CHR_VALUE [134] =  0            ;
    UTL_CHR_VALUE [135] =  0            ;
    UTL_CHR_VALUE [136] =  0            ;
    UTL_CHR_VALUE [137] =  0            ;
    UTL_CHR_VALUE [138] =  0            ;
    UTL_CHR_VALUE [139] =  0            ;

    UTL_CHR_VALUE [140] =  0            ;
    UTL_CHR_VALUE [141] =  0            ;
    UTL_CHR_VALUE [142] =  0            ;
    UTL_CHR_VALUE [143] =  0            ;
    UTL_CHR_VALUE [144] =  0            ;
    UTL_CHR_VALUE [145] =  0            ;
    UTL_CHR_VALUE [146] =  0            ;
    UTL_CHR_VALUE [147] =  0            ;
    UTL_CHR_VALUE [148] =  0            ;
    UTL_CHR_VALUE [149] =  0            ;

    UTL_CHR_VALUE [150] =  0            ;
    UTL_CHR_VALUE [151] =  0            ;
    UTL_CHR_VALUE [152] =  0            ;
    UTL_CHR_VALUE [153] =  0            ;
    UTL_CHR_VALUE [154] =  0            ;
    UTL_CHR_VALUE [155] =  0            ;
    UTL_CHR_VALUE [156] =  0            ;
    UTL_CHR_VALUE [157] =  0            ;
    UTL_CHR_VALUE [158] =  0            ;
    UTL_CHR_VALUE [159] =  0            ;

    UTL_CHR_VALUE [160] =  0            ;
    UTL_CHR_VALUE [161] =  0            ;
    UTL_CHR_VALUE [162] =  0            ;
    UTL_CHR_VALUE [163] =  0            ;
    UTL_CHR_VALUE [164] =  0            ;
    UTL_CHR_VALUE [165] =  0            ;
    UTL_CHR_VALUE [166] =  0            ;
    UTL_CHR_VALUE [167] =  0            ;
    UTL_CHR_VALUE [168] =  0            ;
    UTL_CHR_VALUE [169] =  0            ;

    UTL_CHR_VALUE [170] =  0            ;
    UTL_CHR_VALUE [171] =  0            ;
    UTL_CHR_VALUE [172] =  0            ;
    UTL_CHR_VALUE [173] =  0            ;
    UTL_CHR_VALUE [174] =  0            ;
    UTL_CHR_VALUE [175] =  0            ;
    UTL_CHR_VALUE [176] =  0            ;
    UTL_CHR_VALUE [177] =  0            ;
    UTL_CHR_VALUE [178] =  0            ;
    UTL_CHR_VALUE [179] =  0            ;

    UTL_CHR_VALUE [180] =  0            ;
    UTL_CHR_VALUE [181] =  0            ;
    UTL_CHR_VALUE [182] =  0            ;
    UTL_CHR_VALUE [183] =  0            ;
    UTL_CHR_VALUE [184] =  0            ;
    UTL_CHR_VALUE [185] =  0            ;
    UTL_CHR_VALUE [186] =  0            ;
    UTL_CHR_VALUE [187] =  0            ;
    UTL_CHR_VALUE [188] =  0            ;
    UTL_CHR_VALUE [189] =  0            ;

    UTL_CHR_VALUE [190] =  0            ;
    UTL_CHR_VALUE [191] =  0            ;
    UTL_CHR_VALUE [192] =  0            ;
    UTL_CHR_VALUE [193] =  0            ;
    UTL_CHR_VALUE [194] =  0            ;
    UTL_CHR_VALUE [195] =  0            ;
    UTL_CHR_VALUE [196] =  0            ;
    UTL_CHR_VALUE [197] =  0            ;
    UTL_CHR_VALUE [198] =  0            ;
    UTL_CHR_VALUE [199] =  0            ;

    UTL_CHR_VALUE [200] =  0            ;
    UTL_CHR_VALUE [201] =  0            ;
    UTL_CHR_VALUE [202] =  0            ;
    UTL_CHR_VALUE [203] =  0            ;
    UTL_CHR_VALUE [204] =  0            ;
    UTL_CHR_VALUE [205] =  0            ;
    UTL_CHR_VALUE [206] =  0            ;
    UTL_CHR_VALUE [207] =  0            ;
    UTL_CHR_VALUE [208] =  0            ;
    UTL_CHR_VALUE [209] =  0            ;

    UTL_CHR_VALUE [210] =  0            ;
    UTL_CHR_VALUE [211] =  0            ;
    UTL_CHR_VALUE [212] =  0            ;
    UTL_CHR_VALUE [213] =  0            ;
    UTL_CHR_VALUE [214] =  0            ;
    UTL_CHR_VALUE [215] =  0            ;
    UTL_CHR_VALUE [216] =  0            ;
    UTL_CHR_VALUE [217] =  0            ;
    UTL_CHR_VALUE [218] =  0            ;
    UTL_CHR_VALUE [219] =  0            ;

    UTL_CHR_VALUE [220] =  0            ;
    UTL_CHR_VALUE [221] =  0            ;
    UTL_CHR_VALUE [222] =  0            ;
    UTL_CHR_VALUE [223] =  0            ;
    UTL_CHR_VALUE [224] =  0            ;
    UTL_CHR_VALUE [225] =  0            ;
    UTL_CHR_VALUE [226] =  0            ;
    UTL_CHR_VALUE [227] =  0            ;
    UTL_CHR_VALUE [228] =  0            ;
    UTL_CHR_VALUE [229] =  0            ;

    UTL_CHR_VALUE [230] =  0            ;
    UTL_CHR_VALUE [231] =  0            ;
    UTL_CHR_VALUE [232] =  0            ;
    UTL_CHR_VALUE [233] =  0            ;
    UTL_CHR_VALUE [234] =  0            ;
    UTL_CHR_VALUE [235] =  0            ;
    UTL_CHR_VALUE [236] =  0            ;
    UTL_CHR_VALUE [237] =  0            ;
    UTL_CHR_VALUE [238] =  0            ;
    UTL_CHR_VALUE [239] =  0            ;

    UTL_CHR_VALUE [240] =  0            ;
    UTL_CHR_VALUE [241] =  0            ;
    UTL_CHR_VALUE [242] =  0            ;
    UTL_CHR_VALUE [243] =  0            ;
    UTL_CHR_VALUE [244] =  0            ;
    UTL_CHR_VALUE [245] =  0            ;
    UTL_CHR_VALUE [246] =  0            ;
    UTL_CHR_VALUE [247] =  0            ;
    UTL_CHR_VALUE [248] =  0            ;
    UTL_CHR_VALUE [249] =  0            ;

    UTL_CHR_VALUE [250] =  0            ;
    UTL_CHR_VALUE [251] =  0            ;
    UTL_CHR_VALUE [252] =  0            ;
    UTL_CHR_VALUE [253] =  0            ;
    UTL_CHR_VALUE [254] =  0            ;
    UTL_CHR_VALUE [255] =  0            ;

	/* ###------------------------------------------------------### */
	/*   set the status						*/
	/* ###------------------------------------------------------### */

    UTL_STATUS |= UTL_STS__INITIALIZED;
    }
  }
