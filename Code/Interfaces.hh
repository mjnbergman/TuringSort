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
  } out;

  dzn::port::meta meta;
  inline iMotor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnClockwise) throw dzn::binding_error(meta, "in.turnClockwise");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.turnCounterClockwise) throw dzn::binding_error(meta, "in.turnCounterClockwise");


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
#ifndef IBLACKWHITESENSOR_HH
#define IBLACKWHITESENSOR_HH




struct iBlackWhiteSensor
{
#ifndef ENUM_iBlackWhiteSensor_State
#define ENUM_iBlackWhiteSensor_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_iBlackWhiteSensor_State

  struct
  {
    std::function< void()> turnOn;
    std::function< void()> turnOff;
    std::function< void()> calibrate;
  } in;

  struct
  {
    std::function< void()> measuresBlack;
    std::function< void()> measuresWhite;
    std::function< void()> measuresError;
  } out;

  dzn::port::meta meta;
  inline iBlackWhiteSensor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.calibrate) throw dzn::binding_error(meta, "in.calibrate");

    if (! out.measuresBlack) throw dzn::binding_error(meta, "out.measuresBlack");
    if (! out.measuresWhite) throw dzn::binding_error(meta, "out.measuresWhite");
    if (! out.measuresError) throw dzn::binding_error(meta, "out.measuresError");

  }
};

