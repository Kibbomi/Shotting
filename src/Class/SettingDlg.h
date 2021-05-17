#pragma once


// CSettingDlg ��ȭ �����Դϴ�.
#include "Gun.h"
#include "Gunparts.h"

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSettingDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_SETTING_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int m_gun;
	class Gun m_selectGun;
	class Gunparts m_selectParts;
	class Gunparts m_seleteMuzzleParts;
	int m_parts;
	int m_muzzlepart;
};
