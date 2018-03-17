find_package(PCL REQUIRED)

message("PCL_INCLUDE_DIRS: ${PCL_INCLUDE_DIRS}")

set(OpenCV_DIR "/home/davidz/work/3rdlibs/opencv/build")
find_package(OpenCV REQUIRED)
message("OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
set(ADDITIONAL_OPENCV_DIR "/home/davidz/work/3rdlibs/opencv/modules/cudafeatures2d/include" "/home/davidz/work/3rdlibs/opencv/modules/cudafilters/include")

find_package(VTK REQUIRED)
find_package(Eigen REQUIRED)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED )


include_directories("${OD_SOURCE_DIR}" ${EIGEN_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} ${OD_SOURCE_DIR}/3rdparty/SiftGPU/src/SiftGPU ${OD_SOURCE_DIR}/3rdparty/pugixml-1.6/src  ${ADDITIONAL_OPENCV_DIR})
