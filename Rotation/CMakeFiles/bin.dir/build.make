# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bdb/master/M1S2/project/starter_main_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bdb/master/M1S2/project/starter_main_2

# Include any dependencies generated for this target.
include CMakeFiles/bin.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bin.dir/flags.make

CMakeFiles/bin.dir/src/rotation.cpp.o: CMakeFiles/bin.dir/flags.make
CMakeFiles/bin.dir/src/rotation.cpp.o: src/rotation.cpp
CMakeFiles/bin.dir/src/rotation.cpp.o: CMakeFiles/bin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bdb/master/M1S2/project/starter_main_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bin.dir/src/rotation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bin.dir/src/rotation.cpp.o -MF CMakeFiles/bin.dir/src/rotation.cpp.o.d -o CMakeFiles/bin.dir/src/rotation.cpp.o -c /home/bdb/master/M1S2/project/starter_main_2/src/rotation.cpp

CMakeFiles/bin.dir/src/rotation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bin.dir/src/rotation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bdb/master/M1S2/project/starter_main_2/src/rotation.cpp > CMakeFiles/bin.dir/src/rotation.cpp.i

CMakeFiles/bin.dir/src/rotation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bin.dir/src/rotation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bdb/master/M1S2/project/starter_main_2/src/rotation.cpp -o CMakeFiles/bin.dir/src/rotation.cpp.s

CMakeFiles/bin.dir/src/warp.cpp.o: CMakeFiles/bin.dir/flags.make
CMakeFiles/bin.dir/src/warp.cpp.o: src/warp.cpp
CMakeFiles/bin.dir/src/warp.cpp.o: CMakeFiles/bin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bdb/master/M1S2/project/starter_main_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bin.dir/src/warp.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bin.dir/src/warp.cpp.o -MF CMakeFiles/bin.dir/src/warp.cpp.o.d -o CMakeFiles/bin.dir/src/warp.cpp.o -c /home/bdb/master/M1S2/project/starter_main_2/src/warp.cpp

CMakeFiles/bin.dir/src/warp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bin.dir/src/warp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bdb/master/M1S2/project/starter_main_2/src/warp.cpp > CMakeFiles/bin.dir/src/warp.cpp.i

CMakeFiles/bin.dir/src/warp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bin.dir/src/warp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bdb/master/M1S2/project/starter_main_2/src/warp.cpp -o CMakeFiles/bin.dir/src/warp.cpp.s

CMakeFiles/bin.dir/src/main.cpp.o: CMakeFiles/bin.dir/flags.make
CMakeFiles/bin.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/bin.dir/src/main.cpp.o: CMakeFiles/bin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bdb/master/M1S2/project/starter_main_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bin.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bin.dir/src/main.cpp.o -MF CMakeFiles/bin.dir/src/main.cpp.o.d -o CMakeFiles/bin.dir/src/main.cpp.o -c /home/bdb/master/M1S2/project/starter_main_2/src/main.cpp

CMakeFiles/bin.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bin.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bdb/master/M1S2/project/starter_main_2/src/main.cpp > CMakeFiles/bin.dir/src/main.cpp.i

CMakeFiles/bin.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bin.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bdb/master/M1S2/project/starter_main_2/src/main.cpp -o CMakeFiles/bin.dir/src/main.cpp.s

# Object files for target bin
bin_OBJECTS = \
"CMakeFiles/bin.dir/src/rotation.cpp.o" \
"CMakeFiles/bin.dir/src/warp.cpp.o" \
"CMakeFiles/bin.dir/src/main.cpp.o"

# External object files for target bin
bin_EXTERNAL_OBJECTS =

