#pragma once
class Statisticsgun
{
	public:
	
		Statisticsgun(int damage, float hitrate, int hit , int headshot,float headshotrate,int shoot)
		{
			m_damage = damage;
			m_hitrate = hitrate;
			m_hit = hit;
			m_headshot = headshot;
			m_headshotrate = headshotrate;
			m_shoot = shoot;
		};
		Statisticsgun();
		~Statisticsgun();

	public:
		int m_damage;
		float m_hitrate;
		int m_hit;
		int m_headshot;
		float m_headshotrate;
		int m_shoot;
};

