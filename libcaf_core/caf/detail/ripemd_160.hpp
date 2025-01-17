// This file is part of CAF, the C++ Actor Framework. See the file LICENSE in
// the main distribution directory for license terms and copyright or visit
// https://github.com/actor-framework/actor-framework/blob/master/LICENSE.

// Based on http://homes.esat.kuleuven.be/~cosicart/ps/AB-9601/rmd160.h;
// original header:
//
//    AUTHOR:   Antoon Bosselaers, ESAT-COSIC
//    DATE:     1 March 1996
//    VERSION:  1.0
//
//    Copyright (c) Katholieke Universiteit Leuven
//    1996, All Rights Reserved
//
//  Conditions for use of the RIPEMD-160 Software
//
//  The RIPEMD-160 software is freely available for use under the terms and
//  conditions described hereunder, which shall be deemed to be accepted by
//  any user of the software and applicable on any use of the software:
//
//  1. K.U.Leuven Department of Electrical Engineering-ESAT/COSIC shall for
//     all purposes be considered the owner of the RIPEMD-160 software and of
//     all copyright, trade secret, patent or other intellectual property
//     rights therein.
//  2. The RIPEMD-160 software is provided on an "as is" basis without
//     warranty of any sort, express or implied. K.U.Leuven makes no
//     representation that the use of the software will not infringe any
//     patent or proprietary right of third parties. User will indemnify
//     K.U.Leuven and hold K.U.Leuven harmless from any claims or liabilities
//     which may arise as a result of its use of the software. In no
//     circumstances K.U.Leuven R&D will be held liable for any deficiency,
//     fault or other mishappening with regard to the use or performance of
//     the software.
//  3. User agrees to give due credit to K.U.Leuven in scientific publications
//     or communications in relation with the use of the RIPEMD-160 software
//     as follows: RIPEMD-160 software written by Antoon Bosselaers,
//     available at http://www.esat.kuleuven.be/~cosicart/ps/AB-9601/.

#pragma once

#include <array>
#include <cstdint>
#include <string>

#include "caf/detail/core_export.hpp"

namespace caf::detail {

/// Creates a hash from `data` using the RIPEMD-160 algorithm.
CAF_CORE_EXPORT void ripemd_160(std::array<uint8_t, 20>& storage,
                                const std::string& data);

} // namespace caf::detail
