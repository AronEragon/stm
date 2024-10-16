# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-src"
  "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-build"
  "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-subbuild/libopencm3_repo-populate-prefix"
  "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-subbuild/libopencm3_repo-populate-prefix/tmp"
  "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-subbuild/libopencm3_repo-populate-prefix/src/libopencm3_repo-populate-stamp"
  "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-subbuild/libopencm3_repo-populate-prefix/src"
  "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-subbuild/libopencm3_repo-populate-prefix/src/libopencm3_repo-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-subbuild/libopencm3_repo-populate-prefix/src/libopencm3_repo-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/filin_vg/lab325/stm2/build/_deps/libopencm3_repo-subbuild/libopencm3_repo-populate-prefix/src/libopencm3_repo-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
