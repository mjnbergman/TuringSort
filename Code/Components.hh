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
#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>

/***********************************  FOREIGN  **********************************/
#ifndef SKEL_MOTOR_HH
#define SKEL_MOTOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "Interfaces.hh"



namespace skel {
  struct Motor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::iMotor port;


    Motor(const dzn::locator& dzn_locator)
    : dzn_meta{"","Motor",0,0,{},{},{[this]{port.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , port({{"port",this,&dzn_meta},{"",0,0}})


    {
      port.in.turnClockwise = [&](){return dzn::call_in(this,[=]{ return port_turnClockwise();}, this->port.meta, "turnClockwise");};
      port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};
      port.in.turnCounterClockwise = [&](){return dzn::call_in(this,[=]{ return port_turnCounterClockwise();}, this->port.meta, "turnCounterClockwise");};


    }
    virtual ~ Motor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Motor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void port_turnClockwise () = 0;
    virtual void port_turnOff () = 0;
    virtual void port_turnCounterClockwise () = 0;

  };
}

#endif // MOTOR_HH

/***********************************  FOREIGN  **********************************/
/********************************** COMPONENT *********************************/
#ifndef PUSHER_HH
#define PUSHER_HH

#include "Interfaces.hh"
#include "Interfaces.hh"
#include "Interfaces.hh"



struct Pusher
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;

  ::iMotor::State::type motorState;
  ::iPusher::State::type state;
  double time;

  bool reply_bool;

  std::function<void ()> out_port;

  ::iPusher port;

  ::iMotor motor;
  ::iTimer timer;


  Pusher(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Pusher& m)  {
    (void)m;
    return os << "[" << m.motorState <<", " << m.state <<", " << m.time <<"]" ;
  }
  private:
  void port_down();
  void port_up();
  bool port_isMoving();
  void timer_timeout();

};

#endif // PUSHER_HH

/********************************** COMPONENT *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_TIMER_HH
#define SKEL_TIMER_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "Interfaces.hh"



namespace skel {
  struct Timer
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::iTimer port;


    Timer(const dzn::locator& dzn_locator)
    : dzn_meta{"","Timer",0,0,{},{},{[this]{port.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , port({{"port",this,&dzn_meta},{"",0,0}})


    {
      port.in.createTimer = [&](double time){return dzn::call_in(this,[=]{ return port_createTimer(time);}, this->port.meta, "createTimer");};
      port.in.cancelTimer = [&](){return dzn::call_in(this,[=]{ return port_cancelTimer();}, this->port.meta, "cancelTimer");};


    }
    virtual ~ Timer() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Timer& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void port_createTimer (double time) = 0;
    virtual void port_cancelTimer () = 0;

  };
}

#endif // TIMER_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_DISPLAY_HH
#define SKEL_DISPLAY_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "Interfaces.hh"



namespace skel {
  struct Display
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::iOutput port;


    Display(const dzn::locator& dzn_locator)
    : dzn_meta{"","Display",0,0,{},{},{[this]{port.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , port({{"port",this,&dzn_meta},{"",0,0}})


    {
      port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
      port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};
      port.in.output = [&](std::string output){return dzn::call_in(this,[=]{ return port_output(output);}, this->port.meta, "output");};


    }
    virtual ~ Display() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Display& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void port_turnOn () = 0;
    virtual void port_turnOff () = 0;
    virtual void port_output (std::string output) = 0;

  };
}

#endif // DISPLAY_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_LIGHT_HH
#define SKEL_LIGHT_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "Interfaces.hh"



namespace skel {
  struct Light
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::iControl port;


    Light(const dzn::locator& dzn_locator)
    : dzn_meta{"","Light",0,0,{},{},{[this]{port.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , port({{"port",this,&dzn_meta},{"",0,0}})


    {
      port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
      port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};


    }
    virtual ~ Light() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Light& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void port_turnOn () = 0;
    virtual void port_turnOff () = 0;

  };
}

#endif // LIGHT_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_LIGHTSENSOR_HH
#define SKEL_LIGHTSENSOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "Interfaces.hh"



namespace skel {
  struct LightSensor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::iSensor port;


    LightSensor(const dzn::locator& dzn_locator)
    : dzn_meta{"","LightSensor",0,0,{},{},{[this]{port.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , port({{"port",this,&dzn_meta},{"",0,0}})


    {
      port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
      port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};
      port.in.calibrate = [&](){return dzn::call_in(this,[=]{ return port_calibrate();}, this->port.meta, "calibrate");};


    }
    virtual ~ LightSensor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const LightSensor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void port_turnOn () = 0;
    virtual void port_turnOff () = 0;
    virtual void port_calibrate () = 0;

  };
}

#endif // LIGHTSENSOR_HH

/***********************************  FOREIGN  **********************************/
/********************************** COMPONENT *********************************/
#ifndef BLACKWHITESENSORCONTROL_HH
#define BLACKWHITESENSORCONTROL_HH

#include "Interfaces.hh"
#include "Interfaces.hh"
#include "Interfaces.hh"



