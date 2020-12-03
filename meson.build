project('rp-scrabble', 'cpp')

include_dir = include_directories('include')
logpath = meson.project_source_root() + '/logs/'

# Hacky way to get environment variables
pymodule = import('python3')
python3 = pymodule.find_python()
res = run_command(python3, '-c', 'import os; print(os.environ["HOME"], end=\'\')')
if res.returncode() == 0
  homedir = res.stdout()
endif

if get_option('buildtype') == 'debug'
  add_project_arguments('-DDEBUG', '-DLOG_PATH="'+logpath+'"', language : 'cpp')
else
  add_project_arguments('-DLOG_PATH="'+homedir+'/.local/share/rp-scrabble/logs/"', language : 'cpp')
endif

src = [
  'src/bag.cc',
  'src/board.cc',
  'src/game.cc',
  'src/main.cc',
  'src/play.cc',
  'src/player.cc',
  'src/rack.cc',
  'src/square.cc',
  'src/tile.cc',
  'src/utils.cc'
]

executable('rp-scrabble', src, include_directories : include_dir)
