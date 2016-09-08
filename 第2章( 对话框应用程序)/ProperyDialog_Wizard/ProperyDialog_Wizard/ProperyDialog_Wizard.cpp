// ProperyDialog_Wizard.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ProperyDialog_Wizard.h"
#include "ProperyDialog_WizardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MySheet.h"

// CProperyDialog_WizardApp

BEGIN_MESSAGE_MAP(CProperyDialog_WizardApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CProperyDialog_WizardApp ����

CProperyDialog_WizardApp::CProperyDialog_WizardApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CProperyDialog_WizardApp ����

CProperyDialog_WizardApp theApp;


// CProperyDialog_WizardApp ��ʼ��

BOOL CProperyDialog_WizardApp::InitInstance()
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

	///////////////////////////////////////
	// �������ԶԻ������
	CMySheet MySheet ( L"[��2��]���ԶԻ��򡪡��򵼶Ի���" ) ;
	// �������ԶԻ���Ϊ��ģ��
	MySheet.SetWizardMode () ;
	// ��ʾ�򵼶Ի���
	MySheet.DoModal () ;
	return TRUE ;
	///////////////////////////////////////

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CProperyDialog_WizardDlg dlg;
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
