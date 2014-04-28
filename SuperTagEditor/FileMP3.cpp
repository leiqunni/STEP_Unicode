// ======================================================
// �T  �v    �F �l�o�R�t�@�C���Ǘ��N���X
// �^�[�Q�b�g�F Windows95/98/NT
// �����n    �F Visual C++ Ver 6.0
// �쐬��    �F MERCURY
// �쐬��    �F 00/01/18(��)
// ���쌠�\�L�F Copyright(C) 2000 MERCURY.
// ======================================================



// ======================================
// =====   �����R���p�C���t���O     =====
// ======================================



// ======================================
// =====   �C���N���[�h�t�@�C��     =====
// ======================================
#include "stdafx.h"
#include "FileMP3.h"
#include "supertageditor.h"
#include "DlgFileOverWrite.h"
#include "DlgFileNameChange.h"


#define USE_SCMPX_GENRE_ANIMEJ g_genreListSCMPX[255].bAddList /* BeachMonster 099 */

// ======================================
// =====           ��  ��           =====
// ======================================



// ======================================
// =====           �}�N��           =====
// ======================================



// ======================================
// =====       typedef�^enum        =====
// ======================================



// ======================================
// =====       �\���́^���p��       =====
// ======================================



// ======================================
// =====         const �ϐ�         =====
// ======================================



// ======================================
// =====        extern �ϐ�         =====
// ======================================
int	 g_nWriteTagProcFlag = 0;

