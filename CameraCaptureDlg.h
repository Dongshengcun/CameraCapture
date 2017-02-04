// CameraCaptureDlg.h : 头文件
//

#pragma once

#include <tmTransDefine.h>
#include<tmControlClient.h>
#include<tmMpegCodeID.h>
#include "afxwin.h"


// CCameraCaptureDlg 对话框
class CCameraCaptureDlg : public CDialogEx
{
// 构造
public:
	CCameraCaptureDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CAMERACAPTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonSaveonce();
	afx_msg void OnBnClickedButtonSavemultiple();

private:
	HANDLE hRealStream;
	tmPlayRealStreamCfg_t realStream;
public:
	// 端口号
	int m_iPort;
	// 用户名
	CString m_strUserName;
	// 密码
	CString m_strPassword;
	// IP地址
	CString m_strAddress;
	// 码流
	int m_iStream;
	// 通道号
	int m_iChannal;
	// 缓冲区大小
	int m_ibuffer;
	// 显示区域
	CStatic m_ctrlImage;
};
