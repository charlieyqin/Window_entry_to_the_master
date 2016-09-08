// ResDumpDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "PEInfo.h"


#define MAX_DEF_RES_TYPE 24

// CResDumpDlg �Ի���
class CResDumpDlg : public CDialog
{
// ����
public:
	CResDumpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RESDUMP_DIALOG };

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
	CTreeCtrl		m_ResDirectory;						// ���Ϳؼ�
	CPEInfo			PEInfo ;								
	BOOL			isDumpValid ;						// ��ʶ���Ϳؼ��ĵ�ǰ��ѡ���Ƿ����DUMP�����Ƿ�Ҷ�ӽ�㣩
	LPVOID			lpDumpResStart ;					// ��ǰѡ������Դ��VA
	DWORD			dwResSize ;							// ��ǰѡ������Դ��SIZE
	CString			szResourceType[MAX_DEF_RES_TYPE] ;	// ��Դ���͵�ID���ַ�����Ӧ��

public:
	afx_msg void OnBnClickedOk();						// ����DUMP��ǰѡ������Դ
public:
	afx_msg void OnBnClickedCancel();
public:
	BOOL GetResourceInfo(LPTSTR lpFilePath);			// ȡ��Ŀ����ļ��������Ϣ����ҪΪ��Դ��Ϣ��
public:
	CString m_FilePath;									// Ŀ���ļ���
public:
	CString m_RootNameEntryNum;	
public:
	CString m_RootIdEntryNum;
public:
	CString m_SubNameEntryNum;
public:
	CString m_SubIdEntryNum;
public:
	CString m_DataOffset;
public:
	CString m_DataRVA;
public:
	CString m_DataSize;
public:
	afx_msg void OnBnClickedBrowse();
public:
	void UpdateTreeCtrl(void);
public:
	// ȡ�õ�ǰѡ���������ֵܽ���е�����
	int GetIndexOfTreeCtrl(HTREEITEM hTreeItem);
public:
	// ��Ӧ���Ϳؼ���ϢSelected Item Changed
	afx_msg void OnTvnSelchangedResDirectory(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CString m_ResInfo;			// ��Դ������Ϣ
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
