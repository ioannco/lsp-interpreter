#pragma once
#include "Lisp.h"

std::map <std::string, int> getFuncNames ();
std::map <int, (icl::list <LispObj>) (*Func) (icl::list <LispObj> x)> get
