#pragma once


// CSettingDlg 대화 상자입니다.
#include "Gun.h"
#include "Gunparts.h"

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSettingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_SETTING_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
