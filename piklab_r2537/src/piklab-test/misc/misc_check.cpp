/***************************************************************************
 *   Copyright (C) 2007 Nicolas Hadacek <hadacek@kde.org>                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "misc_check.h"

#include "common/global/purl.h"

//----------------------------------------------------------------------------
bool MiscCheck::execute()
{
  {
    PURL::Url url = PURL::Url::fromPathOrUrl(QString::null);
    if ( !url.isEmpty() ) TEST_FAILED("isEmpty");
    TEST_PASSED;
  }
  {
    PURL::Url url = PURL::Url::fromPathOrUrl("");
    if ( !url.isEmpty() ) TEST_FAILED("isEmpty");
    TEST_PASSED;
  }
  {
    PURL::Url url = PURL::Url::fromPathOrUrl("/");
    if ( url.isEmpty() ) TEST_FAILED("isEmpty");
    if ( url.isRelative() ) TEST_FAILED("isRelative");
    if ( !url.isLocal() ) TEST_FAILED("isLocal");
    if ( url.path()!="/" ) TEST_FAILED("");
    if ( url.filepath()!="/" ) TEST_FAILED(url.filepath());
    if ( url.unterminatedPath()!="/" ) TEST_FAILED("");
    if ( !url.filename().isEmpty() ) TEST_FAILED(url.filename());
    TEST_PASSED;
  }
  {
    PURL::Url url = PURL::Url::fromPathOrUrl("test");
    if ( url.isEmpty() ) TEST_FAILED("isEmpty");
    if ( !url.isRelative() ) TEST_FAILED("isRelative");
    if ( !url.isLocal() ) TEST_FAILED("isLocal");
    if ( url.filename()!="test" ) TEST_FAILED(url.filename());
    TEST_PASSED;
  }
  {
    PURL::Url url = PURL::Url::fromPathOrUrl("/test");
    if ( url.isEmpty() ) TEST_FAILED("isEmpty");
    if ( url.isRelative() ) TEST_FAILED("isRelative");
    if ( !url.isLocal() ) TEST_FAILED("isLocal");
    if ( url.path()!="/" ) TEST_FAILED("");
    if ( url.unterminatedPath()!="/" ) TEST_FAILED("");
    if ( url.filepath()!="/test" ) TEST_FAILED(url.filepath());
    if ( url.filename()!="test" ) TEST_FAILED(url.filename());
    TEST_PASSED;
  }
  {
    PURL::Url url = PURL::Url::fromPathOrUrl("/test/");
    if ( url.isEmpty() ) TEST_FAILED("isEmpty");
    if ( url.isRelative() ) TEST_FAILED("isRelative");
    if ( !url.isLocal() ) TEST_FAILED("isLocal");
    if ( url.path()!="/test/" ) TEST_FAILED("");
    if ( url.unterminatedPath()!="/test" ) TEST_FAILED("");
    if ( url.filepath()!="/test/" ) TEST_FAILED(url.filepath());
    if ( !url.filename().isEmpty() ) TEST_FAILED(url.filename());
    TEST_PASSED;
  }
  {
    PURL::Url url = PURL::Url::fromPathOrUrl("c:/test");
    if ( url.isEmpty() ) TEST_FAILED("isEmpty");
    if ( url.isRelative() ) TEST_FAILED("isRelative");
    if ( !url.isLocal() ) TEST_FAILED("isLocal");
    PURL::Url url2 = PURL::Url::fromPathOrUrl("c:/");
    if ( url.path()!=url2.path() ) TEST_FAILED(url.path());
    if ( url==url2 ) TEST_FAILED(url.path());
    if ( url.filename()!="test" ) TEST_FAILED(url.filename());
    TEST_PASSED;
  }
  {
    PURL::Url url = PURL::Url::fromPathOrUrl("d:/test/");
    if ( url.isEmpty() ) TEST_FAILED("isEmpty");
    if ( url.isRelative() ) TEST_FAILED("isRelative");
    if ( !url.isLocal() ) TEST_FAILED("isLocal");
    if ( !url.filename().isEmpty() ) TEST_FAILED(url.filename());
    TEST_PASSED;
  }
  {
    PURL::Url url(KURL::fromPathOrURL("http://test.net/test"));
    if ( url.isEmpty() ) TEST_FAILED("isEmpty");
    if ( url.isRelative() ) TEST_FAILED("isRelative");
    if ( url.isLocal() ) TEST_FAILED("isLocal");
    if ( url.filename()!="test" ) TEST_FAILED(url.filename());
    TEST_PASSED;
  }

  return true;
}

//----------------------------------------------------------------------------
TEST_MAIN(MiscCheck)
