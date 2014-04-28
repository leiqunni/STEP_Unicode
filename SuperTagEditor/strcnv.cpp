#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "imm.h"

#ifndef iskanji
#define iskanji(c)		((c) >= 0x81 && (c) <= 0x9f || (c) >= 0xe0 && (c) <= 0xfc)
#endif

enum { CONV_SUJI = 1, CONV_ALPHA = 2, CONV_KATA = 4, CONV_KIGOU = 8, CONV_ALL = 15 };

#ifdef __cplusplus
extern "C" {
#endif

	extern	int conv_han2zens(wchar_t *, const wchar_t *, int);
	extern	int conv_zen2hans(wchar_t *, const wchar_t *, int);
	extern	void conv_kata2hira(wchar_t *);
	extern	void conv_kata_erase_dakuon(wchar_t *);
	extern	void conv_hira2kata(wchar_t *);
	extern	void conv_upper(wchar_t *);
	extern	void conv_lower(wchar_t *);
	extern	void conv_first_upper(wchar_t *, const wchar_t *, const wchar_t *, bool);
	//extern	DWORD conv_kan2hira(HWND, wchar_t *, DWORD);
	//extern	void conv_romaji(HWND hwnd, wchar_t *str, wchar_t *sRomaji);
#ifdef __cplusplus
}
#endif

unsigned short han2zen(int c, int flag)
{
	if (c <= 0x19 || (c >= 0x80 && c <= 0xa0) || c >= 0xe0) {
		return c;					// §Œä–¢’è‹`
	}
	if (flag & CONV_ALPHA) {
		if (c >= 'A' && c <= 'Z') return(0x8260U + (c - 'A'));	// ‰p‘å•¶š
		if (c >= 'a' && c <= 'z') return(0x8281U + (c - 'a'));	// ‰p¬•¶š
	}
	if (flag & CONV_SUJI) {
		if (c >= '0' && c <= '9') return(0x824FU + (c - '0'));	// ”š
	}

	int		i;
	static const wchar_t *s1 = (const wchar_t *)
		/* 0123456789ABCDEF		        ‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e */
		"   ,. :;?!Şß   "		/* 212X:@@ABCDEFGHIJKLMN */
		/* STEP 016 *///" ¤¡,.¥:;?!Şß   "		/* 212X:@@ABCDEFGHIJKLMN */
		/* BeachMonster 102 *///"^~_         °- /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		/* Baja 169 *///"^~_          - /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		"^~_            /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		"   |  `\' \"()  []"	/* 214X:_`abcdefghijklmn */
		"{}          +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		/* STEP 016 *///"{}    ¢£    +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		" = <>          \\"	/* 216X:€‚ƒ„…†‡ˆ‰Š‹Œ */
		"$  %#&*@        ";	/* 217X:‘’“”•–—˜™š›œ   */
	static const wchar_t *s2 = (const wchar_t *)
		/* 0123456789ABCDEF		        ‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e */
		"§±¨²©³ª´«µ¶Ş·Ş¸"		/* 252X:@ƒ@ƒAƒBƒCƒDƒEƒFƒGƒHƒIƒJƒKƒLƒMƒN */
		"Ş¹ŞºŞ»Ş¼Ş½Ş¾Ş¿ŞÀ"	/* 253X:ƒOƒPƒQƒRƒSƒTƒUƒVƒWƒXƒYƒZƒ[ƒ\ƒ]ƒ^ */
		"ŞÁŞ¯ÂŞÃŞÄŞÅÆÇÈÉÊ"	/* 254X:ƒ_ƒ`ƒaƒbƒcƒdƒeƒfƒgƒhƒiƒjƒkƒlƒmƒn */
		"ŞßËŞßÌŞßÍŞßÎŞßÏĞ "	/* 255X:ƒoƒpƒqƒrƒsƒtƒuƒvƒwƒxƒyƒzƒ{ƒ|ƒ}ƒ~7F */
		"ÑÒÓ¬Ô­Õ®Ö×ØÙÚÛ Ü"	/* 256X:ƒ€ƒƒ‚ƒƒƒ„ƒ…ƒ†ƒ‡ƒˆƒ‰ƒŠƒ‹ƒŒƒƒƒ */
		"  ¦İ";				/* 257X:ƒƒ‘ƒ’ƒ“ƒ”ƒ•ƒ– */
	static const wchar_t *s3 = (const wchar_t *) /* BeachMonster 102 */
		/* 0123456789ABCDEF		        ‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e */
		"                "	/* 212X:@@ABCDEFGHIJKLMN */
		"            °   "	/* 213X:OPQRSTUVWXYZ[\]^ */
		"                "	/* 214X:_`abcdefghijklmn */
		"                "	/* 215X:opqrstuvwxyz{|}~7F */
		"                "	/* 216X:€‚ƒ„…†‡ˆ‰Š‹Œ */
		"                ";	/* 217X:‘’“”•–—˜™š›œ   */
	;
	static const wchar_t *s4 = (const wchar_t *) /* STEP 016 */
		/* 0123456789ABCDEF		        ‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e */
		"  ¤¡  ¥         "	/* 212X:@@ABCDEFGHIJKLMN */
		"                "	/* 213X:OPQRSTUVWXYZ[\]^ */
		"                "	/* 214X:_`abcdefghijklmn */
		"      ¢£        "	/* 215X:opqrstuvwxyz{|}~7F */
		"                "	/* 216X:€‚ƒ„…†‡ˆ‰Š‹Œ */
		"                ";	/* 217X:‘’“”•–—˜™š›œ   */
	;
	if (flag & CONV_KIGOU) {
		for (i = 0; s1[i]; i++) if (c == s1[i]) return(0x8140U + i);	// ‹L†
	}
	if (flag & CONV_KATA) {
		for (i = 0; s2[i]; i++) if (c == s2[i]) return(0x8340U + i);	// ƒJƒ^ƒJƒi
	}
	if (flag & CONV_KATA) { /* BeachMonster 102 */
		for (i = 0; s3[i]; i++) if (c == s3[i]) return(0x8140U + i - 1/* STEP 016*/);	// ‹L†‚¾‚¯‚ÇƒJƒ^ƒJƒiˆµ‚¢
	}
	extern bool g_bZenHanKigouKana; /* STEP 016 */
	if ((!g_bZenHanKigouKana && flag & CONV_KIGOU)
		|| (g_bZenHanKigouKana && flag & CONV_KATA)) { /* STEP 016 */
		for (i = 0; s4[i]; i++) if (c == s4[i]) return(0x8140U + i - 1);
	}
	return(c);
}

