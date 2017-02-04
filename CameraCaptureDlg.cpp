
// CameraCaptureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CameraCapture.h"
#include "CameraCaptureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CCameraCaptureDlg 对话框



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


// CCameraCaptureDlg 消息处理程序

BOOL CCameraCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAVEONCE)->EnableWindow(false);
	GetDlgItem(IDC_USERNAME)->SetWindowText("system");
	GetDlgItem(IDC_PASSWORD)->SetWindowText("system");
	GetDlgItem(IDC_IPADDRESS)->SetWindowText("192.168.1.4");
	GetDlgItem(IDC_PORT)->SetWindowText("6002");
	GetDlgItem(IDC_STREAM)->SetWindowText("0");
	GetDlgItem(IDC_CHANNAL)->SetWindowText("0");
	GetDlgItem(IDC_BUFFER)->SetWindowText("0");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCameraCaptureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCameraCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开当前摄像机
void CCameraCaptureDlg::OnBnClickedButtonConnect()
{
	UpdateData(true);

	// 打开相机
	hRealStream = TMCC_Init(TMCC_INITTYPE_REALSTREAM);

	memset(&realStream, 0, sizeof(tmPlayRealStreamCfg_t));
	realStream.dwSize = sizeof(tmPlayRealStreamCfg_t);

	sprintf_s(realStream.szAddress, m_strAddress);
	sprintf_s(realStream.szUser, m_strUserName);
	sprintf_s(realStream.szPass, m_strPassword);
	realStream.iPort = m_iPort;
	realStream.byChannel = m_iChannal;		// NVR等设备会有多通道，通道编号从0开始
	realStream.byStream = m_iStream;		// 码流号，0为主码流，1为从码流，2为第三码流，依次类推		
	realStream.byForceDecode = 1;	// byForceDecode=1表示强制解码m_ctrlImage.GetSafeHwnd()
	realStream.byConnectType = 0;	// 连接类型，设备会根据这个标记启用对应的传输协议		
	realStream.byMultiStream = 0;	// 此值有效忽略byStream，同时取得多码流数据，用于连接鱼眼全景设备

	if (TMCC_ERR_SUCCESS != TMCC_ConnectStream(hRealStream, &realStream,NULL))
	{
		MessageBox("连接视频失败....");
	}


	//界面调整
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_SAVEONCE)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAVEMULTIPLE)->EnableWindow(false);
}

//断开当前摄像机
void CCameraCaptureDlg::OnBnClickedButtonDisconnect()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SAVEONCE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_SAVEMULTIPLE)->EnableWindow(true);
}

//保存当前摄像机图像（单张）
void CCameraCaptureDlg::OnBnClickedButtonSaveonce()
{
	// TODO:  在此添加控件通知处理程序代码
	if (TMCC_ERR_SUCCESS != TMCC_CapturePictureToFile(hRealStream, "./test.jpg", "JPEG"))
	{
		MessageBox("保存图像失败");
	}
	//WriteProfileString("",)
}

//保存所有摄像机，多张
void CCameraCaptureDlg::OnBnClickedButtonSavemultiple()
{
	// TODO:  在此添加控件通知处理程序代码
}
