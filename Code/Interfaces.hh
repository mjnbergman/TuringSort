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

/********************************** INTERFACE *********************************/
#ifndef IMOTOR_HH
#define IMOTOR_HH




struct iMotor
{
#ifndef ENUM_iMotor_State
#define ENUM_iMotor_State 1


  struct State
  {
    enum type
    {
      Clock,Off,CounterClock
    };
  };


#endif // ENUM_iMotor_State

  struct
  {
    std::function< void()> turnClockwise;
    std::function< void()> turnOff;
    std::function< void()> turnCounterClockwise;
  } in;

  struct
  {
    std::function< void()> error;
  } out;

  dzn::port::meta meta;
  inline iMotor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnClockwise) throw dzn::binding_error(meta, "in.turnClockwise");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.turnCounterClockwise) throw dzn::binding_error(meta, "in.turnCounterClockwise");

    if (! out.error) throw dzn::binding_error(meta, "out.error");

  }
};

inline void connect (iMotor& provided, iMotor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iMotor_State
#define ENUM_TO_STRING_iMotor_State 1
inline std::string to_string(::iMotor::State::type v)
{
  switch(v)
  {
    case ::iMotor::State::Clock: return "State_Clock";
    case ::iMotor::State::Off: return "State_Off";
    case ::iMotor::State::CounterClock: return "State_CounterClock";

  }
  return "";
}
#endif // ENUM_TO_STRING_iMotor_State

#ifndef STRING_TO_ENUM_iMotor_State
#define STRING_TO_ENUM_iMotor_State 1
inline ::iMotor::State::type to_iMotor_State(std::string s)
{
  static std::map<std::string, ::iMotor::State::type> m = {
    {"State_Clock", ::iMotor::State::Clock},
    {"State_Off", ::iMotor::State::Off},
    {"State_CounterClock", ::iMotor::State::CounterClock},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iMotor_State


#endif // IMOTOR_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef IOUTPUT_HH
#define IOUTPUT_HH




struct iOutput
{
#ifndef ENUM_iOutput_State
#define ENUM_iOutput_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_iOutput_State

  struct
  {
    std::function< void()> turnOn;
    std::function< void()> turnOff;
    std::function< void(std::string output)> output;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline iOutput(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.output) throw dzn::binding_error(meta, "in.output");


  }
};

inline void connect (iOutput& provided, iOutput& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iOutput_State
#define ENUM_TO_STRING_iOutput_State 1
inline std::string to_string(::iOutput::State::type v)
{
  switch(v)
  {
    case ::iOutput::State::On: return "State_On";
    case ::iOutput::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_iOutput_State

#ifndef STRING_TO_ENUM_iOutput_State
#define STRING_TO_ENUM_iOutput_State 1
inline ::iOutput::State::type to_iOutput_State(std::string s)
{
  static std::map<std::string, ::iOutput::State::type> m = {
    {"State_On", ::iOutput::State::On},
    {"State_Off", ::iOutput::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iOutput_State


#endif // IOUTPUT_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef ISENSOR_HH
#define ISENSOR_HH




struct iSensor
{
#ifndef ENUM_iSensor_State
#define ENUM_iSensor_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_iSensor_State

  struct
  {
    std::function< void()> turnOn;
    std::function< void()> turnOff;
    std::function< void()> calibrate;
  } in;

  struct
  {
    std::function< void(int value)> measures;
  } out;

  dzn::port::meta meta;
  inline iSensor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.calibrate) throw dzn::binding_error(meta, "in.calibrate");

    if (! out.measures) throw dzn::binding_error(meta, "out.measures");

  }
};

inline void connect (iSensor& provided, iSensor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iSensor_State
#define ENUM_TO_STRING_iSensor_State 1
inline std::string to_string(::iSensor::State::type v)
{
  switch(v)
  {
    case ::iSensor::State::On: return "State_On";
    case ::iSensor::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_iSensor_State

#ifndef STRING_TO_ENUM_iSensor_State
#define STRING_TO_ENUM_iSensor_State 1
inline ::iSensor::State::type to_iSensor_State(std::string s)
{
  static std::map<std::string, ::iSensor::State::type> m = {
    {"State_On", ::iSensor::State::On},
    {"State_Off", ::iSensor::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iSensor_State


#endif // ISENSOR_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef ICONTROL_HH
#define ICONTROL_HH




struct iControl
{
#ifndef ENUM_iControl_State
#define ENUM_iControl_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_iControl_State

  struct
  {
    std::function< void()> turnOn;
    std::function< void()> turnOff;
  } in;

  struct
  {
    std::function< void()> error;
  } out;

  dzn::port::meta meta;
  inline iControl(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");

    if (! out.error) throw dzn::binding_error(meta, "out.error");

  }
};

inline void connect (iControl& provided, iControl& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iControl_State
#define ENUM_TO_STRING_iControl_State 1
inline std::string to_string(::iControl::State::type v)
{
  switch(v)
  {
    case ::iControl::State::On: return "State_On";
    case ::iControl::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_iControl_State

#ifndef STRING_TO_ENUM_iControl_State
#define STRING_TO_ENUM_iControl_State 1
inline ::iControl::State::type to_iControl_State(std::string s)
{
  static std::map<std::string, ::iControl::State::type> m = {
    {"State_On", ::iControl::State::On},
    {"State_Off", ::iControl::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iControl_State


#endif // ICONTROL_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef ICONVEYERBELT_HH
#define ICONVEYERBELT_HH




struct iConveyerBelt
{
#ifndef ENUM_iConveyerBelt_State
#define ENUM_iConveyerBelt_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_iConveyerBelt_State
#ifndef ENUM_iConveyerBelt_Direction
#define ENUM_iConveyerBelt_Direction 1


  struct Direction
  {
    enum type
    {
      Clockwise,CounterClockwise
    };
  };


#endif // ENUM_iConveyerBelt_Direction

  struct
  {
    std::function< void()> turnOn;
    std::function< void()> turnOff;
    std::function< void()> setClockwise;
    std::function< void()> setCounterClockwise;
  } in;

  struct
  {
    std::function< void()> error;
  } out;

  dzn::port::meta meta;
  inline iConveyerBelt(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.setClockwise) throw dzn::binding_error(meta, "in.setClockwise");
    if (! in.setCounterClockwise) throw dzn::binding_error(meta, "in.setCounterClockwise");

    if (! out.error) throw dzn::binding_error(meta, "out.error");

  }
};

inline void connect (iConveyerBelt& provided, iConveyerBelt& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iConveyerBelt_State
#define ENUM_TO_STRING_iConveyerBelt_State 1
inline std::string to_string(::iConveyerBelt::State::type v)
{
  switch(v)
  {
    case ::iConveyerBelt::State::On: return "State_On";
    case ::iConveyerBelt::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_iConveyerBelt_State
#ifndef ENUM_TO_STRING_iConveyerBelt_Direction
#define ENUM_TO_STRING_iConveyerBelt_Direction 1
inline std::string to_string(::iConveyerBelt::Direction::type v)
{
  switch(v)
  {
    case ::iConveyerBelt::Direction::Clockwise: return "Direction_Clockwise";
    case ::iConveyerBelt::Direction::CounterClockwise: return "Direction_CounterClockwise";

  }
  return "";
}
#endif // ENUM_TO_STRING_iConveyerBelt_Direction

#ifndef STRING_TO_ENUM_iConveyerBelt_State
#define STRING_TO_ENUM_iConveyerBelt_State 1
inline ::iConveyerBelt::State::type to_iConveyerBelt_State(std::string s)
{
  static std::map<std::string, ::iConveyerBelt::State::type> m = {
    {"State_On", ::iConveyerBelt::State::On},
    {"State_Off", ::iConveyerBelt::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iConveyerBelt_State
#ifndef STRING_TO_ENUM_iConveyerBelt_Direction
#define STRING_TO_ENUM_iConveyerBelt_Direction 1
inline ::iConveyerBelt::Direction::type to_iConveyerBelt_Direction(std::string s)
{
  static std::map<std::string, ::iConveyerBelt::Direction::type> m = {
    {"Direction_Clockwise", ::iConveyerBelt::Direction::Clockwise},
    {"Direction_CounterClockwise", ::iConveyerBelt::Direction::CounterClockwise},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iConveyerBelt_Direction


#endif // ICONVEYERBELT_HH

/********************************** INTERFACE *********************************/


//version: 2.8.2