struct BlackWhiteSensorControl
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_BlackWhiteSensorControl_State
#define ENUM_BlackWhiteSensorControl_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_BlackWhiteSensorControl_State

  ::BlackWhiteSensorControl::State::type state;


  std::function<void ()> out_port;

  ::iBlackWhiteSensor port;

  ::iControl light;
  ::iSensor sensor;


  BlackWhiteSensorControl(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const BlackWhiteSensorControl& m)  {
    (void)m;
    return os << "[" << m.state <<"]" ;
  }
  private:
  void port_turnOn();
  void port_turnOff();
  void port_calibrate();
  void sensor_measures(int value);

};

#endif // BLACKWHITESENSORCONTROL_HH

/********************************** COMPONENT *********************************/
/********************************** COMPONENT *********************************/
#ifndef CONVEYERBELTCONTROL_HH
#define CONVEYERBELTCONTROL_HH

#include "Interfaces.hh"
#include "Interfaces.hh"



struct ConveyerBeltControl
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;

  ::iConveyerBelt::Direction::type direction;
  ::iConveyerBelt::State::type state;


  std::function<void ()> out_port;

  ::iConveyerBelt port;

  ::iMotor motor;


  ConveyerBeltControl(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const ConveyerBeltControl& m)  {
    (void)m;
    return os << "[" << m.direction <<", " << m.state <<"]" ;
  }
  private:
  void port_turnOn();
  void port_turnOff();
  void port_setClockwise();
  void port_setCounterClockwise();

};

#endif // CONVEYERBELTCONTROL_HH

/********************************** COMPONENT *********************************/
/********************************** COMPONENT *********************************/
#ifndef PUSHERCONTROL_HH
#define PUSHERCONTROL_HH

#include "Interfaces.hh"
#include "Interfaces.hh"
#include "Interfaces.hh"
#include "Interfaces.hh"



struct PusherControl
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  bool reply_bool;

  std::function<void ()> out_port;

  ::iPusherControl port;

  ::iPusher push1;
  ::iPusher push2;
  ::iPusher push3;


  PusherControl(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const PusherControl& m)  {
    (void)m;
    return os << "[" << "]" ;
  }
  private:
  void port_cancelAll();
  void port_enqueueBox1(double time);
  void port_enqueueBox2(double time);
  void port_enqueueBox3(double time);
  void port_enqueueBox4(double time);
  void push1_stopped();
  void push2_stopped();
  void push3_stopped();

};

#endif // PUSHERCONTROL_HH

/********************************** COMPONENT *********************************/
/********************************** COMPONENT *********************************/
#ifndef SEQUENCEBEHAVIOUR_HH
#define SEQUENCEBEHAVIOUR_HH

#include "Interfaces.hh"
#include "Interfaces.hh"



struct SequenceBehaviour
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;

  ::iSequenceInterpreter::Mode::type mode;
  int SEQ_LENGTH;
  int current;
  int time;


  std::function<void ()> out_port;

  ::iSequenceInterpreter port;

  ::iTimer timer;


  SequenceBehaviour(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const SequenceBehaviour& m)  {
    (void)m;
    return os << "[" << m.mode <<", " << m.SEQ_LENGTH <<", " << m.current <<", " << m.time <<"]" ;
  }
  private:
  void port_startSequence();
  void port_appendWhite();
  void port_appendBlack();
  void port_cancelSequence();
  void timer_timeout();

};

#endif // SEQUENCEBEHAVIOUR_HH

/********************************** COMPONENT *********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef BLACKWHITESENSOR_HH
#define BLACKWHITESENSOR_HH


#include <dzn/locator.hh>

#include "LightSensor.hh"
#include "Light.hh"



struct BlackWhiteSensor
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::BlackWhiteSensorControl control;
  ::LightSensor sensor;
  ::Light light;

  ::iBlackWhiteSensor& port;


  BlackWhiteSensor(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // BLACKWHITESENSOR_HH

/***********************************  SYSTEM  ***********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef CONVEYERBELT_HH
#define CONVEYERBELT_HH


#include <dzn/locator.hh>

#include "Motor.hh"



struct ConveyerBelt
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::ConveyerBeltControl control;
  ::Motor motor;

  ::iConveyerBelt& port;


  ConveyerBelt(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // CONVEYERBELT_HH

/***********************************  SYSTEM  ***********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef PUSHERSYSTEM_HH
#define PUSHERSYSTEM_HH


#include <dzn/locator.hh>

#include "Timer.hh"
#include "Motor.hh"
#include "Timer.hh"
#include "Motor.hh"
#include "Timer.hh"
#include "Motor.hh"



struct PusherSystem
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::PusherControl control;
  ::Pusher p1;
  ::Timer t1;
  ::Motor m1;
  ::Pusher p2;
  ::Timer t2;
  ::Motor m2;
  ::Pusher p3;
  ::Timer t3;
  ::Motor m3;

  ::iPusherControl& port;


  PusherSystem(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // PUSHERSYSTEM_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.8.2
