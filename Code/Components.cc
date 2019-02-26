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
#include "Components.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>


ReflectionControl::ReflectionControl(const dzn::locator& dzn_locator)
: dzn_meta{"","ReflectionControl",0,0,{& light.meta,& sensor.meta},{},{[this]{port.check_bindings();},[this]{light.check_bindings();},[this]{sensor.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::ReflectionControl::State::Off)

, port({{"port",this,&dzn_meta},{"",0,0}})

, light({{"",0,0},{"light",this,&dzn_meta}})
, sensor({{"",0,0},{"sensor",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
  port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};
  port.in.calibrate = [&](){return dzn::call_in(this,[=]{ return port_calibrate();}, this->port.meta, "calibrate");};
  sensor.out.measures = [&](){return dzn::call_out(this,[=]{ return sensor_measures();}, this->sensor.meta, "measures");};





}

void ReflectionControl::port_turnOn()
{
  if ((state == ::ReflectionControl::State::Off && true)) 
  {
    state = ::ReflectionControl::State::On;
    this->light.in.turnOn();
    this->sensor.in.turnOn();
  }
  else if ((state == ::ReflectionControl::State::On && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((state == ::ReflectionControl::State::On && true)) && (!((state == ::ReflectionControl::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void ReflectionControl::port_turnOff()
{
  if ((state == ::ReflectionControl::State::Off && true)) ;
  else if ((state == ::ReflectionControl::State::On && true)) 
  {
    state = ::ReflectionControl::State::Off;
    this->light.in.turnOff();
    this->sensor.in.turnOff();
  }
  else if ((!((state == ::ReflectionControl::State::On && true)) && (!((state == ::ReflectionControl::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void ReflectionControl::port_calibrate()
{
  if ((state == ::ReflectionControl::State::Off && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((state == ::ReflectionControl::State::On && true)) this->sensor.in.calibrate();
  else if ((!((state == ::ReflectionControl::State::On && true)) && (!((state == ::ReflectionControl::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void ReflectionControl::sensor_measures()
{
  if (true) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void ReflectionControl::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void ReflectionControl::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

ReflectionSensor::ReflectionSensor(const dzn::locator& dzn_locator)
: dzn_meta{"","ReflectionSensor",0,0,{},{& control.dzn_meta,& sensor.dzn_meta,& light.dzn_meta},{[this]{port.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, control(dzn_locator)
, sensor(dzn_locator)
, light(dzn_locator)

, port(control.port)

{


  control.dzn_meta.parent = &dzn_meta;
  control.dzn_meta.name = "control";
  sensor.dzn_meta.parent = &dzn_meta;
  sensor.dzn_meta.name = "sensor";
  light.dzn_meta.parent = &dzn_meta;
  light.dzn_meta.name = "light";


  connect(sensor.port, control.sensor);
  connect(light.port, control.light);

  dzn::rank(port.meta.provides.meta, 0);

}

void ReflectionSensor::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void ReflectionSensor::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////



//version: 2.8.2
