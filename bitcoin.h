// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#ifdef _MSC_VER
#pragma warning(disable:4786)
#pragma warning(disable:4804)
#pragma warning(disable:4717)
#endif
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0400
#define WIN32_LEAN_AND_MEAN 1
#define BOUNDSCHECK 1
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>


#pragma hdrstop
using namespace std;
using namespace boost;



