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



Pusher::Pusher(const dzn::locator& dzn_locator)
: dzn_meta{"","Pusher",0,0,{& motor.meta,& timer.meta},{},{[this]{port.check_bindings();},[this]{motor.check_bindings();},[this]{timer.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, motorState(::iMotor::State::Off), state(::iPusher::State::Up), time()

, port({{"port",this,&dzn_meta},{"",0,0}})

, motor({{"",0,0},{"motor",this,&dzn_meta}})
, timer({{"",0,0},{"timer",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  port.in.down = [&](){return dzn::call_in(this,[=]{ return port_down();}, this->port.meta, "down");};
  port.in.up = [&](){return dzn::call_in(this,[=]{ return port_up();}, this->port.meta, "up");};
  timer.out.timeout = [&](){return dzn::call_out(this,[=]{ return timer_timeout();}, this->timer.meta, "timeout");};


  port.in.isMoving = [&](){return dzn::call_in(this,[=]{ return port_isMoving();}, this->port.meta, "isMoving");};



}

void Pusher::port_down()
{
  if ((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Off && true))) 
  {
    this->motor.in.turnClockwise();
    motorState = ::iMotor::State::CounterClock;
    state = ::iPusher::State::Down;
    this->timer.in.createTimer(time);
  }
  else if ((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((state == ::iPusher::State::Down && (motorState == ::iMotor::State::Off && true))) 
  {
    this->port.out.stopped();
  }
  else if ((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) ;
  else if ((!((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) && (!((state == ::iPusher::State::Down && (motorState == ::iMotor::State::Off && true))) && (!((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) && (!((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Off && true))) && true))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Pusher::port_up()
{
  if ((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Off && true))) 
  {
    this->port.out.stopped();
  }
  else if ((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) ;
  else if ((state == ::iPusher::State::Down && (motorState == ::iMotor::State::Off && true))) 
  {
    this->motor.in.turnCounterClockwise();
    motorState = ::iMotor::State::Clock;
    state = ::iPusher::State::Up;
    this->timer.in.createTimer(time);
  }
  else if ((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) && (!((state == ::iPusher::State::Down && (motorState == ::iMotor::State::Off && true))) && (!((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) && (!((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Off && true))) && true))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
bool Pusher::port_isMoving()
{
  if ((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Off && true))) { this->reply_bool = false; }
  else if ((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) { this->reply_bool = true; }
  else if ((state == ::iPusher::State::Down && (motorState == ::iMotor::State::Off && true))) { this->reply_bool = false; }
  else if ((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) { this->reply_bool = true; }
  else if ((!((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) && (!((state == ::iPusher::State::Down && (motorState == ::iMotor::State::Off && true))) && (!((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) && (!((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Off && true))) && true))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return this->reply_bool;
}
void Pusher::timer_timeout()
{
  if ((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) 
  {
    this->port.out.stopped();
    motorState = ::iMotor::State::Off;
    this->motor.in.turnOff();
  }
  else if ((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) 
  {
    this->port.out.stopped();
    motorState = ::iMotor::State::Off;
    this->motor.in.turnOff();
  }
  else if ((!((state == ::iPusher::State::Down && (motorState == ::iMotor::State::CounterClock && true))) && (!((state == ::iPusher::State::Up && (motorState == ::iMotor::State::Clock && true))) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void Pusher::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Pusher::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}


BlackWhiteSensorControl::BlackWhiteSensorControl(const dzn::locator& dzn_locator)
: dzn_meta{"","BlackWhiteSensorControl",0,0,{& light.meta,& sensor.meta},{},{[this]{port.check_bindings();},[this]{light.check_bindings();},[this]{sensor.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::BlackWhiteSensorControl::State::Off)

, port({{"port",this,&dzn_meta},{"",0,0}})

, light({{"",0,0},{"light",this,&dzn_meta}})
, sensor({{"",0,0},{"sensor",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
  port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};
  port.in.calibrate = [&](){return dzn::call_in(this,[=]{ return port_calibrate();}, this->port.meta, "calibrate");};
  sensor.out.measures = [&](int value){return dzn::call_out(this,[=]{ return sensor_measures(value);}, this->sensor.meta, "measures");};





}

void BlackWhiteSensorControl::port_turnOn()
{
  if ((state == ::BlackWhiteSensorControl::State::Off && true)) 
  {
    state = ::BlackWhiteSensorControl::State::On;
    this->light.in.turnOn();
    this->sensor.in.turnOn();
  }
  else if ((state == ::BlackWhiteSensorControl::State::On && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((state == ::BlackWhiteSensorControl::State::On && true)) && (!((state == ::BlackWhiteSensorControl::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void BlackWhiteSensorControl::port_turnOff()
{
  if ((state == ::BlackWhiteSensorControl::State::Off && true)) ;
  else if ((state == ::BlackWhiteSensorControl::State::On && true)) 
  {
    state = ::BlackWhiteSensorControl::State::Off;
    this->light.in.turnOff();
    this->sensor.in.turnOff();
  }
  else if ((!((state == ::BlackWhiteSensorControl::State::On && true)) && (!((state == ::BlackWhiteSensorControl::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void BlackWhiteSensorControl::port_calibrate()
{
  if ((state == ::BlackWhiteSensorControl::State::Off && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((state == ::BlackWhiteSensorControl::State::On && true)) this->sensor.in.calibrate();
  else if ((!((state == ::BlackWhiteSensorControl::State::On && true)) && (!((state == ::BlackWhiteSensorControl::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void BlackWhiteSensorControl::sensor_measures(int value)
{
  if ((state == ::BlackWhiteSensorControl::State::On && true)) ;
  else if ((!((state == ::BlackWhiteSensorControl::State::On && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void BlackWhiteSensorControl::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void BlackWhiteSensorControl::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}


ConveyerBeltControl::ConveyerBeltControl(const dzn::locator& dzn_locator)
: dzn_meta{"","ConveyerBeltControl",0,0,{& motor.meta},{},{[this]{port.check_bindings();},[this]{motor.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, direction(::iConveyerBelt::Direction::Clockwise), state(::iConveyerBelt::State::Off)

, port({{"port",this,&dzn_meta},{"",0,0}})

, motor({{"",0,0},{"motor",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
  port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};
  port.in.setClockwise = [&](){return dzn::call_in(this,[=]{ return port_setClockwise();}, this->port.meta, "setClockwise");};
  port.in.setCounterClockwise = [&](){return dzn::call_in(this,[=]{ return port_setCounterClockwise();}, this->port.meta, "setCounterClockwise");};





}

void ConveyerBeltControl::port_turnOn()
{
  if ((state == ::iConveyerBelt::State::Off && (direction == ::iConveyerBelt::Direction::Clockwise && true))) 
  {
    state = ::iConveyerBelt::State::On;
    this->motor.in.turnClockwise();
  }
  else if ((state == ::iConveyerBelt::State::Off && (direction == ::iConveyerBelt::Direction::CounterClockwise && true))) 
  {
    state = ::iConveyerBelt::State::On;
    this->motor.in.turnCounterClockwise();
  }
  else if ((state == ::iConveyerBelt::State::On && true)) true;
  else if ((!((state == ::iConveyerBelt::State::On && true)) && (!((state == ::iConveyerBelt::State::Off && (direction == ::iConveyerBelt::Direction::CounterClockwise && true))) && (!((state == ::iConveyerBelt::State::Off && (direction == ::iConveyerBelt::Direction::Clockwise && true))) && true)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void ConveyerBeltControl::port_turnOff()
{
  if ((state == ::iConveyerBelt::State::Off && true)) ;
  else if ((state == ::iConveyerBelt::State::On && true)) 
  {
    this->motor.in.turnOff();
    state = ::iConveyerBelt::State::Off;
  }
  else if ((!((state == ::iConveyerBelt::State::On && true)) && (!((state == ::iConveyerBelt::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void ConveyerBeltControl::port_setClockwise()
{
  if ((state == ::iConveyerBelt::State::Off && true)) direction = ::iConveyerBelt::Direction::Clockwise;
  else if ((state == ::iConveyerBelt::State::On && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((state == ::iConveyerBelt::State::On && true)) && (!((state == ::iConveyerBelt::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void ConveyerBeltControl::port_setCounterClockwise()
{
  if ((state == ::iConveyerBelt::State::Off && true)) direction = ::iConveyerBelt::Direction::CounterClockwise;
  else if ((state == ::iConveyerBelt::State::On && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!((state == ::iConveyerBelt::State::On && true)) && (!((state == ::iConveyerBelt::State::Off && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void ConveyerBeltControl::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void ConveyerBeltControl::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}


PusherControl::PusherControl(const dzn::locator& dzn_locator)
: dzn_meta{"","PusherControl",0,0,{& push1.meta,& push2.meta,& push3.meta},{},{[this]{port.check_bindings();},[this]{push1.check_bindings();},[this]{push2.check_bindings();},[this]{push3.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, port({{"port",this,&dzn_meta},{"",0,0}})

, push1({{"",0,0},{"push1",this,&dzn_meta}})
, push2({{"",0,0},{"push2",this,&dzn_meta}})
, push3({{"",0,0},{"push3",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  port.in.cancelAll = [&](){return dzn::call_in(this,[=]{ return port_cancelAll();}, this->port.meta, "cancelAll");};
  port.in.enqueueBox1 = [&](double time){return dzn::call_in(this,[=]{ return port_enqueueBox1(time);}, this->port.meta, "enqueueBox1");};
  port.in.enqueueBox2 = [&](double time){return dzn::call_in(this,[=]{ return port_enqueueBox2(time);}, this->port.meta, "enqueueBox2");};
  port.in.enqueueBox3 = [&](double time){return dzn::call_in(this,[=]{ return port_enqueueBox3(time);}, this->port.meta, "enqueueBox3");};
  port.in.enqueueBox4 = [&](double time){return dzn::call_in(this,[=]{ return port_enqueueBox4(time);}, this->port.meta, "enqueueBox4");};
  push1.out.stopped = [&](){return dzn::call_out(this,[=]{ return push1_stopped();}, this->push1.meta, "stopped");};
  push2.out.stopped = [&](){return dzn::call_out(this,[=]{ return push2_stopped();}, this->push2.meta, "stopped");};
  push3.out.stopped = [&](){return dzn::call_out(this,[=]{ return push3_stopped();}, this->push3.meta, "stopped");};





}

void PusherControl::port_cancelAll()
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void PusherControl::port_enqueueBox1(double time)
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void PusherControl::port_enqueueBox2(double time)
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void PusherControl::port_enqueueBox3(double time)
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void PusherControl::port_enqueueBox4(double time)
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void PusherControl::push1_stopped()
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void PusherControl::push2_stopped()
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void PusherControl::push3_stopped()
{
  if (true) ;
  else if ((!(true) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void PusherControl::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void PusherControl::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}


SequenceBehaviour::SequenceBehaviour(const dzn::locator& dzn_locator)
: dzn_meta{"","SequenceBehaviour",0,0,{& timer.meta},{},{[this]{port.check_bindings();},[this]{timer.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, mode(::iSequenceInterpreter::Mode::Done), SEQ_LENGTH(8), current(0), time()

, port({{"port",this,&dzn_meta},{"",0,0}})

, timer({{"",0,0},{"timer",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  port.in.startSequence = [&](){return dzn::call_in(this,[=]{ return port_startSequence();}, this->port.meta, "startSequence");};
  port.in.appendWhite = [&](){return dzn::call_in(this,[=]{ return port_appendWhite();}, this->port.meta, "appendWhite");};
  port.in.appendBlack = [&](){return dzn::call_in(this,[=]{ return port_appendBlack();}, this->port.meta, "appendBlack");};
  port.in.cancelSequence = [&](){return dzn::call_in(this,[=]{ return port_cancelSequence();}, this->port.meta, "cancelSequence");};
  timer.out.timeout = [&](){return dzn::call_out(this,[=]{ return timer_timeout();}, this->timer.meta, "timeout");};





}

void SequenceBehaviour::port_startSequence()
{
  if ((mode == ::iSequenceInterpreter::Mode::Done && true)) 
  {
    mode = ::iSequenceInterpreter::Mode::Reading;
    current = 0;
    this->timer.in.createTimer(time);
  }
  else if ((!((mode == ::iSequenceInterpreter::Mode::Done && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SequenceBehaviour::port_appendWhite()
{
  if ((mode == ::iSequenceInterpreter::Mode::Reading && true)) 
  {
    current = current + 1;
    {
      if (current == 8) 
      {
        this->port.out.readSequence();
        mode = ::iSequenceInterpreter::Mode::Done;
        this->timer.in.cancelTimer();
      }
    }
  }
  else if ((!((mode == ::iSequenceInterpreter::Mode::Reading && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SequenceBehaviour::port_appendBlack()
{
  if ((mode == ::iSequenceInterpreter::Mode::Reading && true)) 
  {
    current = current + 1;
    {
      if (current == 8) 
      {
        this->port.out.readSequence();
        mode = ::iSequenceInterpreter::Mode::Done;
        this->timer.in.cancelTimer();
      }
    }
  }
  else if ((!((mode == ::iSequenceInterpreter::Mode::Reading && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SequenceBehaviour::port_cancelSequence()
{
  if ((mode == ::iSequenceInterpreter::Mode::Done && true)) ;
  else if ((mode == ::iSequenceInterpreter::Mode::Reading && true)) 
  {
    this->timer.in.cancelTimer();
    mode = ::iSequenceInterpreter::Mode::Done;
  }
  else if ((!((mode == ::iSequenceInterpreter::Mode::Reading && true)) && (!((mode == ::iSequenceInterpreter::Mode::Done && true)) && true))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SequenceBehaviour::timer_timeout()
{
  if ((mode == ::iSequenceInterpreter::Mode::Reading && true)) 
  {
    this->port.out.timeout();
    mode = ::iSequenceInterpreter::Mode::Done;
  }
  else if ((!((mode == ::iSequenceInterpreter::Mode::Reading && true)) && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void SequenceBehaviour::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void SequenceBehaviour::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

BlackWhiteSensor::BlackWhiteSensor(const dzn::locator& dzn_locator)
: dzn_meta{"","BlackWhiteSensor",0,0,{},{& control.dzn_meta,& sensor.dzn_meta,& light.dzn_meta},{[this]{port.check_bindings();}}}
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

void BlackWhiteSensor::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void BlackWhiteSensor::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////
//SYSTEM

ConveyerBelt::ConveyerBelt(const dzn::locator& dzn_locator)
: dzn_meta{"","ConveyerBelt",0,0,{},{& control.dzn_meta,& motor.dzn_meta},{[this]{port.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, control(dzn_locator)
, motor(dzn_locator)

, port(control.port)

{


  control.dzn_meta.parent = &dzn_meta;
  control.dzn_meta.name = "control";
  motor.dzn_meta.parent = &dzn_meta;
  motor.dzn_meta.name = "motor";


  connect(motor.port, control.motor);

  dzn::rank(port.meta.provides.meta, 0);

}

void ConveyerBelt::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void ConveyerBelt::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////
//SYSTEM

PusherSystem::PusherSystem(const dzn::locator& dzn_locator)
: dzn_meta{"","PusherSystem",0,0,{},{& control.dzn_meta,& p1.dzn_meta,& t1.dzn_meta,& m1.dzn_meta,& p2.dzn_meta,& t2.dzn_meta,& m2.dzn_meta,& p3.dzn_meta,& t3.dzn_meta,& m3.dzn_meta},{[this]{port.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, control(dzn_locator)
, p1(dzn_locator)
, t1(dzn_locator)
, m1(dzn_locator)
, p2(dzn_locator)
, t2(dzn_locator)
, m2(dzn_locator)
, p3(dzn_locator)
, t3(dzn_locator)
, m3(dzn_locator)

, port(control.port)

{


  control.dzn_meta.parent = &dzn_meta;
  control.dzn_meta.name = "control";
  p1.dzn_meta.parent = &dzn_meta;
  p1.dzn_meta.name = "p1";
  t1.dzn_meta.parent = &dzn_meta;
  t1.dzn_meta.name = "t1";
  m1.dzn_meta.parent = &dzn_meta;
  m1.dzn_meta.name = "m1";
  p2.dzn_meta.parent = &dzn_meta;
  p2.dzn_meta.name = "p2";
  t2.dzn_meta.parent = &dzn_meta;
  t2.dzn_meta.name = "t2";
  m2.dzn_meta.parent = &dzn_meta;
  m2.dzn_meta.name = "m2";
  p3.dzn_meta.parent = &dzn_meta;
  p3.dzn_meta.name = "p3";
  t3.dzn_meta.parent = &dzn_meta;
  t3.dzn_meta.name = "t3";
  m3.dzn_meta.parent = &dzn_meta;
  m3.dzn_meta.name = "m3";


  connect(p1.port, control.push1);
  connect(t1.port, p1.timer);
  connect(m1.port, p1.motor);
  connect(p2.port, control.push2);
  connect(t2.port, p2.timer);
  connect(m2.port, p2.motor);
  connect(p3.port, control.push3);
  connect(t3.port, p3.timer);
  connect(m3.port, p3.motor);

  dzn::rank(port.meta.provides.meta, 0);

}

void PusherSystem::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void PusherSystem::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////



//version: 2.8.2
