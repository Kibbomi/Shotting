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
	float m_control_x_recoil;	//수평 반동 억제
	float m_control_y_recoil;	//수직 반동 억제
	float m_control_aiming;	//정조준 시간 감소율
	float m_control_recoil_recovery;	//반동회복
};