int conv_han2zens(wchar_t *zen, const wchar_t *han, int flag)
{
	int		i;
	int		pzen = 0;		// ‘SŠpˆÊ’u
	int		l = wcslen(han);
	zen[0] = '\0';

	for (i = 0; i < l; i++, pzen++, zen[pzen] = '\0') {
		if (han[i] == ' ') {		// ‹ó”’
			if (flag & CONV_KIGOU) {
				zen[pzen] = 0x81U;
				pzen++;
				zen[pzen] = 0x40U;
			} else {
				zen[pzen] = ' ';
			}
			continue;
		}

		if (iskanji(han[i])) {		// Š¿š
			zen[pzen] = han[i];
			pzen++;
			i++;
			zen[pzen] = han[i];
			continue;
		}

		if (flag & CONV_KATA) {
			unsigned int	x;
			static const wchar_t *s1 = (const wchar_t *)
				/* 0123456789ABCDEF		        ‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e */
				"¶ · ¸"	/* 252X:@ƒ@ƒAƒBƒCƒDƒEƒFƒGƒHƒIƒJƒKƒLƒMƒN */
				" ¹ º » ¼ ½ ¾ ¿ À"	/* 253X:ƒOƒPƒQƒRƒSƒTƒUƒVƒWƒXƒYƒZƒ[ƒ\ƒ]ƒ^ */
				" Á ¯Â Ã Ä ÅÆÇÈÉÊ"	/* 254X:ƒ_ƒ`ƒaƒbƒcƒdƒeƒfƒgƒhƒiƒjƒkƒlƒmƒn */
				"  Ë  Ì  Í  Î";		/* 255X:ƒoƒpƒqƒrƒsƒtƒuƒvƒwƒxƒyƒzƒ{ƒ|     */
			static const wchar_t *s2 = (const wchar_t *)
				/* 0123456789ABCDEF		        ‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e */
				"Ê"	/* 254X:                              ƒn */
				"  Ë  Ì  Í  Î";		/* 255X:ƒoƒpƒqƒrƒsƒtƒuƒvƒwƒxƒyƒzƒ{ƒ|     */

			// [³Ş] => [ƒ”] ‚Ì•ÏŠ·
			if (han[i] == (unsigned char)'³' && han[i + 1] == (unsigned char)'Ş') {
				zen[pzen] = 0x83U;
				pzen++;
				i++;
				zen[pzen] = 0x94U;
				goto cont;
			}

			// ‘÷‰¹‚Ì•ÏŠ·
			for (x = 0; s1[x]; x++) {
				if (han[i] == s1[x] && han[i + 1] == (unsigned char)'Ş') {
					zen[pzen] = 0x83U;
					pzen++;
					i++;
					zen[pzen] = 0x4BU + x;
					goto cont;
				}
			}

			// ”¼‘÷‰¹‚Ì•ÏŠ·
			for (x = 0; s2[x]; x++) {
				if (han[i] == s2[x] && han[i + 1] == (unsigned char)'ß') {
					// ”¼‘÷‰¹
					zen[pzen] = 0x83U;
					pzen++;
					i++;
					zen[pzen] = 0x70U + x;
					goto cont;
				}
			}
		}

		// ‚»‚Ì‘¼‚Ì•ÏŠ·
		{
			unsigned short z = han2zen(han[i], flag);
			if (z >= 0x100) {
				zen[pzen] = (unsigned char)(z >> 8);
				pzen++;
				zen[pzen] = (unsigned char)z;
			} else {
				zen[pzen] = (unsigned char)z;
			}
		}
	cont:;
	}

	return(pzen);
}

