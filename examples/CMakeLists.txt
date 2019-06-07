project(ECSX)

file(GLOB examples "${CMAKE_SOURCE_DIR}/examples/*.cpp")

foreach(file ${examples})
	get_filename_component(base ${file} NAME_WE)
	add_executable(${base} ${file})
	add_dependencies(${base} ecsx)
	target_include_directories(${base} PUBLIC "${CMAKE_SOURCE_DIR}/include/")
	target_link_libraries(${base} ecsx)
endforeach()