// ======================================
// =====        static �ϐ�         =====
// ======================================
// �W���������̃e�[�u��
GENRE_LIST	g_genreListSCMPX[] = {
	{true,   0, L"Blues"},					// 0(ID3 Tag�݊�)
	{true,   1, L"Classic Rock"},			// 1(ID3 Tag�݊�)
	{true,   2, L"Country"},					// 2(ID3 Tag�݊�)
	{true,   3, L"Dance"},					// 3(ID3 Tag�݊�)
	{true,   4, L"Disco"},					// 4(ID3 Tag�݊�)
	{true,   5, L"Funk"},					// 5(ID3 Tag�݊�)
	{true,   6, L"Grunge"},					// 6(ID3 Tag�݊�)
	{true,   7, L"Hip-Hop"},					// 7(ID3 Tag�݊�)
	{true,   8, L"Jazz"},					// 8(ID3 Tag�݊�)
	{true,   9, L"Metal"},					// 9(ID3 Tag�݊�)
	{true,  10, L"New Age"},					// 10(ID3 Tag�݊�)
	{true,  11, L"Oldies"},					// 11(ID3 Tag�݊�)
	{true,  12, L"Other"},					// 12(ID3 Tag�݊�)
	{true,  13, L"Pop"},						// 13(ID3 Tag�݊�)
	{true,  14, L"R&B"},						// 14(ID3 Tag�݊�)
	{true,  15, L"Rap"},						// 15(ID3 Tag�݊�)
	{true,  16, L"Reggae"},					// 16(ID3 Tag�݊�)
	{true,  17, L"Rock"},					// 17(ID3 Tag�݊�)
	{true,  18, L"Techno"},					// 18(ID3 Tag�݊�)
	{true,  19, L"Industrial"},				// 19(ID3 Tag�݊�)
	{true,  20, L"Alternative"},				// 20(ID3 Tag�݊�)
	{true,  21, L"Ska"},						// 21(ID3 Tag�݊�)
	{true,  22, L"Death Metal"},				// 22(ID3 Tag�݊�)
	{true,  23, L"Pranks"},					// 23(ID3 Tag�݊�)
	{true,  24, L"Soundtrack"},				// 24(ID3 Tag�݊�)
	{true,  25, L"Euro-Techno"},				// 25(ID3 Tag�݊�)
	{true,  26, L"Ambient"},					// 26(ID3 Tag�݊�)
	{true,  27, L"Trip-Hop"},				// 27(ID3 Tag�݊�)
	{true,  28, L"Vocal"},					// 28(ID3 Tag�݊�)
	{true,  29, L"Jazz+Funk"},				// 29(ID3 Tag�݊�)
	{true,  30, L"Fusion"},					// 30(ID3 Tag�݊�)
	{true,  31, L"Trance"},					// 31(ID3 Tag�݊�)
	{true,  32, L"Classical"},				// 32(ID3 Tag�݊�)
	{true,  33, L"Instrumental"},			// 33(ID3 Tag�݊�)
	{true,  34, L"Acid"},					// 34(ID3 Tag�݊�)
	{true,  35, L"House"},					// 35(ID3 Tag�݊�)
	{true,  36, L"Game"},					// 36(ID3 Tag�݊�)
	{true,  37, L"Sound Clip"},				// 37(ID3 Tag�݊�)
	{true,  38, L"Gospel"},					// 38(ID3 Tag�݊�)
	{true,  39, L"Noise"},					// 39(ID3 Tag�݊�)
	{true,  40, L"AlternRock"},				// 40(ID3 Tag�݊�)
	{true,  41, L"Bass"},					// 41(ID3 Tag�݊�)
	{true,  42, L"Soul"},					// 42(ID3 Tag�݊�)
	{true,  43, L"Punk"},					// 43(ID3 Tag�݊�)
	{true,  44, L"Space"},					// 44(ID3 Tag�݊�)
	{true,  45, L"Meditative"},				// 45(ID3 Tag�݊�)
	{true,  46, L"Instrumental Pop"},		// 46(ID3 Tag�݊�)
	{true,  47, L"Instrumental Rock"},		// 47(ID3 Tag�݊�)
	{true,  48, L"Ethnic"},					// 48(ID3 Tag�݊�)
	{true,  49, L"Gothic"},					// 49(ID3 Tag�݊�)
	{true,  50, L"Darkwave"},				// 50(ID3 Tag�݊�)
	{true,  51, L"Techno-Industrial"},		// 51(ID3 Tag�݊�)
	{true,  52, L"Electronic"},				// 52(ID3 Tag�݊�)
	{true,  53, L"Pop-Folk"},				// 53(ID3 Tag�݊�)
	{true,  54, L"Eurodance"},				// 54(ID3 Tag�݊�)
	{true,  55, L"Dream"},					// 55(ID3 Tag�݊�)
	{true,  56, L"Southern Rock"},			// 56(ID3 Tag�݊�)
	{true,  57, L"Comedy"},					// 57(ID3 Tag�݊�)
	{true,  58, L"Cult"},					// 58(ID3 Tag�݊�)
	{true,  59, L"Gangsta"},					// 59(ID3 Tag�݊�)
	{true,  60, L"Top 40"},					// 60(ID3 Tag�݊�)
	{true,  61, L"Christian Rap"},			// 61(ID3 Tag�݊�)
	{true,  62, L"Pop/Funk"},				// 62(ID3 Tag�݊�)
	{true,  63, L"Jungle"},					// 63(ID3 Tag�݊�)
	{true,  64, L"Native American"},			// 64(ID3 Tag�݊�)
	{true,  65, L"Cabaret"},					// 65(ID3 Tag�݊�)
	{true,  66, L"New Wave"},				// 66(ID3 Tag�݊�)
	{true,  67, L"Psychedelic"},				// 67(ID3 Tag�݊�)
	{true,  68, L"Rave"},					// 68(ID3 Tag�݊�)
	{true,  69, L"Showtunes"},				// 69(ID3 Tag�݊�)
	{true,  70, L"Trailer"},					// 70(ID3 Tag�݊�)
	{true,  71, L"Lo-Fi"},					// 71(ID3 Tag�݊�)
	{true,  72, L"Tribal"},					// 72(ID3 Tag�݊�)
	{true,  73, L"Acid Punk"},				// 73(ID3 Tag�݊�)
	{true,  74, L"Acid Jazz"},				// 74(ID3 Tag�݊�)
	{true,  75, L"Polka"},					// 75(ID3 Tag�݊�)
	{true,  76, L"Retro"},					// 76(ID3 Tag�݊�)
	{true,  77, L"Musical"},					// 77(ID3 Tag�݊�)
	{true,  78, L"Rock & Roll"},				// 78(ID3 Tag�݊�)
	{true,  79, L"Hard Rock"},				// 79(ID3 Tag�݊�)
	{true,  80, L"Folk"},					// 80(ID3 Tag�݊�)
	{true,  81, L"Folk/Rock"},				// 81(ID3 Tag�݊�)
	{true,  82, L"National Folk"},			// 82(ID3 Tag�݊�)
	{true,  83, L"Swing"},					// 83(ID3 Tag�݊�)
	{true,  84, L"Fast-Fusion"},				// 84(Winamp�݊�)
	{true,  85, L"Bebob"},					// 85(Winamp�݊�)
	{true,  86, L"Latin"},					// 86(Winamp�݊�)
	{true,  87, L"Revival"},					// 87(Winamp�݊�)
	{true,  88, L"Celtic"},					// 88(Winamp�݊�)
	{true,  89, L"Bluegrass"},				// 89(Winamp�݊�)
	{true,  90, L"Avantgarde"},				// 90(Winamp�݊�)
	{true,  91, L"Gothic Rock"},				// 91(Winamp�݊�)
	{true,  92, L"Progressive Rock"},		// 92(Winamp�݊�)
	{true,  93, L"Psychedelic Rock"},		// 93(Winamp�݊�)
	{true,  94, L"Symphonic Rock"},			// 94(Winamp�݊�)
	{true,  95, L"Slow Rock"},				// 95(Winamp�݊�)
	{true,  96, L"Big Band"},				// 96(Winamp�݊�)
	{true,  97, L"Chorus"},					// 97(Winamp�݊�)
	{true,  98, L"Easy Listening"},			// 98(Winamp�݊�)
	{true,  99, L"Acoustic"},				// 99(Winamp�݊�)
	{true, 100, L"Humour"},					// 100(Winamp�݊�)
	{true, 101, L"Speech"},					// 101(Winamp�݊�)
	{true, 102, L"Chanson"},					// 102(Winamp�݊�)
	{true, 103, L"Opera"},					// 103(Winamp�݊�)
	{true, 104, L"Chamber Music"},			// 104(Winamp�݊�)
	{true, 105, L"Sonata"},					// 105(Winamp�݊�)
	{true, 106, L"Symphony"},				// 106(Winamp�݊�)
	{true, 107, L"Booty Bass"},				// 107(Winamp�݊�)
	{true, 108, L"Primus"},					// 108(Winamp�݊�)
	{true, 109, L"Porn Groove"},				// 109(Winamp�݊�)
	{true, 110, L"Satire"},					// 110(Winamp�݊�)
	{true, 111, L"Slow Jam"},				// 111(Winamp�݊�)
	{true, 112, L"Club"},					// 112(Winamp�݊�)
	{true, 113, L"Tango"},					// 113(Winamp�݊�)
	{true, 114, L"Samba"},					// 114(Winamp�݊�)
	{true, 115, L"Folklore"},				// 115(Winamp�݊�)
	{true, 116, L"Ballad"},					// 116(Winamp�݊�)
	{true, 117, L"Power Ballad"},			// 117(Winamp�݊�)
	{true, 118, L"Phythmic Soul"},			// 118(Winamp�݊�)
	{true, 119, L"Freestyle"},				// 119(Winamp�݊�)
	{true, 120, L"Duet"},					// 120(Winamp�݊�)
	{true, 121, L"Punk Rock"},				// 121(Winamp�݊�)
	{true, 122, L"Drum Solo"},				// 122(Winamp�݊�)
	{true, 123, L"A Cappella"},				// 123(Winamp�݊�)
	{true, 124, L"Euro-House"},				// 124(Winamp�݊�)
	{true, 125, L"Dance Hall"},				// 125(Winamp�݊�)
	{true, 126, L"Goa"},						// 126(Winamp�݊�)
	{true, 127, L"Drum & Bass"},				// 127(Winamp�݊�)
	{true, 128, L"Club-House"},				// 128(Winamp�݊�)
	{true, 129, L"Hardcore"},				// 129(Winamp�݊�)
	{true, 130, L"Terror"},					// 130(Winamp�݊�)
	{true, 131, L"Indie"},					// 131(Winamp�݊�)
	{true, 132, L"BritPop"},					// 132(Winamp�݊�)
	{true, 133, L"Negerpunk"},				// 133(Winamp�݊�)
	{true, 134, L"Polsk Punk"},				// 134(Winamp�݊�)
	{true, 135, L"Beat"},					// 135(Winamp�݊�)
	{true, 136, L"Christian Gangsta Rap"},	// 136(Winamp�݊�)
	{true, 137, L"Heavy Metal"},				// 137(Winamp�݊�)
	{true, 138, L"Black Metal"},				// 138(Winamp�݊�)
	{true, 139, L"Crossover"},				// 139(Winamp�݊�)
	{true, 140, L"Contemporary Christian"},	// 140(Winamp�݊�)
	{true, 141, L"Christian Rock"},			// 141(Winamp�݊�)
	{true, 142, L"Merengue"},				// 142(Winamp�݊�)
	{true, 143, L"Salsa"},					// 143(Winamp�݊�)
	{true, 144, L"Thrash Metal"},			// 144(Winamp�݊�)
	{true, 145, L"Anime"},					// 145(Winamp�݊�)
	{true, 146, L"JPop"},					// 146(Winamp�݊�)
	{true, 147, L"Synthpop"},				// 147(Winamp�݊�)
	{false, 148, L"����`(148)"},			// 148
	{false, 148, L"����`(148)"},			// 148
	{false, 149, L"����`(149)"},			// 149
	{false, 150, L"����`(150)"},			// 150
	{false, 151, L"����`(151)"},			// 151
	{false, 152, L"����`(152)"},			// 152
	{false, 153, L"����`(153)"},			// 153
	{false, 154, L"����`(154)"},			// 154
	{false, 155, L"����`(155)"},			// 155
	{false, 156, L"����`(156)"},			// 156
	{false, 157, L"����`(157)"},			// 157
	{false, 158, L"����`(158)"},			// 158
	{false, 159, L"����`(159)"},			// 159
	{false, 160, L"����`(160)"},			// 160
	{false, 161, L"����`(161)"},			// 161
	{false, 162, L"����`(162)"},			// 162
	{false, 163, L"����`(163)"},			// 163
	{false, 164, L"����`(164)"},			// 164
	{false, 165, L"����`(165)"},			// 165
	{false, 166, L"����`(166)"},			// 166
	{false, 167, L"����`(167)"},			// 167
	{false, 168, L"����`(168)"},			// 168
	{false, 169, L"����`(169)"},			// 169
	{false, 170, L"����`(170)"},			// 170
	{false, 171, L"����`(171)"},			// 171
	{false, 172, L"����`(172)"},			// 172
	{false, 173, L"����`(173)"},			// 173
	{false, 174, L"����`(174)"},			// 174
	{false, 175, L"����`(175)"},			// 175
	{false, 176, L"����`(176)"},			// 176
	{false, 177, L"����`(177)"},			// 177
	{false, 178, L"����`(178)"},			// 178
	{false, 179, L"����`(179)"},			// 179
	{false, 180, L"����`(180)"},			// 180
	{false, 181, L"����`(181)"},			// 181
	{false, 182, L"����`(182)"},			// 182
	{false, 183, L"����`(183)"},			// 183
	{false, 184, L"����`(184)"},			// 184
	{false, 185, L"����`(185)"},			// 185
	{false, 186, L"����`(186)"},			// 186
	{false, 187, L"����`(187)"},			// 187
	{false, 188, L"����`(188)"},			// 188
	{false, 189, L"����`(189)"},			// 189
	{false, 190, L"����`(190)"},			// 190
	{false, 191, L"����`(191)"},			// 191
	{false, 192, L"����`(192)"},			// 192
	{false, 193, L"����`(193)"},			// 193
	{false, 194, L"����`(194)"},			// 194
	{false, 195, L"����`(195)"},			// 195
	{false, 196, L"����`(196)"},			// 196
	{false, 197, L"����`(197)"},			// 197
	{false, 198, L"����`(198)"},			// 198
	{false, 199, L"����`(199)"},			// 199
	{false, 200, L"����`(200)"},			// 200
	{false, 201, L"����`(201)"},			// 201
	{false, 202, L"����`(202)"},			// 202
	{false, 203, L"����`(203)"},			// 203
	{false, 204, L"����`(204)"},			// 204
	{false, 205, L"����`(205)"},			// 205
	{false, 206, L"����`(206)"},			// 206
	{false, 207, L"����`(207)"},			// 207
	{false, 208, L"����`(208)"},			// 208
	{false, 209, L"����`(209)"},			// 209
	{false, 210, L"����`(210)"},			// 210
	{false, 211, L"����`(211)"},			// 211
	{false, 212, L"����`(212)"},			// 212
	{false, 213, L"����`(213)"},			// 213
	{false, 214, L"����`(214)"},			// 214
	{false, 215, L"����`(215)"},			// 215
	{false, 216, L"����`(216)"},			// 216
	{false, 217, L"����`(217)"},			// 217
	{false, 218, L"����`(218)"},			// 218
	{false, 219, L"����`(219)"},			// 219
	{false, 220, L"����`(220)"},			// 220
	{false, 221, L"����`(221)"},			// 221
	{false, 222, L"����`(222)"},			// 222
	{false, 223, L"����`(223)"},			// 223
	{false, 224, L"����`(224)"},			// 224
	{false, 225, L"����`(225)"},			// 225
	{false, 226, L"����`(226)"},			// 226
	{false, 227, L"����`(227)"},			// 227
	{false, 228, L"����`(228)"},			// 228
	{false, 229, L"����`(229)"},			// 229
	{false, 230, L"����`(230)"},			// 230
	{false, 231, L"����`(231)"},			// 231
	{false, 232, L"����`(232)"},			// 232
	{false, 233, L"����`(233)"},			// 233
	{false, 234, L"����`(234)"},			// 234
	{false, 235, L"����`(235)"},			// 235
	{false, 236, L"����`(236)"},			// 236
	{false, 237, L"����`(237)"},			// 237
	{false, 238, L"����`(238)"},			// 238
	{false, 239, L"����`(239)"},			// 239
	{false, 240, L"����`(240)"},			// 240
	{false, 241, L"����`(241)"},			// 241
	{false, 242, L"����`(242)"},			// 242
	{false, 243, L"����`(243)"},			// 243
	{false, 244, L"����`(244)"},			// 244
	{false, 245, L"����`(245)"},			// 245
	{false, 246, L"����`(246)"},			// 246
	{false, 247, L"����`(247)"},			// 247
	{false, 248, L"Heavy Rock(J)"},			// 248(SCMPX�݊�)
	{false, 249, L"Doom Rock(J)"},			// 249(SCMPX�݊�)
	{false, 250, L"J-POP(J)"},				// 250(SCMPX�݊�)
	{false, 251, L"Seiyu(J)"},				// 251(SCMPX�݊�)
	{false, 252, L"Tecno Ambient(J)"},		// 252(SCMPX�݊�)
	{false, 253, L"Moemoe(J)"},				// 253(SCMPX�݊�)
	{false, 254, L"Tokusatsu(J)"},			// 254(SCMPX�݊�)
	{false, 255, L"Anime(J)"},				// 255(SCMPX�݊�)
	{false, 255, L"���w��"},					// 255
	{false, 255, NULL},						// �I�[�R�[�h
};
USER_GENRE_LIST*	g_genreListUSER = NULL;



