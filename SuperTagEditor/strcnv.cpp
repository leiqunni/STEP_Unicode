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
		return c;					// ���䖢��`
	}
	if (flag & CONV_ALPHA) {
		if (c >= 'A' && c <= 'Z') return(0x8260U + (c - 'A'));	// �p�啶��
		if (c >= 'a' && c <= 'z') return(0x8281U + (c - 'a'));	// �p������
	}
	if (flag & CONV_SUJI) {
		if (c >= '0' && c <= '9') return(0x824FU + (c - '0'));	// ����
	}

	int		i;
	static const wchar_t *s1 = (const wchar_t *)
		/* 0123456789ABCDEF		        �O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e */
		"   ,. :;?!��   "		/* 212X:�@�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N */
		/* STEP 016 *///" ��,.�:;?!��   "		/* 212X:�@�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N */
		/* BeachMonster 102 *///"^~_         �- /"	/* 213X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
		/* Baja 169 *///"^~_          - /"	/* 213X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
		"^~_            /"	/* 213X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
		"   |  `\' \"()  []"	/* 214X:�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n */
		"{}          +-   "	/* 215X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~7F */
		/* STEP 016 *///"{}    ��    +-   "	/* 215X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~7F */
		" = <>          \\"	/* 216X:�������������������������������� */
		"$  %#&*@        ";	/* 217X:������������������������������   */
	static const wchar_t *s2 = (const wchar_t *)
		/* 0123456789ABCDEF		        �O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e */
		"�����������޷޸"		/* 252X:�@�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N */
		"޹޺޻޼޽޾޿��"	/* 253X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
		"��ޯ������������"	/* 254X:�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n */
		"���������������� "	/* 255X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~7F */
		"��Ӭԭծ������ �"	/* 256X:�������������������������������� */
		"  ��";				/* 257X:�������������� */
	static const wchar_t *s3 = (const wchar_t *) /* BeachMonster 102 */
		/* 0123456789ABCDEF		        �O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e */
		"                "	/* 212X:�@�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N */
		"            �   "	/* 213X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
		"                "	/* 214X:�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n */
		"                "	/* 215X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~7F */
		"                "	/* 216X:�������������������������������� */
		"                ";	/* 217X:������������������������������   */
	;
	static const wchar_t *s4 = (const wchar_t *) /* STEP 016 */
		/* 0123456789ABCDEF		        �O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e */
		"  ��  �         "	/* 212X:�@�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N */
		"                "	/* 213X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
		"                "	/* 214X:�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n */
		"      ��        "	/* 215X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~7F */
		"                "	/* 216X:�������������������������������� */
		"                ";	/* 217X:������������������������������   */
	;
	if (flag & CONV_KIGOU) {
		for (i = 0; s1[i]; i++) if (c == s1[i]) return(0x8140U + i);	// �L��
	}
	if (flag & CONV_KATA) {
		for (i = 0; s2[i]; i++) if (c == s2[i]) return(0x8340U + i);	// �J�^�J�i
	}
	if (flag & CONV_KATA) { /* BeachMonster 102 */
		for (i = 0; s3[i]; i++) if (c == s3[i]) return(0x8140U + i - 1/* STEP 016*/);	// �L�������ǃJ�^�J�i����
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
	int		pzen = 0;		// �S�p�ʒu
	int		l = wcslen(han);
	zen[0] = '\0';

	for (i = 0; i < l; i++, pzen++, zen[pzen] = '\0') {
		if (han[i] == ' ') {		// ��
			if (flag & CONV_KIGOU) {
				zen[pzen] = 0x81U;
				pzen++;
				zen[pzen] = 0x40U;
			} else {
				zen[pzen] = ' ';
			}
			continue;
		}

		if (iskanji(han[i])) {		// ����
			zen[pzen] = han[i];
			pzen++;
			i++;
			zen[pzen] = han[i];
			continue;
		}

		if (flag & CONV_KATA) {
			unsigned int	x;
			static const wchar_t *s1 = (const wchar_t *)
				/* 0123456789ABCDEF		        �O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e */
				"� � �"	/* 252X:�@�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N */
				" � � � � � � � �"	/* 253X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
				" � �� � � ������"	/* 254X:�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n */
				"  �  �  �  �";		/* 255X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|     */
			static const wchar_t *s2 = (const wchar_t *)
				/* 0123456789ABCDEF		        �O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e */
				"�"	/* 254X:                              �n */
				"  �  �  �  �";		/* 255X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|     */

			// [��] => [��] �̕ϊ�
			if (han[i] == (unsigned char)'�' && han[i + 1] == (unsigned char)'�') {
				zen[pzen] = 0x83U;
				pzen++;
				i++;
				zen[pzen] = 0x94U;
				goto cont;
			}

			// �����̕ϊ�
			for (x = 0; s1[x]; x++) {
				if (han[i] == s1[x] && han[i + 1] == (unsigned char)'�') {
					zen[pzen] = 0x83U;
					pzen++;
					i++;
					zen[pzen] = 0x4BU + x;
					goto cont;
				}
			}

			// �������̕ϊ�
			for (x = 0; s2[x]; x++) {
				if (han[i] == s2[x] && han[i + 1] == (unsigned char)'�') {
					// ������
					zen[pzen] = 0x83U;
					pzen++;
					i++;
					zen[pzen] = 0x70U + x;
					goto cont;
				}
			}
		}

		// ���̑��̕ϊ�
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
	if (c <= 0x100) return(c);				// �񊿎�
	if (flag & CONV_ALPHA) {
		if (c == 0x8140U) return(' ');			// ��
		if (c >= 0x8260U && c <= 0x8279U) {		// �`�|�y
			return('A' + (c - 0x8260U));
		}
		if (c >= 0x8281U && c <= 0x829AU) {		// ���|��
			return('a' + (c - 0x8281U));
		}
	}
	if (flag & CONV_SUJI) {
		if (c >= 0x824FU && c <= 0x8258U) {		// �O�|�X
			return('0' + (c - 0x824FU));
		}
	}

	int		i;
	if (flag & CONV_KIGOU) {
		// �Ȃ��"�`"��"-"�ɂ��Ă�̂��o���ĂȂ��̂ō폜 041018
		static const wchar_t *han = (const wchar_t *)
			",.:;?!��^~_-/|`\'\"()[]{}+-=<>\\$%#&*@"; /* BeachMonster 102 *//* STEP 016 */
		static const wchar_t *zen = (const wchar_t *)
			"�C�D�F�G�H�I�J�K�O�P�Q�|�^�b�M�f�h�i�j�m�n�o�p�{�|��������������������\0"; /* BeachMonster 102 *//* STEP 016 */
		for (i = 0; zen[i + 1]; i += 2) {
			if (c == ((zen[i] << 8) | zen[i + 1])) return(han[i / 2]);
		}
		extern bool g_bZenHanKigouKana; /* STEP 016 */
		if (!g_bZenHanKigouKana) { /* STEP 016 */
			static const wchar_t *han2 = (const wchar_t *)
				"�����";
			static const wchar_t *zen2 = (const wchar_t *)
				"�E�A�B�u�v\0";
			for (i = 0; zen2[i + 1]; i += 2) {
				if (c == ((zen2[i] << 8) | zen2[i + 1])) return(han2[i / 2]);
			}
		}
	}
	if (flag & CONV_KATA) {
		static const wchar_t *han = (const wchar_t *)
			"����������������������������������������Ӭԭծ������ܦݰ";
		static const wchar_t *kata = (const wchar_t *)
			"�@�A�B�C�D�E�F�G�H�I�J�L�N�P�R�T�V�X�Z�\�^�`�b�c�e�g�i�j�k�l�m"
			"�n�q�t�w�z�}�~�����������������������������������[\0";
		// �J�^�J�i
		for (i = 0; kata[i + 1]; i += 2) {
			if (c == ((kata[i] << 8) | kata[i + 1])) return(han[i / 2]);
		}
		extern bool g_bZenHanKigouKana; /* STEP 016 */
		if (g_bZenHanKigouKana) { /* STEP 016 */
			static const wchar_t *han2 = (const wchar_t *)
				"�����";
			static const wchar_t *kata2 = (const wchar_t *)
				"�E�A�B�u�v\0";
			for (i = 0; kata2[i + 1]; i += 2) {
				if (c == ((kata2[i] << 8) | kata2[i + 1])) return(han2[i / 2]);
			}
		}
	}

	// �ϊ��ł��Ȃ�����
	return(c);
}

int conv_zen2hans(wchar_t *han, const wchar_t *zen, int flag)
{
	int		i;
	int		phan = 0;		// ���p�ʒu
	int		l = wcslen(zen);
	han[0] = '\0';

	for (i = 0; i < l; i++, phan++, han[phan] = '\0') {
		if (!iskanji(zen[i])) {		// �񊿎�
			han[phan] = zen[i];
			continue;				// ���ϊ�
		}

		if (flag & CONV_KATA) {
			int		j;
			static const wchar_t *k1 = (const wchar_t *)"�K�M�O�Q�S�U�W�Y�[�]�_�a�d�f�h�o�r�u�x�{��\0";
			static const wchar_t *h1 = (const wchar_t *)"�������������������������Âłǂ΂тԂׂ�\0\0\0";
			static const wchar_t *k2 = (const wchar_t *)"�p�s�v�y�|\0";
			static const wchar_t *h2 = (const wchar_t *)"�ς҂Ղ؂�\0";
			// �����̕ϊ�
			for (j = 0; k1[j + 1]; j += 2) {
#if 1
				if (zen[i] == k1[j] && zen[i + 1] == k1[j + 1]) {	// �J�^�J�i
#else
				if ((zen[i] == k1[j] && zen[i+1] == k1[j+1])	// �J�^�J�i
					||  (zen[i] == h1[j] && zen[i+1] == h1[j+1])) {	// �Ђ炪��
#endif
					static const wchar_t *h = (const wchar_t *)"�������������������γ";
					han[phan] = h[j / 2];
					phan++;
					han[phan] = (unsigned char)'�';
					i++;
					goto cont;
				}
			}

			// �������̕ϊ�
			for (j = 0; k2[j + 1]; j += 2) {
#if 1
				if (zen[i] == k2[j] && zen[i + 1] == k2[j + 1]) {	// �J�^�J�i
#else
				if ((zen[i] == k2[j] && zen[i+1] == k2[j+1])	// �J�^�J�i
					||  (zen[i] == h2[j] && zen[i+1] == h2[j+1])) {	// �Ђ炪��
#endif
					static const wchar_t *h = (const wchar_t *)"�����";
					han[phan] = h[j / 2];
					phan++;
					han[phan] = (unsigned char)'�';
					i++;
					goto cont;
				}
			}
		}

		// ���̑��̕ϊ�
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
"�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]"
"�^�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y�z�{�|"
"�}�~������������������������������������";
static const wchar_t *hira = (const wchar_t *)
"������������������������������������������������������������"
"�����������ÂĂłƂǂȂɂʂ˂̂͂΂ςЂт҂ӂԂՂւׂ؂قڂ�"
"�܂݂ނ߂������������������";
static const wchar_t *alphaS = (const wchar_t *)
"�����������������������������������������������������f�O�P�Q�R�S�T�U�V�W�X" /* STEP 026 */;
static const wchar_t *alphaL = (const wchar_t *)
"�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y�f�O�P�Q�R�S�T�U�V�W�X" /* STEP 026 */;

static const wchar_t *kata_dakuon = (const wchar_t *) /* FunnyCorn 179 */
"�@�A�B�C�D�E�F�G�H�I�J�J�L�L�N�N�P�P�R�R�T�T�V�V�X�X�Z�Z�\�\"
"�^�^�`�`�b�c�c�e�e�g�g�i�j�k�l�m�n�n�n�q�q�q�t�t�t�w�w�w�z�z�z"
"�}�~������������������������������������";

void conv_table(const wchar_t *before, const wchar_t *after, wchar_t *str)
{
	while (*str != '\0') {
		if (iskanji(*str)) {		// ����
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
// [�J�^�J�i]�̑����A���������Ȃ���
void conv_kata_erase_dakuon(wchar_t *str)
{
	conv_table(kata, kata_dakuon, str);
}
// [�J�^�J�i]=>[�Ђ炪��]�ɕϊ�
void conv_kata2hira(wchar_t *str)
{
	conv_table(kata, hira, str);
}

// [�Ђ炪��]=>[�J�^�J�i]�ɕϊ�
void conv_hira2kata(wchar_t *str)
{
	conv_table(hira, kata, str);
}

// [������]=>[�啶��]�ɕϊ�
void conv_upper(wchar_t *str)
{
	_wcsupr(str);
	conv_table(alphaS, alphaL, str);
}

// [�啶��]=>[������]�ɕϊ�
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
			if (iskanji(*str)) {		// ����
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
		if (iskanji(c)) {		// ����
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

// �P��̂P�����ڂ̂݁A[������]=>[�啶��]�ɕϊ�
void conv_first_upper(wchar_t *str, const wchar_t *suffixs, const wchar_t* separator, bool bUseSuffix)
{
	bool	bFirst = true;
	wchar_t*	pFirstPos = NULL; /* STEP 026 */
	wchar_t*	pEndPos = NULL; /* STEP 026 */
	bool	bFirstWord = true; /* STEP 026 */
	while (TRUE) {
		if (iskanji(*str)) {		// ����
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
			if (alphaS[i] == '\0') {	// �P��̋�؂�
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
		} else {					// �񊿎�
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
				// �P��̋�؂�
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
		/* 0123456789ABCDEF		        �O�P�Q�R�S�T�U�V�W�X�`�a�b�c�d�e */
		"   ,. :;?!��   "		/* 212X:�@�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N */
		"^~_            /"	/* 213X:�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^ */
		"   |  `\' \"()  []"	/* 214X:�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n */
		"{}          +-   "	/* 215X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~7F */
		/* STEP 016 *///"{}    ��    +-   "	/* 215X:�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~7F */
		" = <>          \\"	/* 216X:�������������������������������� */
		"$  %#&*@        ";	/* 217X:������������������������������   */
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
				if (iskanji(*pos)) {		// ����
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
		//if (iskanji(*str)) {		// ����
		//	str++;
		//}
		//str++;
		bool bBreak;
		if (current == str) {
			bBreak = TRUE;
		}
		while (TRUE) {
			if (*str == '\0')	break;
			if (iskanji(*str)) {		// ����
				int i; for (i = 0; alphaS[i]; i += 2) {
					if ((alphaS[i] == str[0] && alphaS[i + 1] == str[1])
						|| (alphaL[i] == str[0] && alphaL[i + 1] == str[1])) {
						break;
					}
				}
				if (alphaS[i] == '\0') {	// �P��̋�؂�
					str += 2;
					continue;
				} else {
					if (!bBreak) {
						break;
					}
					str += 2;
				}
			} else {					// �񊿎�
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
