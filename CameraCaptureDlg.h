// CameraCaptureDlg.h : ͷ�ļ�
//

#pragma once

#include <tmTransDefine.h>
#include<tmControlClient.h>
#include<tmMpegCodeID.h>
#include "afxwin.h"


// CCameraCaptureDlg �Ի���
class CCameraCaptureDlg : public CDialogEx
{
// ����
public:
	CCameraCaptureDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CAMERACAPTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// �˿ں�
	int m_iPort;
	// �û���
	CString m_strUserName;
	// ����
	CString m_strPassword;
	// IP��ַ
	CString m_strAddress;
	// ����
	int m_iStream;
	// ͨ����
	int m_iChannal;
	// ��������С
	int m_ibuffer;
	// ��ʾ����
	CStatic m_ctrlImage;
};
