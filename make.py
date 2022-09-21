import os
import sys
import subprocess


COMMAND = (
    "C:\\msys64\\mingw64\\bin\\g++.exe "
    "-fdiagnostics-color=always "
    "-g "
    "{files} "
    "-o "
    "{output_executable} "
    "-I "
    "{dirname} "
)


def find_all_cpp(root_dir):
    cpp_files = []
    for root, _, files in os.walk(root_dir):
        for file in files:
            if not file.endswith(".cpp"):
                continue
            cpp_files.append(os.path.join(root, file))
    return cpp_files

if __name__ == "__main__":

    dirname = sys.argv[1]
    output_executable = sys.argv[2]

    cpp_files = find_all_cpp(root_dir=dirname)

    cmd = COMMAND.format(files=" ".join(cpp_files), output_executable=output_executable, dirname=dirname)

    print(cmd)

    process = subprocess.Popen(cmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    out, err = process.communicate()

    if err:
        raise Exception(err.decode("utf-8"))
