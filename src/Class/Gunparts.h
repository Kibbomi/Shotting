#pragma once
class Gunparts
{
public:
	Gunparts();
	~Gunparts();
	Gunparts(float x_recoil, float y_recoil, float aiming, float recovery)
	{
		m_control_x_recoil = x_recoil;
		m_control_y_recoil = y_recoil;
		m_control_aiming = aiming;
		m_control_recoil_recovery = recovery;
	}

public:
	float m_control_x_recoil;	//���� �ݵ� ����
	float m_control_y_recoil;	//���� �ݵ� ����
	float m_control_aiming;	//������ �ð� ������
	float m_control_recoil_recovery;	//�ݵ�ȸ��
};

