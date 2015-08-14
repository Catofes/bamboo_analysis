#ifndef ENERGY_DEPOSITION_H
#define ENERGY_DEPOSITION_H

#include <TString.h>
#include <string>

using std::string;

class EnergyDeposition {
public:
  EnergyDeposition ();
  ~EnergyDeposition ();
  
  TString & getTypeString();
  void setTypeString(TString &t);
  void setTypeString(const char * t);
  void setTypeString(const string &t);

  TString & getParentType();
  void setParentType(TString & pt);
  void setParentType(const char * pt);
  void setParentType(const string & pt);

  TString & getCreateProcess();
  void setCreateProcess(TString &cp);
  void setCreateProcess(const char * cp);
  void setCreateProcess(const string & cp);

  TString & getEnergyDepositionProcess ();
  void setEnergyDepositionProcess (TString &edp);
  void setEnergyDepositionProcess (const char * edp);
  void setEnergyDepositionProcess (const string & edp);

  TString & getVolume();
  void setVolume(TString &v);
  void setVolume(const char * v);
  void setVolume(const string & v);

  Int_t getType();
  void setType(Int_t t);

  Double_t getX();
  Double_t getY();
  Double_t getZ();

  void setX(Double_t x);
  void setY(Double_t y);
  void setZ(Double_t z);
  void setXYZ(Double_t x, Double_t y, Double_t z);

  Double_t getEnergy();
  void setEnergy(Double_t e);

  Double_t getEnergyNr();
  void setEnergyNr(Double_t e);

  Double_t getEnergyEr();
  void setEnergyEr(Double_t e);

  Double_t getTime() const;
  void setTime(Double_t t);

  Int_t getNNrSteps() const;
  void setNNrSteps(Int_t n);

  Int_t getNErSteps() const;
  void setNErSteps(Int_t n);

  Int_t getNSteps() const;
  
  void merge (EnergyDeposition & ed);

private:

  TString _typeString;
  TString _parentType;
  TString _createProcess;
  TString _energyDepositionProcess;
  TString _volume;

  Int_t _type;
  Double_t _x;
  Double_t _y;
  Double_t _z;
  Double_t _energy;
  Double_t _energyNr;
  Double_t _energyEr;
  Double_t _time;
  
  Int_t _nNrSteps;
  Int_t _nErSteps;
};

#endif
