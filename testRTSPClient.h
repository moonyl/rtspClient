//
// Created by admin on 2020-10-14.
//

#pragma once
#include "UsageEnvironment.hh"
#include "NetAddress.hh"
// The main streaming routine (for each "rtsp://" URL):
void openURL(UsageEnvironment& env, char const* progName, char const* rtspURL, portNumBits tunnelOverHTTPPortNum = 0);