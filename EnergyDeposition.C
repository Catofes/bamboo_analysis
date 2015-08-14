#include "EnergyDeposition.h"

EnergyDeposition::EnergyDeposition()
{
  _energy = 0;
  _energyNr = 0;
  _energyEr = 0;
  _nNrSteps = 0;
  _nErSteps = 0;
}

EnergyDeposition::~EnergyDeposition()
{
}

TString & EnergyDeposition::getTypeString ()
{
  return _typeString;
}


void EnergyDeposition::setTypeString(TString & t)
{
  _typeString = t;
}

void EnergyDeposition::setTypeString(const char * t)
{
  _typeString = t;
}

void EnergyDeposition::setTypeString(const string &t)
{
  _typeString = t;
}

TString & EnergyDeposition::getParentType ()
{
  return _parentType;
}

void EnergyDeposition::setParentType (TString & pt)
{
  _parentType = pt;
}

void EnergyDeposition::setParentType (const char *pt)
{
  _parentType = pt;
}

void EnergyDeposition::setParentType (const string &pt)
{
  _parentType = pt;
}

TString & EnergyDeposition::getCreateProcess ()
{
  return _createProcess;
}

void EnergyDeposition::setCreateProcess(TString & cp)
{
  _createProcess = cp;
}

void EnergyDeposition::setCreateProcess(const char *cp)
{
  _createProcess = cp;
}

void EnergyDeposition::setCreateProcess(const string & cp)
{
  _createProcess = cp;
}

TString & EnergyDeposition::getEnergyDepositionProcess()
{
  return _energyDepositionProcess;
}

void EnergyDeposition::setEnergyDepositionProcess(TString &ed)
{
  _energyDepositionProcess = ed;
}

void EnergyDeposition::setEnergyDepositionProcess(const char * ed)
{
  _energyDepositionProcess = ed;
}

void EnergyDeposition::setEnergyDepositionProcess(const string & ed)
{
  _energyDepositionProcess = ed;
}

TString & EnergyDeposition::getVolume ()
{
  return _volume;
}

void EnergyDeposition::setVolume(TString & v)
{
  _volume = v;
}

void EnergyDeposition::setVolume(const char * v)
{
  _volume = v;
}

void EnergyDeposition::setVolume(const string & v)
{
  _volume = v;
}

Int_t EnergyDeposition::getType()
{
  return _type;
}

void EnergyDeposition::setType(Int_t t)
{
  _type = t;
}

Double_t EnergyDeposition::getX()
{
  return _x;
}

Double_t EnergyDeposition::getY()
{
  return _y;
}

Double_t EnergyDeposition::getZ()
{
  return _z;
}

void EnergyDeposition::setX(Double_t x)
{
  _x = x;
}

void EnergyDeposition::setY(Double_t y)
{
  _y = y;
}

void EnergyDeposition::setZ(Double_t z)
{
  _z = z;
}

void EnergyDeposition::setXYZ (Double_t x, Double_t y, Double_t z)
{
  _x = x;
  _y = y;
  _z = z;
}

Double_t EnergyDeposition::getEnergy()
{
  return _energy;
}

Double_t EnergyDeposition::getEnergyNr()
{
  return _energyNr;
}

Double_t EnergyDeposition::getEnergyEr()
{
  return _energyEr;
}

void EnergyDeposition::setEnergy(Double_t e)
{
  _energy = e;
}

void EnergyDeposition::setEnergyNr(Double_t e)
{
  _energyNr = e;
  _energy += e;
}

void EnergyDeposition::setEnergyEr(Double_t e)
{
  _energyEr = e;
  _energy += e;
}

Double_t EnergyDeposition::getTime () const
{
  return _time;
}

void EnergyDeposition::setTime(Double_t t)
{
  _time = t;
}

Int_t EnergyDeposition::getNNrSteps() const
{
  return _nNrSteps;
}

void EnergyDeposition::setNNrSteps(Int_t n)
{
  _nNrSteps = n;
}

Int_t EnergyDeposition::getNErSteps() const
{
  return _nErSteps;
}

void EnergyDeposition::setNErSteps(Int_t n)
{
  _nErSteps = n;
}

Int_t EnergyDeposition::getNSteps() const
{
  return _nErSteps + _nNrSteps;
}

void EnergyDeposition::merge (EnergyDeposition & ed)
{
  _typeString.Append(" ").Append(ed._typeString);
  _parentType.Append(" ").Append(ed._parentType);
  _createProcess.Append(" ").Append(ed._createProcess);
  _energyDepositionProcess.Append(" ").Append(ed._energyDepositionProcess);
  _volume.Append(" ").Append(ed._volume);

  if (_type != ed._type) {
    _type = 3;
  }

  Double_t energy = _energy + ed._energy;
  Double_t energyNr = _energyNr + ed._energyNr;
  Double_t energyEr = _energyEr + ed._energyEr;
  Double_t fracA = _energy/energy;
  Double_t fracB = ed._energy/energy;
  _x = _x*fracA + ed._x*fracB;
  _y = _y*fracA + ed._y*fracB;
  _z = _z*fracA + ed._z*fracB;
  _energy = energy;
  _energyEr = energyEr;
  _energyNr = energyNr;
  _time = _time<ed._time?_time:ed._time;
  _nErSteps += ed._nErSteps;
  _nNrSteps += ed._nNrSteps;
}
