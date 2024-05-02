from os.path import isfile, join, abspath
from os import listdir, system
from sys import argv

def run():
    file_location = "/".join(abspath(__file__).split("/")[:-1]) + "/"
    files = []
    folders = []
    for f in listdir(file_location):
        if isfile(join(file_location, f)):
            files.append(f)
        else:
            folders.append(f)
    if "CMakeLists.txt" not in files or "src" not in folders:
        exit(
            "Project requires a CMakeLists.txt file for build deps and a src folder to build"
        )

    src_folder = []
    for proj_files in listdir(file_location + "src"):
        if proj_files.endswith(".cpp"):
            src_folder.append(proj_files)

    if not src_folder:
        exit("No source files found in src folder")

    print("Select a file to build & run:")
    for i, file in enumerate(src_folder):
        print(f"[{i+1}] {file}")
    choice = src_folder[int(input("~ ")) - 1]

    system("cmake -S . -B build")
    system("cmake --build build")
    system(f"clear && ./build/{choice[:-4]}{'' if len(argv) == 1 else ' ' + ' '.join(argv[1:])}")


if __name__ == "__main__":
    run()
