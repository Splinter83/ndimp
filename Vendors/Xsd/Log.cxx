// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "Log.hxx"

namespace cs
{
  // LogType
  // 

  const LogType::Text_type& LogType::
  Text () const
  {
    return this->Text_.get ();
  }

  LogType::Text_type& LogType::
  Text ()
  {
    return this->Text_.get ();
  }

  void LogType::
  Text (const Text_type& x)
  {
    this->Text_.set (x);
  }

  void LogType::
  Text (::std::auto_ptr< Text_type > x)
  {
    this->Text_.set (x);
  }

  const LogType::LogLevel_optional& LogType::
  LogLevel () const
  {
    return this->LogLevel_;
  }

  LogType::LogLevel_optional& LogType::
  LogLevel ()
  {
    return this->LogLevel_;
  }

  void LogType::
  LogLevel (const LogLevel_type& x)
  {
    this->LogLevel_.set (x);
  }

  void LogType::
  LogLevel (const LogLevel_optional& x)
  {
    this->LogLevel_ = x;
  }

  void LogType::
  LogLevel (::std::auto_ptr< LogLevel_type > x)
  {
    this->LogLevel_.set (x);
  }


  // LogList
  // 

  const LogList::LOG_type& LogList::
  LOG () const
  {
    return this->LOG_.get ();
  }

  LogList::LOG_type& LogList::
  LOG ()
  {
    return this->LOG_.get ();
  }

  void LogList::
  LOG (const LOG_type& x)
  {
    this->LOG_.set (x);
  }

  void LogList::
  LOG (::std::auto_ptr< LOG_type > x)
  {
    this->LOG_.set (x);
  }


  // LogLevel
  // 

  LogLevel::
  LogLevel (value v)
  : ::xml_schema::string (_xsd_LogLevel_literals_[v])
  {
  }

  LogLevel::
  LogLevel (const char* v)
  : ::xml_schema::string (v)
  {
  }

  LogLevel::
  LogLevel (const ::std::string& v)
  : ::xml_schema::string (v)
  {
  }

  LogLevel::
  LogLevel (const ::xml_schema::string& v)
  : ::xml_schema::string (v)
  {
  }