// ======================================
// =====     �֐��v���g�^�C�v       =====
// ======================================


// =============================================
// GetGenreNameSIF
// �T�v  : �W�������ԍ�����W�����������擾(SI�t�B�[���h�p)
// ����  : byGenre			= �W�������ԍ�
// �߂�l: const wchar_t *		= �W��������
// =============================================
const wchar_t *GetGenreNameSIF(BYTE byGenre)
{
	int		i;
	for (i = 0; g_genreListSCMPX[i].sName != NULL; i++) {
		if (g_genreListSCMPX[i].byGenre == byGenre) {
			if (byGenre == 0xff) {
				// SCMPX �݊����ǂ����ŕ������ς���
				return(g_genreListSCMPX[i].bAddList ? "Anime(J)" : "");
			}
			return(g_genreListSCMPX[i].sName);
		}
	}
	return(L"");
}

// =============================================
// GetGenreCode
// �T�v  : �W������������W�������ԍ����擾
// ����  : sGenre		= �W��������
// �߂�l: int			= �W�������ԍ�(-1:���Ή�)
// =============================================
int GetGenreCode(const wchar_t *sGenre)
{
	int		i;
	for (i = 0; g_genreListSCMPX[i].sName != NULL; i++) {
		if (_wcscmpi(g_genreListSCMPX[i].sName, sGenre) == 0) {
			return(g_genreListSCMPX[i].byGenre);
		}
	}
	for (i = 0; i < USER_GENRE_LIST_MAX; i++) {
		if (_wcscmpi(g_genreListUSER[i].sName, sGenre) == 0 && g_genreListUSER[i].bUse) {
			return(g_genreListUSER[i].byGenre);
		}
	}
	return(-1);
}

