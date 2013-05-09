Import ('env')

name = 'acuoso'
inc = env.Dir('.')
ext_inc = env.Dir('acuoso')
src = env.Glob('src/*.cpp') 
deps = ['mili', 'biopp', 'fideo', 'biopp-filer', 'stl-debug']

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)

