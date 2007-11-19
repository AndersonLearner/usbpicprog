/***************************************************************************
 *   Copyright (C) 2006 Nicolas Hadacek <hadacek@kde.org>                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef PIC30_UI_H
#define PIC30_UI_H

#include "tools/gui/tool_config_widget.h"
#include "tools/gui/tool_group_ui.h"

namespace PIC30
{

//----------------------------------------------------------------------------
class CompilerConfigWidget : public ToolConfigWidget
{
Q_OBJECT
public:
  CompilerConfigWidget(Project *project);
  virtual void initEntries();
};

//----------------------------------------------------------------------------
class AssemblerConfigWidget : public ToolConfigWidget
{
Q_OBJECT
public:
  AssemblerConfigWidget(Project *project);
  virtual void initEntries();
};

//----------------------------------------------------------------------------
class LinkerConfigWidget : public ToolConfigWidget
{
Q_OBJECT
public:
  LinkerConfigWidget(Project *project);
  virtual void initEntries();
};

//----------------------------------------------------------------------------
class GroupUI : public Tool::GroupUI
{
public:
  virtual ::ToolConfigWidget *configWidgetFactory(Tool::Category category, ::Project *project) const;
};

} // namespace

#endif
