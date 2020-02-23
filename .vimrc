"vundle插件
set nocompatible              " be iMproved, required
filetype off                  " required

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'tpope/vim-fugitive'
Plugin 'git://git.wincent.com/command-t.git'
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
Plugin 'vim-airline/vim-airline'
Plugin 'connorholyday/vim-snazzy'

call vundle#end()            " required
filetype plugin indent on    " required
"vundel插件结束


"vim 配置
set nocompatible    "关闭 vi 兼容模式
filetype on
filetype indent on
filetype plugin on
filetype plugin indent on
let mapleader=" "   "将空格键变成leader键
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
"let &t_SR = "\<Esc>]50;CursorShape=2\x7"
let &t_EI = "\<Esc>]50;CursorShape=0\x7"
set laststatus=2
set autochdir
au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

syntax on           "代码高亮
set number          "行号
set cursorline      "在当前行显示一条线
set wrap            "不会超出页面 类似换行功能但没有回车符号
set showcmd         "显示命令
set wildmenu        "可以用Tap键 提示
set hlsearch        "查找单词高亮
set  incsearch      "边输入边高亮
	"打开文档时执行取消高亮
exec "nohlsearch"
set ignorecase      "忽略大小写
set smartcase       "智能搜索

noremap i k
noremap k j
noremap j h

noremap <LEADER><CR> :nohlsearch<CR>
map S :w<CR>       
map s :<nop>      
map Q :q<CR>     
map R :source $MYVIMRC<CR>
imap <C-k> <Esc>



let g:SnazzyTransparent = 1   "背景透明
color snazzy            "设置snazzy背景



