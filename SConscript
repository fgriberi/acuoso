Import ('env')

name = 'acuoso'
inc = env.Dir('.')
ext_inc = []
src = env.Glob('src/*.cpp') 
deps = ['etilico', 'mili', 'biopp', 'biopp-filer']

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)