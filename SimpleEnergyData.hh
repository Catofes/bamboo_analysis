#ifndef SIMPLEENERGYDATA_H
#define SIMPLEENERGYDATA_H

#include <string>

using std::string;

class SimpleEnergyData {
public:

  SimpleEnergyData();
  ~SimpleEnergyData() {}

  int getRunId() const;
  void setRunId(int i);

  int getEventId() const;
  void setEventId(int i);

  double getEnergy() const;
  void setEnergy(double e);

  double getT0() const;
  void setT0(double t);
  
  const string & getParent() const;
  void setParent(const string &);

  double getPrimaryX() const;
  void setPrimaryX(double x);

  double getPrimaryY() const;
  void setPrimaryY(double y);

  double getPrimaryZ() const;
  void setPrimaryZ(double z);

  void mergeData(const SimpleEnergyData & data);
private:
  int runId;
  int eventId;
  double energy;
  double t0;
  string parent;
  double primaryX;
  double primaryY;
  double primaryZ;
};

#endif
