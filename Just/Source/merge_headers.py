import os

# method to iterate file names
def iterate_files(directory):
    for root, _, files in os.walk(directory):
        for file_name in files:
            file_path = os.path.join(root, file_name)
            yield file_path

# iterate header files and build dictionary of file content
files_content = {}
files_order = ['Strings\\From\\Basics.h']
for directory in ['Strings', 'Files', 'Execute', 'Http', 'SharedMemory', 'DLLs']:
    for file_path in iterate_files(directory):
        if ((file_path == ".\\JustAll.h") or file_path.endswith('\\All.h') or (not file_path.endswith('.h'))):
            continue
        print(file_path)
        if file_path not in files_order:
            files_order.append(file_path)
        files_content[file_path] = open(file_path, 'r').read()
        
# build unified output file
outfile = open("../JustAll.h", 'w')
outfile.write("#pragma once\n\n")
for file_path in files_order:
    content = files_content[file_path].replace("#pragma once", "// #pragma once").replace('#include "', '// #include "')
    outfile.write('\n\n// ::' + file_path + '::\n\n')
    outfile.write(content)
    outfile.write('\n\n')