bool IsUserGenre(const wchar_t *sGenre)
{
	if (wcslen(sGenre) == 0) return false; /* WildCherry2 075 */
	int		i;
	for (i = 0; g_genreListSCMPX[i].sName != NULL; i++) {
		if (_wcscmpi(g_genreListSCMPX[i].sName, sGenre) == 0) {
			return false;
		}
	}
	for (i = 0; i < USER_GENRE_LIST_MAX; i++) { 

		if (_wcscmpi(g_genreListUSER[i].sName, sGenre) == 0 && g_genreListUSER[i].bUse) {
			return true;
		}
	}
	return true;
}

/* �����̂P�o�C�g�ڂ��ǂ����̌��� */
#ifndef iskanji
#define iskanji(c)		((unsigned char)(c) >= 0x81 && (unsigned char)(c) <= 0x9f || (unsigned char)(c) >= 0xe0 && (unsigned char)(c) <= 0xfc)
#endif
void StringCopyN(wchar_t *sDest, const wchar_t *sSrc, int nLen, BOOL bTerm)
{
	if (wcslen(sSrc) < (unsigned int)nLen) {
		if (bTerm) wcscpy(sDest, sSrc);
		else       memcpy(sDest, sSrc, wcslen(sSrc));
		return;
	}
	while(nLen > 0) {
		if (iskanji(*sSrc)) {
			if (nLen >= 2) {
				*sDest++ = *sSrc++;
				*sDest++ = *sSrc++;
			} else {
				if (bTerm) *sDest = '\0';
			}
			nLen -= 2;
		} else {
			*sDest++ = *sSrc++;
			nLen--;
		}
	}
}

static	bool MyChangeFileName(const wchar_t *sFileName, const wchar_t *sNewName)
{
	if (MoveFile(sFileName, sNewName) == FALSE) {
		CString	strBuffer;
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					  FORMAT_MESSAGE_FROM_SYSTEM |
					  FORMAT_MESSAGE_IGNORE_INSERTS,
					  NULL, GetLastError(),
					  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // �f�t�H���g����
					  (LPTSTR)&lpMsgBuf, 0, NULL);
		strBuffer.Format(L"�ύX�O�F%s\n�ύX��F%s\n\n%s", sFileName, sNewName, (const wchar_t *)lpMsgBuf);
		LocalFree(lpMsgBuf);
		MessageBox(NULL, strBuffer, L"�t�@�C������ύX�ł��܂���ł���", MB_ICONSTOP|MB_OK|MB_TOPMOST);
		return(false);
	}
	return(true);
}

static	bool MyCopyFile(const wchar_t *sFileName, const wchar_t *sNewName, bool bMoveFlag)
{
	BOOL	bResult;

	// �R�s�[�^�ړ������s
	if (bMoveFlag) {
		// �ړ���ɓ����̃t�@�C��������ꍇ�́A�\�ߍ폜����
		if (SetFileAttributes(sNewName, CFile::normal) == TRUE) {
			if (DeleteFile(sNewName) == FALSE) {
//				CString	strBuffer;
//				LPVOID lpMsgBuf;
//				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
//							  FORMAT_MESSAGE_FROM_SYSTEM |
//							  FORMAT_MESSAGE_IGNORE_INSERTS,
//							  NULL, GetLastError(),
//							  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // �f�t�H���g����
//							  (LPTSTR)&lpMsgBuf, 0, NULL);
//				strBuffer.Format(L"�t�@�C�����F%s\n\n%s", sNewName, (const wchar_t *)lpMsgBuf);
//				LocalFree(lpMsgBuf);
//				MessageBox(NULL, strBuffer, L"�t�@�C���̍폜�Ɏ��s���܂���", MB_OK/*MB_ABORTRETRYIGNORE*/|MB_TOPMOST);
//				return(false);
			}
		}
		bResult = MoveFile(sFileName, sNewName);
	} else {
		bResult = CopyFile(sFileName, sNewName, FALSE);
	}

	// �G���[����
	if (bResult == FALSE) {
		static	const wchar_t *sMessage[][2] = {
			{"�R�s�[���F%s\n�R�s�[��F%s\n\n%s", L"�t�@�C���̃R�s�[�Ɏ��s���܂���"},
			{"�ړ����F%s\n�ړ���F%s\n\n%s", L"�t�@�C���̈ړ��Ɏ��s���܂���"},
		};
		CString	strBuffer;
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					  FORMAT_MESSAGE_FROM_SYSTEM |
					  FORMAT_MESSAGE_IGNORE_INSERTS,
					  NULL, GetLastError(),
					  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // �f�t�H���g����
					  (LPTSTR)&lpMsgBuf, 0, NULL);
		strBuffer.Format(sMessage[bMoveFlag?1:0][0], sFileName, sNewName, (const wchar_t *)lpMsgBuf);
		LocalFree(lpMsgBuf);
		MessageBox(NULL, strBuffer, sMessage[bMoveFlag?1:0][1], MB_ICONSTOP|MB_OK|MB_TOPMOST);
		return(false);
	}
	return(true);
}