unsigned short zen2han(unsigned short c, int flag)
{
	if (c <= 0x100) return(c);				// ”ñŠ¿š
	if (flag & CONV_ALPHA) {
		if (c == 0x8140U) return(' ');			// ‹ó”’
		if (c >= 0x8260U && c <= 0x8279U) {		// ‚`|‚y
			return('A' + (c - 0x8260U));
		}
		if (c >= 0x8281U && c <= 0x829AU) {		// ‚|‚š
			return('a' + (c - 0x8281U));
		}
	}
	if (flag & CONV_SUJI) {
		if (c >= 0x824FU && c <= 0x8258U) {		// ‚O|‚X
			return('0' + (c - 0x824FU));
		}
	}

	int		i;
	if (flag & CONV_KIGOU) {
		// ‚È‚ñ‚Å"`"‚ğ"-"‚É‚µ‚Ä‚é‚Ì‚©Šo‚¦‚Ä‚È‚¢‚Ì‚Åíœ 041018
		static const wchar_t *han = (const wchar_t *)
			",.:;?!Şß^~_-/|`\'\"()[]{}+-=<>\\$%#&*@"; /* BeachMonster 102 *//* STEP 016 */
		static const wchar_t *zen = (const wchar_t *)
			"CDFGHIJKOPQ|^bMfhijmnop{|ƒ„“”•–—\0"; /* BeachMonster 102 *//* STEP 016 */
		for (i = 0; zen[i + 1]; i += 2) {
			if (c == ((zen[i] << 8) | zen[i + 1])) return(han[i / 2]);
		}
		extern bool g_bZenHanKigouKana; /* STEP 016 */
		if (!g_bZenHanKigouKana) { /* STEP 016 */
			static const wchar_t *han2 = (const wchar_t *)
				"¥¤¡¢£";
			static const wchar_t *zen2 = (const wchar_t *)
				"EABuv\0";
			for (i = 0; zen2[i + 1]; i += 2) {
				if (c == ((zen2[i] << 8) | zen2[i + 1])) return(han2[i / 2]);
			}
		}
	}
	if (flag & CONV_KATA) {
		static const wchar_t *han = (const wchar_t *)
			"§±¨²©³ª´«µ¶·¸¹º»¼½¾¿ÀÁ¯ÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓ¬Ô­Õ®Ö×ØÙÚÛÜ¦İ°";
		static const wchar_t *kata = (const wchar_t *)
			"ƒ@ƒAƒBƒCƒDƒEƒFƒGƒHƒIƒJƒLƒNƒPƒRƒTƒVƒXƒZƒ\ƒ^ƒ`ƒbƒcƒeƒgƒiƒjƒkƒlƒm"
			"ƒnƒqƒtƒwƒzƒ}ƒ~ƒ€ƒƒ‚ƒƒƒ„ƒ…ƒ†ƒ‡ƒˆƒ‰ƒŠƒ‹ƒŒƒƒƒ’ƒ“[\0";
		// ƒJƒ^ƒJƒi
		for (i = 0; kata[i + 1]; i += 2) {
			if (c == ((kata[i] << 8) | kata[i + 1])) return(han[i / 2]);
		}
		extern bool g_bZenHanKigouKana; /* STEP 016 */
		if (g_bZenHanKigouKana) { /* STEP 016 */
			static const wchar_t *han2 = (const wchar_t *)
				"¥¤¡¢£";
			static const wchar_t *kata2 = (const wchar_t *)
				"EABuv\0";
			for (i = 0; kata2[i + 1]; i += 2) {
				if (c == ((kata2[i] << 8) | kata2[i + 1])) return(han2[i / 2]);
			}
		}
	}

	// •ÏŠ·‚Å‚«‚È‚©‚Á‚½
	return(c);
}

