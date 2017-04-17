#include "Timer.h"

//#include "mmsystem.h"


#include "utils.h"

#include "cocos2d.h"

USING_NS_CC;



class Regulator /*: public CCNode*/
{
private:

	//the time period between updates 
	double m_dUpdatePeriod;

	//the next time the regulator allows code flow
	float m_dwNextUpdateTime;


public:


	Regulator(double NumUpdatesPerSecondRqd)
	{
		//this->scheduleUpdate();
		m_dwNextUpdateTime = /*(DWORD)(timeGetTime()+RandFloat()*1000)*/ (float)(Clock->getCurrentTime()); /*+ RandFloat() * 1000);*/
		
		if (NumUpdatesPerSecondRqd > 0)
		{
			m_dUpdatePeriod =( 1000.0 / NumUpdatesPerSecondRqd) /1000;
		}

		//else if (isEqual(0.0, NumUpdatesPerSecondRqd))
		//{
			//m_dUpdatePeriod = 0.0;
		//}

		else if (NumUpdatesPerSecondRqd < 0)
		{
			m_dUpdatePeriod = -1;
		}
	}


	//returns true if the current time exceeds m_dwNextUpdateTime
	bool isReady()
	{
	
		
		//if a regulator is instantiated with a zero freq then it goes into
		//stealth mode (doesn't regulate)
		//if (isEqual(0.0, m_dUpdatePeriod)) return true;

		//if the regulator is instantiated with a negative freq then it will
		//never allow the code to flow
		if (m_dUpdatePeriod < 0) return false;


		float CurrentTime = /*timeGetTime()*/  (float)Clock->getCurrentTime();

		//the number of milliseconds the update period can vary per required
		//update-step. This is here to make sure any multiple clients of this class
		//have their updates spread evenly
		static const double UpdatePeriodVariator = 10.0;

		//m_dwNextUpdateTime = 10;

		if (CurrentTime >=m_dwNextUpdateTime  )
		{
			m_dwNextUpdateTime = (float)(CurrentTime + m_dUpdatePeriod /*+ RandInRange(-UpdatePeriodVariator, UpdatePeriodVariator)*/);

			return true;
		}
		
		return false;
	}
};
