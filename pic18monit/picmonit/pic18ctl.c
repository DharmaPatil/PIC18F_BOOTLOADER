/*********************************************************************
 *	DLL main
 *********************************************************************
 *
 */

#include <windows.h>
#include <stdio.h>


/*********************************************************************
 *	���C��
 *********************************************************************
 */

/*********************************************************************
 *
 *********************************************************************
 */

/*
 * DLL�G���g���|�C���g�֐��̌^�ƓT�^�I�ȃX�P���g���R�[�h
 */
BOOL APIENTRY					/* int __stdcall */
DllMain(HINSTANCE hInstance, DWORD ul_reason_for_call, LPVOID pParam)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		/* �����ɃO���[�o���ϐ����̏������R�[�h������ */
		/* ��loaddll ��DLL�����[�h�������͂��������s����� */
		break;

	case DLL_PROCESS_DETACH:
		/* �����ɃO���[�o���ϐ����̌�n���R�[�h������ */
		/* ��freedll ��DLL���A�����[�h�������͂��������s����� */
		break;

	case DLL_THREAD_ATTACH:
		/* �����ɃX���b�h���ɕK�v�ȕϐ����̏������R�[�h������ */
		break;

	case DLL_THREAD_DETACH:
		/* �����ɃX���b�h���ɕK�v�ȕϐ����̌�n���R�[�h������ */
		break;
	}
	return TRUE;
}


/*********************************************************************
 *	�ȉ��Adummy�֐�.
 *********************************************************************
 */

int disasm_print(unsigned char *buf,int size,int adr)
{
	return 0;
}

void cmdPortPrintOne(char *name,int adrs,int val)
{
//	char tmp[32];
//	printf("%8s(%02x) %02x %s\n",name,adrs,val,radix2str(tmp,val));
}

