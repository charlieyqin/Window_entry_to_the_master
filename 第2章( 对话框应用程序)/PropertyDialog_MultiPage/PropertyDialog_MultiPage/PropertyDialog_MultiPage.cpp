// PropertyDialog_MultiPage.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PropertyDialog_MultiPage.h"
#include "PropertyDialog_MultiPageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MySheet.h"


// CPropertyDialog_MultiPageApp

BEGIN_MESSAGE_MAP(CPropertyDialog_MultiPageApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPropertyDialog_MultiPageApp ����

CPropertyDialog_MultiPageApp::CPropertyDialog_MultiPageApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPropertyDialog_MultiPageApp ����

CPropertyDialog_MultiPageApp theApp;


// CPropertyDialog_MultiPageApp ��ʼ��

BOOL CPropertyDialog_MultiPageApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	///////////////////////////////////////////////////////////
	// �������ԶԻ������
	CMySheet MySheet ( L"[��2��]���ԶԻ��򡪡���ҳ���л�" ) ;
	// ��ʾ���ԶԻ���
	MySheet.DoModal () ;
	// ����Ҫִ������Ĵ�����
	return TRUE ;
	///////////////////////////////////////////////////////////

	CPropertyDialog_MultiPageDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
