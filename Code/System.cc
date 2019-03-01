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



Test::Test(const dzn::locator& dzn_locator)
: dzn_meta{"","Test",0,0,{& reflectionSensor.meta,& output.meta,& belt.meta},{},{[this]{port.check_bindings();},[this]{reflectionSensor.check_bindings();},[this]{output.check_bindings();},[this]{belt.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::iControl::State::Off)

, port({{"port",this,&dzn_meta},{"",0,0}})

, reflectionSensor({{"",0,0},{"reflectionSensor",this,&dzn_meta}})
, output({{"",0,0},{"output",this,&dzn_meta}})
, belt({{"",0,0},{"belt",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
  port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};
  reflectionSensor.out.measures = [&](int value){return dzn::call_out(this,[=]{ return reflectionSensor_measures(value);}, this->reflectionSensor.meta, "measures");};
  belt.out.error = [&](){return dzn::call_out(this,[=]{ return belt_error();}, this->belt.meta, "error");};





}

void Test::port_turnOn()
{
  if ((state == ::iControl::State::On && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((state == ::iControl::State::Off && true)) 
  {
    state = ::iControl::State::On;
    this->reflectionSensor.in.turnOn();
    this->reflectionSensor.in.calibrate();
    this->output.in.turnOn();
    this->belt.in.turnOn();
  }
  else if ((!((state == ::iControl::State::Off && true)) && (!((state == ::iControl::State::On && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Test::port_turnOff()
{
  if ((state == ::iControl::State::On && true)) 
  {
    state = ::iControl::State::Off;
    this->belt.in.turnOff();
    this->reflectionSensor.in.turnOff();
    this->output.in.turnOff();
  }
  else if ((state == ::iControl::State::Off && true)) ;
  else if ((!((state == ::iControl::State::Off && true)) && (!((state == ::iControl::State::On && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Test::reflectionSensor_measures(int value)
{
  if ((state == ::iControl::State::On && true)) 
  {
    this->output.in.output(value);
  }
  else if ((!((state == ::iControl::State::On && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Test::belt_error()
{
  if ((state == ::iControl::State::On && true)) 
  {
    state = ::iControl::State::Off;
    this->belt.in.turnOff();
    this->reflectionSensor.in.turnOff();
    this->output.in.turnOff();
    this->port.out.error();
  }
  else if ((state == ::iControl::State::Off && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((state == ::iControl::State::Off && true)) && (!((state == ::iControl::State::On && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void Test::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Test::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

System::System(const dzn::locator& dzn_locator)
: dzn_meta{"","System",0,0,{},{& test.dzn_meta,& belt.dzn_meta,& sensor.dzn_meta,& display.dzn_meta},{[this]{port.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, test(dzn_locator)
, belt(dzn_locator)
, sensor(dzn_locator)
, display(dzn_locator)

, port(test.port)

{


  test.dzn_meta.parent = &dzn_meta;
  test.dzn_meta.name = "test";
  belt.dzn_meta.parent = &dzn_meta;
  belt.dzn_meta.name = "belt";
  sensor.dzn_meta.parent = &dzn_meta;
  sensor.dzn_meta.name = "sensor";
  display.dzn_meta.parent = &dzn_meta;
  display.dzn_meta.name = "display";


  connect(belt.port, test.belt);
  connect(sensor.port, test.reflectionSensor);
  connect(display.port, test.output);

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