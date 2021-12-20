/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_SLIDESHOW_SOURCE_ENGINE_TRANSITIONS_CLIPPINGFUNCTOR_HXX
#define INCLUDED_SLIDESHOW_SOURCE_ENGINE_TRANSITIONS_CLIPPINGFUNCTOR_HXX

#include <basegfx/vector/b2dsize.hxx>
#include <basegfx/matrix/b2dhommatrix.hxx>
#include <transitioninfo.hxx>
#include "parametricpolypolygon.hxx"


namespace slideshow::internal
    {
        /** Generates the final clipping polygon.

            This class serves as the functor, which generates the
            final clipping polygon from a given ParametricPolyPolygon
            and a TransitionInfo.

            The ParametricPolyPolygon can be obtained from the
            ParametricPolyPolygonFactory, see there.

            The TransitionInfo further parametrizes the polygon
            generated by the ParametricPolyPolygon, with common
            modifications such as rotation, flipping, or change of
            direction. This allows the ParametricPolyPolygonFactory to
            provide only prototypical shapes, with the ClippingFunctor
            further customizing the output.
         */
        class ClippingFunctor
        {
        public:
            ClippingFunctor(
                const ParametricPolyPolygonSharedPtr&   rPolygon,
                const TransitionInfo&                   rTransitionInfo,
                bool                                    bDirectionForward,
                bool                                    bModeIn );

            /** Generate clip polygon.

                @param nValue
                Value to generate the polygon for. Must be in the
                range [0,1].

                @param rTargetSize
                Size the clip polygon should cover. This is typically
                the size of the object the effect is applied on.
             */
            ::basegfx::B2DPolyPolygon operator()( double                    nValue,
                                                  const ::basegfx::B2DSize& rTargetSize );

        private:
            ParametricPolyPolygonSharedPtr     mpParametricPoly;
            ::basegfx::B2DHomMatrix            maStaticTransformation;
            // AW: Not needed
            // ::basegfx::B2DPolyPolygon          maBackgroundRect;
            bool                               mbForwardParameterSweep;
            bool                               mbSubtractPolygon;
            const bool                         mbScaleIsotrophically;
            bool                               mbFlip;
        };


}

#endif // INCLUDED_SLIDESHOW_SOURCE_ENGINE_TRANSITIONS_CLIPPINGFUNCTOR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */