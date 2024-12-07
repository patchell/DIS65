#pragma once

constexpr auto MAX_SYMBOL_NAME_LEN = 32;
constexpr auto MAX_NAME_LEN = 32;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys\stat.h>
#include <sys\types.h>

#include "Bin.h"
#include "Bucket.h"
#include "Symbol.h"
#include "SymTab.h"

#include "DIS65.h"
