Import ('env')

env.Append(CXXFLAGS=['--std=c++0x'])

name = 'acuoso'
inc = env.Dir('.')
ext_inc = []
src = env.Glob('src/*.cpp') 
deps = ['etilico', 'mili', 'biopp', 'biopp-filer']

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)