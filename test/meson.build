e = executable('runtests',
    [
        'Test.cpp',
        'TerminalTests.cpp',
        'ObjectPoolTests.cpp',
        'main.cpp'
    ],
    include_directories: inc,
    link_with: mainlib)

test('unittests', e)

