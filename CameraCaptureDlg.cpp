
// CameraCaptureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CameraCapture.h"
#include "CameraCaptureDlg.h"
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


// CCameraCaptureDlg �Ի���



CCameraCaptureDlg::CCameraCaptureDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CCameraCaptureDlg::IDD, pParent)
, m_iPort(0)
, m_strUserName(_T(""))
, m_strPassword(_T(""))
, m_strAddress(_T(""))
, m_iStream(0)
, m_iChannal(0)
, m_ibuffer(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCameraCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PORT, m_iPort);
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_IPADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_STREAM, m_iStream);
	DDX_Text(pDX, IDC_CHANNAL, m_iChannal);
	DDX_Text(pDX, IDC_BUFFER, m_ibuffer);
	DDX_Control(pDX, IDC_IMAGE, m_ctrlImage);
}

BEGIN_MESSAGE_MAP(CCameraCaptureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CCameraCaptureDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CCameraCaptureDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_SAVEONCE, &CCameraCaptureDlg::OnBnClickedButtonSaveonce)
	ON_BN_CLICKED(IDC_BUTTON_SAVEMULTIPLE, &CCameraCaptureDlg::OnBnClickedButtonSavemultiple)
END_MESSAGE_MAP()


// CCameraCaptureDlg ��Ϣ�������

BOOL CCameraCaptureDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAVEONCE)->EnableWindow(false);
	GetDlgItem(IDC_USERNAME)->SetWindowText("system");
	GetDlgItem(IDC_PASSWORD)->SetWindowText("system");
	GetDlgItem(IDC_IPADDRESS)->SetWindowText("192.168.1.4");
	GetDlgItem(IDC_PORT)->SetWindowText("6002");
	GetDlgItem(IDC_STREAM)->SetWindowText("0");
	GetDlgItem(IDC_CHANNAL)->SetWindowText("0");
	GetDlgItem(IDC_BUFFER)->SetWindowText("0");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCameraCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCameraCaptureDlg::OnPaint()
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
HCURSOR CCameraCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�򿪵�ǰ�����
void CCameraCaptureDlg::OnBnClickedButtonConnect()
{
	UpdateData(true);

	// �����
	hRealStream = TMCC_Init(TMCC_INITTYPE_REALSTREAM);

	memset(&realStream, 0, sizeof(tmPlayRealStreamCfg_t));
	realStream.dwSize = sizeof(tmPlayRealStreamCfg_t);

	sprintf_s(realStream.szAddress, m_strAddress);
	sprintf_s(realStream.szUser, m_strUserName);
	sprintf_s(realStream.szPass, m_strPassword);
	realStream.iPort = m_iPort;
	realStream.byChannel = m_iChannal;		// NVR���豸���ж�ͨ����ͨ����Ŵ�0��ʼ
	realStream.byStream = m_iStream;		// �����ţ�0Ϊ��������1Ϊ��������2Ϊ������������������		
	realStream.byForceDecode = 1;	// byForceDecode=1��ʾǿ�ƽ���m_ctrlImage.GetSafeHwnd()
	realStream.byConnectType = 0;	// �������ͣ��豸��������������ö�Ӧ�Ĵ���Э��		
	realStream.byMultiStream = 0;	// ��ֵ��Ч����byStream��ͬʱȡ�ö��������ݣ�������������ȫ���豸

	if (TMCC_ERR_SUCCESS != TMCC_ConnectStream(hRealStream, &realStream,NULL))
	{
		MessageBox("������Ƶʧ��....");
	}


	//�������
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_SAVEONCE)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAVEMULTIPLE)->EnableWindow(false);
}

//�Ͽ���ǰ�����
void CCameraCaptureDlg::OnBnClickedButtonDisconnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAVEONCE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_SAVEMULTIPLE)->EnableWindow(true);
}

//���浱ǰ�����ͼ�񣨵��ţ�
void CCameraCaptureDlg::OnBnClickedButtonSaveonce()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (TMCC_ERR_SUCCESS != TMCC_CapturePictureToFile(hRealStream, "./test.jpg", "JPEG"))
	{
		MessageBox("����ͼ��ʧ��");
	}
	//WriteProfileString("",)
}

//�������������������
void CCameraCaptureDlg::OnBnClickedButtonSavemultiple()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