int conv_zen2hans(wchar_t *han, const wchar_t *zen, int flag)
{
	int		i;
	int		phan = 0;		// ”¼ŠpˆÊ’u
	int		l = wcslen(zen);
	han[0] = '\0';

	for (i = 0; i < l; i++, phan++, han[phan] = '\0') {
		if (!iskanji(zen[i])) {		// ”ñŠ¿š
			han[phan] = zen[i];
			continue;				// –³•ÏŠ·
		}

		if (flag & CONV_KATA) {
			int		j;
			static const wchar_t *k1 = (const wchar_t *)"ƒKƒMƒOƒQƒSƒUƒWƒYƒ[ƒ]ƒ_ƒaƒdƒfƒhƒoƒrƒuƒxƒ{ƒ”\0";
			static const wchar_t *h1 = (const wchar_t *)"‚ª‚¬‚®‚°‚²‚´‚¶‚¸‚º‚¼‚¾‚À‚Ã‚Å‚Ç‚Î‚Ñ‚Ô‚×‚Ú\0\0\0";
			static const wchar_t *k2 = (const wchar_t *)"ƒpƒsƒvƒyƒ|\0";
			static const wchar_t *h2 = (const wchar_t *)"‚Ï‚Ò‚Õ‚Ø‚Û\0";
			// ‘÷‰¹‚Ì•ÏŠ·
			for (j = 0; k1[j + 1]; j += 2) {
#if 1
				if (zen[i] == k1[j] && zen[i + 1] == k1[j + 1]) {	// ƒJƒ^ƒJƒi
#else
				if ((zen[i] == k1[j] && zen[i+1] == k1[j+1])	// ƒJƒ^ƒJƒi
					||  (zen[i] == h1[j] && zen[i+1] == h1[j+1])) {	// ‚Ğ‚ç‚ª‚È
#endif
					static const wchar_t *h = (const wchar_t *)"¶·¸¹º»¼½¾¿ÀÁÂÃÄÊËÌÍÎ³";
					han[phan] = h[j / 2];
					phan++;
					han[phan] = (unsigned char)'Ş';
					i++;
					goto cont;
				}
			}

			// ”¼‘÷‰¹‚Ì•ÏŠ·
			for (j = 0; k2[j + 1]; j += 2) {
#if 1
				if (zen[i] == k2[j] && zen[i + 1] == k2[j + 1]) {	// ƒJƒ^ƒJƒi
#else
				if ((zen[i] == k2[j] && zen[i+1] == k2[j+1])	// ƒJƒ^ƒJƒi
					||  (zen[i] == h2[j] && zen[i+1] == h2[j+1])) {	// ‚Ğ‚ç‚ª‚È
#endif
					static const wchar_t *h = (const wchar_t *)"ÊËÌÍÎ";
					han[phan] = h[j / 2];
					phan++;
					han[phan] = (unsigned char)'ß';
					i++;
					goto cont;
				}
			}
		}

		// ‚»‚Ì‘¼‚Ì•ÏŠ·
		{
			unsigned short c;
			c = zen2han((zen[i] << 8) | zen[i + 1], flag);
			i++;
			if (c >= 0x100) {
				han[phan] = (unsigned char)(c >> 8);
				phan++;
				han[phan] = (unsigned char)c;
			} else {
				han[phan] = (unsigned char)c;
			}
		}

	cont:;
	}

	return(phan);
}

static const wchar_t *kata = (const wchar_t *)
"ƒ@ƒAƒBƒCƒDƒEƒFƒGƒHƒIƒJƒKƒLƒMƒNƒOƒPƒQƒRƒSƒTƒUƒVƒWƒXƒYƒZƒ[ƒ\ƒ]"
"ƒ^ƒ_ƒ`ƒaƒbƒcƒdƒeƒfƒgƒhƒiƒjƒkƒlƒmƒnƒoƒpƒqƒrƒsƒtƒuƒvƒwƒxƒyƒzƒ{ƒ|"
"ƒ}ƒ~ƒ€ƒƒ‚ƒƒƒ„ƒ…ƒ†ƒ‡ƒˆƒ‰ƒŠƒ‹ƒŒƒƒƒƒ’ƒ“";
static const wchar_t *hira = (const wchar_t *)
"‚Ÿ‚ ‚¡‚¢‚£‚¤‚¥‚¦‚§‚¨‚©‚ª‚«‚¬‚­‚®‚¯‚°‚±‚²‚³‚´‚µ‚¶‚·‚¸‚¹‚º‚»‚¼"
"‚½‚¾‚¿‚À‚Á‚Â‚Ã‚Ä‚Å‚Æ‚Ç‚È‚É‚Ê‚Ë‚Ì‚Í‚Î‚Ï‚Ğ‚Ñ‚Ò‚Ó‚Ô‚Õ‚Ö‚×‚Ø‚Ù‚Ú‚Û"
"‚Ü‚İ‚Ş‚ß‚à‚á‚â‚ã‚ä‚å‚æ‚ç‚è‚é‚ê‚ë‚ì‚í‚ğ‚ñ";
static const wchar_t *alphaS = (const wchar_t *)
"‚‚‚‚ƒ‚„‚…‚†‚‡‚ˆ‚‰‚Š‚‹‚Œ‚‚‚‚‚‘‚’‚“‚”‚•‚–‚—‚˜‚™‚šf‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X" /* STEP 026 */;
static const wchar_t *alphaL = (const wchar_t *)
"‚`‚a‚b‚c‚d‚e‚f‚g‚h‚i‚j‚k‚l‚m‚n‚o‚p‚q‚r‚s‚t‚u‚v‚w‚x‚yf‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X" /* STEP 026 */;

static const wchar_t *kata_dakuon = (const wchar_t *) /* FunnyCorn 179 */
"ƒ@ƒAƒBƒCƒDƒEƒFƒGƒHƒIƒJƒJƒLƒLƒNƒNƒPƒPƒRƒRƒTƒTƒVƒVƒXƒXƒZƒZƒ\ƒ\"
"ƒ^ƒ^ƒ`ƒ`ƒbƒcƒcƒeƒeƒgƒgƒiƒjƒkƒlƒmƒnƒnƒnƒqƒqƒqƒtƒtƒtƒwƒwƒwƒzƒzƒz"
"ƒ}ƒ~ƒ€ƒƒ‚ƒƒƒ„ƒ…ƒ†ƒ‡ƒˆƒ‰ƒŠƒ‹ƒŒƒƒƒƒ’ƒ“";

void conv_table(const wchar_t *before, const wchar_t *after, wchar_t *str)
{
	while (*str != '\0') {
		if (iskanji(*str)) {		// Š¿š
			int i; for (i = 0; before[i]; i += 2) {
				if (before[i] == str[0] && before[i + 1] == str[1]) {
					str[0] = after[i];
					str[1] = after[i + 1];
					break;
				}
			}
			str++;
		}
		str++;
	}
}
// [ƒJƒ^ƒJƒi]‚Ì‘÷‰¹A”¼‘÷‰¹‚ğ‚È‚­‚·
void conv_kata_erase_dakuon(wchar_t *str)
{
	conv_table(kata, kata_dakuon, str);
}
// [ƒJƒ^ƒJƒi]=>[‚Ğ‚ç‚ª‚È]‚É•ÏŠ·
void conv_kata2hira(wchar_t *str)
{
	conv_table(kata, hira, str);
}

// [‚Ğ‚ç‚ª‚È]=>[ƒJƒ^ƒJƒi]‚É•ÏŠ·
void conv_hira2kata(wchar_t *str)
{
	conv_table(hira, kata, str);
}

// [¬•¶š]=>[‘å•¶š]‚É•ÏŠ·
void conv_upper(wchar_t *str)
{
	_wcsupr(str);
	conv_table(alphaS, alphaL, str);
}

// [‘å•¶š]=>[¬•¶š]‚É•ÏŠ·
void conv_lower(wchar_t *str)
{
	_wcslwr(str);
	conv_table(alphaL, alphaS, str);
}

void lower_suffix_word(wchar_t *str, int len, CString suffixs) /* STEP 026*/
{
	CString strZWord((LPCWSTR)str, len);
	CString strWord;
	conv_zen2hans((wchar_t *)strWord.GetBuffer(len * 2 + 1), (const wchar_t *)(const wchar_t *)strZWord, CONV_ALL);
	strWord.ReleaseBuffer();
	strWord.MakeLower();
	while (1) {
		CString suffix = suffixs.SpanExcluding(L",");
		if (suffix == strWord) {
			if (iskanji(*str)) {		// Š¿š
				int i; for (i = 0; alphaS[i]; i += 2) {
					if ((alphaS[i] == str[0] && alphaS[i + 1] == str[1])
						|| (alphaL[i] == str[0] && alphaL[i + 1] == str[1])) {
						str[0] = alphaS[i];
						str[1] = alphaS[i + 1];
						break;
					}
				}
			} else {
				*str = tolower(*str);
			}
			return;
		}
		suffixs.TrimLeft(suffix);
		suffixs.TrimLeft(',');
		if (suffixs.GetLength() == 0) {
			return;
		}
	}
}

bool isSentenceSeparate(wchar_t* str, int len, CString separator) /* STEP 026 */
{
	CString strZWord((LPCWSTR)str, len);
	CString strChar;
	conv_zen2hans((wchar_t *)strChar.GetBuffer(2 + 1), (const wchar_t *)(const wchar_t *)strZWord, CONV_ALL);
	strChar.ReleaseBuffer();
	for (int i = 0; i < separator.GetLength(); i++) {
		unsigned char c = separator.GetAt(i);
		if (iskanji(c)) {		// Š¿š
			char	kanji[3];
			kanji[0] = separator.GetAt(i);
			kanji[1] = separator.GetAt(i + 1);
			kanji[2] = '\0';
			if (strChar == kanji) {
				return true;
			}
		} else {
			if (strChar == separator.GetAt(i)) {
				return true;
			}
		}
	}
	return false;
}

// ’PŒê‚Ì‚P•¶š–Ú‚Ì‚İA[¬•¶š]=>[‘å•¶š]‚É•ÏŠ·
void conv_first_upper(wchar_t *str, const wchar_t *suffixs, const wchar_t* separator, bool bUseSuffix)
{
	bool	bFirst = true;
	wchar_t*	pFirstPos = NULL; /* STEP 026 */
	wchar_t*	pEndPos = NULL; /* STEP 026 */
	bool	bFirstWord = true; /* STEP 026 */
	while (TRUE) {
		if (iskanji(*str)) {		// Š¿š
			int i; for (i = 0; alphaS[i]; i += 2) {
				if ((alphaS[i] == str[0] && alphaS[i + 1] == str[1])
					|| (alphaL[i] == str[0] && alphaL[i + 1] == str[1])) {
					if (bFirst) {
						str[0] = alphaL[i];
						str[1] = alphaL[i + 1];
						pFirstPos = str; /* STEP 026 */
					}
					bFirst = false;
					break;
				}
			}
			if (alphaS[i] == '\0') {	// ’PŒê‚Ì‹æØ‚è
				pEndPos = str - 1; /* STEP 026 */
				if (pFirstPos != NULL && pEndPos != NULL && !bFirstWord && bUseSuffix) { /* STEP 026 */
					lower_suffix_word(pFirstPos, pEndPos - pFirstPos + 1, suffixs);
				}
				pFirstPos = NULL; /* STEP 026 */
				pEndPos = NULL; /* STEP 026 */
				if (!bFirst) bFirstWord = FALSE; /* STEP 026 */
				if (bUseSuffix) { /* STEP 026 */
					if (isSentenceSeparate(str, 2, separator)) {
						bFirstWord = TRUE;
					}
				}
				bFirst = true;
			}
			if (*str == '\0')	break; /* STEP 026 */
			str++;
		} else {					// ”ñŠ¿š
			if ((*str >= 'a' && *str <= 'z')
				|| (*str >= 'A' && *str <= 'Z')
				|| (*str >= '0' && *str <= '9') /* STEP 026 2005.12.02 */
				|| (*str == '\'')) {
				if (bFirst) {
					*str = toupper(*str);
					bFirst = false;
					pFirstPos = str; /* STEP 026 */
				}
			} else {
				// ’PŒê‚Ì‹æØ‚è
				pEndPos = str - 1;
				if (pFirstPos != NULL && pEndPos != NULL && !bFirstWord && bUseSuffix) { /* STEP 026 */
					lower_suffix_word(pFirstPos, pEndPos - pFirstPos + 1, suffixs);
				}
				pFirstPos = NULL; /* STEP 026 */
				pEndPos = NULL; /* STEP 026 */
				if (!bFirst) bFirstWord = FALSE; /* STEP 026 */
				if (bUseSuffix) { /* STEP 026 */
					if (isSentenceSeparate(str, 1, separator)) {
						bFirstWord = TRUE;
					}
				}
				if (*str == '\n') {
					bFirstWord = TRUE;
				}
				bFirst = true;
			}
		}
		if (*str == '\0')	break; /* STEP 026 */
		str++;
	}
}

bool isKigou(char ch) {
	static const wchar_t *s1 = (const wchar_t *)
		/* 0123456789ABCDEF		        ‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e */
		"   ,. :;?!Şß   "		/* 212X:@@ABCDEFGHIJKLMN */
		"^~_            /"	/* 213X:OPQRSTUVWXYZ[\]^ */
		"   |  `\' \"()  []"	/* 214X:_`abcdefghijklmn */
		"{}          +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		/* STEP 016 *///"{}    ¢£    +-   "	/* 215X:opqrstuvwxyz{|}~7F */
		" = <>          \\"	/* 216X:€‚ƒ„…†‡ˆ‰Š‹Œ */
		"$  %#&*@        ";	/* 217X:‘’“”•–—˜™š›œ   */
	for (int i = 0; s1[i] != '\0'; i++) {
		if (ch == s1[i]) {
			return true;
		}
	}
	return false;
}

wchar_t* fixed_upper_lower(wchar_t *str, CStringArray& fixedWords) /* STEP 040*/
{
	CString strZWord((LPCWSTR)str);
	CString strWord;
	conv_zen2hans((wchar_t *)strWord.GetBuffer(wcslen((wchar_t*)str) + 1), (const wchar_t *)(const wchar_t *)strZWord, CONV_ALL);
	strWord.ReleaseBuffer();
	strWord.MakeLower();
	for (int i = 0; i < fixedWords.GetSize(); i++) {
		CString fixed = fixedWords.GetAt(i);
		CString strFixZWord(fixed);
		CString strFixWord;
		conv_zen2hans((wchar_t *)strFixWord.GetBuffer(strFixZWord.GetLength() + 1), (const wchar_t *)(const wchar_t *)strFixZWord, CONV_ALL);
		strFixWord.ReleaseBuffer();
		fixed = strFixWord;
		fixed.MakeLower();
		//		if (fixed == strWord) {
		if (strWord.Find(fixed, 0) == 0 && (strWord == fixed || (strWord.GetLength() >= fixed.GetLength() && isKigou(strWord.GetAt(wcslen(fixed)))))) {
			wchar_t* pos = str;
			for (int j = 0; j < fixed.GetLength(); j++) {
				if (iskanji(*pos)) {		// Š¿š
					for (int k = 0; alphaS[k]; k += 2) {
						if ((alphaS[k] == pos[0] && alphaS[k + 1] == pos[1])
							|| (alphaL[k] == pos[0] && alphaL[k + 1] == pos[1])) {
							if (isupper(strFixWord.GetAt(j))) {
								pos[0] = alphaL[k];
								pos[1] = alphaL[k + 1];
							} else {
								pos[0] = alphaS[k];
								pos[1] = alphaS[k + 1];
							}
							break;
						}
					}
					pos += 2;
				} else {
					*pos = strFixWord.GetAt(j);
					pos++;
				}
			}
			return pos;
		}
	}
	return NULL;
}

void conv_fixed_upper_lower(wchar_t *str, CStringArray& fixedWords) /* STEP 040 */
{
	wchar_t* current = str;
	bool bConv = false;
	while (TRUE) {
		if ((current = fixed_upper_lower(str, fixedWords))) {
			bConv = true;
			str = current;
		} else {
			bConv = false;
			current = str;
		}
		if (*str == '\0')	break;
		if (bConv)	continue;
		//if (iskanji(*str)) {		// Š¿š
		//	str++;
		//}
		//str++;
		bool bBreak;
		if (current == str) {
			bBreak = TRUE;
		}
		while (TRUE) {
			if (*str == '\0')	break;
			if (iskanji(*str)) {		// Š¿š
				int i; for (i = 0; alphaS[i]; i += 2) {
					if ((alphaS[i] == str[0] && alphaS[i + 1] == str[1])
						|| (alphaL[i] == str[0] && alphaL[i + 1] == str[1])) {
						break;
					}
				}
				if (alphaS[i] == '\0') {	// ’PŒê‚Ì‹æØ‚è
					str += 2;
					continue;
				} else {
					if (!bBreak) {
						break;
					}
					str += 2;
				}
			} else {					// ”ñŠ¿š
				if ((*str >= 'a' && *str <= 'z')
					|| (*str >= 'A' && *str <= 'Z')
					|| (*str >= '0' && *str <= '9')
					|| (*str == '\'')) {
					if (!bBreak) {
						break;
					}
					str++;
				} else {
					str++;
					if (bBreak) {
						break;
					}
					continue;
				}
			}
		}
	}
}
