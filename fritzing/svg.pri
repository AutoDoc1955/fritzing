# /*******************************************************************
# Part of the Fritzing project - http://fritzing.org
# Copyright (c) 2007-08 Fachhochschule Potsdam - http://fh-potsdam.de
# Fritzing is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# Fritzing is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with Fritzing. If not, see <http://www.gnu.org/licenses/>.
# ********************************************************************
# $Revision$:
# $Author$:
# $Date$
# ********************************************************************/
HEADERS += src/svg/svgfilesplitter.h \
    src/svg/svgpathparser.h \
    src/svg/svgpathgrammar_p.h \
    src/svg/svgpathlexer.h \
    src/svg/svgpathrunner.h \
    src/svg/svg2gerber.h \
    src/svg/svgflattener.h
SOURCES += src/svg/svgfilesplitter.cpp \
    src/svg/svgpathparser.cpp \
    src/svg/svgpathgrammar.cpp \
    src/svg/svgpathlexer.cpp \
    src/svg/svgpathrunner.cpp \
    src/svg/svg2gerber.cpp \
    src/svg/svgflattener.cpp
