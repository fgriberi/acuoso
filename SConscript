Import ('env')

name = 'acuoso'
inc = env.Dir('.')
ext_inc = []
src = env.Glob('src/*.cpp') 
deps = ['mili', 'biopp', 'biopp-filer', 'stl-debug']

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)

