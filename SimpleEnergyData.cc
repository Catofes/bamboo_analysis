#include "SimpleEnergyData.hh"

SimpleEnergyData::SimpleEnergyData() :
  runId(0), eventId(0), energy(0), t0(-1), parent(""), primaryX(0), primaryY(0), primaryZ(0)
{
}


int SimpleEnergyData::getRunId() const
{
  return runId;
}

void SimpleEnergyData::setRunId(int i)
{
  runId = i;
}

int SimpleEnergyData::getEventId() const
{
  return eventId;
}

void SimpleEnergyData::setEventId(int i)
{
  eventId = i;
}

double SimpleEnergyData::getEnergy () const
{
  return energy;
}

void SimpleEnergyData::setEnergy(double e)
{
  energy = e;
}

double SimpleEnergyData::getT0() const
{
  return t0;
}

void SimpleEnergyData::setT0(double t)
{
  t0 = t;
}

const string & SimpleEnergyData::getParent() const
{
  return parent;
}

void SimpleEnergyData::setParent(const string & s)
{
  parent = s;
}

double SimpleEnergyData::getPrimaryX() const
{
  return primaryX;
}

void SimpleEnergyData::setPrimaryX(double x)
{
  primaryX = x;
}

double SimpleEnergyData::getPrimaryY() const
{
  return primaryY;
}

void SimpleEnergyData::setPrimaryY(double y)
{
  primaryY = y;
}

double SimpleEnergyData::getPrimaryZ() const
{
  return primaryZ;
}

void SimpleEnergyData::setPrimaryZ(double z)
{
  primaryZ = z;
}

void SimpleEnergyData::mergeData(const SimpleEnergyData & data)
{
  if (runId != data.runId)
    return;
  if (eventId != data.eventId)
    return;
  energy += data.energy;
  parent += " ";
  parent += data.parent;
}
