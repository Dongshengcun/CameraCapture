
// CameraCapture.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCameraCaptureApp: 
// �йش����ʵ�֣������ CameraCapture.cpp
//

class CCameraCaptureApp : public CWinApp
{
public:
	CCameraCaptureApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCameraCaptureApp theApp;