static	void ChangeFileAttr(const wchar_t *sFileName, DWORD dwAttr)
{
	DWORD	dwAttrNow;
	if ((dwAttrNow = GetFileAttributes((LPTSTR)sFileName)) != (DWORD)-1L) {
		if (dwAttrNow != dwAttr) {
			SetFileAttributes((LPTSTR)sFileName, dwAttr);
		}
	}
}

// �Ōオ '\\' �ɂȂ��Ă��邩�ǂ����̃`�F�b�N�֐�
bool IsFolderName(const wchar_t *sName)
{
	bool	bResult = false;
	while(*sName != NULL) {
		if (iskanji(*sName)) {
			bResult = false;
			sName += 2;
		} else {
			bResult = (*sName == '\\') ? true : false;
			sName++;
		}
	}
	return(bResult);
}


// =============================================
// CFileMP3::CFileMP3
// Func  : �R���X�g���N�^
// Input : none
// Output: none
// =============================================
CFileMP3::CFileMP3()
{
	m_fileMP3.fileSpecificInfo = NULL;
	Initialize();
}

// =============================================
// CFileMP3::~CFileMP3
// Func  : �f�X�g���N�^
// Input : none
// Output: none
// =============================================
CFileMP3::~CFileMP3()
{
	//if (m_fileMP3.fileOGG != NULL)	delete m_fileMP3.fileOGG; /* Conspiracy 196 */
}

// =============================================
// CFileMP3::InitData
// �T�v  : MP3 �t�@�C�����̍\���̂����������܂�
// ����  : fileMP3		= ����������\����
// �߂�l: none
// =============================================
void CFileMP3::InitData(FILE_MP3 *fileMP3)
{
	extern void InitFileSpecificInfo(FILE_MP3* pFileMP3);
	if (fileMP3->fileSpecificInfo != NULL) {
		InitFileSpecificInfo(fileMP3);
		fileMP3->fileSpecificInfo = NULL;
	}

	fileMP3->bModifyFlag	= false;	// �O������ҏW���ꂽ���ǂ����̃t���O
	fileMP3->bCheckFlag		= false;	// �`�F�b�N���
	fileMP3->lFileSize		= 0L;		// �t�@�C���T�C�Y
	fileMP3->time			= CTime(0);	// �t�@�C���X�V��
	fileMP3->timeCreate		= CTime(0);	// �t�@�C���쐬��
#ifdef USE_VBMP3_DLL
	fileMP3->nPlayTime		= 0;		// ���t����(�P�ʁF�b)
#endif
	fileMP3->nPlayTime		= -1;		// ���t����(�P�ʁF�b) /* Conspiracy 195 */
	fileMP3->bExistLyricFile = false;	// �̎��t�@�C���̑���
	fileMP3->nFormat		= FILE_FORMAT_UNKNOWN;	// �t�@�C���`���F���m�̌`��
	fileMP3->strFullPathName.Empty();	// �t�@�C����(�t���p�X)
	fileMP3->strFileName.Empty();		// �t�@�C����
	fileMP3->strFilePath.Empty();		// �p�X��

	// ID3 �̃N���A
	InitDataID3(fileMP3); /* STEP 029 */

	// SIF �̃N���A
	InitDataSIF(fileMP3);
}

void CFileMP3::InitDataID3(FILE_MP3 *fileMP3) /* STEP 029 */
{
	fileMP3->strTrackName.Empty();		// �g���b�N��
	fileMP3->strArtistName.Empty();		// �A�[�e�B�X�g��
	fileMP3->strAlbumName.Empty();		// �A���o����
	fileMP3->strComment.Empty();		// �R�����g
	fileMP3->strYear.Empty();			// �����[�X�N��
	fileMP3->byTrackNumber	= 0xff;		// �g���b�N�ԍ�(���l�ҏW�p)
	fileMP3->strTrackNumber.Empty();	// �g���b�N�ԍ�(������ҏW�p)
	fileMP3->byDiskNumber	= 0xff;
	fileMP3->strDiskNumber.Empty();
	fileMP3->byGenre		= 0xff;		// �W�������ԍ�
	fileMP3->strGenre.Empty();			// �W��������
}

// =============================================
//  CFileMP3::InitDataSIF
//  �T�v  : MP3 �t�@�C�����̍\���̂����������܂�(SIF�֘A�̂�)
//  ����  : fileMP3		= ����������\����
//  �߂�l: �Ȃ�
// =============================================
void CFileMP3::InitDataSIF(FILE_MP3 *fileMP3)
{
	// RIFF MP3 �� SI �t�B�[���h
	fileMP3->strTrackNameSI.Empty();	// �Ȗ�
	fileMP3->strArtistNameSI.Empty();	// �A�[�e�B�X�g��
	fileMP3->strAlbumNameSI.Empty();	// ���i��
	fileMP3->strCommentSI.Empty();		// �R�����g������
	fileMP3->strYearSI.Empty();			// �����[�X�N��
	fileMP3->strGenreSI.Empty();		// �W��������
	fileMP3->strCopyrightSI.Empty();	// ���쌠
	fileMP3->strEngineerSI.Empty();		// �G���W�j�A
	fileMP3->strSourceSI.Empty();		// �\�[�X
	fileMP3->strSoftwareSI.Empty();		// �\�t�g�E�F�A
	fileMP3->strKeywordSI.Empty();		// �L�[���[�h
	fileMP3->strTechnicianSI.Empty();	// �Z�p��
	fileMP3->strLyricSI.Empty();		// �̎�
	fileMP3->strCommissionSI.Empty();	// �R�~�b�V����

	if (IsUserGenre(fileMP3->strGenre)) {
		fileMP3->strGenre = GetGenreNameSIF(fileMP3->byGenre);
	}
	fileMP3->strTrackNumber.Empty();
	if (fileMP3->byTrackNumber != 0xFF) {
		fileMP3->strTrackNumber.Format(L"%d", fileMP3->byTrackNumber);
	}
	fileMP3->strTrackNumberSI.Empty();
	fileMP3->strWriterSI.Empty();		// �쎌
	fileMP3->strComposerSI.Empty();		// ���
	fileMP3->strAlbmArtistSI.Empty();	// Albm.�A�[�e�B�X�g
	fileMP3->strOrigArtistSI.Empty();	// Orig.�A�[�e�B�X�g
	fileMP3->strURLSI.Empty();			// URL
	fileMP3->strEncodest.Empty();		// �G���R�[�h�����l
	fileMP3->strOther.Empty();			// ���̑�
}

