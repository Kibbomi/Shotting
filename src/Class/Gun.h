#pragma once
class Gun
{
	public:
		Gun(unsigned int damage, unsigned int x_recoil, unsigned int y_recoil, int speed, 
			unsigned int load, unsigned int reloadtime, CString sound, int bulletspeed)
		{
			m_damage = damage;
			m_x_recoil = x_recoil;
			m_y_recoil = y_recoil;
			m_speed = speed;
			m_load = load;
			m_reloadtime = reloadtime;
			m_sound = sound;
			m_bulletspeed = bulletspeed;
			m_bullet = load;
		};
		Gun();
		~Gun();


	public:
		unsigned int m_damage;	//데미지
		unsigned int m_x_recoil;	//x축 반동
		unsigned int m_y_recoil;	//y축 반동
		int m_speed;	//연사
		unsigned int m_load;	//탄창
		unsigned int m_reloadtime;	//재장전 시간
		CString m_sound;	//총 사운드
		int m_bulletspeed;	//탄속
		int m_bullet;	//현재 탄창

};

