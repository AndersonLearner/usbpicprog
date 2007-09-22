/***************************************************************************
 *   Copyright (C) 2006 Nicolas Hadacek <hadacek@kde.org>                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef PROG_XML_TO_DATA_H
#define PROG_XML_TO_DATA_H

#include <qfile.h>
#include <qtextstream.h>
#include <qmap.h>

#include "xml_to_data.h"
#include "devices/list/device_list.h"

//----------------------------------------------------------------------------
template <class Data>
class ExtXmlToData : public ::XmlToData
{
public:
  ExtXmlToData(const QString &basename, const QString &namespac)
    : _basename(basename), _namespace(namespac) {}

protected:
  QString _basename, _namespace;
  virtual bool hasFamilies() const { return true; }
  const QStringList &families() const { return _families; }
  virtual uint familyIndex(const QString &family) const { return _families.findIndex(family); }
  virtual void parseData(QDomElement, Data &) = 0;
  virtual void includes(QTextStream &) const {}
  virtual void outputData(const Data &, QTextStream &) const {}
  virtual void outputFunctions(QTextStream &) const {}
  virtual QString currentDevice() const { return _current; }
  virtual void parseDevice(QDomElement element);
  ::Group::SupportType extractSupportType(const QString &s) const;
  bool hasDevice(const QString &device) const { return _map.contains(device); }
  virtual void parse();

private:
  QString _current;
  class PData {
  public:
    uint family;
    ::Group::SupportType supportType;
    Data data;
  };
  QMap<QString, PData> _map;
  QStringList         _families;

  virtual void output();
};

template <class Data>
::Group::SupportType ExtXmlToData<Data>::extractSupportType(const QString &s) const
{
  if ( s.isEmpty() ) return Group::Untested;
  for (uint i=0; i<Group::Nb_SupportTypes; i++)
    if ( s==Group::SUPPORT_TYPE_NAMES[i] ) {
      if ( Group::SupportType(i)==Group::NotSupported ) qFatal("Cannot be \"not supported\"");
      return Group::SupportType(i);
    }
  qFatal("Unknown support type");
  return Group::Nb_SupportTypes;
}

template <class Data>
void ExtXmlToData<Data>::parseDevice(QDomElement element)
{
  if ( element.nodeName()!="device" ) qFatal("Root node child should be named \"device\"");
  _current = element.attribute("name").upper();
  if ( Device::lister().data(_current)==0 ) qFatal(QString("Device name \"%1\" unknown").arg(_current));
  PData data;
  if ( hasFamilies() ) {
    QString family = element.attribute("family");
    if ( family.isEmpty() ) qFatal(QString("Family is empty").arg(family));
    if ( _families.find(family)==_families.end() ) _families.append(family);
    data.family = familyIndex(family);
  }
  data.supportType = extractSupportType(element.attribute("support_type"));
  parseData(element, data.data);
  _map[_current] = data;
}

template <class Data>
void ExtXmlToData<Data>::parse()
{
  QDomDocument doc = parseFile(_basename + ".xml");
  QDomElement root = doc.documentElement();
  if ( root.nodeName()!="type" ) qFatal("Root node should be \"type\"");
  if ( root.attribute("name")!=_basename ) qFatal(QString("Root node name is not \"%1\"").arg(_basename));
  QDomNode child = root.firstChild();
  while ( !child.isNull() ) {
    if ( child.isComment() ) qDebug("comment: %s", child.toComment().data().latin1());
    else {
      if ( !child.isElement() ) qFatal("Root node child should be an element");
      parseDevice(child.toElement());
    }
    child = child.nextSibling();
  }
}

template <class Data>
void ExtXmlToData<Data>::output()
{
  // write .cpp file
  QFile file(_basename + "_data.cpp");
  if ( !file.open(IO_WriteOnly) ) qFatal(QString("Cannot open output file \"%1\"").arg(file.name()));
  QTextStream s(&file);
  s << "// #### Do not edit: this file is autogenerated !!!" << endl << endl;
  s << "#include \"devices/list/device_list.h\"" << endl;
  s << "#include \"" + _basename + ".h\"" << endl;
  s << "#include \"" + _basename + "_data.h\"" << endl;
  includes(s);
  s << endl;
  s << "namespace " << _namespace << endl;
  s << "{" << endl;
  s << "struct CData {" << endl;
  s << "  const char *name;" << endl;
  if ( hasFamilies() ) s << "  uint family;" << endl;
  s << "  uint supportType;" << endl;
  s << "  Data data;" << endl;
  s << "};" << endl;
  s << endl;

  // data list
  typename QMap<QString, PData>::const_iterator it = _map.begin();
  for (; it!=_map.end(); ++it) {
    s << "const CData PIC" << it.key() << "_DATA = {";
    s << "  \"" << it.key() << "\", ";
    if ( hasFamilies() ) s << it.data().family << ", ";
    s << it.data().supportType << ", ";
    s << "{ ";
    outputData(it.data().data, s);
    s << " }";
    s << " };" << endl;
  }
  s << endl;
  s << "const CData *DATA_LIST[] = {" << endl;
  uint i = 0;
  it = _map.begin();
  for (; it!=_map.end(); ++it) {
    s << "&PIC" << it.key() << "_DATA,";
    i++;
    if ( (i%10)==0 ) s << endl;
  }
  s << "0 " << endl;
  s << "};" << endl;

  // functions
  s << endl;
  s << "const CData *cdata(const QString &device)" << endl;
  s << "{" << endl;
  s << "  for(uint i=0; DATA_LIST[i]; i++)" << endl;
  s << "    if ( device==DATA_LIST[i]->name ) return DATA_LIST[i];" << endl;
  s << "  return 0;" << endl;
  s << "}" << endl;
  s << "bool isSupported(const QString &device)" << endl;
  s << "{" << endl;
  s << "  return cdata(device);" << endl;
  s << "}" << endl;
  if ( hasFamilies() ) {
    s << "uint family(const QString &device)" << endl;
    s << "{" << endl;
    s << "  return cdata(device)->family;" << endl;
    s << "}" << endl;
  }
  s << "::Group::SupportType supportType(const QString &device)" << endl;
  s << "{" << endl;
  s << "  return ::Group::SupportType(cdata(device)->supportType);" << endl;
  s << "}" << endl;
  s << "const Data &data(const QString &device)" << endl;
  s << "{" << endl;
  s << "  return cdata(device)->data;" << endl;
  s << "}" << endl;
  s << endl;
  outputFunctions(s);
  s << endl;
  s << "}" << endl;
}

//----------------------------------------------------------------------------
namespace Programmer
{
template <class Data>
class XmlToData : public ExtXmlToData<Data>
{
public:
  XmlToData(const QString &basename, const QString &namespac)
    : ExtXmlToData<Data>(basename, namespac) {}

protected:
  virtual void outputFunctions(QTextStream &s) const;
  virtual void includes(QTextStream &) const;
};

template <class Data>
void Programmer::XmlToData<Data>::outputFunctions(QTextStream &s) const
{
  s << "void Group::initSupported()" << endl;
  s << "{" << endl;
  s << "  for (uint i=0; DATA_LIST[i]; i++) {" << endl;
  s << "    ::Group::DeviceData data;" << endl;
  s << "    data.supportType = ::Group::SupportType(DATA_LIST[i]->supportType);" << endl;
  s << "    data.data = Device::lister().data(DATA_LIST[i]->name);" << endl;
  s << "    addDevice(data);" << endl;
  s << "  }" << endl;
  s << "}" << endl;
  s << endl;
}

template <class Data>
void Programmer::XmlToData<Data>::includes(QTextStream &s) const
{
  s << "#include \"" << ExtXmlToData<Data>::_basename << "_prog.h\"" << endl;
}

} // namespace

#endif
