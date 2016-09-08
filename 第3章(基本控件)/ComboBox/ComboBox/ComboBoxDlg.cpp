// ComboBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComboBox.h"
#include "ComboBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CComboBoxDlg �Ի���




CComboBoxDlg::CComboBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComboBoxDlg::IDD, pParent)
	, szFruitName(_T(""))
	, szCurName(_T(""))
	, szCurName2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComboBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, MyComboBox);
	DDX_Text(pDX, IDC_EDIT2, szFruitName);
	DDX_Text(pDX, IDC_EDIT1, szCurName);
	DDX_Control(pDX, IDC_COMBO2, MyComboBox2);
	DDX_Text(pDX, IDC_EDIT3, szCurName2);
}

BEGIN_MESSAGE_MAP(CComboBoxDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT2, &CComboBoxDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_ADD, &CComboBoxDlg::OnBnClickedAdd)
	ON_CBN_SELCHANGE(IDC_COMBO, &CComboBoxDlg::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CComboBoxDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CComboBoxDlg ��Ϣ�������

BOOL CComboBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	this->MyComboBox.AddString ( L"ƻ��" ) ;
	this->MyComboBox.AddString ( L"�㽶" ) ;
	this->MyComboBox.AddString ( L"����" ) ;
	this->MyComboBox.SetCurSel ( 0 ) ;
	this->OnCbnSelchangeCombo () ;

	this->MyComboBox2.AddString ( L"ƻ��" ) ;
	this->MyComboBox2.AddString ( L"�㽶" ) ;
	this->MyComboBox2.AddString ( L"����" ) ;
	this->MyComboBox2.SetCurSel ( 0 ) ;
	this->OnCbnSelchangeCombo2 () ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CComboBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CComboBoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CComboBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CComboBoxDlg::OnEnChangeEdit2()
{
	this->UpdateData() ;
}

void CComboBoxDlg::OnBnClickedAdd()
{
	if ( this->szFruitName.IsEmpty() == TRUE )
		this->MessageBox ( L"������ˮ������", L"Error" ) ;
	else
	{
		this->MyComboBox.AddString ( this->szFruitName ) ;
		this->MyComboBox2.AddString ( this->szFruitName ) ;
	}
}

void CComboBoxDlg::OnCbnSelchangeCombo()
{
	int nCurSel = this->MyComboBox.GetCurSel () ;
	if ( nCurSel != LB_ERR )
	{
		this->MyComboBox.GetLBText(nCurSel, this->szCurName) ;
		this->UpdateData ( FALSE ) ;
	}
}

void CComboBoxDlg::OnCbnSelchangeCombo2()
{
	int nCurSel = this->MyComboBox2.GetCurSel () ;
	if ( nCurSel != LB_ERR )
	{
		this->MyComboBox2.GetLBText(nCurSel, this->szCurName2) ;
		this->UpdateData ( FALSE ) ;
	}
}
