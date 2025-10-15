/*
* This header file serves as a central inclusion point for a comprehensive numerical methods library.
* It aggregates various modules that provide functionalities for solving ordinary differential equations (ODEs),
* performing numerical integration, root finding, solving linear systems, and computing eigenvalues.
*/
#pragma once

// Core numerical methods headers
#include "ODESolver.h"
#include "Integration.h"
#include "RootFinding.h"
#include "LinearSystems.h"
#include "EigenvalueComputations.h"

// Test headers
#include "ODESolverTests.h"
#include "RootFindingTests.h"
#include "LinearSystemsTests.h"
#include "IntegrationTests.h"
#include "EigenvalueTests.h"