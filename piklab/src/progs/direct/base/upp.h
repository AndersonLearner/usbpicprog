/***************************************************************************
 * Copyright (C) 2005 Lorenz Mösenlechner & Matthias Kranz                 *
 *                    <icd2linux@hcilab.org>                               *
 * Copyright (C) 2005 Nicolas Hadacek <hadacek@kde.org>                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef UPP_H
#define UPP_H

#include "common/global/global.h"
#ifdef Q_OS_UNIX
#  include <termios.h>
#elif defined(Q_OS_WIN)
#  include <io.h>
#endif
//#include "port_base.h"

#ifdef Q_OS_UNIX
#  include <stdio.h>
#  include <fcntl.h>
#  include <sys/time.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <sys/ioctl.h>
#  include <errno.h>
#  include <unistd.h> // needed on some system
#endif
#include <qdatetime.h>
#include "common/port/port_base.h"

/*struct usb_dev_handle;
struct usb_device;
struct usb_bus;
*/
namespace Port
{

class UPP : public Base
{
public:


 /* enum Property { NoProperty = 0, NeedDrain = 1, NeedFlush = 2, NeedBreak = 4,
                  Blocking = 8 };
  Q_DECLARE_FLAGS(Properties, Property)*/
  UPP(const QString &device, Log::Base &base);

  virtual Description description() const { return Description(USBType, _device); }
  virtual ~UPP() { close(); }
  static const QStringList &probedDeviceList();
  static IODirs probe(const QString &device);
  static bool isAvailable() { return true; }

  //enum InputFlag { NoInputFlag = 0, IgnoreBreak = 1, IgnoreParity = 2 };
  //Q_DECLARE_FLAGS(InputFlags, InputFlag)
  //enum ControlFlag { NoControlFlag = 0, ByteSize8 = 1, HardwareFlowControl = 2,
  //                   EnableReceiver = 4, IgnoreControlLines = 8 };
  //Q_DECLARE_FLAGS(ControlFlags, ControlFlag)
  //bool setMode(InputFlags inputFlags, ControlFlags controlFlags, Speed speed, uint readTimeout); // in ms
  bool drain(uint timeout);
  bool flush(uint timeout);
  bool doBreak(uint duration); // in ms
  //bool setHardwareFlowControl(bool on);

  enum Pin { VPP=0, VPP_Reset, DATA, CLOCK, Nb_Pins };
  struct SPinData {
    IODir dir;
    const char *label;
  };
  static const SPinData PIN_DATA[Nb_Pins];
  virtual bool setPinOn(uint pin, bool on, LogicType type);
  virtual bool readPin(uint pin, LogicType type, bool &value);
  virtual QValueVector<PinData> pinData(IODir dir) const;
  //virtual bool isGroundPin(uint pin) const;
  //virtual uint groundPin() const { return SG; }
  virtual IODir ioDir(uint pin) const;



private:

  QString    _device;
 // Properties _properties;
#if defined(Q_OS_UNIX)
  typedef int Handle;
  typedef termios Parameters;
#elif defined(Q_OS_WIN)
  typedef HANDLE Handle;
  struct Parameters {
    DCB             dcb;
    COMMTIMEOUTS    comtmo;
  };
#endif
  Handle  _fd;
  Parameters _oldParameters;

  bool setParameters(const Parameters &parameters);
  bool getParameters(Parameters &parameters);
  virtual bool internalOpen();
  virtual void internalClose();
  virtual bool internalSend(const char *data, uint size, uint timeout);
  virtual bool internalReceive(uint size, char *data, uint timeout);
  virtual void setSystemError(const QString &message);
  bool internalSetPinOn(Pin pin, bool on);
  bool internalReadPin(Pin pin, LogicType type, bool &value);
  static const Handle INVALID_HANDLE;
  static Handle openHandle(const QString &device, IODirs dirs);
  static void closeHandle(Handle handle);
  static QStringList *_list;
  static QStringList deviceList();
  void send_usb(struct usb_dev_handle * d, int len, const char * src);
  void recv_usb(struct usb_dev_handle * d, int len, const char * dest);
  //static void setHardwareFlowControl(Parameters &parameters, bool o
};

} // namespace

#endif
