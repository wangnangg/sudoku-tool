#!/usr/bin/python3
import os.path


def list2makestr(objs):
    obj_str = []
    for obj in objs:
        obj_str.append(obj)
        obj_str.append(' ')
    return ''.join(obj_str)


# recursively list all files that match specified extensions
def find_files(target_dir, exts):
    if type(exts) is str:
        exts = [exts]
    files = []
    for dirpath, dirnames, filenames in os.walk(target_dir):
        for f in filenames:
            for e in exts:
                if (f.endswith(e)):
                    files.append(os.path.join(dirpath, f))
                    break

    return files


target_set = set()


def dir_rule(target):
    if target in target_set:
        return ''
    else:
        target_set.add(target)
        return "%s:\n\tmkdir -p $@\n" % target


def compile_rule(compiler, flags, src_file, target):
    if target in target_set:
        return ''
    else:
        target_set.add(target)
        target_path = os.path.dirname(target)
        return "%s: %s | %s \n\t%s %s -c %s -o %s\n" % (
            target, src_file, target_path, compiler, flags, src_file,
            target) + dir_rule(target_path)


def link_rule(linker, flags, objs, target):
    if target in target_set:
        return ''
    else:
        target_set.add(target)
        target_path = os.path.dirname(target)
        objs_str = list2makestr(objs)
        return "%s: %s | %s\n\t%s %s %s -o %s\n" % (
            target, objs_str, target_path, linker, objs_str, flags,
            target) + dir_rule(target_path)


def ar_rule(ar, flags, objs, target):
    if target in target_set:
        return ''
    else:
        target_set.add(target)
        target_path = os.path.dirname(target)
        objs_str = list2makestr(objs)
        return "%s: %s | %s\n\t%s %s %s %s\n" % (
            target, objs_str, target_path, ar, flags, target,
            objs_str) + dir_rule(target_path)


def change_ext(filename, new_ext):
    return os.path.splitext(filename)[0] + new_ext


def transform_src_files(source_files, obj_dir):
    objs = []
    for src in source_files:
        obj = os.path.join(obj_dir, src)
        obj = change_ext(obj, '.o')
        objs.append(obj)
    return objs


cpp_compiler = 'g++'
linker = 'g++'

makefile_head = [
    """
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
"""
]
makefile_major_targets = [
    """
.PHONY: all sdtool utest
all: sdtool utest
sdtool: ${build_dir}/sdtool
utest: ${build_dir}/utest
"""
]
makefile_body = []
makefile_tail = ["""
.PHONY: clean
clean:
	  rm build -rf
-include ${deps}
"""]

src_files = find_files('src', '.cpp')
obj_files = transform_src_files(src_files, "${build_dir}")
for i in range(0, len(src_files)):
    makefile_body.append(
        compile_rule(cpp_compiler, "${flags}", src_files[i], obj_files[i]))

test_src_files = find_files('test', 'cpp')
test_obj_files = transform_src_files(test_src_files, "${build_dir}")
for i in range(0, len(test_src_files)):
    makefile_body.append(
        compile_rule(cpp_compiler, "${gtest_flags} ${flags}",
                     test_src_files[i], test_obj_files[i]))

gtest_src_files = ["${gtest_dir}/src/gtest-all.cc"]
gtest_obj_files = transform_src_files(gtest_src_files, "${build_dir}")
for i in range(0, len(gtest_src_files)):
    makefile_body.append(
        compile_rule(cpp_compiler, "${gtest_flags}", gtest_src_files[i],
                     gtest_obj_files[i]))

makefile_body.append(
    link_rule(linker, "${link_flags}",
              list(filter(lambda f: not f.endswith('main.o'), obj_files)) + test_obj_files + gtest_obj_files,
              '${build_dir}/utest'))

makefile_body.append(
    link_rule(linker, "${link_flags}",
              obj_files,
              '${build_dir}/sdtool'))

deps = list2makestr(
    map(lambda obj: change_ext(obj, '.d'),
        obj_files + test_obj_files + gtest_obj_files))

makefile_body.append('deps:=' + deps + '\n')

f = open('makefile', 'w')
f.write(''.join(
    makefile_head + makefile_major_targets + makefile_body + makefile_tail))
f.close()
print('build with: make config=debug|release|profile|coverage')
