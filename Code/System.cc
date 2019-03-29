// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "System.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



SortingApplication::SortingApplication(const dzn::locator& dzn_locator)
: dzn_meta{"","SortingApplication",0,0,{& sensor.meta,& belt.meta,& pushers.meta,& sequence.meta,& rebootTimer.meta},{},{[this]{comms.check_bindings();},[this]{sensor.check_bindings();},[this]{belt.check_bindings();},[this]{pushers.check_bindings();},[this]{sequence.check_bindings();},[this]{rebootTimer.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, beltState(::iConveyerBelt::State::On), mode(::SortingApplication::OperationMode::Sort), box1Time(), box2Time(), box3Time(), box4Time(), rebootTime()

, comms({{"comms",this,&dzn_meta},{"",0,0}})

, sensor({{"",0,0},{"sensor",this,&dzn_meta}})
, belt({{"",0,0},{"belt",this,&dzn_meta}})
, pushers({{"",0,0},{"pushers",this,&dzn_meta}})
, sequence({{"",0,0},{"sequence",this,&dzn_meta}})
, rebootTimer({{"",0,0},{"rebootTimer",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  comms.in.takeItem = [&](){return dzn::call_in(this,[=]{ return comms_takeItem();}, this->comms.meta, "takeItem");};
  comms.in.startSequence = [&](){return dzn::call_in(this,[=]{ return comms_startSequence();}, this->comms.meta, "startSequence");};
  comms.in.reboot = [&](){return dzn::call_in(this,[=]{ return comms_reboot();}, this->comms.meta, "reboot");};
  sensor.out.measuresBlack = [&](){return dzn::call_out(this,[=]{ return sensor_measuresBlack();}, this->sensor.meta, "measuresBlack");};
  sensor.out.measuresWhite = [&](){return dzn::call_out(this,[=]{ return sensor_measuresWhite();}, this->sensor.meta, "measuresWhite");};
  sensor.out.measuresError = [&](){return dzn::call_out(this,[=]{ return sensor_measuresError();}, this->sensor.meta, "measuresError");};
  sequence.out.readSequence = [&](){return dzn::call_out(this,[=]{ return sequence_readSequence();}, this->sequence.meta, "readSequence");};
  sequence.out.timeout = [&](){return dzn::call_out(this,[=]{ return sequence_timeout();}, this->sequence.meta, "timeout");};
  rebootTimer.out.timeout = [&](){return dzn::call_out(this,[=]{ return rebootTimer_timeout();}, this->rebootTimer.meta, "timeout");};





}

void SortingApplication::comms_takeItem()
{
  if (((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && true)) 
  {
    setSystemOperating(true);
  }
  else if ((mode == ::SortingApplication::OperationMode::SequenceReading && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((mode == ::SortingApplication::OperationMode::SequenceReading && true)) && (!(((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::comms_startSequence()
{
  if (((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && true)) 
  {
    mode = ::SortingApplication::OperationMode::SequenceReading;
    this->sequence.in.startSequence();
    setSystemOperating(true);
  }
  else if ((mode == ::SortingApplication::OperationMode::SequenceReading && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((mode == ::SortingApplication::OperationMode::SequenceReading && true)) && (!(((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::comms_reboot()
{
  if ((!(mode == ::SortingApplication::OperationMode::Rebooting) && true)) 
  {
    this->belt.in.turnOn();
    beltState = ::iConveyerBelt::State::On;
    mode = ::SortingApplication::OperationMode::Rebooting;
    this->sensor.in.turnOff();
    this->sequence.in.cancelSequence();
    this->pushers.in.cancelAll();
    this->rebootTimer.in.createTimer(rebootTime);
  }
  else if ((mode == ::SortingApplication::OperationMode::Rebooting && true)) 
  {
    this->rebootTimer.in.cancelTimer();
    this->rebootTimer.in.createTimer(rebootTime);
  }
  else if ((!((mode == ::SortingApplication::OperationMode::Rebooting && true)) && (!((!(mode == ::SortingApplication::OperationMode::Rebooting) && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::sensor_measuresBlack()
{
  if (((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && (beltState == ::iConveyerBelt::State::On && true))) ;
  else if ((mode == ::SortingApplication::OperationMode::SequenceReading && true)) this->sequence.in.appendBlack();
  else if ((!((mode == ::SortingApplication::OperationMode::SequenceReading && true)) && (!(((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && (beltState == ::iConveyerBelt::State::On && true))) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::sensor_measuresWhite()
{
  if (((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && (beltState == ::iConveyerBelt::State::On && true))) ;
  else if ((mode == ::SortingApplication::OperationMode::SequenceReading && true)) this->sequence.in.appendWhite();
  else if ((!((mode == ::SortingApplication::OperationMode::SequenceReading && true)) && (!(((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && (beltState == ::iConveyerBelt::State::On && true))) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::sensor_measuresError()
{
  if (((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && (beltState == ::iConveyerBelt::State::On && true))) 
  {
    this->pushers.in.enqueueBox4(box4Time);
  }
  else if ((mode == ::SortingApplication::OperationMode::SequenceReading && true)) 
  {
    this->pushers.in.enqueueBox4(box4Time);
  }
  else if ((!((mode == ::SortingApplication::OperationMode::SequenceReading && true)) && (!(((!(mode == ::SortingApplication::OperationMode::SequenceReading) && !(mode == ::SortingApplication::OperationMode::Rebooting)) && (beltState == ::iConveyerBelt::State::On && true))) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::sequence_readSequence()
{
  if ((mode == ::SortingApplication::OperationMode::SequenceReading && true)) 
  {
    setSystemOperating(false);
    this->comms.out.sequenceReceived();
    this->comms.out.available();
    mode = ::SortingApplication::OperationMode::Sort;
  }
  else if ((!((mode == ::SortingApplication::OperationMode::SequenceReading && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::sequence_timeout()
{
  if ((mode == ::SortingApplication::OperationMode::SequenceReading && true)) 
  {
    setSystemOperating(false);
    this->comms.out.sequenceReceived();
    this->comms.out.available();
    mode = ::SortingApplication::OperationMode::Sort;
  }
  else if ((!((mode == ::SortingApplication::OperationMode::SequenceReading && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingApplication::rebootTimer_timeout()
{
  if ((mode == ::SortingApplication::OperationMode::Rebooting && true)) 
  {
    this->belt.in.turnOff();
    beltState = ::iConveyerBelt::State::Off;
    mode = ::SortingApplication::OperationMode::Sort;
    this->comms.out.available();
  }
  else if ((!((mode == ::SortingApplication::OperationMode::Rebooting && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}

void SortingApplication::setSystemOperating (bool operational) 
{
  {
    if (operational) 
    {
      this->belt.in.turnOn();
      beltState = ::iConveyerBelt::State::On;
      this->sensor.in.turnOn();
      this->sensor.in.calibrate();
    }
    else 
    {
      this->belt.in.turnOff();
      beltState = ::iConveyerBelt::State::Off;
      this->sensor.in.turnOff();
    }
  }
  return ;
}

void SortingApplication::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void SortingApplication::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

System::System(const dzn::locator& dzn_locator)
: dzn_meta{"","System",0,0,{},{& app.dzn_meta,& belt.dzn_meta,& sensor.dzn_meta,& pusherSystem.dzn_meta,& sequence.dzn_meta,& timer.dzn_meta,& rebootTimer.dzn_meta},{[this]{port.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, app(dzn_locator)
, belt(dzn_locator)
, sensor(dzn_locator)
, pusherSystem(dzn_locator)
, sequence(dzn_locator)
, timer(dzn_locator)
, rebootTimer(dzn_locator)

, port(app.comms)

{


  app.dzn_meta.parent = &dzn_meta;
  app.dzn_meta.name = "app";
  belt.dzn_meta.parent = &dzn_meta;
  belt.dzn_meta.name = "belt";
  sensor.dzn_meta.parent = &dzn_meta;
  sensor.dzn_meta.name = "sensor";
  pusherSystem.dzn_meta.parent = &dzn_meta;
  pusherSystem.dzn_meta.name = "pusherSystem";
  sequence.dzn_meta.parent = &dzn_meta;
  sequence.dzn_meta.name = "sequence";
  timer.dzn_meta.parent = &dzn_meta;
  timer.dzn_meta.name = "timer";
  rebootTimer.dzn_meta.parent = &dzn_meta;
  rebootTimer.dzn_meta.name = "rebootTimer";


  connect(rebootTimer.port, app.rebootTimer);
  connect(sequence.port, app.sequence);
  connect(timer.port, sequence.timer);
  connect(belt.port, app.belt);
  connect(sensor.port, app.sensor);
  connect(pusherSystem.port, app.pushers);

  dzn::rank(port.meta.provides.meta, 0);

}

void System::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void System::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////



//version: 2.8.2