// =============================================
// CFileMP3::Initialize
// �T�v  : ����������
// ����  : none
// �߂�l: none
// =============================================
void CFileMP3::Initialize(void)
{
	//m_fileMP3.fileSpecificInfo = NULL;
	InitData(&m_fileMP3);
}

// =============================================
// CFileMP3::DeleteLineEndSpace
// �T�v  : �s���̃X�y�[�X����菜��
// ����  : sBuffer		= ������
// �߂�l: none
// =============================================
void CFileMP3::DeleteLineEndSpace(wchar_t *sBuffer)
{
	int		nPos = wcslen(sBuffer) - 1;
	while(nPos >= 0 && sBuffer[nPos] == ' ') {
		sBuffer[nPos] = '\0';
		nPos--;
	}
}

// =============================================
//  CFileMP3::Attach
//  �T�v  : �N���X�Ƀt�@�C���Ɋ֘A�t������
//  ����  : sFileName	= �t�@�C����
//  �߂�l: bool		= true:����I�� / false:�G���[
// =============================================
bool CFileMP3::Attach(const wchar_t *sFileName)
{
	Initialize();

	// �^�C���X�^���v���擾
	CFileStatus	fileStatus;
	if (CFile::GetStatus(sFileName, fileStatus) == FALSE || fileStatus.m_mtime == -1) {
		fileStatus.m_mtime = CTime(0);
		fileStatus.m_ctime = CTime(0);
	}
	m_fileMP3.time			= fileStatus.m_mtime;	// �t�@�C���X�V��
	m_fileMP3.timeCreate	= fileStatus.m_ctime;	// �t�@�C���쐬��
	m_fileMP3.lFileSize		= fileStatus.m_size;	// �t�@�C���T�C�Y

	// �t���p�X���p�X���ƃt�@�C�����ɕ���
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	ZeroMemory(ext, sizeof(ext));
	_tsplitpath(sFileName, drive, dir, fname, ext);
	m_fileMP3.strFilePath.Format(L"%s%s", drive, dir);
	m_fileMP3.strFileName.Format(L"%s%s", fname, ext);
	m_fileMP3.strFullPathName = sFileName;

	// �t�@�C�����̓ǂݍ���
	extern bool LoadFile(const wchar_t *sFileName, const wchar_t *sExt, FILE_MP3* pFileMP3);
	if (LoadFile(sFileName, &ext[1], &m_fileMP3) == false) {
		Initialize();
		return(false);
	}

	// �̎��t�@�C���̑��݂��`�F�b�N
	if (g_bOptSearchLyricFile) {
		// �̎��t�@�C��������
		m_fileMP3.bExistLyricFile = SearchLyricsFile(&m_fileMP3).IsEmpty() ? false : true;
	}

	return(true);
}

// =============================================
//  CFileMP3::Detach
//  �T�v  : �N���X�ƃt�@�C���̊֘A�t�����폜����
//  ����  : �Ȃ�
//  �߂�l: �Ȃ�
// =============================================
void CFileMP3::Detach(void)
{
	Initialize();
}

// =============================================
//  CFileMP3::WriteTag
//  �T�v  : �^�O���̍X�V
//  ����  : fileMP3		= �t�@�C�����
//        : bKeepTimeStamp= �^�C���X�^���v��ێ�����t���O
//  �߂�l: bool		= true:����I�� / false:�G���[
// =============================================
bool CFileMP3::WriteTag(FILE_MP3 *fileMP3, bool bKeepTimeStamp)
{
	CFileStatus	fileStatus;
	bool	bResult = false;

	if (g_nWriteTagProcFlag == 3) {
		return(false);						// �ȍ~���~
	}

	// �^�C���X�^���v���擾
	if (CFile::GetStatus(fileMP3->strFullPathName, fileStatus) == FALSE) {
		return(false);
	}
	if (fileStatus.m_mtime == -1)	fileStatus.m_mtime = fileStatus.m_ctime; /* 2005.10.11 ���������������ꍇ�ɗ����Ȃ��悤�� */
	if (fileStatus.m_atime == -1)	fileStatus.m_atime = fileStatus.m_mtime; /* 2005.10.11 ���������������ꍇ�ɗ����Ȃ��悤�� */

	// �ǂݏo����p�t�@�C���́A�㏑���m�F���s��
	if (fileStatus.m_attribute & CFile::readOnly) {
		if (g_nWriteTagProcFlag != 1) {
			// �㏑���m�F�_�C�A���O���J��
			CDlgFileOverWrite	dialog;
			dialog.m_strFileName = fileMP3->strFullPathName;
			dialog.m_strSize.Format(L"%ld byte", fileStatus.m_size);
			if (fileStatus.m_mtime.GetTime() < 0) {
				dialog.m_strTimeStamp.Format(L"----/--/-- --:--:--");
			} else {
				dialog.m_strTimeStamp.Format(L"%04d/%02d/%02d %02d:%02d:%02d",
											 fileStatus.m_mtime.GetYear(),
											 fileStatus.m_mtime.GetMonth(),
											 fileStatus.m_mtime.GetDay(),
											 fileStatus.m_mtime.GetHour(),
											 fileStatus.m_mtime.GetMinute(),
											 fileStatus.m_mtime.GetSecond());
			}
			dialog.DoModal();
			g_nWriteTagProcFlag = dialog.m_nResult;
			switch(dialog.m_nResult) {
			case 0:				// ���̃t�@�C�����㏑��
			case 1:				// �ȍ~�S�ď㏑��
				break;
			case 2:				// �X�L�b�v
			case 3:				// ���~
			default:
				return(false);
			}
		}

		// �ǂݍ��ݐ�p����������
		SetFileAttributes(fileMP3->strFullPathName, CFile::normal);
		// �ύX��ɑ�����߂����邽�߂� bKeepTimeStamp �� true �ɂ���
		bKeepTimeStamp = true;
	}

	extern bool SaveFile(FILE_MP3* pFileMP3);
	if ((bResult = SaveFile(fileMP3)) == true) {
		// �t�@�C�����ϊ�
		//bResult = ConvFileName(fileMP3);
	}

	// �^�C���X�^���v���t�@�C���X�V�O�ɖ߂�
	if (bResult) {
		if (bKeepTimeStamp) {
			if (fileMP3->time.GetTime() != -1) {
				// �t�@�C���X�V���Ԃ�ݒ�
				fileStatus.m_mtime = fileMP3->time;
				if (g_bOptSyncCreateTime) fileStatus.m_ctime = fileMP3->time;
			}
			TRY {
				CFile::SetStatus(fileMP3->strFullPathName, fileStatus);
			}
			CATCH(CFileException, e) {
				CString	strMsg;
				strMsg.Format(L"%s ���I�[�v���ł��܂���ł���", fileMP3->strFullPathName);
				MessageBox(NULL, strMsg, L"�^�C���X�^���v�̍X�V�G���[", MB_ICONSTOP|MB_OK|MB_TOPMOST);
				bResult = false;
			}
			END_CATCH
		} else {
			// �X�V��̃^�C���X�^���v���擾
			if (CFile::GetStatus(fileMP3->strFullPathName, fileStatus) != FALSE) {
				fileMP3->time = fileStatus.m_mtime;
			}
		}
	}

	return(bResult);
}

