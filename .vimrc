set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()


Plugin 'VundleVim/Vundle.vim'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'connorholyday/vim-snazzy'

call vundle#end()
filetype plugin indent on

"插件配置

"airline
let g:airline#extensions#tabline#enabled = 1
"airline theme
let g:airline_theme='jellybeans'

"color snazzy
"let g:SnazzyTransparent = 1
"colorscheme snazzy



"零碎配置
let mapleader=" "
set nu
syntax on
set norelativenumber
set cursorline
set wrap
set showcmd
set wildmenu
set noshowmode
set hlsearch
exec "nohlsearch"
set incsearch
set ignorecase
set smartcase

filetype on
filetype indent on
filetype plugin on
filetype plugin indent on
set mouse=a
set encoding=utf-8
let &t_ut=''
set expandtab
set tabstop=4
set shiftwidth=4
set softtabstop=4
set list
set listchars=tab:▸\ ,trail:▫
set scrolloff=5
set tw=0
set indentexpr=
set backspace=indent,eol,start
set foldmethod=indent
set foldlevel=99
let &t_SI = "\<Esc>]50;CursorShape=1\x7"
let &t_SR = "\<Esc>]50;CursorShape=2\x7"
let &t_EI = "\<Esc>]50;CursorShape=0\x7"
set laststatus=2
set autochdir
au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

noremap <LEADER><CR> :nohlsearch<CR>
" 调整窗口移动
map <C-l> <C-w>l
map <C-j> <C-w>k
map <C-h> <C-w>h
map <C-k> <C-w>j



vnoremap < <gv
vnoremap > >gv

map sl :set splitright<CR>:vsplit<CR>
map sh :set nosplitright<CR>:vsplit<CR>
map sj :set nosplitbelow<CR>:split<CR>
map sk :set splitbelow<CR>:split<CR>

noremap j k
noremap k j

map wj :res +5<CR>
map wk :res -5<CR>
map wh :vertical resize-5<CR>
map wl :vertical resize+5<CR>

map fu :tabe<CR>
map fh :-tabnext<CR>
map fl :+tabnext<CR>

map ; :
map <C-s> :w<CR>
map Q :wq<CR>

