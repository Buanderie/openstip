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
	${OBJECTDIR}/src/SpaceTimeBuffer.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/TemporalFrame.o


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
LDLIBSOPTIONS=/opt/local/lib/libSDL.dylib /opt/local/lib/libopencv_core.dylib /opt/local/lib/libopencv_highgui.dylib /opt/local/lib/libopencv_imgproc.dylib /opt/local/lib/libopencv_video.dylib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibopenstip.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibopenstip.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibopenstip.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibopenstip.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibopenstip.a

${OBJECTDIR}/src/SpaceTimeBuffer.o: src/SpaceTimeBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/local/include -I./inc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SpaceTimeBuffer.o src/SpaceTimeBuffer.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/local/include -I./inc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/TemporalFrame.o: src/TemporalFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/opt/local/include -I./inc -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TemporalFrame.o src/TemporalFrame.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibopenstip.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
