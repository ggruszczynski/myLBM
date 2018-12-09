cmake_minimum_required(VERSION 3.10)
project(myLB_v2)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
#set(CMAKE_BUILD_TYPE Debug)


if (CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE MATCHES "^(Debug|Release|RelWithDebInfo|MinSizeRel)$")
  message(FATAL_ERROR "Invalid value for CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug is on.")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb3")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

if(CMAKE_BUILD_TYPE MATCHES Release)
    message("Release is on.")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif(CMAKE_BUILD_TYPE MATCHES Release)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    message("OpenMP found")
else(OPENMP_FOUND)
    message("ERROR: OpenMP could not be found.")
endif(OPENMP_FOUND)

message("listing CMAKE_C_FLAGS flags: ${CMAKE_C_FLAGS}")
message("listing CMAKE_CXX_FLAGS flags: ${CMAKE_CXX_FLAGS}")

find_package(Boost 1.65 REQUIRED COMPONENTS system filesystem thread regex iostreams )
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(CODE/Cases)
    include_directories(CODE/Constants)
    include_directories(CODE/IO)
    include_directories(CODE/Mesher)
    include_directories(CODE/Nodes)
    include_directories(CODE/Solver)

    set(SOURCE_FILES
            CODE/Cases/Case.h
            CODE/Constants/D2Q5Constants.h
            CODE/Constants/D2Q9Constants.h
            CODE/Constants/Enums.h
            CODE/Constants/Singleton.h
#            CODE/IO/
            CODE/IO/VTKWriter.cpp
            CODE/IO/VTKWriter.h
            CODE/IO/XMLParser.cpp
            CODE/IO/XMLParser.h
            CODE/Mesher/AdvectionValidatorMeshBuilder.cpp
            CODE/Mesher/AdvectionValidatorMeshBuilder.h
            CODE/Mesher/ChannelMeshBuider.h
            CODE/Mesher/ChannelMeshBuilder.cpp
            CODE/Mesher/DiffusionValidatorMeshBuilder.cpp
            CODE/Mesher/DiffusionValidatorMeshBuilder.h
            CODE/Mesher/LidMeshBuilder.h
            CODE/Mesher/MeshBuilder.cpp
            CODE/Mesher/MeshBuilder.h
            CODE/Mesher/MeshDirector.cpp
            CODE/Mesher/MeshDirector.h
            CODE/Mesher/WallForceValidatorMeshBuilder.cpp
            CODE/Mesher/WallForceValidatorMeshBuilder.h
            CODE/Nodes/MovingWall.cpp
            CODE/Nodes/MovingWall.h
            CODE/Nodes/Node.cpp
            CODE/Nodes/Node.h
            CODE/Nodes/PeriodicNode.h
            CODE/Nodes/PressureOutlet.cpp
            CODE/Nodes/PressureOutlet.h
            CODE/Nodes/SymmetryNode.h
            CODE/Nodes/VelocityInlet.cpp
            CODE/Nodes/VelocityInlet.h
            CODE/Nodes/Wall.cpp
            CODE/Nodes/Wall.h
            CODE/Solver/Solver.cpp
            CODE/Solver/Solver.h
            MAIN.cpp CODE/Mesher/LidMeshBuilder.h.cpp)

#    set(SOURCE_FILES
#            CODE/Cases/Case.h
#            CODE/Constants/D2Q5Constants.h
#            CODE/Constants/D2Q9Constants.h
#            CODE/Constants/DdQqConstants.h
#            CODE/Constants/Enums.h
#            CODE/Constants/Singleton.cpp
#            CODE/Constants/Singleton.h
#            CODE/IO/VTKWriter.cpp
#            CODE/IO/VTKWriter.h
#            CODE/IO/XMLParser.cpp
#            CODE/IO/XMLParser.h
#            CODE/Mesher/
#            CODE/Nodes/
#            CODE/Solver/Solver.cpp
#            CODE/Solver/Solver.h
#            MAIN.cpp)

    add_executable(myLB_v2 ${SOURCE_FILES})



    target_link_libraries(myLB_v2 ${Boost_LIBRARIES})
endif()

if (NOT Boost_FOUND)
  BUILD_ERROR ("Boost not found. Please install thread system filesystem regex iostreams boost version 1.54.0 or higher.")
endif()

