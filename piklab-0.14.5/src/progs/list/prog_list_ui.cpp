/***************************************************************************
 *   Copyright (C) 2005-2006 Nicolas Hadacek <hadacek@kde.org>             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "prog_list.h"

#include "progs/direct/base/direct_prog.h"
#include "progs/direct/gui/direct_config_widget.h"
#include "progs/icd2/base/icd2_prog.h"
#include "progs/icd2/base/icd2_debug.h"
#include "progs/icd2/gui/icd2_group_ui.h"
#include "progs/icd1/base/icd1_prog.h"
#include "progs/icd1/gui/icd1_group_ui.h"
#include "progs/pickit2/base/pickit2_prog.h"
#include "progs/pickit2/gui/pickit2_group_ui.h"
#include "progs/pickit2v2/base/pickit2v2_prog.h"
#include "progs/pickit2v2/gui/pickit2v2_group_ui.h"
#include "progs/pickit1/base/pickit1_prog.h"
#include "progs/pickit1/gui/pickit1_group_ui.h"
#include "progs/psp/base/psp_prog.h"
#include "progs/psp/gui/psp_group_ui.h"
#include "progs/gpsim/gpsim_debug.h"
#include "progs/gpsim/gui/gpsim_group_ui.h"
#include "progs/bootloader/base/bootloader_prog.h"
#include "progs/bootloader/gui/bootloader_config_widget.h"

Programmer::Lister::Lister()
{
  addGroup(new Direct::DGroup, new Direct::GroupUI);
  addGroup(new Icd2::ProgrammerGroup, new Icd2::GroupUI);
  addGroup(new Icd2::DebuggerGroup, new Icd2::GroupUI);
  addGroup(new Icd1::Group, new Icd1::GroupUI);
  addGroup(new Pickit2::Group, new Pickit2::GroupUI);
  //addGroup(new Pickit2V2::Group, new Pickit2V2::GroupUI);
  addGroup(new Pickit1::Group, new Pickit1::GroupUI);
  addGroup(new Psp::Group, new Psp::GroupUI);
  addGroup(new GPSim::Group, new GPSim::GroupUI);
  for (uint i=0; i<Bootloader::Nb_Types; i++)
    addGroup(new Bootloader::Group(Bootloader::Type(i)), new Bootloader::GroupUI);
}
