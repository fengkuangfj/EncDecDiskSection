
// EncDiskSectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EncDiskSection.h"
#include "EncDiskSectionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEncDiskSectionDlg �Ի���




CEncDiskSectionDlg::CEncDiskSectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncDiskSectionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncDiskSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEncDiskSectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CEncDiskSectionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEncDiskSectionDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CEncDiskSectionDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CEncDiskSectionDlg ��Ϣ�������

BOOL CEncDiskSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEncDiskSectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEncDiskSectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEncDiskSectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEncDiskSectionDlg::OnBnClickedOk()
{
	UCHAR	Key[4]				= {0};
	HANDLE	hFile				= INVALID_HANDLE_VALUE;
	TCHAR	tchLog[MAX_PATH]	= {0};
	CHAR	chBufIn[0x200]		= {0};
	CHAR	chBufOut[0x200]		= {0};
	DWORD	dwRet				= 0;


	__try
	{
		Key[0] = 0x12;
		Key[1] = 0x34;
		Key[2] = 0x56;
		Key[3] = 0x78;

		hFile = CreateFile(
			_T("\\\\.\\f:"),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			StringCchPrintf(tchLog, _countof(tchLog), _T("CreateFile failed. (%d)"), GetLastError());
			MessageBox(tchLog, NULL, MB_OK);
			__leave;
		}

		if (!ReadFile(hFile, chBufIn, 0x200, &dwRet, NULL))
		{
			StringCchPrintf(tchLog, _countof(tchLog), _T("ReadFile failed. (%d)"), GetLastError());
			MessageBox(tchLog, NULL, MB_OK);
			__leave;
		}

		Jgg_Encrypt(Key, 4, (const unsigned char *)chBufIn, (unsigned char *)chBufOut, 0x200);

		SetFilePointer(hFile, 0, 0, FILE_BEGIN);

		dwRet = 0;
		if (!WriteFile(hFile, chBufOut, 0x200, &dwRet, NULL))
		{
			StringCchPrintf(tchLog, _countof(tchLog), _T("WriteFile failed. (%d)"), GetLastError());
			MessageBox(tchLog, NULL, MB_OK);
			__leave;
		}
	}
	__finally
	{
		if (INVALID_HANDLE_VALUE != hFile)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}
	}

	return ;
}


void CEncDiskSectionDlg::OnBnClickedCancel()
{
	CDialogEx::OnOK();
}


void CEncDiskSectionDlg::OnBnClickedButton1()
{
	UCHAR	Key[4]				= {0};
	HANDLE	hFile				= INVALID_HANDLE_VALUE;
	TCHAR	tchLog[MAX_PATH]	= {0};
	CHAR	chBufIn[0x200]		= {0};
	CHAR	chBufOut[0x200]		= {0};
	DWORD	dwRet				= 0;


	__try
	{
		Key[0] = 0x12;
		Key[1] = 0x34;
		Key[2] = 0x56;
		Key[3] = 0x78;

		hFile = CreateFile(
			_T("\\\\.\\f:"),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			StringCchPrintf(tchLog, _countof(tchLog), _T("CreateFile failed. (%d)"), GetLastError());
			MessageBox(tchLog, NULL, MB_OK);
			__leave;
		}

		if (!ReadFile(hFile, chBufIn, 0x200, &dwRet, NULL))
		{
			StringCchPrintf(tchLog, _countof(tchLog), _T("ReadFile failed. (%d)"), GetLastError());
			MessageBox(tchLog, NULL, MB_OK);
			__leave;
		}

		Jgg_Decrypt(Key, 4, (const unsigned char *)chBufIn, (unsigned char *)chBufOut, 0x200);

		SetFilePointer(hFile, 0, 0, FILE_BEGIN);

		dwRet = 0;
		if (!WriteFile(hFile, chBufOut, 0x200, &dwRet, NULL))
		{
			StringCchPrintf(tchLog, _countof(tchLog), _T("WriteFile failed. (%d)"), GetLastError());
			MessageBox(tchLog, NULL, MB_OK);
			__leave;
		}
	}
	__finally
	{
		if (INVALID_HANDLE_VALUE != hFile)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}
	}

	return ;
}
