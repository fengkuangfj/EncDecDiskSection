
// EncDiskSection.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEncDiskSectionApp:
// �йش����ʵ�֣������ EncDiskSection.cpp
//

class CEncDiskSectionApp : public CWinApp
{
public:
	CEncDiskSectionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEncDiskSectionApp theApp;