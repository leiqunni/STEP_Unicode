// ======================================================
// 概  要    ： ＭＰ３ファイル管理クラス
// ターゲット： Windows95/98/NT
// 処理系    ： Visual C++ Ver 6.0
// 作成者    ： MERCURY
// 作成日    ： 00/01/18(火)
// 著作権表記： Copyright(C) 2000 MERCURY.
// ======================================================



// ======================================
// =====   条件コンパイルフラグ     =====
// ======================================



// ======================================
// =====   インクルードファイル     =====
// ======================================
#include "stdafx.h"
#include "FileMP3.h"
#include "supertageditor.h"
#include "DlgFileOverWrite.h"
#include "DlgFileNameChange.h"


#define USE_SCMPX_GENRE_ANIMEJ g_genreListSCMPX[255].bAddList /* BeachMonster 099 */

// ======================================
// =====           定  数           =====
// ======================================



// ======================================
// =====           マクロ           =====
// ======================================



// ======================================
// =====       typedef／enum        =====
// ======================================



// ======================================
// =====       構造体／共用体       =====
// ======================================



// ======================================
// =====         const 変数         =====
// ======================================



// ======================================
// =====        extern 変数         =====
// ======================================
int	 g_nWriteTagProcFlag = 0;

// ======================================
// =====        static 変数         =====
// ======================================
// ジャンル名称テーブル
GENRE_LIST	g_genreListSCMPX[] = {
	{true,   0, L"Blues"},					// 0(ID3 Tag互換)
	{true,   1, L"Classic Rock"},			// 1(ID3 Tag互換)
	{true,   2, L"Country"},					// 2(ID3 Tag互換)
	{true,   3, L"Dance"},					// 3(ID3 Tag互換)
	{true,   4, L"Disco"},					// 4(ID3 Tag互換)
	{true,   5, L"Funk"},					// 5(ID3 Tag互換)
	{true,   6, L"Grunge"},					// 6(ID3 Tag互換)
	{true,   7, L"Hip-Hop"},					// 7(ID3 Tag互換)
	{true,   8, L"Jazz"},					// 8(ID3 Tag互換)
	{true,   9, L"Metal"},					// 9(ID3 Tag互換)
	{true,  10, L"New Age"},					// 10(ID3 Tag互換)
	{true,  11, L"Oldies"},					// 11(ID3 Tag互換)
	{true,  12, L"Other"},					// 12(ID3 Tag互換)
	{true,  13, L"Pop"},						// 13(ID3 Tag互換)
	{true,  14, L"R&B"},						// 14(ID3 Tag互換)
	{true,  15, L"Rap"},						// 15(ID3 Tag互換)
	{true,  16, L"Reggae"},					// 16(ID3 Tag互換)
	{true,  17, L"Rock"},					// 17(ID3 Tag互換)
	{true,  18, L"Techno"},					// 18(ID3 Tag互換)
	{true,  19, L"Industrial"},				// 19(ID3 Tag互換)
	{true,  20, L"Alternative"},				// 20(ID3 Tag互換)
	{true,  21, L"Ska"},						// 21(ID3 Tag互換)
	{true,  22, L"Death Metal"},				// 22(ID3 Tag互換)
	{true,  23, L"Pranks"},					// 23(ID3 Tag互換)
	{true,  24, L"Soundtrack"},				// 24(ID3 Tag互換)
	{true,  25, L"Euro-Techno"},				// 25(ID3 Tag互換)
	{true,  26, L"Ambient"},					// 26(ID3 Tag互換)
	{true,  27, L"Trip-Hop"},				// 27(ID3 Tag互換)
	{true,  28, L"Vocal"},					// 28(ID3 Tag互換)
	{true,  29, L"Jazz+Funk"},				// 29(ID3 Tag互換)
	{true,  30, L"Fusion"},					// 30(ID3 Tag互換)
	{true,  31, L"Trance"},					// 31(ID3 Tag互換)
	{true,  32, L"Classical"},				// 32(ID3 Tag互換)
	{true,  33, L"Instrumental"},			// 33(ID3 Tag互換)
	{true,  34, L"Acid"},					// 34(ID3 Tag互換)
	{true,  35, L"House"},					// 35(ID3 Tag互換)
	{true,  36, L"Game"},					// 36(ID3 Tag互換)
	{true,  37, L"Sound Clip"},				// 37(ID3 Tag互換)
	{true,  38, L"Gospel"},					// 38(ID3 Tag互換)
	{true,  39, L"Noise"},					// 39(ID3 Tag互換)
	{true,  40, L"AlternRock"},				// 40(ID3 Tag互換)
	{true,  41, L"Bass"},					// 41(ID3 Tag互換)
	{true,  42, L"Soul"},					// 42(ID3 Tag互換)
	{true,  43, L"Punk"},					// 43(ID3 Tag互換)
	{true,  44, L"Space"},					// 44(ID3 Tag互換)
	{true,  45, L"Meditative"},				// 45(ID3 Tag互換)
	{true,  46, L"Instrumental Pop"},		// 46(ID3 Tag互換)
	{true,  47, L"Instrumental Rock"},		// 47(ID3 Tag互換)
	{true,  48, L"Ethnic"},					// 48(ID3 Tag互換)
	{true,  49, L"Gothic"},					// 49(ID3 Tag互換)
	{true,  50, L"Darkwave"},				// 50(ID3 Tag互換)
	{true,  51, L"Techno-Industrial"},		// 51(ID3 Tag互換)
	{true,  52, L"Electronic"},				// 52(ID3 Tag互換)
	{true,  53, L"Pop-Folk"},				// 53(ID3 Tag互換)
	{true,  54, L"Eurodance"},				// 54(ID3 Tag互換)
	{true,  55, L"Dream"},					// 55(ID3 Tag互換)
	{true,  56, L"Southern Rock"},			// 56(ID3 Tag互換)
	{true,  57, L"Comedy"},					// 57(ID3 Tag互換)
	{true,  58, L"Cult"},					// 58(ID3 Tag互換)
	{true,  59, L"Gangsta"},					// 59(ID3 Tag互換)
	{true,  60, L"Top 40"},					// 60(ID3 Tag互換)
	{true,  61, L"Christian Rap"},			// 61(ID3 Tag互換)
	{true,  62, L"Pop/Funk"},				// 62(ID3 Tag互換)
	{true,  63, L"Jungle"},					// 63(ID3 Tag互換)
	{true,  64, L"Native American"},			// 64(ID3 Tag互換)
	{true,  65, L"Cabaret"},					// 65(ID3 Tag互換)
	{true,  66, L"New Wave"},				// 66(ID3 Tag互換)
	{true,  67, L"Psychedelic"},				// 67(ID3 Tag互換)
	{true,  68, L"Rave"},					// 68(ID3 Tag互換)
	{true,  69, L"Showtunes"},				// 69(ID3 Tag互換)
	{true,  70, L"Trailer"},					// 70(ID3 Tag互換)
	{true,  71, L"Lo-Fi"},					// 71(ID3 Tag互換)
	{true,  72, L"Tribal"},					// 72(ID3 Tag互換)
	{true,  73, L"Acid Punk"},				// 73(ID3 Tag互換)
	{true,  74, L"Acid Jazz"},				// 74(ID3 Tag互換)
	{true,  75, L"Polka"},					// 75(ID3 Tag互換)
	{true,  76, L"Retro"},					// 76(ID3 Tag互換)
	{true,  77, L"Musical"},					// 77(ID3 Tag互換)
	{true,  78, L"Rock & Roll"},				// 78(ID3 Tag互換)
	{true,  79, L"Hard Rock"},				// 79(ID3 Tag互換)
	{true,  80, L"Folk"},					// 80(ID3 Tag互換)
	{true,  81, L"Folk/Rock"},				// 81(ID3 Tag互換)
	{true,  82, L"National Folk"},			// 82(ID3 Tag互換)
	{true,  83, L"Swing"},					// 83(ID3 Tag互換)
	{true,  84, L"Fast-Fusion"},				// 84(Winamp互換)
	{true,  85, L"Bebob"},					// 85(Winamp互換)
	{true,  86, L"Latin"},					// 86(Winamp互換)
	{true,  87, L"Revival"},					// 87(Winamp互換)
	{true,  88, L"Celtic"},					// 88(Winamp互換)
	{true,  89, L"Bluegrass"},				// 89(Winamp互換)
	{true,  90, L"Avantgarde"},				// 90(Winamp互換)
	{true,  91, L"Gothic Rock"},				// 91(Winamp互換)
	{true,  92, L"Progressive Rock"},		// 92(Winamp互換)
	{true,  93, L"Psychedelic Rock"},		// 93(Winamp互換)
	{true,  94, L"Symphonic Rock"},			// 94(Winamp互換)
	{true,  95, L"Slow Rock"},				// 95(Winamp互換)
	{true,  96, L"Big Band"},				// 96(Winamp互換)
	{true,  97, L"Chorus"},					// 97(Winamp互換)
	{true,  98, L"Easy Listening"},			// 98(Winamp互換)
	{true,  99, L"Acoustic"},				// 99(Winamp互換)
	{true, 100, L"Humour"},					// 100(Winamp互換)
	{true, 101, L"Speech"},					// 101(Winamp互換)
	{true, 102, L"Chanson"},					// 102(Winamp互換)
	{true, 103, L"Opera"},					// 103(Winamp互換)
	{true, 104, L"Chamber Music"},			// 104(Winamp互換)
	{true, 105, L"Sonata"},					// 105(Winamp互換)
	{true, 106, L"Symphony"},				// 106(Winamp互換)
	{true, 107, L"Booty Bass"},				// 107(Winamp互換)
	{true, 108, L"Primus"},					// 108(Winamp互換)
	{true, 109, L"Porn Groove"},				// 109(Winamp互換)
	{true, 110, L"Satire"},					// 110(Winamp互換)
	{true, 111, L"Slow Jam"},				// 111(Winamp互換)
	{true, 112, L"Club"},					// 112(Winamp互換)
	{true, 113, L"Tango"},					// 113(Winamp互換)
	{true, 114, L"Samba"},					// 114(Winamp互換)
	{true, 115, L"Folklore"},				// 115(Winamp互換)
	{true, 116, L"Ballad"},					// 116(Winamp互換)
	{true, 117, L"Power Ballad"},			// 117(Winamp互換)
	{true, 118, L"Phythmic Soul"},			// 118(Winamp互換)
	{true, 119, L"Freestyle"},				// 119(Winamp互換)
	{true, 120, L"Duet"},					// 120(Winamp互換)
	{true, 121, L"Punk Rock"},				// 121(Winamp互換)
	{true, 122, L"Drum Solo"},				// 122(Winamp互換)
	{true, 123, L"A Cappella"},				// 123(Winamp互換)
	{true, 124, L"Euro-House"},				// 124(Winamp互換)
	{true, 125, L"Dance Hall"},				// 125(Winamp互換)
	{true, 126, L"Goa"},						// 126(Winamp互換)
	{true, 127, L"Drum & Bass"},				// 127(Winamp互換)
	{true, 128, L"Club-House"},				// 128(Winamp互換)
	{true, 129, L"Hardcore"},				// 129(Winamp互換)
	{true, 130, L"Terror"},					// 130(Winamp互換)
	{true, 131, L"Indie"},					// 131(Winamp互換)
	{true, 132, L"BritPop"},					// 132(Winamp互換)
	{true, 133, L"Negerpunk"},				// 133(Winamp互換)
	{true, 134, L"Polsk Punk"},				// 134(Winamp互換)
	{true, 135, L"Beat"},					// 135(Winamp互換)
	{true, 136, L"Christian Gangsta Rap"},	// 136(Winamp互換)
	{true, 137, L"Heavy Metal"},				// 137(Winamp互換)
	{true, 138, L"Black Metal"},				// 138(Winamp互換)
	{true, 139, L"Crossover"},				// 139(Winamp互換)
	{true, 140, L"Contemporary Christian"},	// 140(Winamp互換)
	{true, 141, L"Christian Rock"},			// 141(Winamp互換)
	{true, 142, L"Merengue"},				// 142(Winamp互換)
	{true, 143, L"Salsa"},					// 143(Winamp互換)
	{true, 144, L"Thrash Metal"},			// 144(Winamp互換)
	{true, 145, L"Anime"},					// 145(Winamp互換)
	{true, 146, L"JPop"},					// 146(Winamp互換)
	{true, 147, L"Synthpop"},				// 147(Winamp互換)
	{false, 148, L"未定義(148)"},			// 148
	{false, 148, L"未定義(148)"},			// 148
	{false, 149, L"未定義(149)"},			// 149
	{false, 150, L"未定義(150)"},			// 150
	{false, 151, L"未定義(151)"},			// 151
	{false, 152, L"未定義(152)"},			// 152
	{false, 153, L"未定義(153)"},			// 153
	{false, 154, L"未定義(154)"},			// 154
	{false, 155, L"未定義(155)"},			// 155
	{false, 156, L"未定義(156)"},			// 156
	{false, 157, L"未定義(157)"},			// 157
	{false, 158, L"未定義(158)"},			// 158
	{false, 159, L"未定義(159)"},			// 159
	{false, 160, L"未定義(160)"},			// 160
	{false, 161, L"未定義(161)"},			// 161
	{false, 162, L"未定義(162)"},			// 162
	{false, 163, L"未定義(163)"},			// 163
	{false, 164, L"未定義(164)"},			// 164
	{false, 165, L"未定義(165)"},			// 165
	{false, 166, L"未定義(166)"},			// 166
	{false, 167, L"未定義(167)"},			// 167
	{false, 168, L"未定義(168)"},			// 168
	{false, 169, L"未定義(169)"},			// 169
	{false, 170, L"未定義(170)"},			// 170
	{false, 171, L"未定義(171)"},			// 171
	{false, 172, L"未定義(172)"},			// 172
	{false, 173, L"未定義(173)"},			// 173
	{false, 174, L"未定義(174)"},			// 174
	{false, 175, L"未定義(175)"},			// 175
	{false, 176, L"未定義(176)"},			// 176
	{false, 177, L"未定義(177)"},			// 177
	{false, 178, L"未定義(178)"},			// 178
	{false, 179, L"未定義(179)"},			// 179
	{false, 180, L"未定義(180)"},			// 180
	{false, 181, L"未定義(181)"},			// 181
	{false, 182, L"未定義(182)"},			// 182
	{false, 183, L"未定義(183)"},			// 183
	{false, 184, L"未定義(184)"},			// 184
	{false, 185, L"未定義(185)"},			// 185
	{false, 186, L"未定義(186)"},			// 186
	{false, 187, L"未定義(187)"},			// 187
	{false, 188, L"未定義(188)"},			// 188
	{false, 189, L"未定義(189)"},			// 189
	{false, 190, L"未定義(190)"},			// 190
	{false, 191, L"未定義(191)"},			// 191
	{false, 192, L"未定義(192)"},			// 192
	{false, 193, L"未定義(193)"},			// 193
	{false, 194, L"未定義(194)"},			// 194
	{false, 195, L"未定義(195)"},			// 195
	{false, 196, L"未定義(196)"},			// 196
	{false, 197, L"未定義(197)"},			// 197
	{false, 198, L"未定義(198)"},			// 198
	{false, 199, L"未定義(199)"},			// 199
	{false, 200, L"未定義(200)"},			// 200
	{false, 201, L"未定義(201)"},			// 201
	{false, 202, L"未定義(202)"},			// 202
	{false, 203, L"未定義(203)"},			// 203
	{false, 204, L"未定義(204)"},			// 204
	{false, 205, L"未定義(205)"},			// 205
	{false, 206, L"未定義(206)"},			// 206
	{false, 207, L"未定義(207)"},			// 207
	{false, 208, L"未定義(208)"},			// 208
	{false, 209, L"未定義(209)"},			// 209
	{false, 210, L"未定義(210)"},			// 210
	{false, 211, L"未定義(211)"},			// 211
	{false, 212, L"未定義(212)"},			// 212
	{false, 213, L"未定義(213)"},			// 213
	{false, 214, L"未定義(214)"},			// 214
	{false, 215, L"未定義(215)"},			// 215
	{false, 216, L"未定義(216)"},			// 216
	{false, 217, L"未定義(217)"},			// 217
	{false, 218, L"未定義(218)"},			// 218
	{false, 219, L"未定義(219)"},			// 219
	{false, 220, L"未定義(220)"},			// 220
	{false, 221, L"未定義(221)"},			// 221
	{false, 222, L"未定義(222)"},			// 222
	{false, 223, L"未定義(223)"},			// 223
	{false, 224, L"未定義(224)"},			// 224
	{false, 225, L"未定義(225)"},			// 225
	{false, 226, L"未定義(226)"},			// 226
	{false, 227, L"未定義(227)"},			// 227
	{false, 228, L"未定義(228)"},			// 228
	{false, 229, L"未定義(229)"},			// 229
	{false, 230, L"未定義(230)"},			// 230
	{false, 231, L"未定義(231)"},			// 231
	{false, 232, L"未定義(232)"},			// 232
	{false, 233, L"未定義(233)"},			// 233
	{false, 234, L"未定義(234)"},			// 234
	{false, 235, L"未定義(235)"},			// 235
	{false, 236, L"未定義(236)"},			// 236
	{false, 237, L"未定義(237)"},			// 237
	{false, 238, L"未定義(238)"},			// 238
	{false, 239, L"未定義(239)"},			// 239
	{false, 240, L"未定義(240)"},			// 240
	{false, 241, L"未定義(241)"},			// 241
	{false, 242, L"未定義(242)"},			// 242
	{false, 243, L"未定義(243)"},			// 243
	{false, 244, L"未定義(244)"},			// 244
	{false, 245, L"未定義(245)"},			// 245
	{false, 246, L"未定義(246)"},			// 246
	{false, 247, L"未定義(247)"},			// 247
	{false, 248, L"Heavy Rock(J)"},			// 248(SCMPX互換)
	{false, 249, L"Doom Rock(J)"},			// 249(SCMPX互換)
	{false, 250, L"J-POP(J)"},				// 250(SCMPX互換)
	{false, 251, L"Seiyu(J)"},				// 251(SCMPX互換)
	{false, 252, L"Tecno Ambient(J)"},		// 252(SCMPX互換)
	{false, 253, L"Moemoe(J)"},				// 253(SCMPX互換)
	{false, 254, L"Tokusatsu(J)"},			// 254(SCMPX互換)
	{false, 255, L"Anime(J)"},				// 255(SCMPX互換)
	{false, 255, L"未指定"},					// 255
	{false, 255, NULL},						// 終端コード
};
USER_GENRE_LIST*	g_genreListUSER = NULL;



