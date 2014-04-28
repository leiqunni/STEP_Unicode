#define WM_SMX_IPC WM_USER
/* SCMPX�E�B���h�E�ɉ��L�̂悤�Ȍ`���Ń��b�Z�[�W�𑗂��Ă������� */

// result = SendMessage( hwnd_scmpx, WM_SMX_IPC, command_data, command );






#define IPC_GETVERSION 0
/* IPC_GETVERSION �𑗂�Ǝ��̒l��Ԃ��܂� */
/* Version 0.0.7e = 0x000007e0 */
/* Version 0.0.8j = 0x00000800 */
/* Version 0.0.9e = 0x000009e0 */
/* Version 0.0.9j = 0x00000900 */
/* Version 0.0.9A = 0x000009a0 */
/* Version 1.00e = 0x000010e0 */
/* Version 1.00j = 0x00001000 */
/* Version 1.10j = 0x00001100 */
/* Version 1.11e = 0x000011e0 */
/* Version 1.11j = 0x00001110 */
/* Version 1.20e = 0x000012e0 */
/* Version 1.20j = 0x00001200 */
/* Version 1.30e = 0x000013e0 */
/* Version 1.30j = 0x00001300 */
/* Version 1.40e = 0x000014e0 */
/* Version 1.40j = 0x00001400 */
/* Version 1.41e = 0x000014e1 */
/* Version 1.41j = 0x00001401 */
/* Version 1.42e = 0x000014e2 */
/* Version 1.42j = 0x00001402 */
/* Version 1.50e = 0x000015e0 */
/* Version 1.50j = 0x00001500 */

// if ( SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_GETVERSION ) != 0x00000800 )
// MessageBox( NULL, L"Error, SCMPX 0.0.8(Japanese) not found", L"Warning", MB_OK );




#define IPC_PLAYFILE 100
/* IPC_PLAYFILE �̓v���C���X�g�Ƀt�@�C����ǉ����܂� */
/* (�g���q�� '.m3u' �̏ꍇ�̓v���C���X�g�t�@�C���Ƃ��ēǂݍ��܂�܂�) */

// char file[] = L"C:\\Song\\mkr.mp3";
// for( i = 0; i <= wcslen( file ); i++ )
// SendMessage( hwnd_scmpx, WM_SMX_IPC, file[i], IPC_PLAYFILE );




#define IPC_DELETE 101
/* IPC_DELETE �̓v���C���X�g���N���A���܂� */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_DELETE );




#define IPC_STARTPLAY 102
/* IPC_STARTPLAY �͍Đ��R�}���h���������܂� */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_STARTPLAY );




#define IPC_CHDIR 103
/* IPC_CHDIR ��SCMPX�̃J�����g�f�B���N�g����ύX���܂� */

// char dir[] = L"C:\\Song";
// for( i = 0; i <= wcslen( dir ); i++ )
// SendMessage( hwnd_scmpx, WM_SMX_IPC, dir[i], IPC_PLAYFILE );




#define IPC_ISPLAYING 104
/* IPC_ISPLAYING �͉��L�̍Đ��X�e�[�^�X��Ԃ��܂� */
/* �߂�l=0 : ��~�� */
/* �߂�l=1 : �Đ��� */
/* �߂�l=3 : �ꎞ��~ */

// status = SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_ISPLAYING );




#define IPC_GETOUTPUTTIME 105
/* IPC_GETOUTPUTTIME �͍Đ����Ԃ�Ԃ��܂� */
/* wParam=0 �ɂ���ƌ��݂̍Đ����Ԃ�ms�P�ʂŕԂ��܂� */
/* wParam=1 �ɂ���Ɠǂݍ��܂�Ă���Ȃ̒������b�P�ʂŖ߂��Ă��܂� */
/* �߂�l=-1 �͍Đ����Ă��Ȃ����A�G���[�ł� */
/* ���Đ����Ԃ͎����b�P�ʂ̂��Ȃ肢��������Ȓl���߂����̂Œ��ӂ��Ă������� */

// song_pos = SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_GETOUTPUTTIME );
// song_len = SendMessage( hwnd_scmpx, WM_SMX_IPC, 1, IPC_GETOUTPUTTIME );




#define IPC_JUMPTOTIME 106
/* IPC_JUMPTOTIME ��ms�P�ʂōĐ����̋Ȃ̈ʒu��ύX���܂� */
/* -1�͒�~���A1��EOF�A0���߂��Ă���Ɛ������Ӗ����܂� */

// status = SendMessage( hwnd_scmpx, WM_SMX_IPC, new_song_pos, IPC_JUMPTOTIME );




#define IPC_WRITEPLAYLIST 120
/* IPC_WRITEPLAYLIST �̓v���C���X�g�������o���܂� */
/* �W���̃v���C���X�g�͐�΃p�X�ŁA�w�肵�����X�g�ɂ͑��΃p�X�ŏ������܂�܂� */

// char favorite[] = L"C:\\mp3z\\favorite.m3u";
// for( i = 0; i <= wcslen( favorite ); i++ )
// SendMessage( hwnd_scmpx, WM_SMX_IPC, favorite[i], IPC_WRITEPLAYLIST );

/*----
�@lParam=121�ȍ~��WinAMP 2.0(Pre2 9/2��)�Œǉ����ꂽ�t�����g�G���h�ł��B
�@SCMPX�ł� version 0.0.9a/e ����Ή����Ă��܂��B
�@lParam=211��WinAMP 2.04�AlParam=125,126��WinAMP 2.05�̃t�����g�G���h��
�@SCMPX�ł͂��ꂼ�� version 1.10�A1.11 ����Ή����Ă��܂��B
----*/





#define IPC_SETPLAYLISTPOS 121
/* �v���C���X�g�̈ʒu��ύX���܂� */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, new_pl_pos, IPC_SETPLAYLISTPOS );




#define IPC_SETVOLUME 122
/* �{�����[����ύX���܂�(�l��0-255�ŁA255���ő�ł�) */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, new_volume, IPC_SETVOLUME );




#define IPC_SETPANNING 123
/* �p����ύX���܂�(�l��0-255�A���l�̒Ⴂ�ق��������Œ�����128�ł�) */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, new_pan, IPC_SETPANNING );




#define IPC_GETLISTLENGTH 124
/* �v���C���X�g�̒�����Ԃ��܂� */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_GETLISTLENGTH );




#define IPC_GETLISTPOS 125
/* �I������Ă���v���C���X�g�ԍ���Ԃ��܂� */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_GETLISTPOS );




#define IPC_GETINFO 126
/* ���ݓǂݍ��܂�Ă���t�@�C���̃t�H�[�}�b�g��Ԃ��܂� */
/* wParam=0 �̂Ƃ��̓T���v�����O���[�g */
/* wParam=1 �̂Ƃ��̓r�b�g���[�g */
/* wParam=2 �̂Ƃ��̓`���l���� */

// sfreq = SendMessage( hwnd_scmpx, WM_SMX_IPC, 0, IPC_GETINFO );
// brate = SendMessage( hwnd_scmpx, WM_SMX_IPC, 1, IPC_GETINFO );
// nch = SendMessage( hwnd_scmpx, WM_SMX_IPC, 2, IPC_GETINFO );




#define IPC_GETPLAYLISTFILE 211
/* �v���C���X�g�ɓo�^����Ă���t�@�C�����̕�����|�C���^��Ԃ��܂� */
/* �߂�l��NULL�̏ꍇ�̓G���[�ł� */

// SendMessage( hwnd_scmpx, WM_SMX_IPC, index, IPC_GETPLAYLISTFILE );
