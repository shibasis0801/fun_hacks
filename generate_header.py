#!/usr/bin/env python3
# Assumes no cyclic dependencies between headers.
# Since that will change with time, this will grow.
# Architecture of this library is not even close to fixed.


"""
Assumptions

1 No Cyclic Dependencies
2 //@// is used as delimiters in some places.
3 namespace mod does not appear outside its definitions (i.e. Not in macros or like using namespace mod)
4 By no means is this platform independent.
"""

import os
from os.path import expanduser


home = expanduser("~")
generated_header = 'generated.hpp'
header_directory = 'bin/cpp_mods'
main_header_name = 'main_header.hpp'

def read_file(path):
    return open(path).read()

def header_path(header):
    return '/'.join([
        home,
        header_directory,
        header
    ])


def select_string(string, start, end):
    #Includes start and end delimiters
    start_idx = string.find(start)
    end_idx = string.rfind(end)

    if start_idx == -1 or end_idx == -1:
        return ""
    
    end_idx += 1

    return string[ string.find(start) : string.rfind(end) + 1 ]

def extract_string(string, boundary):
    start_idx = string.find(boundary)
    end_idx = string.rfind(boundary)

    if start_idx == -1 or end_idx == -1:
        return ""
    
    start_idx += len(boundary)

    return string[
        string.find(boundary) + len(boundary) :
        string.rfind(boundary)
    ]

def get_headers():

    main_header_path = header_path(main_header_name)
    main_header = read_file(main_header_path).split('\n')

    return [
        read_file(
            header_path(
                extract_string(include, '"')
        ))
        for include in main_header
    ]


def get_definitions():

    headers = get_headers()

    content = []

    for header in headers:
        functions = select_string(header, "namespace mod", "}")
        other = extract_string(header, '//@//')
        if functions:
            content += [ functions ]
        if other:
            content += [ other ]
    
    return '\n'.join(content)


def generate_header(refresh = True):
    generated_path = header_path(generated_header)
    
    if refresh:
        print(get_definitions(), file = open(generated_path, 'w'))
    
    return generated_path

generate_header()