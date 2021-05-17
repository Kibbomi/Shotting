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
		unsigned int m_damage;	//������
		unsigned int m_x_recoil;	//x�� �ݵ�
		unsigned int m_y_recoil;	//y�� �ݵ�
		int m_speed;	//����
		unsigned int m_load;	//źâ
		unsigned int m_reloadtime;	//������ �ð�
		CString m_sound;	//�� ����
		int m_bulletspeed;	//ź��
		int m_bullet;	//���� źâ

};