// =============================================
// CFileMP3::SearchFileReent
// �T�v  : �t�@�C�������F��������
// ����  : sDir			= ��������f�B���N�g��
//       : sTargetName	= ��������t�@�C����
// �߂�l: CString		= ���������t�@�C���̃t���p�X(IsEmpty():������)
// =============================================
CString CFileMP3::SearchFileReent(const wchar_t *sDir, const wchar_t *sTargetName)
{
	HANDLE	hFindFile;
	WIN32_FIND_DATA	data;
	CString	strTargetFile;

	// ����f�B���N�g���̑S�Ẵt�@�C��������
	// �����t�@�C���̃p�^�[����ݒ�
	CString	strCurFile;
	strCurFile.Format(L"%s%s", sDir, sTargetName);
	if ((hFindFile = FindFirstFile(strCurFile, &data)) != INVALID_HANDLE_VALUE) {
		do {
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				// �t�@�C����������
				strCurFile.Format(L"%s%s", sDir, data.cFileName);
				return(strCurFile);
			}
		} while(FindNextFile(hFindFile, &data) == TRUE);
	}
	if (hFindFile != INVALID_HANDLE_VALUE) FindClose(hFindFile);

	// �T�u�f�B���N�g���̌���
	if (g_bOptSearchLyricsSubDir == true) {
		strCurFile.Format(L"%s*.*", sDir);
		if ((hFindFile = FindFirstFile(strCurFile, &data)) != INVALID_HANDLE_VALUE) {
			do {
				if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
					if (wcscmp(data.cFileName, L"." ) != 0		// �J�����g�f�B���N�g���ȊO
					&&  wcscmp(data.cFileName, L"..") != 0		// �e�f�B���N�g���ȊO
					&& (data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == 0 /* STEP 032 */) { // �B���t�H���_�ȊO
						// �T�u�f�B���N�g����������
						strCurFile.Format(L"%s%s\\", sDir, data.cFileName);
						strTargetFile = SearchFileReent(strCurFile, sTargetName);
						if (strTargetFile.IsEmpty() == false) {
							break;				// �t�@�C������
						}
					}
				}
			} while(FindNextFile(hFindFile, &data) == TRUE);
		}
		if (hFindFile != INVALID_HANDLE_VALUE) FindClose(hFindFile);
	}

	return(strTargetFile);
}

// =============================================
//  CFileMP3::SearchLyricsFile
//  �T�v  : �̎��t�@�C���̌���
//        : �D�揇�ʁFMP3�Ɠ����t�H���_���̎��t�H���_���̎��t�H���_�̃T�u�f�B���N�g��
//  ����  : fileMP3		= �t�@�C�����
//  �߂�l: CString		= �̎��t�@�C����(������Ȃ������ꍇ�͋�)
// =============================================
CString CFileMP3::SearchLyricsFile(FILE_MP3 *fileMP3)
{
	wchar_t	sTextName[FILENAME_MAX+1];

	// �܂��� MP3 �t�@�C���Ɠ����t�H���_���`�F�b�N
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME];
	_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, NULL);
	// .lrc ������
	_tmakepath(sTextName, drive, dir, fname, L".lrc");
	if (GetFileAttributes(sTextName) != 0xFFFFFFFF) {
		// �t�@�C���𔭌�
		return(CString(sTextName));
	}
	// .txt ������
	_tmakepath(sTextName, drive, dir, fname, L".txt");
	if (GetFileAttributes(sTextName) != 0xFFFFFFFF) {
		// �t�@�C���𔭌�
		return(CString(sTextName));
	}

	// �̎��t�@�C�����쐬
	if (g_bOptSetLyricsDir == true && g_strOptLyricsPath.IsEmpty() == false) {
		// �w�肳�ꂽ�t�H���_
		wchar_t	sLyricsPath[FILENAME_MAX+1];
		CString	strTarget;
		_tsplitpath(fileMP3->strFullPathName, NULL, NULL, fname, NULL);
		wcscpy(sLyricsPath, g_strOptLyricsPath);
		if (IsFolderName(sLyricsPath) == false) {
			wcscat(sLyricsPath, L"\\");
		}
		// .lrc ������
		strTarget.Format(L"%s.lrc", fname);
		strTarget = SearchFileReent(sLyricsPath, strTarget);
		if (strTarget.IsEmpty() == false
		&&  GetFileAttributes(strTarget) != 0xFFFFFFFF) {
			// �t�@�C���𔭌�
			return(strTarget);
		}
		// .txt ������
		strTarget.Format(L"%s.txt", fname);
		strTarget = SearchFileReent(sLyricsPath, strTarget);
		if (strTarget.IsEmpty() == false
		&&  GetFileAttributes(strTarget) != 0xFFFFFFFF) {
			// �t�@�C���𔭌�
			return(strTarget);
		}
	}

	// ������Ȃ�����
	return(CString(L""));
}

