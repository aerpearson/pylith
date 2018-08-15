// -*- C++ -*-
//
// ======================================================================
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, Rice University
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

#include <portinfo>

#include "Physics.hh" // implementation of class methods

#include "pylith/feassemble/AuxiliaryFactory.hh" // USES AuxiliaryFactory
#include "pylith/feassemble/Observers.hh" // USES Observers
#include "spatialdata/units/Nondimensional.hh" // USES Nondimensional

#include "pylith/utils/journals.hh" // USES PYLITH_COMPONENT_*

#include <cassert> // USES assert()
#include <typeinfo> // USES typeid()
#include <stdexcept> \
    // USES std::runtime_error

// ---------------------------------------------------------------------------------------------------------------------
// Constructor
pylith::problems::Physics::Physics(void) :
    _normalizer(new spatialdata::units::Nondimensional)
{}


// ---------------------------------------------------------------------------------------------------------------------
// Destructor
pylith::problems::Physics::~Physics(void) {
    deallocate();
} // destructor


// ---------------------------------------------------------------------------------------------------------------------
// Deallocate PETSc and local data structures.
void
pylith::problems::Physics::deallocate(void) {
    PYLITH_METHOD_BEGIN;

    delete _normalizer;_normalizer = NULL;

    PYLITH_METHOD_END;
} // deallocate


// ---------------------------------------------------------------------------------------------------------------------
// Set database for auxiliary field.
void
pylith::problems::Physics::setAuxiliaryFieldDB(spatialdata::spatialdb::SpatialDB* value) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("setAuxiliaryFieldDB(value="<<value<<")");

    pylith::feassemble::AuxiliaryFactory* factory = _getAuxiliaryFactory();assert(factory);
    factory->setQueryDB(value);

    PYLITH_METHOD_END;
} // setAuxiliaryFieldDB


// ---------------------------------------------------------------------------------------------------------------------
// Set discretization information for auxiliary subfield.
void
pylith::problems::Physics::setAuxiliarySubfieldDiscretization(const char* subfieldName,
                                                              const int basisOrder,
                                                              const int quadOrder,
                                                              const bool isBasisContinuous,
                                                              const pylith::topology::FieldBase::SpaceEnum feSpace) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("setAuxiliarySubfieldDiscretization(subfieldName="<<subfieldName<<", basisOrder="<<basisOrder<<", quadOrder="<<quadOrder<<", isBasisContinuous="<<isBasisContinuous<<")");

    pylith::feassemble::AuxiliaryFactory* factory = _getAuxiliaryFactory();assert(factory);
    factory->setSubfieldDiscretization(subfieldName, basisOrder, quadOrder, isBasisContinuous, feSpace);

    PYLITH_METHOD_END;
} // setAuxSubfieldDiscretization


// ----------------------------------------------------------------------
// Register observer to receive notifications.
void
pylith::problems::Physics::registerObserver(pylith::feassemble::Observer* observer) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("registerObserver(observer="<<typeid(observer).name()<<")");

    assert(_observers);
    _observers->registerObserver(observer);

    PYLITH_METHOD_END;
} // registerObserver


// ----------------------------------------------------------------------
// Remove observer from receiving notifications.
void
pylith::problems::Physics::removeObserver(pylith::feassemble::Observer* observer) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("removeObserver(observer="<<typeid(observer).name()<<")");

    assert(_observers);
    _observers->removeObserver(observer);

    PYLITH_METHOD_END;
} // removeObserver


// ---------------------------------------------------------------------------------------------------------------------
// Get observers receiving notifications of physics updates.
pylith::feassemble::Observers*
pylith::problems::Physics::getObservers(void) {
    return _observers;
} // getObservers


// ---------------------------------------------------------------------------------------------------------------------
// Set manager of scales used to nondimensionalize problem.
void
pylith::problems::Physics::setNormalizer(const spatialdata::units::Nondimensional& dim) {
    PYLITH_COMPONENT_DEBUG("setNormalizer(dim="<<typeid(dim).name()<<")");

    if (!_normalizer) {
        _normalizer = new spatialdata::units::Nondimensional(dim);
    } else {
        *_normalizer = dim;
    } // if/else
} // setNormalizer


// ---------------------------------------------------------------------------------------------------------------------
// Get constants used in kernels (point-wise functions).
const pylith::real_array&
pylith::problems::Physics::getKernelConstants(const PylithReal dt) {
    _updateKernelConstants(dt);

    return _kernelConstants;
} // getKernelConstants


// ---------------------------------------------------------------------------------------------------------------------
// Update kernel constants.
void
pylith::problems::Physics::_updateKernelConstants(const PylithReal dt) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_updateKernelConstants(dt="<<dt<<")");

    // Default is to do nothing.

    PYLITH_METHOD_END;
} // _updateKernelConstants


// End of file
