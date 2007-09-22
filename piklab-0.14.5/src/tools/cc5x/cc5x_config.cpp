/***************************************************************************
 *   Copyright (C) 2007 Nicolas Hadacek <hadacek@kde.org>                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "cc5x_config.h"

CC5X::ConfigWidget::ConfigWidget(Project *project)
  : ToolConfigWidget(project, "cc5x_config_widget")
{}

void CC5X::ConfigWidget::initEntries()
{
  createIncludeDirectoriesEntry();
}