// =============================================
//  CFileMP3::ConvFileName
//  �T�v  : �t�@�C�����̕ύX
//        : ���V�����t�@�C������ fileMP3->strFileName ���g�p
//  ����  : fileMP3		= �t�@�C�����
//  �߂�l: bool		= true:����I�� / false:�G���[
// =============================================
bool CFileMP3::ConvFileName(FILE_MP3 *fileMP3)
{
	// �t�@�C�����𕪉�
	CString	strFileName;
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, ext);
	strFileName.Format(L"%s%s", fname, ext);

	if (wcscmp(strFileName, fileMP3->strFileName) != 0) {
		// �t�@�C�������ύX����Ă���
		if (g_bConfFileNameMaxCheck) {
			if (fileMP3->strFileName.GetLength() > g_nConfFileNameMaxChar) {
				// �t�@�C�����������I�[�o�[
				_tsplitpath(fileMP3->strFileName, NULL, NULL, fname, ext);
				CDlgFileNameChange dialog;
				dialog.m_nMaxChar = g_nConfFileNameMaxChar - wcslen(ext);
				dialog.m_strFileName = fname;
				dialog.m_strOrgFileName = fname;
				//dialog.m_strMsg.Format(L"�t�@�C������ %d �����ȓ��ɕύX���Ă�������", dialog.m_nMaxChar);
				dialog.m_strMsgFormat = L"�t�@�C������ %d(%d) �����ȓ��ɕύX���Ă�������";
				if (dialog.DoModal() == IDOK) {
					fileMP3->strFileName = dialog.m_strFileName + ext;
					_tsplitpath(fileMP3->strFileName, NULL, NULL, fname, ext);
				}
			}
		}
		wchar_t	sNewName[FILENAME_MAX+1];
		_tmakepath(sNewName, drive, dir, NULL, NULL);
		wcscat(sNewName, fileMP3->strFileName);
		if (MyChangeFileName(fileMP3->strFullPathName, sNewName) == false) {
			return(false);
		}

		// �����̃e�L�X�g�t�@�C���̃t�@�C�������ϊ�����
		if (g_bOptChangeTextFile) {
			CString	strLyricsFile;
			// �̎��t�@�C��������
			strLyricsFile = SearchLyricsFile(fileMP3);
			if (strLyricsFile.IsEmpty() == false) {
				// ���������̎��t�@�C���̃p�X�𕪉�
				_tsplitpath(strLyricsFile, drive, dir, fname, ext);

				// �̎��t�@�C�������l�[������
				wchar_t	sNewText[FILENAME_MAX+1];
				_tsplitpath(fileMP3->strFileName, NULL, NULL, fname, NULL);
				_tmakepath(sNewText, drive, dir, fname, ext);
				if (MyChangeFileName(strLyricsFile, sNewText) == false) {
					// return(false);
				}
			}
		}

		// �t�@�C�������X�V����
		fileMP3->strFullPathName = sNewName;
	}

	return(true);
}

// =============================================
//  CFileMP3::CopyFile
//  �T�v  : �t�@�C���̃R�s�[�^�ړ�
//  ����  : fileMP3		= �t�@�C�����
//        : sNewDir		= �ړ���t�H���_��
//        : bMoveFlag	= �t���O(true:�ړ�/false:�R�s�[)
//  �߂�l: bool		= true:����I�� / false:�G���[
// =============================================
bool CFileMP3::CopyFile(FILE_MP3 *fileMP3, const wchar_t *sNewDir, bool bMoveFlag)
{
	// �t�@�C�����𕪉�
	CString	strFileName;
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, ext);
	strFileName.Format(L"%s%s", fname, ext);

	if (_wcscmpi(fileMP3->strFilePath, sNewDir) != 0) {
		// �t�@�C�������ύX����Ă���
		CString	strNewName;
		strNewName.Format(L"%s%s", sNewDir, strFileName);
		if (MyCopyFile(fileMP3->strFullPathName, strNewName, bMoveFlag) == false) {
			// �t�@�C���̃R�s�[�^�ړ��Ɏ��s!!
			return(false);
		}

		// �ړ��̏ꍇ�́A�̎��t�@�C�����ړ�����
		if (g_bSyncLyricsFileMove && bMoveFlag == true) {
			wchar_t	sLyricsFile[FILENAME_MAX+1];
			// MP3 �t�@�C���Ɠ����t�H���_�ɂ���̎��t�@�C��������
			_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, ext);
			// .lrc => .txt �̏��Ō���
			int i; for (i = 0; i < 2; i++) {
				LPSTR	sLyricsExt = (i == 0) ? ".lrc" : ".txt";
				_tmakepath(sLyricsFile, drive, dir, fname, sLyricsExt);
				if (GetFileAttributes(sLyricsFile) != 0xFFFFFFFF) {
					// �t�@�C���𔭌��F�̎��t�@�C�����ړ�����
					CString	strNewName;
					strNewName.Format(L"%s%s%s", sNewDir, fname, sLyricsExt);
					if (MyCopyFile(sLyricsFile, strNewName, true) == false) {
						// ���s!!
						// return(false);
					}
					break;
				}
			}
		}

		// �Ǘ����̃t�@�C�������X�V����
		if (bMoveFlag) {
			fileMP3->strFilePath = sNewDir;
			fileMP3->strFullPathName = strNewName;
		}
	}

	return(true);
}

CString CFileMP3::GetIntTrackNo(const CString &no)
{
	//�g���b�N�ԍ�
	if (IsNumeric(no)) {
		return no;
	} else {
		/* BeachMonster 094 */
		{
			int index = 0;
			for (int i=1;i<no.GetLength();i++) {
				if (IsNumeric(no.Left(i))) {
					index = i;
					continue;
				} else {
					break;
				}
			}
			if (index == 0) {
				//return "255";
			} else {
				CString track;
				track.Format(L"%d",_wtoi(no.Left(index)));
				return track;
			}
		}
		{
			int index = 0;
			for (int i=1;i<no.GetLength();i++) {
				if (IsNumeric(no.Right(i))) {
					index = i;
					continue;
				} else {
					break;
				}
			}
			if (index == 0) {
				return "";
			} else {
				CString track;
				track.Format(L"%d",_wtoi(no.Right(index)));
				return track;
			}
		}
	}
}

CString CFileMP3::GetIntDiskNo(const CString &no)
{
	//�g���b�N�ԍ�
	if (IsNumeric(no)) {
		return no;
	} else {
		/* BeachMonster 094 */
		{
			int index = 0;
			for (int i=1;i<no.GetLength();i++) {
				if (IsNumeric(no.Left(i))) {
					index = i;
					continue;
				} else {
					break;
				}
			}
			if (index == 0) {
				//return "255";
			} else {
				CString disk;
				disk.Format(L"%d",_wtoi(no.Left(index)));
				return disk;
			}
		}
		{
			int index = 0;
			for (int i=1;i<no.GetLength();i++) {
				if (IsNumeric(no.Right(i))) {
					index = i;
					continue;
				} else {
					break;
				}
			}
			if (index == 0) {
				return "";
			} else {
				CString disk;
				disk.Format(L"%d",_wtoi(no.Right(index)));
				return disk;
			}
		}
	}
}


bool CFileMP3::IsNumeric(const CString &str)
{
	if (str.IsEmpty()) {
		return TRUE/*FALSE*/; /* WildCherry 063 */
	}
	for (int i=0;i<str.GetLength();i++) {
		if (_ismbblead(str[i])) {
			// �������[�f�B���O�o�C�g
			i++;
			return FALSE;
		} else {
			if (!isdigit(str[i])) {
				return FALSE;
			}
		}
	}
	return TRUE;
}