bin: CMakeFiles/bin.dir/src/rotation.cpp.o
bin: CMakeFiles/bin.dir/src/warp.cpp.o
bin: CMakeFiles/bin.dir/src/main.cpp.o
bin: CMakeFiles/bin.dir/build.make
bin: /usr/lib/libopencv_gapi.so.4.5.5
bin: /usr/lib/libopencv_stitching.so.4.5.5
bin: /usr/lib/libopencv_alphamat.so.4.5.5
bin: /usr/lib/libopencv_aruco.so.4.5.5
bin: /usr/lib/libopencv_barcode.so.4.5.5
bin: /usr/lib/libopencv_bgsegm.so.4.5.5
bin: /usr/lib/libopencv_bioinspired.so.4.5.5
bin: /usr/lib/libopencv_ccalib.so.4.5.5
bin: /usr/lib/libopencv_cvv.so.4.5.5
bin: /usr/lib/libopencv_dnn_objdetect.so.4.5.5
bin: /usr/lib/libopencv_dnn_superres.so.4.5.5
bin: /usr/lib/libopencv_dpm.so.4.5.5
bin: /usr/lib/libopencv_face.so.4.5.5
bin: /usr/lib/libopencv_freetype.so.4.5.5
bin: /usr/lib/libopencv_fuzzy.so.4.5.5
bin: /usr/lib/libopencv_hdf.so.4.5.5
bin: /usr/lib/libopencv_hfs.so.4.5.5
bin: /usr/lib/libopencv_img_hash.so.4.5.5
bin: /usr/lib/libopencv_intensity_transform.so.4.5.5
bin: /usr/lib/libopencv_line_descriptor.so.4.5.5
bin: /usr/lib/libopencv_mcc.so.4.5.5
bin: /usr/lib/libopencv_quality.so.4.5.5
bin: /usr/lib/libopencv_rapid.so.4.5.5
bin: /usr/lib/libopencv_reg.so.4.5.5
bin: /usr/lib/libopencv_rgbd.so.4.5.5
bin: /usr/lib/libopencv_saliency.so.4.5.5
bin: /usr/lib/libopencv_stereo.so.4.5.5
bin: /usr/lib/libopencv_structured_light.so.4.5.5
bin: /usr/lib/libopencv_superres.so.4.5.5
bin: /usr/lib/libopencv_surface_matching.so.4.5.5
bin: /usr/lib/libopencv_tracking.so.4.5.5
bin: /usr/lib/libopencv_videostab.so.4.5.5
bin: /usr/lib/libopencv_viz.so.4.5.5
bin: /usr/lib/libopencv_wechat_qrcode.so.4.5.5
bin: /usr/lib/libopencv_xfeatures2d.so.4.5.5
bin: /usr/lib/libopencv_xobjdetect.so.4.5.5
bin: /usr/lib/libopencv_xphoto.so.4.5.5
bin: /usr/lib/libopencv_shape.so.4.5.5
bin: /usr/lib/libopencv_highgui.so.4.5.5
bin: /usr/lib/libopencv_datasets.so.4.5.5
bin: /usr/lib/libopencv_plot.so.4.5.5
bin: /usr/lib/libopencv_text.so.4.5.5
bin: /usr/lib/libopencv_ml.so.4.5.5
bin: /usr/lib/libopencv_phase_unwrapping.so.4.5.5
bin: /usr/lib/libopencv_optflow.so.4.5.5
bin: /usr/lib/libopencv_ximgproc.so.4.5.5
bin: /usr/lib/libopencv_video.so.4.5.5
bin: /usr/lib/libopencv_videoio.so.4.5.5
bin: /usr/lib/libopencv_imgcodecs.so.4.5.5
bin: /usr/lib/libopencv_objdetect.so.4.5.5
bin: /usr/lib/libopencv_calib3d.so.4.5.5
bin: /usr/lib/libopencv_dnn.so.4.5.5
bin: /usr/lib/libopencv_features2d.so.4.5.5
bin: /usr/lib/libopencv_flann.so.4.5.5
bin: /usr/lib/libopencv_photo.so.4.5.5
bin: /usr/lib/libopencv_imgproc.so.4.5.5
bin: /usr/lib/libopencv_core.so.4.5.5
bin: CMakeFiles/bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bdb/master/M1S2/project/starter_main_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bin.dir/build: bin
.PHONY : CMakeFiles/bin.dir/build

CMakeFiles/bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bin.dir/clean

CMakeFiles/bin.dir/depend:
	cd /home/bdb/master/M1S2/project/starter_main_2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bdb/master/M1S2/project/starter_main_2 /home/bdb/master/M1S2/project/starter_main_2 /home/bdb/master/M1S2/project/starter_main_2 /home/bdb/master/M1S2/project/starter_main_2 /home/bdb/master/M1S2/project/starter_main_2/CMakeFiles/bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bin.dir/depend
