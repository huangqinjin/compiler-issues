file(READ object-files.txt OBJECT_FILES)

foreach(f ${OBJECT_FILES})
    file(SIZE ${f} s)
    get_filename_component(f ${f} NAME)
    message(STATUS "${f}: ${s}")
endforeach()
