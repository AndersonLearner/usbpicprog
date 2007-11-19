/***************************************************************************
 *   Copyright (C) 2005-2006 Nicolas Hadacek <hadacek@kde.org>             *
 *   Copyright (C) 2004 Alain Gibaud <alain.gibaud@free.fr>                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "tools_config_widget.h"

#include <qwidgetstack.h>
#include <qlabel.h>

#include "tool_list.h"
#include "tools/gui/tool_config_widget.h"
#include "tools/gui/tool_group_ui.h"
#include "compile_config.h"
#include "compile_process.h"

//----------------------------------------------------------------------------
HelpDialog::HelpDialog(QWidget *parent)
  : Dialog(parent, "help_dialog", false, i18n("Help Dialog"), Close, Close, false)
{
  QGridLayout *top = new QGridLayout(mainWidget(), 1, 1, 10, 10);
  uint k = 0;
  for (; Compile::ARGUMENT_DATA[k].key; k++) {
    QLabel *label = new QLabel(Compile::ARGUMENT_DATA[k].key, mainWidget());
    top->addWidget(label, k, 0);
    label = new QLabel(i18n(Compile::ARGUMENT_DATA[k].description), mainWidget());
    top->addWidget(label, k, 1);
  }
  top->setColStretch(2, 1);
  top->setRowStretch(k, 1);
}

//----------------------------------------------------------------------------
ToolsConfigWidget::ToolsConfigWidget(Project *project, QWidget *parent)
  : GridConfigWidget(parent, "tools_config_widget"), _project(project), _helpDialog(0)
{
  QLabel *label = new QLabel(i18n("Toolchain:"), this);
  _topLayout->addWidget(label, 0, 0);
  _tool = new KeyComboBox(this);
  Tool::Lister::ConstIterator it;
  for (it=Tool::lister().begin(); it!=Tool::lister().end(); ++it)
    _tool->appendItem(it.key(), it.data()->label());
  connect(_tool, SIGNAL(activated()), SLOT(toolChanged()));
  _topLayout->addWidget(_tool, 0, 1);

  _mainStack = new QWidgetStack(this);
  _topLayout->addMultiCellWidget(_mainStack, 1,1, 0,2);
  _tabWidget = new QTabWidget(_mainStack);
  _mainStack->addWidget(_tabWidget);
  FOR_EACH(Tool::Category, k) {
    _stacks[k] = new KeyWidgetStack(_tabWidget);
    Tool::Lister::ConstIterator it;
    for (it=Tool::lister().begin(); it!=Tool::lister().end(); ++it) {
      if ( it.data()->isCustom() ) continue;
      ToolConfigWidget *cw = static_cast<const Tool::GroupUI *>(it.data()->gui())->createConfigWidget(k, project);
      if (cw) {
        _stacks[k]->appendItem(it.key(), cw);
        connect(cw, SIGNAL(displayHelp()), SLOT(displayHelp()));
      }
    }
  }
  _customWidget = new QWidget(_mainStack);
  _mainStack->addWidget(_customWidget);
  QVBoxLayout *vbox = new QVBoxLayout(_customWidget);
  label = new QLabel(i18n("Custom shell commands:"), _customWidget);
  vbox->addWidget(label);
  _commandsEditor = new EditListBox(1, _customWidget, "command_editor", EditListBox::DuplicatesAllowed);
  vbox->addWidget(_commandsEditor);

  _topLayout->setColStretch(2, 1);
}

void ToolsConfigWidget::toolChanged()
{
  QString name = _tool->currentItem();
  if ( name==Tool::Group::CUSTOM_NAME ) _mainStack->raiseWidget(_customWidget);
  else {
    _mainStack->raiseWidget(_tabWidget);
    FOR_EACH(Tool::Category, k) {
      _tabWidget->removePage(_stacks[k]);
      _stacks[k]->hide();
      if ( _stacks[k]->contains(name) ) {
        _stacks[k]->setCurrentItem(name);
        _stacks[k]->show();
        _tabWidget->addTab(_stacks[k], i18n(k.data().title));
      }
    }
    _tabWidget->setCurrentPage(0);
  }
}

void ToolsConfigWidget::loadConfig()
{
  const Tool::Group &group = Compile::Config::toolGroup(_project);
  _tool->setCurrentItem(group.name());
  QStringList commands = Compile::Config::customCommands(_project);
  _commandsEditor->setTexts(commands);
  toolChanged();
  FOR_EACH(Tool::Category, k) {
    KeyWidgetStack::ConstIterator it;
    for (it=_stacks[k]->begin(); it!=_stacks[k]->end(); ++it) {
      if ( it.key()==Tool::Group::CUSTOM_NAME ) continue;
      static_cast<ToolConfigWidget *>(_stacks[k]->item(it.key()))->loadConfig();
    }
  }
}

void ToolsConfigWidget::saveConfig()
{
  QString name = _tool->currentItem();
  Compile::Config::setToolGroup(_project, *Tool::lister().group(name));
  Compile::Config::setCustomCommands(_project, _commandsEditor->texts());
  FOR_EACH(Tool::Category, k) {
    if ( !_stacks[k]->contains(name) ) continue;
    QWidget *w = _stacks[k]->item(name);
    static_cast<ToolConfigWidget *>(w)->saveConfig();
  }
}

void ToolsConfigWidget::displayHelp()
{
  if ( _helpDialog.isNull() ) _helpDialog = new HelpDialog(this);
  _helpDialog->show();
}
