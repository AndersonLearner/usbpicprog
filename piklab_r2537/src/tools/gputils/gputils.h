/***************************************************************************
 *   Copyright (C) 2005-2007 Nicolas Hadacek <hadacek@kde.org>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef GPUTILS_H
#define GPUTILS_H

#include "tools/base/tool_group.h"
#include "gputils_generator.h"

namespace GPUtils
{
//----------------------------------------------------------------------------
class Base : public Tool::Base
{
public:
  virtual QString baseExecutable(bool withWine, Tool::OutputType type) const;

private:
  virtual QStringList checkExecutableOptions(bool) const { return "-v"; }
  virtual bool checkExecutableResult(bool withWine, QStringList &lines) const;
};

//----------------------------------------------------------------------------
class Group : public Tool::Group
{
public:
  virtual QString name() const { return "gputils"; }
  virtual QString label() const { return i18n("GPUtils"); }
  virtual QString informationText() const;
  virtual Tool::Category checkDevicesCategory() const { return Tool::Category::Assembler; }
  virtual QStringList checkDevicesOptions(uint) const { return "-l"; }
  virtual PURL::Directory autodetectDirectory(Compile::DirectoryType type, const PURL::Directory &execDir, bool withWine) const;
  virtual bool hasDirectory(Compile::DirectoryType type) const { return type==Compile::DirectoryType::Header || type==Compile::DirectoryType::LinkerScript; }
  virtual PURL::FileType linkerScriptType() const { return PURL::Lkr; }
  virtual Tool::ExecutableType preferedExecutableType() const { return Tool::ExecutableType::Unix; }
  virtual Tool::CompileType compileType() const { return Tool::SeparateFiles; }
  virtual bool needs(Tool::ActionType type, Tool::Category category) const;
  virtual PURL::FileType implementationType(PURL::ToolType type) const { return (type==PURL::ToolType::Assembler ? PURL::AsmGPAsm : PURL::Nb_FileTypes); }

protected:
  virtual Tool::Base *baseFactory(Tool::Category c) const;
  virtual QValueList<const Device::Data *> getSupportedDevices(const QString &s) const { return GPUtils::getSupportedDevices(s); }
  virtual Compile::Process *processFactory(const Compile::Data &data) const;
  virtual Compile::Config *configFactory(::Project *project) const;
  virtual Tool::SourceGenerator *sourceGeneratorFactory() const;
};

} // namespace

#endif
