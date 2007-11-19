/***************************************************************************
 *   Copyright (C) 2006 Nicolas Hadacek <hadacek@kde.org>                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef BOOST_H
#define BOOST_H

#include "tools/base/tool_group.h"
#include "common/gui/pfile_ext.h"
#include "devices/pic/base/pic.h"

namespace Boost
{
//----------------------------------------------------------------------------
class Linker : public Tool::Base
{
private:
  virtual QString baseExecutable(bool, Tool::OutputType) const { return "boostlink.pic.exe"; }
  virtual bool checkExecutableResult(bool withWine, QStringList &lines) const;
  virtual PURL::Directory checkExecutableWorkingDirectory() const;
};

class Linker16 : public Linker
{
private:
  virtual QStringList checkExecutableOptions(bool withWine) const;
};

class Linker18 : public Linker
{
private:
  virtual QStringList checkExecutableOptions(bool withWine) const;
};

//----------------------------------------------------------------------------
class Compiler : public Tool::Base
{
private:
  virtual QStringList checkExecutableOptions(bool withWine) const;
  virtual PURL::Directory checkExecutableWorkingDirectory() const;
};

//----------------------------------------------------------------------------
class Group : public Tool::Group
{
public:
  Group(const QString &extension, const QString &text);
  PURL::Url checkExecutableUrl() const { return _checkExecTmp.url(); }
  virtual QString comment() const;
  virtual Tool::Category checkDevicesCategory() const { return Tool::Category::Nb_Types; }
  virtual Tool::ExecutableType preferedExecutableType() const { return Tool::ExecutableType::Windows; }
  virtual Tool::CompileType compileType() const { return Tool::SeparateFiles; }
  virtual bool hasDirectory(Compile::DirectoryType type) const { return type==Compile::DirectoryType::Library; }
  virtual PURL::Directory autodetectDirectory(Compile::DirectoryType type, const PURL::Directory &execDir, bool withWine) const;
  virtual bool needs(Tool::ActionType, Tool::Category category) const { return ( category==Tool::Category::Linker ); }

protected:
  virtual bool supportedArchitecture(Pic::Architecture architecture) const = 0;

private:
  Log::StringView _sview;
  PURL::TempFile  _checkExecTmp;

  virtual QValueList<const Device::Data *> getSupportedDevices(const QString &s) const;
  virtual Compile::Process *processFactory(const Compile::Data &data) const;
  virtual Compile::Config *configFactory(::Project *project) const;
};

} // namespace

#endif
