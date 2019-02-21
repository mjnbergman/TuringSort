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
#ifndef ITURINGSORT_HH
#define ITURINGSORT_HH




struct ITuringSort
{

  struct
  {
    std::function< void()> init_Machine;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline ITuringSort(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.init_Machine) throw dzn::binding_error(meta, "in.init_Machine");


  }
};

inline void connect (ITuringSort& provided, ITuringSort& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ITURINGSORT_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_TURINGSORT_HH
#define SKEL_TURINGSORT_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct TuringSort
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ITuringSort robotInterface;


    TuringSort(const dzn::locator& dzn_locator)
    : dzn_meta{"","TuringSort",0,0,{},{},{[this]{robotInterface.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , robotInterface({{"robotInterface",this,&dzn_meta},{"",0,0}})


    {
      robotInterface.in.init_Machine = [&](){return dzn::call_in(this,[=]{ return robotInterface_init_Machine();}, this->robotInterface.meta, "init_Machine");};


    }
    virtual ~ TuringSort() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const TuringSort& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void robotInterface_init_Machine () = 0;

  };
}

#endif // TURINGSORT_HH

/***********************************  FOREIGN  **********************************/


//version: 2.8.2
