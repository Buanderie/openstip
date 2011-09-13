#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/SpaceTimeViewer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../libopenstip/dist/Debug/GNU-MacOSX/liblibopenstip.a /opt/local/lib/libSDL.dylib /opt/local/lib/libGL.dylib /opt/local/lib/libGLU.dylib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer: ../libopenstip/dist/Debug/GNU-MacOSX/liblibopenstip.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer: /opt/local/lib/libSDL.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer: /opt/local/lib/libGL.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer: /opt/local/lib/libGLU.dylib

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../libopenstip/inc -I/opt/local/include -Iinc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/SpaceTimeViewer.o: src/SpaceTimeViewer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../libopenstip/inc -I/opt/local/include -Iinc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SpaceTimeViewer.o src/SpaceTimeViewer.cpp

# Subprojects
.build-subprojects:
	cd ../libopenstip && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stviewer

# Subprojects
.clean-subprojects:
	cd ../libopenstip && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc