// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/build_time.h"

// Imports the generated build date, i.e. BUILD_DATE.
#ifdef __ANDROID__
#include <cutils/properties.h>
#endif

#include "base/logging.h"
#include "base/time/time.h"

namespace base {

Time GetBuildTime() {
    Time integral_build_time;
    // The format of __DATE__ and __TIME__ is specified by the ANSI C Standard,
    // section 6.8.8.
    //
    // __DATE__ is exactly "Mmm DD YYYY".
    // __TIME__ is exactly "hh:mm:ss".
#if defined(__ANDROID__)
    char kDateTime[PROPERTY_VALUE_MAX];
    property_get( "ro.build.date", kDateTime, "Sep 02 2008 08:00:00 PST" );
#elif defined(DONT_EMBED_BUILD_METADATA) && !defined(OFFICIAL_BUILD)
    const char kDateTime[] = "Sep 02 2008 08:00:00 PST";
#else
    const char kDateTime[] = __DATE__ " " __TIME__ " PST";
#endif
    bool result = Time::FromString( kDateTime, &integral_build_time );
    DCHECK( result );
    return integral_build_time;
}

}  // namespace base
