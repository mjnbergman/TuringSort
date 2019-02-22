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
      port.in.turnOn = [&](){return dzn::call_in(this,[=]{ return port_turnOn();}, this->port.meta, "turnOn");};
      port.in.turnOff = [&](){return dzn::call_in(this,[=]{ return port_turnOff();}, this->port.meta, "turnOff");};


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
    virtual void port_turnOn () = 0;
    virtual void port_turnOff () = 0;

  };
}

#endif // MOTOR_HH

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
    virtual std::ostream& stream_members(std::ostream& os) const { return os; } // @suppress("Type cannot be resolved")
    void check_bindings() const;
    void dump_tree(std::ostream& os) const; // @suppress("Type cannot be resolved")
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
#ifndef REFLECTIONCONTROL_HH
#define REFLECTIONCONTROL_HH

#include "Interfaces.hh"
#include "Interfaces.hh"
#include "Interfaces.hh"



struct ReflectionControl
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_ReflectionControl_State
#define ENUM_ReflectionControl_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_ReflectionControl_State

  ::ReflectionControl::State::type state;


  std::function<void ()> out_port;

  ::iSensor port;

  ::iControl light;
  ::iSensor sensor;


  ReflectionControl(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const ReflectionControl& m)  {
    (void)m;
    return os << "[" << m.state <<"]" ;
  }
  private:
  void port_turnOn();
  void port_turnOff();
  void port_calibrate();
  void sensor_measures();

};

#endif // REFLECTIONCONTROL_HH

/********************************** COMPONENT *********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef REFLECTIONSENSOR_HH
#define REFLECTIONSENSOR_HH


#include <dzn/locator.hh>

#include "LightSensor.hh"
#include "Light.hh"
#include "LightSensor.hh"


struct ReflectionSensor
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::ReflectionControl control;
  ::LightSensor sensor;
  ::Light light;

  ::iSensor& port;


  ReflectionSensor(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // REFLECTIONSENSOR_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.8.2
