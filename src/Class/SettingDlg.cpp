// SettingDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Class.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ID_SETTING_DLG, pParent)
	, m_gun(0)
	
	, m_parts(0)
	, m_muzzlepart(0)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_GUN_RADIO1, m_gun);

	DDX_Radio(pDX, IDC_PARTS_RADIO1, m_parts);
	DDX_Radio(pDX, IDC_RADIO9, m_muzzlepart);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSettingDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSettingDlg �޽��� ó�����Դϴ�.


void CSettingDlg::OnBnClickedButton1()
{
	
	UpdateData(TRUE);

	switch (m_gun)
	{
	case 0:	//M416
		m_selectGun.m_damage = 43;
		m_selectGun.m_y_recoil = 10;
		m_selectGun.m_x_recoil = 5;
		m_selectGun.m_speed = 85;
		m_selectGun.m_load = 30;
		m_selectGun.m_reloadtime = 1000;
		m_selectGun.m_sound.Format(L"M416.wav");
		m_selectGun.m_bulletspeed = 880; // m/s
		m_selectGun.m_bullet = m_selectGun.m_load;
		break;
	case 1:	//M16A4
		m_selectGun.m_damage = 43;
		m_selectGun.m_y_recoil = 10;
		m_selectGun.m_x_recoil = 5;
		m_selectGun.m_speed = 75;
		m_selectGun.m_load = 30;
		m_selectGun.m_reloadtime = 1000;
		m_selectGun.m_sound.Format(L"M16A4.wav");
		m_selectGun.m_bulletspeed = 900; // m/s
		m_selectGun.m_bullet = m_selectGun.m_load;
		break;
	case 2:	//AKM
		m_selectGun.m_damage = 49;
		m_selectGun.m_y_recoil = 20;
		m_selectGun.m_x_recoil = 7;
		m_selectGun.m_speed = 100;
		m_selectGun.m_load = 30;
		m_selectGun.m_reloadtime = 1000;
		m_selectGun.m_sound.Format(L"AKM.wav");
		m_selectGun.m_bulletspeed = 715; // m/s
		m_selectGun.m_bullet = m_selectGun.m_load;
		break;
	
	case 3: //SCAR-L
		m_selectGun.m_damage = 43;
		m_selectGun.m_y_recoil = 10;
		m_selectGun.m_x_recoil = 7;
		m_selectGun.m_speed = 96;
		m_selectGun.m_load = 30;
		m_selectGun.m_reloadtime = 1000;
		m_selectGun.m_sound.Format(L"SCAR.wav");
		m_selectGun.m_bulletspeed = 870; // m/s
		m_selectGun.m_bullet = m_selectGun.m_load;
		break;
	case 4: //Groza
		m_selectGun.m_damage = 49;
		m_selectGun.m_y_recoil = 10;
		m_selectGun.m_x_recoil = 7;
		m_selectGun.m_speed = 80;
		m_selectGun.m_load = 30;
		m_selectGun.m_reloadtime = 1000;
		m_selectGun.m_sound.Format(L"Groza.wav");
		m_selectGun.m_bulletspeed = 715; // m/s
		m_selectGun.m_bullet = m_selectGun.m_load;
		break;
	case 5: //AUG
		m_selectGun.m_damage = 43;
		m_selectGun.m_y_recoil = 10;
		m_selectGun.m_x_recoil = 7;
		m_selectGun.m_speed = 85;
		m_selectGun.m_load = 30;
		m_selectGun.m_reloadtime = 1000;
		m_selectGun.m_sound.Format(L"M249.wav");	//������
		m_selectGun.m_bulletspeed = 940; // m/s
		m_selectGun.m_bullet = m_selectGun.m_load;
		break;
	case  6: //Mini14
		m_selectGun.m_damage = 46;
		m_selectGun.m_y_recoil = 20;
		m_selectGun.m_x_recoil = 7;
		m_selectGun.m_speed = 133;
		m_selectGun.m_load = 10;
		m_selectGun.m_reloadtime = 1000;
		m_selectGun.m_sound.Format(L"Mini14.wav");
		m_selectGun.m_bulletspeed = 990; // m/s
		m_selectGun.m_bullet = m_selectGun.m_load;
		break;
	}

	switch (m_parts)
	{
		case 0:	//�ޱ� ������
			m_selectParts.m_control_x_recoil = 1.15;
			m_selectParts.m_control_y_recoil = 1;
			m_selectParts.m_control_aiming = 1.15;
			m_selectParts.m_control_recoil_recovery = 1;
			break;
		case 1:	//���� ������
			m_selectParts.m_control_x_recoil = 1;
			m_selectParts.m_control_y_recoil = 1.15;
			m_selectParts.m_control_aiming = 1.15;
			m_selectParts.m_control_recoil_recovery = 1;
			break;
		case 2:	//���� ������
			m_selectParts.m_control_x_recoil = 1.08;
			m_selectParts.m_control_y_recoil = 1.08;
			m_selectParts.m_control_aiming = 1.15;
			m_selectParts.m_control_recoil_recovery = 1.1;
			break;
		case 3:	//���� ������
			m_selectParts.m_control_x_recoil = 1;
			m_selectParts.m_control_y_recoil = 1.05;
			m_selectParts.m_control_aiming = 1.3;
			m_selectParts.m_control_recoil_recovery = 1.15;
			break;
	}
	switch (m_muzzlepart)
	{
		case 0:	//������
			m_seleteMuzzleParts.m_control_x_recoil = 1.1;
			m_seleteMuzzleParts.m_control_y_recoil = 1.15;
			m_seleteMuzzleParts.m_control_aiming = 1.0;
			m_seleteMuzzleParts.m_control_recoil_recovery = 1.0;
			break;
		case 1:	//�ҿ���
			m_seleteMuzzleParts.m_control_x_recoil = 1.1;
			m_seleteMuzzleParts.m_control_y_recoil = 1.1;
			m_seleteMuzzleParts.m_control_aiming = 1.0;
			m_seleteMuzzleParts.m_control_recoil_recovery = 1.0;
			break;
		case 2:	//������
			m_seleteMuzzleParts.m_control_x_recoil = 1.05;
			m_seleteMuzzleParts.m_control_y_recoil = 1.05;
			m_seleteMuzzleParts.m_control_aiming = 1.0;
			m_seleteMuzzleParts.m_control_recoil_recovery = 1.0;
			//�߻��� ����  + 
			break;
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CSettingDlg::OnOK();
	
}