// ======================================
// =====     関数プロトタイプ       =====
// ======================================


// =============================================
// GetGenreNameSIF
// 概要  : ジャンル番号からジャンル名を取得(SIフィールド用)
// 引数  : byGenre			= ジャンル番号
// 戻り値: const wchar_t *		= ジャンル名
// =============================================
const wchar_t *GetGenreNameSIF(BYTE byGenre)
{
	int		i;
	for (i = 0; g_genreListSCMPX[i].sName != NULL; i++) {
		if (g_genreListSCMPX[i].byGenre == byGenre) {
			if (byGenre == 0xff) {
				// SCMPX 互換かどうかで文字列を変える
				return(g_genreListSCMPX[i].bAddList ? "Anime(J)" : "");
			}
			return(g_genreListSCMPX[i].sName);
		}
	}
	return(L"");
}

// =============================================
// GetGenreCode
// 概要  : ジャンル名からジャンル番号を取得
// 引数  : sGenre		= ジャンル名
// 戻り値: int			= ジャンル番号(-1:未対応)
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

/* 漢字の１バイト目かどうかの検査 */
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
					  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // デフォルト言語
					  (LPTSTR)&lpMsgBuf, 0, NULL);
		strBuffer.Format(L"変更前：%s\n変更後：%s\n\n%s", sFileName, sNewName, (const wchar_t *)lpMsgBuf);
		LocalFree(lpMsgBuf);
		MessageBox(NULL, strBuffer, L"ファイル名を変更できませんでした", MB_ICONSTOP|MB_OK|MB_TOPMOST);
		return(false);
	}
	return(true);
}

