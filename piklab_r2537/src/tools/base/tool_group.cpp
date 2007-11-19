/***************************************************************************
 *   Copyright (C) 2005-2007 Nicolas Hadacek <hadacek@kde.org>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "tool_group.h"

#include "devices/list/device_list.h"
#include "devices/base/device_group.h"
#include "devices/base/generic_memory.h"
#include "common/global/process.h"
#include "tools/list/compile_config.h"
#include "tools/list/compile_process.h"
#include "libgui/project.h"

//-----------------------------------------------------------------------------
const char *Tool::Group::CUSTOM_NAME = "custom";

Tool::Group::Group()
  : _sourceGenerator(0), _checkDevicesError(true)
{
  FOR_EACH(Category, i) _bases[i] = 0;
}

void Tool::Group::init()
{
  delete _sourceGenerator;
  _sourceGenerator = sourceGeneratorFactory();
  FOR_EACH(Category, i) {
    delete _bases[i];
    _bases[i] = baseFactory(i);
    if ( _bases[i]==0 ) continue;
    _bases[i]->_category = i;
    _bases[i]->_group = this;
  }
  ::Group::Base::init();
  _version = getToolchainVersion();
}

Compile::Process *Tool::Group::createCompileProcess(const Compile::Data &data, Compile::Manager *manager) const
{
  Compile::Process *p = processFactory(data);
  if (p) p->init(data, manager);
  return p;
}

Compile::Config *Tool::Group::createConfig(::Project *project) const
{
  Compile::Config *c = configFactory(project);
  if (c) c->_group = this;
  return c;
}

PURL::Directory Tool::Group::autodetectDirectory(Compile::DirectoryType, const PURL::Directory &, bool) const
{
  return PURL::Directory();
}

QString Tool::Group::defaultLinkerScriptFilename(Compile::LinkType type, const QString &device) const
{
  QString basename = device.lower();
  if ( type==Compile::Icd2Linking ) basename += 'i';
  return basename + '.' + PURL::extension(PURL::Lkr);
}

bool Tool::Group::hasCustomLinkerScript(const ::Project *project) const
{
  return ( project && !project->customLinkerScript().isEmpty() );
}

PURL::Url Tool::Group::linkerScript(const ::Project *project, Compile::LinkType type) const
{
  if ( hasCustomLinkerScript(project) ) return project->customLinkerScript();
  QString filename = defaultLinkerScriptFilename(type, Compile::Config::device(project));
  return PURL::Url(Compile::Config::directory(*this, Compile::DirectoryType::LinkerScript), filename);
}

::Process::LineOutput *Tool::Group::checkDevicesProcess(uint i, const PURL::Directory &dir, bool withWine) const
{
  ::Process::LineOutput *process = new ::Process::LineOutput;
  Tool::Category cat = checkDevicesCategory();
  QString exec = base(cat)->baseExecutable(withWine, Compile::Config::outputType(*this));
  process->setup(dir.path() + exec, checkDevicesOptions(i), withWine);
  return process;
}

bool Tool::Group::checkExecutable(Tool::Category category, QStringList &lines)
{
  PURL::Directory dir = Compile::Config::directory(*this, Compile::DirectoryType::Executable);
  bool withWine = Compile::Config::withWine(*this);
  Tool::OutputType outputType = Compile::Config::outputType(*this);
  ::Process::LineOutput * process = _bases[category]->checkExecutableProcess(dir, withWine, outputType);
  ::Process::State state = ::Process::runSynchronously(*process, ::Process::Start, 10000);
  if ( state!=::Process::Exited ) return false;
  lines = process->sout() + process->serr();
  return _bases[category]->checkExecutableResult(withWine, lines);
}

void Tool::Group::initSupported()
{
  _checkDevicesError = false;
  Tool::Category cat = checkDevicesCategory();
  QValueList<const Device::Data *> list;
  if ( cat==Tool::Category::Nb_Types ) list = getSupportedDevices(QString::null);
  else {
    PURL::Directory dir = Compile::Config::directory(*this, Compile::DirectoryType::Executable);
    for (uint i=0; i<nbCheckDevices(); i++) {
      QStringList lines;
      ::Process::LineOutput *process = checkDevicesProcess(i, dir, Compile::Config::withWine(*this));
      ::Process::State state = ::Process::runSynchronously(*process, ::Process::Start, 10000);
      if ( state==::Process::Exited ) {
        QStringList lines = process->sout() + process->serr();
        list += getSupportedDevices(lines.join("\n"));
      } else _checkDevicesError = true;
      delete process;
    }
  }
  QValueList<const Device::Data *>::const_iterator it;
  for (it=list.begin(); it!=list.end(); ++it) addDevice((*it)->name(), *it, ::Group::Support::Tested);
}

bool Tool::Group::check(const QString &device, Log::Generic *log) const
{
  const_cast<Tool::Group *>(this)->checkInitSupported();
  if ( hasCheckDevicesError() )
    return (log ? log->askContinue(i18n("There were errors detecting supported devices for the selected toolchain (%1). Please check the toolchain configuration. Continue anyway?").arg(label())) : false);
  if ( !device.isEmpty() && device!=Device::AUTO_DATA.name && !isSupported(device) )
    return (log ? log->askContinue(i18n("The selected toolchain (%1) does not support device %2. Continue anyway?").arg(label()).arg(device)) : false);
  return true;
}
