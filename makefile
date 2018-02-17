
config?=debug
build_dir:=build/${config}
flags:= -Isrc -std=c++1z -Wall -Wfloat-conversion -Wsign-conversion -Werror -MMD
gtest_dir:= googletest/googletest
gtest_flags:=-isystem ${gtest_dir}/include -I${gtest_dir}
link_flags:=-lstdc++ -lm -pthread -lblas
ifeq ($(config), release)
  flags += -O3 -DNDEBUG
  link_flags += -O3 -DNDEBUG
else
  ifeq ($(config), profile)
    flags += -g -O3 -pg -no-pie
    link_flags += -g -O3 -no-pie
  else
    ifeq ($(config), coverage)
      flags += -g -ftest-coverage -fprofile-arcs
      link_flags += -g -fprofile-arcs
    else
      ifeq ($(config), debug)
        flags += -g
        link_flags += -g
      else
$(error Unknown config: $(config))
      endif
    endif
  endif
endif

.PHONY: utest
utest: ${build_dir}/utest
${build_dir}/src/board.o: src/board.cpp | ${build_dir}/src 
	g++ ${flags} -c src/board.cpp -o ${build_dir}/src/board.o
${build_dir}/src:
	mkdir -p $@
${build_dir}/test/test_main.o: test/test_main.cpp | ${build_dir}/test 
	g++ ${gtest_flags} ${flags} -c test/test_main.cpp -o ${build_dir}/test/test_main.o
${build_dir}/test:
	mkdir -p $@
${build_dir}/test/test_solve.o: test/test_solve.cpp | ${build_dir}/test 
	g++ ${gtest_flags} ${flags} -c test/test_solve.cpp -o ${build_dir}/test/test_solve.o
${build_dir}/${gtest_dir}/src/gtest-all.o: ${gtest_dir}/src/gtest-all.cc | ${build_dir}/${gtest_dir}/src 
	g++ ${gtest_flags} -c ${gtest_dir}/src/gtest-all.cc -o ${build_dir}/${gtest_dir}/src/gtest-all.o
${build_dir}/${gtest_dir}/src:
	mkdir -p $@
${build_dir}/utest: ${build_dir}/src/board.o ${build_dir}/test/test_main.o ${build_dir}/test/test_solve.o ${build_dir}/${gtest_dir}/src/gtest-all.o  | ${build_dir}
	g++ ${build_dir}/src/board.o ${build_dir}/test/test_main.o ${build_dir}/test/test_solve.o ${build_dir}/${gtest_dir}/src/gtest-all.o  ${link_flags} -o ${build_dir}/utest
${build_dir}:
	mkdir -p $@
deps:=${build_dir}/src/board.d ${build_dir}/test/test_main.d ${build_dir}/test/test_solve.d ${build_dir}/${gtest_dir}/src/gtest-all.d 

.PHONY: clean
clean:
	  rm build -rf
-include ${deps}
