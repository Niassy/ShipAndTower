

#ifndef _DETECTOR_
//------------------------------------------------------------
// author : Mamadou Niassy
// name : Detector.h
//
// this class is very useful for detect target on the game
// many type of detection exists. Use the appropriate to sense
// your target
//-------------------------------------------------

#define _DETECTOR_

class GamePlay;
class BaseEntity;

enum type_detection
{

	type_all = 0,			// all traget on the game are detected
	type_directional,	// all target on the range of the given direction are detected
	type_radius,		// radius range for detection
	type_tiled			// tile coordinate are used for detection
};


class Detector
{

protected:

protected:

	// the type of sensory memory detection
	unsigned int m_iTypeSensor;

	// the type of range 
	unsigned int m_iTypeRange;

	// the owner of the detector
	BaseEntity* m_pOwner;

	// minimun distance foe detecting target on a direction
	double m_dMinDetection;

	// the difference beetween center for beginning detection
	double m_dMinCenter;

	// the diiference beetween center for determining if two
	// entities are on the same tile
	double m_dMinCenterTile;

public:

	//-------ctor------
	Detector(int type);

	Detector(BaseEntity* owner, int typeRange, int typeSensor);

	// this method is used for detecting potentials
	// target
	virtual void Detect(GamePlay * game, BaseEntity* target, int rangeWeapon);

	// void setMinDectection
	void setMinDetection(double min){ m_dMinDetection = min; }

};


// this detector is only for ship
class Detector_Ship : public Detector
{

public:

	Detector_Ship(BaseEntity* owner);

	// this method is used for detecting potentials
	// target
	virtual void Detect(GamePlay * game, BaseEntity* target, int rangeWeapon);

};

// this detector is only for ship
class Detector_Tower : public Detector
{

public:

	Detector_Tower(BaseEntity* owner);

	// this method is used for detecting potentials
	// target
	virtual void Detect(GamePlay * game, BaseEntity* target, int rangeWeapon);

};


#endif