  LogLevel::
  LogLevel (const LogLevel& v,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
  : ::xml_schema::string (v, f, c)
  {
  }

  LogLevel& LogLevel::
  operator= (value v)
  {
    static_cast< ::xml_schema::string& > (*this) = 
    ::xml_schema::string (_xsd_LogLevel_literals_[v]);

    return *this;
  }
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace cs
{
  // LogType
  //

  LogType::
  LogType (const Text_type& Text)
  : ::xml_schema::type (),
    Text_ (Text, ::xml_schema::flags (), this),
    LogLevel_ (::xml_schema::flags (), this)
  {
  }

  LogType::
  LogType (const LogType& x,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
  : ::xml_schema::type (x, f, c),
    Text_ (x.Text_, f, this),
    LogLevel_ (x.LogLevel_, f, this)
  {
  }

  LogType::
  LogType (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    Text_ (f, this),
    LogLevel_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
      this->parse (p, f);
    }
  }

  void LogType::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // Text
      //
      if (n.name () == "Text" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< Text_type > r (
          Text_traits::create (i, f, this));

        if (!Text_.present ())
        {
          this->Text_.set (r);
          continue;
        }
      }

      // LogLevel
      //
      if (n.name () == "LogLevel" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< LogLevel_type > r (
          LogLevel_traits::create (i, f, this));

        if (!this->LogLevel_)
        {
          this->LogLevel_.set (r);
          continue;
        }
      }

      break;
    }

    if (!Text_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "Text",
        "");
    }
  }

  LogType* LogType::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class LogType (*this, f, c);
  }

  LogType::
  ~LogType ()
  {
  }

  // LogList
  //

  LogList::
  LogList (const LOG_type& LOG)
  : ::xml_schema::type (),
    LOG_ (LOG, ::xml_schema::flags (), this)
  {
  }

  LogList::
  LogList (::std::auto_ptr< LOG_type >& LOG)
  : ::xml_schema::type (),
    LOG_ (LOG, ::xml_schema::flags (), this)
  {
  }

  LogList::
  LogList (const LogList& x,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
  : ::xml_schema::type (x, f, c),
    LOG_ (x.LOG_, f, this)
  {
  }

  LogList::
  LogList (const ::xercesc::DOMElement& e,
           ::xml_schema::flags f,
           ::xml_schema::container* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    LOG_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, false);
      this->parse (p, f);
    }
  }

  void LogList::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // LOG
      //
      if (n.name () == "LOG" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< LOG_type > r (
          LOG_traits::create (i, f, this));

        if (!LOG_.present ())
        {
          this->LOG_.set (r);
          continue;
        }
      }

      break;
    }

    if (!LOG_.present ())
    {
      throw ::xsd::cxx::tree::expected_element< char > (
        "LOG",
        "");
    }
  }

  LogList* LogList::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class LogList (*this, f, c);
  }

  LogList::
  ~LogList ()
  {
  }

  // LogLevel
  //

  LogLevel::
  LogLevel (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
  : ::xml_schema::string (e, f, c)
  {
    _xsd_LogLevel_convert ();
  }

  LogLevel::
  LogLevel (const ::xercesc::DOMAttr& a,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
  : ::xml_schema::string (a, f, c)
  {
    _xsd_LogLevel_convert ();
  }

  LogLevel::
  LogLevel (const ::std::string& s,
            const ::xercesc::DOMElement* e,
            ::xml_schema::flags f,
            ::xml_schema::container* c)
  : ::xml_schema::string (s, e, f, c)
  {
    _xsd_LogLevel_convert ();
  }

  LogLevel* LogLevel::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class LogLevel (*this, f, c);
  }

  LogLevel::value LogLevel::
  _xsd_LogLevel_convert () const
  {
    ::xsd::cxx::tree::enum_comparator< char > c (_xsd_LogLevel_literals_);
    const value* i (::std::lower_bound (
                      _xsd_LogLevel_indexes_,
                      _xsd_LogLevel_indexes_ + 4,
                      *this,
                      c));

    if (i == _xsd_LogLevel_indexes_ + 4 || _xsd_LogLevel_literals_[*i] != *this)
    {
      throw ::xsd::cxx::tree::unexpected_enumerator < char > (*this);
    }

    return *i;
  }

  const char* const LogLevel::
  _xsd_LogLevel_literals_[4] =
  {
    "ERROR",
    "INFO",
    "WARN",
    "DEBUG"
  };

  const LogLevel::value LogLevel::
  _xsd_LogLevel_indexes_[4] =
  {
    ::cs::LogLevel::DEBUG,
    ::cs::LogLevel::ERROR,
    ::cs::LogLevel::INFO,
    ::cs::LogLevel::WARN
  };
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace cs
{
  ::std::auto_ptr< ::cs::LogList >
  LogList_ (const ::std::string& u,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::cs::LogList > r (
      ::cs::LogList_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (const ::std::string& u,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::cs::LogList > r (
      ::cs::LogList_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (const ::std::string& u,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::cs::LogList > r (
      ::cs::LogList_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::std::istream& is,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::cs::LogList_ (isrc, f, p);
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::std::istream& is,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::cs::LogList_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::std::istream& is,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::cs::LogList_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::cs::LogList_ (isrc, f, p);
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::std::istream& is,
            const ::std::string& sid,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::cs::LogList_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::std::istream& is,
            const ::std::string& sid,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::cs::LogList_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::xercesc::InputSource& i,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::cs::LogList > r (
      ::cs::LogList_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::xercesc::InputSource& i,
            ::xml_schema::error_handler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::cs::LogList > r (
      ::cs::LogList_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::xercesc::InputSource& i,
            ::xercesc::DOMErrorHandler& h,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::cs::LogList > r (
      ::cs::LogList_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (const ::xercesc::DOMDocument& d,
            ::xml_schema::flags f,
            const ::xml_schema::properties& p)
  {
    if (f & ::xml_schema::flags::keep_dom)
    {
      ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
        static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

      ::std::auto_ptr< ::cs::LogList > r (
        ::cs::LogList_ (
          c, f | ::xml_schema::flags::own_dom, p));

      return r;
    }

    const ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "LogList" &&
        n.namespace_ () == "")
    {
      ::std::auto_ptr< ::cs::LogList > r (
        ::xsd::cxx::tree::traits< ::cs::LogList, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "LogList",
      "");
  }

  ::std::auto_ptr< ::cs::LogList >
  LogList_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
            ::xml_schema::flags f,
            const ::xml_schema::properties&)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      ((f & ::xml_schema::flags::keep_dom) &&
       !(f & ::xml_schema::flags::own_dom))
      ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
      : 0);

    ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
    const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (f & ::xml_schema::flags::keep_dom)
      doc.setUserData (::xml_schema::dom::tree_node_key,
                       (c.get () ? &c : &d),
                       0);

    if (n.name () == "LogList" &&
        n.namespace_ () == "")
    {
      ::std::auto_ptr< ::cs::LogList > r (
        ::xsd::cxx::tree::traits< ::cs::LogList, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "LogList",
      "");
  }
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace cs
{
  void
  LogList_ (::std::ostream& o,
            const ::cs::LogList& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cs::LogList_ (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  LogList_ (::std::ostream& o,
            const ::cs::LogList& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cs::LogList_ (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  LogList_ (::std::ostream& o,
            const ::cs::LogList& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cs::LogList_ (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  LogList_ (::xercesc::XMLFormatTarget& t,
            const ::cs::LogList& s,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cs::LogList_ (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  LogList_ (::xercesc::XMLFormatTarget& t,
            const ::cs::LogList& s,
            ::xml_schema::error_handler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cs::LogList_ (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  LogList_ (::xercesc::XMLFormatTarget& t,
            const ::cs::LogList& s,
            ::xercesc::DOMErrorHandler& h,
            const ::xml_schema::namespace_infomap& m,
            const ::std::string& e,
            ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::cs::LogList_ (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  LogList_ (::xercesc::DOMDocument& d,
            const ::cs::LogList& s,
            ::xml_schema::flags)
  {
    ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "LogList" &&
        n.namespace_ () == "")
    {
      e << s;
    }
    else
    {
      throw ::xsd::cxx::tree::unexpected_element < char > (
        n.name (),
        n.namespace_ (),
        "LogList",
        "");
    }
  }

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
  LogList_ (const ::cs::LogList& s,
            const ::xml_schema::namespace_infomap& m,
            ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::serialize< char > (
        "LogList",
        "",
        m, f));

    ::cs::LogList_ (*d, s, f);
    return d;
  }

  void
  operator<< (::xercesc::DOMElement& e, const LogType& i)
  {
    e << static_cast< const ::xml_schema::type& > (i);

    // Text
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "Text",
          e));

      s << i.Text ();
    }

    // LogLevel
    //
    if (i.LogLevel ())
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "LogLevel",
          e));

      s << *i.LogLevel ();
    }
  }

  void
  operator<< (::xercesc::DOMElement& e, const LogList& i)
  {
    e << static_cast< const ::xml_schema::type& > (i);

    // LOG
    //
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "LOG",
          e));

      s << i.LOG ();
    }
  }

  void
  operator<< (::xercesc::DOMElement& e, const LogLevel& i)
  {
    e << static_cast< const ::xml_schema::string& > (i);
  }

  void
  operator<< (::xercesc::DOMAttr& a, const LogLevel& i)
  {
    a << static_cast< const ::xml_schema::string& > (i);
  }

  void
  operator<< (::xml_schema::list_stream& l,
              const LogLevel& i)
  {
    l << static_cast< const ::xml_schema::string& > (i);
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