static	bool MyCopyFile(const wchar_t *sFileName, const wchar_t *sNewName, bool bMoveFlag)
{
	BOOL	bResult;

	// コピー／移動を実行
	if (bMoveFlag) {
		// 移動先に同名のファイルがある場合は、予め削除する
		if (SetFileAttributes(sNewName, CFile::normal) == TRUE) {
			if (DeleteFile(sNewName) == FALSE) {
//				CString	strBuffer;
//				LPVOID lpMsgBuf;
//				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
//							  FORMAT_MESSAGE_FROM_SYSTEM |
//							  FORMAT_MESSAGE_IGNORE_INSERTS,
//							  NULL, GetLastError(),
//							  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // デフォルト言語
//							  (LPTSTR)&lpMsgBuf, 0, NULL);
//				strBuffer.Format(L"ファイル名：%s\n\n%s", sNewName, (const wchar_t *)lpMsgBuf);
//				LocalFree(lpMsgBuf);
//				MessageBox(NULL, strBuffer, L"ファイルの削除に失敗しました", MB_OK/*MB_ABORTRETRYIGNORE*/|MB_TOPMOST);
//				return(false);
			}
		}
		bResult = MoveFile(sFileName, sNewName);
	} else {
		bResult = CopyFile(sFileName, sNewName, FALSE);
	}

	// エラー処理
	if (bResult == FALSE) {
		static	const wchar_t *sMessage[][2] = {
			{"コピー元：%s\nコピー先：%s\n\n%s", L"ファイルのコピーに失敗しました"},
			{"移動元：%s\n移動先：%s\n\n%s", L"ファイルの移動に失敗しました"},
		};
		CString	strBuffer;
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
					  FORMAT_MESSAGE_FROM_SYSTEM |
					  FORMAT_MESSAGE_IGNORE_INSERTS,
					  NULL, GetLastError(),
					  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // デフォルト言語
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

// 最後が '\\' になっているかどうかのチェック関数
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
// Func  : コンストラクタ
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
// Func  : デストラクタ
// Input : none
// Output: none
// =============================================
CFileMP3::~CFileMP3()
{
	//if (m_fileMP3.fileOGG != NULL)	delete m_fileMP3.fileOGG; /* Conspiracy 196 */
}

// =============================================
// CFileMP3::InitData
// 概要  : MP3 ファイル情報の構造体を初期化します
// 引数  : fileMP3		= 初期化する構造体
// 戻り値: none
// =============================================
void CFileMP3::InitData(FILE_MP3 *fileMP3)
{
	extern void InitFileSpecificInfo(FILE_MP3* pFileMP3);
	if (fileMP3->fileSpecificInfo != NULL) {
		InitFileSpecificInfo(fileMP3);
		fileMP3->fileSpecificInfo = NULL;
	}

	fileMP3->bModifyFlag	= false;	// 外部から編集されたかどうかのフラグ
	fileMP3->bCheckFlag		= false;	// チェック状態
	fileMP3->lFileSize		= 0L;		// ファイルサイズ
	fileMP3->time			= CTime(0);	// ファイル更新日
	fileMP3->timeCreate		= CTime(0);	// ファイル作成日
#ifdef USE_VBMP3_DLL
	fileMP3->nPlayTime		= 0;		// 演奏時間(単位：秒)
#endif
	fileMP3->nPlayTime		= -1;		// 演奏時間(単位：秒) /* Conspiracy 195 */
	fileMP3->bExistLyricFile = false;	// 歌詞ファイルの存在
	fileMP3->nFormat		= FILE_FORMAT_UNKNOWN;	// ファイル形式：未知の形式
	fileMP3->strFullPathName.Empty();	// ファイル名(フルパス)
	fileMP3->strFileName.Empty();		// ファイル名
	fileMP3->strFilePath.Empty();		// パス名

	// ID3 のクリア
	InitDataID3(fileMP3); /* STEP 029 */

	// SIF のクリア
	InitDataSIF(fileMP3);
}

void CFileMP3::InitDataID3(FILE_MP3 *fileMP3) /* STEP 029 */
{
	fileMP3->strTrackName.Empty();		// トラック名
	fileMP3->strArtistName.Empty();		// アーティスト名
	fileMP3->strAlbumName.Empty();		// アルバム名
	fileMP3->strComment.Empty();		// コメント
	fileMP3->strYear.Empty();			// リリース年号
	fileMP3->byTrackNumber	= 0xff;		// トラック番号(数値編集用)
	fileMP3->strTrackNumber.Empty();	// トラック番号(文字列編集用)
	fileMP3->byDiskNumber	= 0xff;
	fileMP3->strDiskNumber.Empty();
	fileMP3->byGenre		= 0xff;		// ジャンル番号
	fileMP3->strGenre.Empty();			// ジャンル名
}

// =============================================
//  CFileMP3::InitDataSIF
//  概要  : MP3 ファイル情報の構造体を初期化します(SIF関連のみ)
//  引数  : fileMP3		= 初期化する構造体
//  戻り値: なし
// =============================================
void CFileMP3::InitDataSIF(FILE_MP3 *fileMP3)
{
	// RIFF MP3 の SI フィールド
	fileMP3->strTrackNameSI.Empty();	// 曲名
	fileMP3->strArtistNameSI.Empty();	// アーティスト名
	fileMP3->strAlbumNameSI.Empty();	// 製品名
	fileMP3->strCommentSI.Empty();		// コメント文字列
	fileMP3->strYearSI.Empty();			// リリース年号
	fileMP3->strGenreSI.Empty();		// ジャンル名
	fileMP3->strCopyrightSI.Empty();	// 著作権
	fileMP3->strEngineerSI.Empty();		// エンジニア
	fileMP3->strSourceSI.Empty();		// ソース
	fileMP3->strSoftwareSI.Empty();		// ソフトウェア
	fileMP3->strKeywordSI.Empty();		// キーワード
	fileMP3->strTechnicianSI.Empty();	// 技術者
	fileMP3->strLyricSI.Empty();		// 歌詞
	fileMP3->strCommissionSI.Empty();	// コミッション

	if (IsUserGenre(fileMP3->strGenre)) {
		fileMP3->strGenre = GetGenreNameSIF(fileMP3->byGenre);
	}
	fileMP3->strTrackNumber.Empty();
	if (fileMP3->byTrackNumber != 0xFF) {
		fileMP3->strTrackNumber.Format(L"%d", fileMP3->byTrackNumber);
	}
	fileMP3->strTrackNumberSI.Empty();
	fileMP3->strWriterSI.Empty();		// 作詞
	fileMP3->strComposerSI.Empty();		// 作曲
	fileMP3->strAlbmArtistSI.Empty();	// Albm.アーティスト
	fileMP3->strOrigArtistSI.Empty();	// Orig.アーティスト
	fileMP3->strURLSI.Empty();			// URL
	fileMP3->strEncodest.Empty();		// エンコードした人
	fileMP3->strOther.Empty();			// その他
}

// =============================================
// CFileMP3::Initialize
// 概要  : 初期化処理
// 引数  : none
// 戻り値: none
// =============================================
void CFileMP3::Initialize(void)
{
	//m_fileMP3.fileSpecificInfo = NULL;
	InitData(&m_fileMP3);
}

// =============================================
// CFileMP3::DeleteLineEndSpace
// 概要  : 行末のスペースを取り除く
// 引数  : sBuffer		= 文字列
// 戻り値: none
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
//  概要  : クラスにファイルに関連付けする
//  引数  : sFileName	= ファイル名
//  戻り値: bool		= true:正常終了 / false:エラー
// =============================================
bool CFileMP3::Attach(const wchar_t *sFileName)
{
	Initialize();

	// タイムスタンプを取得
	CFileStatus	fileStatus;
	if (CFile::GetStatus(sFileName, fileStatus) == FALSE || fileStatus.m_mtime == -1) {
		fileStatus.m_mtime = CTime(0);
		fileStatus.m_ctime = CTime(0);
	}
	m_fileMP3.time			= fileStatus.m_mtime;	// ファイル更新日
	m_fileMP3.timeCreate	= fileStatus.m_ctime;	// ファイル作成日
	m_fileMP3.lFileSize		= fileStatus.m_size;	// ファイルサイズ

	// フルパスをパス名とファイル名に分解
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	ZeroMemory(ext, sizeof(ext));
	_tsplitpath(sFileName, drive, dir, fname, ext);
	m_fileMP3.strFilePath.Format(L"%s%s", drive, dir);
	m_fileMP3.strFileName.Format(L"%s%s", fname, ext);
	m_fileMP3.strFullPathName = sFileName;

	// ファイル情報の読み込み
	extern bool LoadFile(const wchar_t *sFileName, const wchar_t *sExt, FILE_MP3* pFileMP3);
	if (LoadFile(sFileName, &ext[1], &m_fileMP3) == false) {
		Initialize();
		return(false);
	}

	// 歌詞ファイルの存在をチェック
	if (g_bOptSearchLyricFile) {
		// 歌詞ファイルを検索
		m_fileMP3.bExistLyricFile = SearchLyricsFile(&m_fileMP3).IsEmpty() ? false : true;
	}

	return(true);
}

// =============================================
//  CFileMP3::Detach
//  概要  : クラスとファイルの関連付けを削除する
//  引数  : なし
//  戻り値: なし
// =============================================
void CFileMP3::Detach(void)
{
	Initialize();
}

// =============================================
//  CFileMP3::WriteTag
//  概要  : タグ情報の更新
//  引数  : fileMP3		= ファイル情報
//        : bKeepTimeStamp= タイムスタンプを保持するフラグ
//  戻り値: bool		= true:正常終了 / false:エラー
// =============================================
bool CFileMP3::WriteTag(FILE_MP3 *fileMP3, bool bKeepTimeStamp)
{
	CFileStatus	fileStatus;
	bool	bResult = false;

	if (g_nWriteTagProcFlag == 3) {
		return(false);						// 以降中止
	}

	// タイムスタンプを取得
	if (CFile::GetStatus(fileMP3->strFullPathName, fileStatus) == FALSE) {
		return(false);
	}
	if (fileStatus.m_mtime == -1)	fileStatus.m_mtime = fileStatus.m_ctime; /* 2005.10.11 日時がおかしい場合に落ちないように */
	if (fileStatus.m_atime == -1)	fileStatus.m_atime = fileStatus.m_mtime; /* 2005.10.11 日時がおかしい場合に落ちないように */

	// 読み出し専用ファイルは、上書き確認を行う
	if (fileStatus.m_attribute & CFile::readOnly) {
		if (g_nWriteTagProcFlag != 1) {
			// 上書き確認ダイアログを開く
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
			case 0:				// このファイルを上書き
			case 1:				// 以降全て上書き
				break;
			case 2:				// スキップ
			case 3:				// 中止
			default:
				return(false);
			}
		}

		// 読み込み専用属性を解除
		SetFileAttributes(fileMP3->strFullPathName, CFile::normal);
		// 変更後に属性を戻させるために bKeepTimeStamp を true にする
		bKeepTimeStamp = true;
	}

	extern bool SaveFile(FILE_MP3* pFileMP3);
	if ((bResult = SaveFile(fileMP3)) == true) {
		// ファイル名変換
		//bResult = ConvFileName(fileMP3);
	}

	// タイムスタンプをファイル更新前に戻す
	if (bResult) {
		if (bKeepTimeStamp) {
			if (fileMP3->time.GetTime() != -1) {
				// ファイル更新時間を設定
				fileStatus.m_mtime = fileMP3->time;
				if (g_bOptSyncCreateTime) fileStatus.m_ctime = fileMP3->time;
			}
			TRY {
				CFile::SetStatus(fileMP3->strFullPathName, fileStatus);
			}
			CATCH(CFileException, e) {
				CString	strMsg;
				strMsg.Format(L"%s がオープンできませんでした", fileMP3->strFullPathName);
				MessageBox(NULL, strMsg, L"タイムスタンプの更新エラー", MB_ICONSTOP|MB_OK|MB_TOPMOST);
				bResult = false;
			}
			END_CATCH
		} else {
			// 更新後のタイムスタンプを取得
			if (CFile::GetStatus(fileMP3->strFullPathName, fileStatus) != FALSE) {
				fileMP3->time = fileStatus.m_mtime;
			}
		}
	}

	return(bResult);
}

// =============================================
// CFileMP3::SearchFileReent
// 概要  : ファイル検索：検索処理
// 引数  : sDir			= 検索するディレクトリ
//       : sTargetName	= 検索するファイル名
// 戻り値: CString		= 発見したファイルのフルパス(IsEmpty():未発見)
// =============================================
CString CFileMP3::SearchFileReent(const wchar_t *sDir, const wchar_t *sTargetName)
{
	HANDLE	hFindFile;
	WIN32_FIND_DATA	data;
	CString	strTargetFile;

	// 同一ディレクトリの全てのファイルを検索
	// 検索ファイルのパターンを設定
	CString	strCurFile;
	strCurFile.Format(L"%s%s", sDir, sTargetName);
	if ((hFindFile = FindFirstFile(strCurFile, &data)) != INVALID_HANDLE_VALUE) {
		do {
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				// ファイル発見処理
				strCurFile.Format(L"%s%s", sDir, data.cFileName);
				return(strCurFile);
			}
		} while(FindNextFile(hFindFile, &data) == TRUE);
	}
	if (hFindFile != INVALID_HANDLE_VALUE) FindClose(hFindFile);

	// サブディレクトリの検索
	if (g_bOptSearchLyricsSubDir == true) {
		strCurFile.Format(L"%s*.*", sDir);
		if ((hFindFile = FindFirstFile(strCurFile, &data)) != INVALID_HANDLE_VALUE) {
			do {
				if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
					if (wcscmp(data.cFileName, L"." ) != 0		// カレントディレクトリ以外
					&&  wcscmp(data.cFileName, L"..") != 0		// 親ディレクトリ以外
					&& (data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == 0 /* STEP 032 */) { // 隠しフォルダ以外
						// サブディレクトリ検索処理
						strCurFile.Format(L"%s%s\\", sDir, data.cFileName);
						strTargetFile = SearchFileReent(strCurFile, sTargetName);
						if (strTargetFile.IsEmpty() == false) {
							break;				// ファイル発見
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
//  概要  : 歌詞ファイルの検索
//        : 優先順位：MP3と同じフォルダ→歌詞フォルダ→歌詞フォルダのサブディレクトリ
//  引数  : fileMP3		= ファイル情報
//  戻り値: CString		= 歌詞ファイル名(見つからなかった場合は空)
// =============================================
CString CFileMP3::SearchLyricsFile(FILE_MP3 *fileMP3)
{
	wchar_t	sTextName[FILENAME_MAX+1];

	// まずは MP3 ファイルと同じフォルダをチェック
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME];
	_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, NULL);
	// .lrc を検索
	_tmakepath(sTextName, drive, dir, fname, L".lrc");
	if (GetFileAttributes(sTextName) != 0xFFFFFFFF) {
		// ファイルを発見
		return(CString(sTextName));
	}
	// .txt を検索
	_tmakepath(sTextName, drive, dir, fname, L".txt");
	if (GetFileAttributes(sTextName) != 0xFFFFFFFF) {
		// ファイルを発見
		return(CString(sTextName));
	}

	// 歌詞ファイル名作成
	if (g_bOptSetLyricsDir == true && g_strOptLyricsPath.IsEmpty() == false) {
		// 指定されたフォルダ
		wchar_t	sLyricsPath[FILENAME_MAX+1];
		CString	strTarget;
		_tsplitpath(fileMP3->strFullPathName, NULL, NULL, fname, NULL);
		wcscpy(sLyricsPath, g_strOptLyricsPath);
		if (IsFolderName(sLyricsPath) == false) {
			wcscat(sLyricsPath, L"\\");
		}
		// .lrc を検索
		strTarget.Format(L"%s.lrc", fname);
		strTarget = SearchFileReent(sLyricsPath, strTarget);
		if (strTarget.IsEmpty() == false
		&&  GetFileAttributes(strTarget) != 0xFFFFFFFF) {
			// ファイルを発見
			return(strTarget);
		}
		// .txt を検索
		strTarget.Format(L"%s.txt", fname);
		strTarget = SearchFileReent(sLyricsPath, strTarget);
		if (strTarget.IsEmpty() == false
		&&  GetFileAttributes(strTarget) != 0xFFFFFFFF) {
			// ファイルを発見
			return(strTarget);
		}
	}

	// 見つからなかった
	return(CString(L""));
}

// =============================================
//  CFileMP3::ConvFileName
//  概要  : ファイル名の変更
//        : ※新しいファイル名は fileMP3->strFileName を使用
//  引数  : fileMP3		= ファイル情報
//  戻り値: bool		= true:正常終了 / false:エラー
// =============================================
bool CFileMP3::ConvFileName(FILE_MP3 *fileMP3)
{
	// ファイル名を分解
	CString	strFileName;
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, ext);
	strFileName.Format(L"%s%s", fname, ext);

	if (wcscmp(strFileName, fileMP3->strFileName) != 0) {
		// ファイル名が変更されている
		if (g_bConfFileNameMaxCheck) {
			if (fileMP3->strFileName.GetLength() > g_nConfFileNameMaxChar) {
				// ファイル名文字数オーバー
				_tsplitpath(fileMP3->strFileName, NULL, NULL, fname, ext);
				CDlgFileNameChange dialog;
				dialog.m_nMaxChar = g_nConfFileNameMaxChar - wcslen(ext);
				dialog.m_strFileName = fname;
				dialog.m_strOrgFileName = fname;
				//dialog.m_strMsg.Format(L"ファイル名を %d 文字以内に変更してください", dialog.m_nMaxChar);
				dialog.m_strMsgFormat = L"ファイル名を %d(%d) 文字以内に変更してください";
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

		// 同名のテキストファイルのファイル名も変換する
		if (g_bOptChangeTextFile) {
			CString	strLyricsFile;
			// 歌詞ファイルを検索
			strLyricsFile = SearchLyricsFile(fileMP3);
			if (strLyricsFile.IsEmpty() == false) {
				// 発見した歌詞ファイルのパスを分解
				_tsplitpath(strLyricsFile, drive, dir, fname, ext);

				// 歌詞ファイルをリネームする
				wchar_t	sNewText[FILENAME_MAX+1];
				_tsplitpath(fileMP3->strFileName, NULL, NULL, fname, NULL);
				_tmakepath(sNewText, drive, dir, fname, ext);
				if (MyChangeFileName(strLyricsFile, sNewText) == false) {
					// return(false);
				}
			}
		}

		// ファイル名を更新する
		fileMP3->strFullPathName = sNewName;
	}

	return(true);
}

// =============================================
//  CFileMP3::CopyFile
//  概要  : ファイルのコピー／移動
//  引数  : fileMP3		= ファイル情報
//        : sNewDir		= 移動先フォルダ名
//        : bMoveFlag	= フラグ(true:移動/false:コピー)
//  戻り値: bool		= true:正常終了 / false:エラー
// =============================================
bool CFileMP3::CopyFile(FILE_MP3 *fileMP3, const wchar_t *sNewDir, bool bMoveFlag)
{
	// ファイル名を分解
	CString	strFileName;
	wchar_t	drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, ext);
	strFileName.Format(L"%s%s", fname, ext);

	if (_wcscmpi(fileMP3->strFilePath, sNewDir) != 0) {
		// ファイル名が変更されている
		CString	strNewName;
		strNewName.Format(L"%s%s", sNewDir, strFileName);
		if (MyCopyFile(fileMP3->strFullPathName, strNewName, bMoveFlag) == false) {
			// ファイルのコピー／移動に失敗!!
			return(false);
		}

		// 移動の場合は、歌詞ファイルも移動する
		if (g_bSyncLyricsFileMove && bMoveFlag == true) {
			wchar_t	sLyricsFile[FILENAME_MAX+1];
			// MP3 ファイルと同じフォルダにある歌詞ファイルを検索
			_tsplitpath(fileMP3->strFullPathName, drive, dir, fname, ext);
			// .lrc => .txt の順で検索
			int i; for (i = 0; i < 2; i++) {
				LPSTR	sLyricsExt = (i == 0) ? ".lrc" : ".txt";
				_tmakepath(sLyricsFile, drive, dir, fname, sLyricsExt);
				if (GetFileAttributes(sLyricsFile) != 0xFFFFFFFF) {
					// ファイルを発見：歌詞ファイルを移動する
					CString	strNewName;
					strNewName.Format(L"%s%s%s", sNewDir, fname, sLyricsExt);
					if (MyCopyFile(sLyricsFile, strNewName, true) == false) {
						// 失敗!!
						// return(false);
					}
					break;
				}
			}
		}

		// 管理情報のファイル名を更新する
		if (bMoveFlag) {
			fileMP3->strFilePath = sNewDir;
			fileMP3->strFullPathName = strNewName;
		}
	}

	return(true);
}

CString CFileMP3::GetIntTrackNo(const CString &no)
{
	//トラック番号
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
	//トラック番号
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
			// 漢字リーディングバイト
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
