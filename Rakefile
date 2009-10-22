require 'rake/clean'

APPLICATION = 'c-cgi'

task :default => [APPLICATION]

SRC = FileList['src/*.c']
OBJ = SRC.ext('o')

rule '.o' => '.c' do |t|
  sh "gcc -g -c -o #{t.name} #{t.source}"
end

file APPLICATION => OBJ do
  sh "gcc -o #{APPLICATION} #{OBJ}"
end

CLEAN.include(OBJ)
CLOBBER.include(APPLICATION)
