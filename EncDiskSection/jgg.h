
//*****************************************************
//
//			Author:		blueapplez
//			Email:		blueapple1987@163.com
//			Home:		http://hi.baidu.com/blueapple_c/home
//			Time:		2011-05
//
//*********************************************************

/*/******	��ע�⡿:���㷨�������������㷨, ��ģʽ���ܱ����һ����������, 
					����rc4�㷨�е��Ǹ��ṹ��� x y
					���㷨�ӽ��ܺ��������Ļ����СҪһ�£�����Ҫһ����ɼӽ��� 
					���������㷨rc4��û���������
					��ԭ����  ����һ����ôJgg���㷨.(- -!)
*/

#ifndef Jgg_INCLUDED
#define Jgg_INCLUDED

#include <Windows.h>
#include <strsafe.h>

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifdef __cplusplus
extern "C" 
{
#endif

	void Jgg_Encrypt(unsigned char IN *key, int iKeyLen, const unsigned char IN *inn, unsigned char OUT *out, int IN iSize);
	void Jgg_Decrypt(unsigned char IN *key, int iKeyLen, const unsigned char IN *inn, unsigned char OUT *out, int IN iSize);

	void Jgg_EncryptStream(
		__in PUCHAR key, 
		__in INT KeyLen, 
		__in PUCHAR Input, 
		__out PUCHAR Output, 
		__in INT Size );

	void Jgg_DecryptStream(
		__in PUCHAR key, 
		__in INT KeyLen, 
		__in PUCHAR Input, 
		__out PUCHAR Output, 
		__in INT Size );

#ifdef __cplusplus
}  /* end extern "C" */
#endif

#endif /* Jgg_INCLUDED */
