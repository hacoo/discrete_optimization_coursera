project('anyint', 'cpp',
	default_options : ['cpp_std=c++14'])

gtest = dependency('gtest', main : false)

src = ['anyint.cpp']

lib = shared_library('anyint_lib', 'anyint.cpp')

e = executable('anyint', 'main.cpp', dependencies : gtest, link_with : lib)

test('google test', e, args : ['test'])