inline void connect (iBlackWhiteSensor& provided, iBlackWhiteSensor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iBlackWhiteSensor_State
#define ENUM_TO_STRING_iBlackWhiteSensor_State 1
inline std::string to_string(::iBlackWhiteSensor::State::type v)
{
  switch(v)
  {
    case ::iBlackWhiteSensor::State::On: return "State_On";
    case ::iBlackWhiteSensor::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_iBlackWhiteSensor_State

#ifndef STRING_TO_ENUM_iBlackWhiteSensor_State
#define STRING_TO_ENUM_iBlackWhiteSensor_State 1
inline ::iBlackWhiteSensor::State::type to_iBlackWhiteSensor_State(std::string s)
{
  static std::map<std::string, ::iBlackWhiteSensor::State::type> m = {
    {"State_On", ::iBlackWhiteSensor::State::On},
    {"State_Off", ::iBlackWhiteSensor::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iBlackWhiteSensor_State


#endif // IBLACKWHITESENSOR_HH

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
  } out;

  dzn::port::meta meta;
  inline iControl(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");


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
  } out;

  dzn::port::meta meta;
  inline iConveyerBelt(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.setClockwise) throw dzn::binding_error(meta, "in.setClockwise");
    if (! in.setCounterClockwise) throw dzn::binding_error(meta, "in.setCounterClockwise");


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
/********************************** INTERFACE *********************************/
#ifndef COMMUNICATIONPROTOCOL_HH
#define COMMUNICATIONPROTOCOL_HH




struct CommunicationProtocol
{
#ifndef ENUM_CommunicationProtocol_Mode
#define ENUM_CommunicationProtocol_Mode 1


  struct Mode
  {
    enum type
    {
      SequenceReading,Available,Rebooting
    };
  };


#endif // ENUM_CommunicationProtocol_Mode

  struct
  {
    std::function< void()> takeItem;
    std::function< void()> startSequence;
    std::function< void()> reboot;
  } in;

  struct
  {
    std::function< void()> sendEmergency;
    std::function< void()> sequenceReceived;
    std::function< void()> available;
  } out;

  dzn::port::meta meta;
  inline CommunicationProtocol(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.takeItem) throw dzn::binding_error(meta, "in.takeItem");
    if (! in.startSequence) throw dzn::binding_error(meta, "in.startSequence");
    if (! in.reboot) throw dzn::binding_error(meta, "in.reboot");

    if (! out.sendEmergency) throw dzn::binding_error(meta, "out.sendEmergency");
    if (! out.sequenceReceived) throw dzn::binding_error(meta, "out.sequenceReceived");
    if (! out.available) throw dzn::binding_error(meta, "out.available");

  }
};

inline void connect (CommunicationProtocol& provided, CommunicationProtocol& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_CommunicationProtocol_Mode
#define ENUM_TO_STRING_CommunicationProtocol_Mode 1
inline std::string to_string(::CommunicationProtocol::Mode::type v)
{
  switch(v)
  {
    case ::CommunicationProtocol::Mode::SequenceReading: return "Mode_SequenceReading";
    case ::CommunicationProtocol::Mode::Available: return "Mode_Available";
    case ::CommunicationProtocol::Mode::Rebooting: return "Mode_Rebooting";

  }
  return "";
}
#endif // ENUM_TO_STRING_CommunicationProtocol_Mode

#ifndef STRING_TO_ENUM_CommunicationProtocol_Mode
#define STRING_TO_ENUM_CommunicationProtocol_Mode 1
inline ::CommunicationProtocol::Mode::type to_CommunicationProtocol_Mode(std::string s)
{
  static std::map<std::string, ::CommunicationProtocol::Mode::type> m = {
    {"Mode_SequenceReading", ::CommunicationProtocol::Mode::SequenceReading},
    {"Mode_Available", ::CommunicationProtocol::Mode::Available},
    {"Mode_Rebooting", ::CommunicationProtocol::Mode::Rebooting},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_CommunicationProtocol_Mode


#endif // COMMUNICATIONPROTOCOL_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef ISEQUENCEINTERPRETER_HH
#define ISEQUENCEINTERPRETER_HH




struct iSequenceInterpreter
{
#ifndef ENUM_iSequenceInterpreter_Mode
#define ENUM_iSequenceInterpreter_Mode 1


  struct Mode
  {
    enum type
    {
      Reading,Done
    };
  };


#endif // ENUM_iSequenceInterpreter_Mode

  struct
  {
    std::function< void()> startSequence;
    std::function< void()> appendWhite;
    std::function< void()> appendBlack;
    std::function< void()> cancelSequence;
  } in;

  struct
  {
    std::function< void()> readSequence;
    std::function< void()> timeout;
  } out;

  dzn::port::meta meta;
  inline iSequenceInterpreter(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.startSequence) throw dzn::binding_error(meta, "in.startSequence");
    if (! in.appendWhite) throw dzn::binding_error(meta, "in.appendWhite");
    if (! in.appendBlack) throw dzn::binding_error(meta, "in.appendBlack");
    if (! in.cancelSequence) throw dzn::binding_error(meta, "in.cancelSequence");

    if (! out.readSequence) throw dzn::binding_error(meta, "out.readSequence");
    if (! out.timeout) throw dzn::binding_error(meta, "out.timeout");

  }
};

inline void connect (iSequenceInterpreter& provided, iSequenceInterpreter& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iSequenceInterpreter_Mode
#define ENUM_TO_STRING_iSequenceInterpreter_Mode 1
inline std::string to_string(::iSequenceInterpreter::Mode::type v)
{
  switch(v)
  {
    case ::iSequenceInterpreter::Mode::Reading: return "Mode_Reading";
    case ::iSequenceInterpreter::Mode::Done: return "Mode_Done";

  }
  return "";
}
#endif // ENUM_TO_STRING_iSequenceInterpreter_Mode

#ifndef STRING_TO_ENUM_iSequenceInterpreter_Mode
#define STRING_TO_ENUM_iSequenceInterpreter_Mode 1
inline ::iSequenceInterpreter::Mode::type to_iSequenceInterpreter_Mode(std::string s)
{
  static std::map<std::string, ::iSequenceInterpreter::Mode::type> m = {
    {"Mode_Reading", ::iSequenceInterpreter::Mode::Reading},
    {"Mode_Done", ::iSequenceInterpreter::Mode::Done},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iSequenceInterpreter_Mode


#endif // ISEQUENCEINTERPRETER_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef IPUSHERCONTROL_HH
#define IPUSHERCONTROL_HH




struct iPusherControl
{

  struct
  {
    std::function< void()> cancelAll;
    std::function< void(double time)> enqueueBox1;
    std::function< void(double time)> enqueueBox2;
    std::function< void(double time)> enqueueBox3;
    std::function< void(double time)> enqueueBox4;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline iPusherControl(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.cancelAll) throw dzn::binding_error(meta, "in.cancelAll");
    if (! in.enqueueBox1) throw dzn::binding_error(meta, "in.enqueueBox1");
    if (! in.enqueueBox2) throw dzn::binding_error(meta, "in.enqueueBox2");
    if (! in.enqueueBox3) throw dzn::binding_error(meta, "in.enqueueBox3");
    if (! in.enqueueBox4) throw dzn::binding_error(meta, "in.enqueueBox4");


  }
};

inline void connect (iPusherControl& provided, iPusherControl& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // IPUSHERCONTROL_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef IPUSHER_HH
#define IPUSHER_HH




struct iPusher
{
#ifndef ENUM_iPusher_State
#define ENUM_iPusher_State 1


  struct State
  {
    enum type
    {
      Down,Up
    };
  };


#endif // ENUM_iPusher_State

  struct
  {
    std::function< void()> down;
    std::function< void()> up;
    std::function< bool()> isMoving;
  } in;

  struct
  {
    std::function< void()> stopped;
  } out;

  dzn::port::meta meta;
  inline iPusher(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.down) throw dzn::binding_error(meta, "in.down");
    if (! in.up) throw dzn::binding_error(meta, "in.up");
    if (! in.isMoving) throw dzn::binding_error(meta, "in.isMoving");

    if (! out.stopped) throw dzn::binding_error(meta, "out.stopped");

  }
};

inline void connect (iPusher& provided, iPusher& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iPusher_State
#define ENUM_TO_STRING_iPusher_State 1
inline std::string to_string(::iPusher::State::type v)
{
  switch(v)
  {
    case ::iPusher::State::Down: return "State_Down";
    case ::iPusher::State::Up: return "State_Up";

  }
  return "";
}
#endif // ENUM_TO_STRING_iPusher_State

#ifndef STRING_TO_ENUM_iPusher_State
#define STRING_TO_ENUM_iPusher_State 1
inline ::iPusher::State::type to_iPusher_State(std::string s)
{
  static std::map<std::string, ::iPusher::State::type> m = {
    {"State_Down", ::iPusher::State::Down},
    {"State_Up", ::iPusher::State::Up},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iPusher_State


#endif // IPUSHER_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef ITIMER_HH
#define ITIMER_HH




struct iTimer
{
#ifndef ENUM_iTimer_State
#define ENUM_iTimer_State 1


  struct State
  {
    enum type
    {
      Idle,Busy
    };
  };


#endif // ENUM_iTimer_State

  struct
  {
    std::function< void(double time)> createTimer;
    std::function< void()> cancelTimer;
  } in;

  struct
  {
    std::function< void()> timeout;
  } out;

  dzn::port::meta meta;
  inline iTimer(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.createTimer) throw dzn::binding_error(meta, "in.createTimer");
    if (! in.cancelTimer) throw dzn::binding_error(meta, "in.cancelTimer");

    if (! out.timeout) throw dzn::binding_error(meta, "out.timeout");

  }
};

inline void connect (iTimer& provided, iTimer& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iTimer_State
#define ENUM_TO_STRING_iTimer_State 1
inline std::string to_string(::iTimer::State::type v)
{
  switch(v)
  {
    case ::iTimer::State::Idle: return "State_Idle";
    case ::iTimer::State::Busy: return "State_Busy";

  }
  return "";
}
#endif // ENUM_TO_STRING_iTimer_State

#ifndef STRING_TO_ENUM_iTimer_State
#define STRING_TO_ENUM_iTimer_State 1
inline ::iTimer::State::type to_iTimer_State(std::string s)
{
  static std::map<std::string, ::iTimer::State::type> m = {
    {"State_Idle", ::iTimer::State::Idle},
    {"State_Busy", ::iTimer::State::Busy},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iTimer_State


#endif // ITIMER_HH

/********************************** INTERFACE *********************************/


//version: 2.8.2
